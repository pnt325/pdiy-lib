/**
 * @file    ptc.c
 * @brief   Protocol handle
 * @date    01 Jan 2023
 * 
 * @author Phat Nguyen <phat.nt@hotmail.com>
*/

#include <stdio.h>
#include "ptc.h"
#include "inc/core_ptc.h"

/* Core protocol variable */
static core_ptc_t _core_ptc_ctx;

/**
 * @brief       Protocol initialize
 * @param[out]  ctx: @ref ptc_t
 * @param[in]   init: point to initialize data
 * @return      NULL on failure, otherwise is success
*/
ptc_t ptc_init(const ptc_init_t* init)
{
    if(init == NULL || init->get_tick_ms == NULL)
    {
        return NULL;
    }

    _core_ptc_ctx.send_event = init->send_event;
    _core_ptc_ctx.recv_event = init->recv_event;
    _core_ptc_ctx.get_tick_ms = init->get_tick_ms;

    core_ptc_err_t err = core_ptc_init(&_core_ptc_ctx);
    if(err != CORE_PTC_OK)
    {
        return NULL;
    }

    return (ptc_t)&_core_ptc_ctx;
}

/**
 * @brief       Protocol receive handle
 * @param[in]   ctx: Point to @ref ptc_t
 * @param[in]   data: Point to data array
 * @param       len: Data len, number of byte
 * @return      PTC_OK on success, otherwise @ref ptc_state_t
*/
ptc_state_t ptc_handle(const ptc_t ctx, const uint8_t* data, size_t len)
{
    if(ctx == NULL || data == NULL || len = 0)
    {
        return PTC_ARG_INVALID;
    }

    core_ptc_t *ptc = (core_ptc_t *)ctx;
    ptc->recv(ptc, data, len);

    return PTC_OK;
}

/**
 * @brief       Protocol send
 * @param[in]   ctx: Point to @ref ptc_t
 * @param[in]   data: Point to data array
 * @param       len: Data len, number of byte
 * @return      PTC_OK on success, otherwise @ref ptc_state_t
*/
ptc_state_t ptc_send(const ptc_t ctx, const uint8_t* data, size_t len)
{
    if(ctx == NULL || data == NULL || len == 0)
    {
        return PTC_ARG_INVALID;
    }

    core_ptc_t* ptc = (core_ptc_t*)ctx;
    ptc->send(ptc, data, len);

    return PTC_OK;
}
