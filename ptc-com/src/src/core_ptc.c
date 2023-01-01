/**
 * @file    core_ptc.c
 * @brief   Core Protocol
 * @date    01 Jan 2023
 * 
 * @author  Phat Nguyen <phat.nt@hotmail.com>
*/

#include "../inc/core_ptc.h"
#include "../inc/core_ptc_crc.h"

const static uint8_t ptc_headers[] = CORE_PTC_HEADERS;
const static uint8_t ptc_trailers[] = CORE_PTC_TRAILERS;

static void core_send(core_ptc_t* ctx, const uint8_t* data, size_t len);
static void core_recv(core_ptc_t* ctx, const uint8_t* data, size_t len);

/**
 * @brief       Initialize core protocol
 * @param[in]   ctx: Point to @ref core_ptc_t
 * @return      CORE_PTC_OK on success, otherwise @ref core_ptc_t
*/
core_ptc_err_t core_ptc_init(core_ptc_t* ctx)
{
    if(ctx == NULL || ctx->get_tick_ms == NULL)
    {
        return CORE_PTC_FAIL;
    }

    /* Set function handle */
    ctx->recv = core_recv;
    ctx->send = core_send;

    /* init header */
    ctx->send_buf.datas[0] = ptc_headers[0];
    ctx->send_buf.datas[1] = ptc_headers[1];
    return CORE_PTC_OK;
}

/**
 * @brief       Core send data
 * @param[in]   ctx: Point to @ref ptc_t
 * @param[in]   data: Point to send data array
 * @param       len: Data length, number of byte
*/
static void core_send(core_ptc_t* ctx, const uint8_t* data, size_t len)
{
    /* init buffer info */
    ctx->send_buf.data_len = CORE_PTC_HEADER_SIZE;

    /* Set data length */
    ctx->send_buf.datas[ctx->send_buf.data_len++] = (uint8_t)(len >> 8);
    ctx->send_buf.datas[ctx->send_buf.data_len++] = (uint8_t)(len & 0xff);

    /* Copy data */
    for(size_t i = 0; i < len; i++)
    {
        ctx->send_buf.datas[ctx->send_buf.data_len] = data[i];
    }

    /* Set trailer data */
    ctx->send_buf.datas[ctx->send_buf.data_len++] = ptc_trailers[0];
    ctx->send_buf.datas[ctx->send_buf.data_len++] = ptc_trailers[1];

    /* Set crc */
    uint16_t crc = core_ptc_crc_calc(ctx->send_buf.datas, ctx->send_buf.data_len);
    ctx->send_buf.datas[ctx->send_buf.data_len++] = (uint8_t)(crc >> 8);
    ctx->send_buf.datas[ctx->send_buf.data_len++] = (uint8_t)(crc & 0xff);

    if(ctx->send_event)
    {
        ctx->send_event(ctx->send_buf.datas, ctx->send_buf.data_len);
    }
}

static void core_recv_process(core_ptc_t* ptc, uint8_t data)
{
    core_ptc_recv_buf_t* ctx = &ptc->recv_buf;

#if CORE_PTC_RECV_TIMEOUT_ENABLE
        if(ctx->step != CORE_PTC_STEP_HEADER_0)
        {
            uint32_t ms = (uint32_t)(ptc->get_tick_ms() - ptc->current_tick);
            if(ms >= CORE_PTC_RECV_TIMEOUT_MS)
            {
                ctx->step = CORE_PTC_STEP_HEADER_0;
            }
        }
#endif

    switch(ctx->step)
    {
    case CORE_PTC_STEP_HEADER_0:
        if(data == ptc_headers[0])
        {
            ctx->data_index   = 0;
            ctx->step         = CORE_PTC_STEP_HEADER_1;
            ptc->current_tick = ptc->get_tick_ms();
            ctx->datas[ctx->data_index++] = data;
        }
        break;
    case CORE_PTC_STEP_HEADER_1:
        if (data == ptc_headers[1])
        {
            ctx->datas[ctx->data_index++] = data;
            ctx->step = CORE_PTC_STEP_LENGTH_0;
        }
        else 
        {
            ctx->step = CORE_PTC_STEP_HEADER_0;
        }
        break;
    case CORE_PTC_STEP_LENGTH_0:
        ctx->data_len = data;
        ctx->step = CORE_PTC_STEP_LENGTH_1;
        ctx->datas[ctx->data_index++] = data;
        break;
    case CORE_PTC_STEP_LENGTH_1:
        ctx->data_len = (ctx->data_len << 8) | data;
        if(ctx->data_len >= CORE_PTC_DATA_SIZE)
        {
            ctx->step = CORE_PTC_STEP_HEADER_0;
        }
        else 
        {
            ctx->datas[ctx->data_index++] = data;
            ctx->step = CORE_PTC_STEP_DATA;
        }
        break;
    case CORE_PTC_STEP_DATA:
        ctx->datas[ctx->data_index++] = data;
        if(ctx->data_index >= (ctx->data_len + CORE_PTC_HEADER_SIZE + CORE_PTC_LENGTH_SIZE))
        {
            ctx->step = CORE_PTC_STEP_TRAILER_0;
        }
        break;
    case CORE_PTC_STEP_TRAILER_0:
        if(data == ptc_trailers[0])
        {
            ctx->datas[ctx->data_index++] = data;
            ctx->step = CORE_PTC_STEP_TRAILER_1;
        }
        else 
        {
            ctx->step = CORE_PTC_STEP_HEADER_0;
        }
        break;
    case CORE_PTC_STEP_TRAILER_1:
        if(data == ptc_trailers[1])
        {
            ctx->datas[ctx->data_index++] = data;
            ctx->step = CORE_PTC_STEP_CRC_0;
        }
        else 
        {
            ctx->step = CORE_PTC_STEP_HEADER_0;
        }
        break;
    case CORE_PTC_STEP_CRC_0:
        ctx->crc = data;
        ctx->step = CORE_PTC_STEP_CRC_1;
        break;
    case CORE_PTC_STEP_CRC_1:
        ctx->crc = (ctx->crc << 8) | data;
        ctx->step = CORE_PTC_STEP_HEADER_0;
        if(ctx->crc  == core_ptc_crc_calc(ctx->datas, ctx->data_index))
        {
            // TODO callback data received
            if(ptc->recv_event)
            {
                ptc->recv_event(&ctx->datas[CORE_PTC_HEADER_SIZE + CORE_PTC_LENGTH_SIZE], ctx->data_len);
            }
        }
        break;
    default:
        break;
    }
}

static void core_recv(core_ptc_t* ctx, const uint8_t* data, size_t len)
{
    for (size_t i = 0; i < len; i++)
    {
        core_recv_process(ctx, data[i]);
    }
}