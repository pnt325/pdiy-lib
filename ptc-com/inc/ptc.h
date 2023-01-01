/**
 * @file    ptc_uart.h
 * @brief   Protocol handle
 * @date    01 Jan 2023
 * 
 * @author  Phat Nguyen <phat.nt@hotmail.com>
*/

#ifndef _PTC_H_
#define _PTC_H_

#include <stdint.h>
#include "ptc_defs.h"

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

typedef void* ptc_t;

ptc_t ptc_init(const ptc_init_t* init);
ptc_state_t ptc_handle(const ptc_t ctx, const uint8_t* data, size_t len);
ptc_state_t ptc_send(const ptc_t ctx, const uint8_t* data, size_t len);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _PTC_UART_H_ */
