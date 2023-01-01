/**
 * @file    core_ptc.h
 * @brief   Core Protocol
 * @date    01 Jan 2023
 * 
 * @author  Phat Nguyen <phat.nt@hotmail.com>
*/

#ifndef _CORE_PTC_H_
#define _CORE_PTC_H_

#include <stdint.h>
#include <stdio.h>
#include "../inc/core_ptc_defs.h"

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

typedef enum
{
    CORE_PTC_OK = 0,
    CORE_PTC_FAIL = -1,
} core_ptc_err_t;

core_ptc_err_t core_ptc_init(core_ptc_t* ctx);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _CORE_PTC_H_ */
