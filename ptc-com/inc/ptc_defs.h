/**
 * @file    ptc_defs.h
 * @brief   Define protocol types
 * @date    01 Jan 2023
 * 
 * @author  Phat Nguyen <phat.nt@hotmail.com>
*/

#ifndef _PTC_DEFS_H_
#define _PTC_DEFS_H_

#include <stdint.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief       Protocol init
*/
typedef struct
{
    /**
     * @brief       Data send event callback
     * @param[in]   data: Point to data array
     * @param[in]   len: Data size, number of byte
    */
    void (*send_event)(const uint8_t *data, size_t len);

    /**
     * @brief       Received data event callback
     * @param[in]   data: Point to data, byte array
     * @param       len: Data length, number of byte
    */
    void (*recv_event)(const uint8_t* data, size_t len); /*!< Received event callback */

    /**
     * @brief       Get tick as ms
     * @return      miliseconds timing
    */
    void (*get_tick_ms)(void);
} ptc_init_t;

/**
 * @brief       Protocol state
 */
typedef enum
{
    PTC_OK = 0,      /*!< No error */
    PTC_ARG_INVALID, /*!< Error argument invalid */
    PTC_NOT_INIT,    /*!< Error protocol is not initialize */
    PTC_INIT,        /*!< Error protocol init */
    PTC_ERR,         /*!< Protocol error */
} ptc_state_t;

#ifdef __cplusplus
}
#endif

#endif /* _PTC_DEFS_H_ */
