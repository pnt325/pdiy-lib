/**
 * @file    core_ptc_crc.h
 * @brief   Core Protocol checksum
 * @date    01 Jan 2023
 * 
 * @author  Phat Nguyen <phat.nt@hotmail.com>
*/

#ifndef _CORE_PTC_CRC_H_
#define _CORE_PTC_CRC_H_

#include <stdint.h>
#include <stdio.h>
#include "core_ptc_defs.h"

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

uint16_t core_ptc_crc_calc(const uint8_t* ctx, size_t len);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _CORE_PTC_CRC_H_ */