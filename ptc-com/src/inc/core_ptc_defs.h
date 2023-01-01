/**
 * @file    core_ptc_defs.h
 * @brief   Core Protocol define
 * @date    01 Jan 2023
 * 
 * @author  Phat Nguyen <phat.nt@hotmail.com>
*/

#ifndef _CORE_PTC_DEFS_H_
#define _CORE_PTC_DEFS_H_

#include <stdint.h>
#include <stdio.h>
#include "core_ptc_config.h"

#ifndef CORE_PTC_RECV_TIMEOUT_ENABLE
#error  "CORE_PTC_RECV_TIMEOUT is not define"
#endif

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

#define CORE_PTC_HEADER_SIZE        (2)
#define CORE_PTC_TRAILER_SIZE       (2)
#define CORE_PTC_LENGTH_SIZE        (2)
#define CORE_PTC_DATA_SIZE          (256)
#define CORE_PTC_CRC_SIZE           (2)
#define CORE_PTC_HEADERS            {0xAA, 0xFF}
#define CORE_PTC_TRAILERS           {0xFF, 0xAA}
#define CORE_PTC_PACKET_SIZE        (CORE_PTC_HEADER_SIZE +  \
                                     CORE_PTC_LENGTH_SIZE +  \
                                     CORE_PTC_DATA_SIZE +    \
                                     CORE_PTC_TRAILER_SIZE + \
                                     CORE_PTC_CRC_SIZE)

/**
 * @brief    Protocol receive step enum
*/
enum 
{
    CORE_PTC_STEP_HEADER_0,
    CORE_PTC_STEP_HEADER_1,
    CORE_PTC_STEP_LENGTH_0,
    CORE_PTC_STEP_LENGTH_1,
    CORE_PTC_STEP_DATA,
    CORE_PTC_STEP_TRAILER_0,
    CORE_PTC_STEP_TRAILER_1,
    CORE_PTC_STEP_CRC_0,
    CORE_PTC_STEP_CRC_1,
};

typedef struct 
{
    size_t data_len;                        /*!< Data length, number of byte */
    uint8_t datas[CORE_PTC_PACKET_SIZE];    /*!< Data buffer, byte array*/
} core_ptc_send_buf_t;

typedef struct
{
    uint8_t step;                           /*!< Receive step process */
    uint16_t crc;                           /*!< Receive crc value */
    size_t data_len;                        /*!< Data length, number of byte */
    size_t data_index;                      /*!< Data received index */           
    uint8_t datas[CORE_PTC_PACKET_SIZE];    /*!< Data buffer, byte array */
} core_ptc_recv_buf_t;

typedef struct core_ptc
{
    void (*send_event)(const uint8_t* data, size_t len);
    void (*recv_event)(const uint8_t* data, size_t len);
#if (CORE_PTC_RECV_TIMEOUT_ENABLE)
    uint32_t (*get_tick_ms)(void);
    uint32_t current_tick;
#endif
    void (*recv)(struct core_ptc* ctx, const uint8_t* data, size_t len);
    void (*send)(struct core_ptc* ctx, const uint8_t* data, size_t len);
    core_ptc_send_buf_t send_buf;
    core_ptc_recv_buf_t recv_buf;
} core_ptc_t;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _CORE_PTC_DEFS_H_ */