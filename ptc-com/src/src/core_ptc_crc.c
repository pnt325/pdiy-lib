/**
 * @file    core_ptc_crc.c
 * @brief   Core Protocol checksum
 * @date    01 Jan 2023
 * 
 * @author  Phat Nguyen <phat.nt@hotmail.com>
*/

#include <stdio.h>
#include "../inc/core_ptc_crc.h"

#define CORE_PTC_CRC_INIT   (0xFFFF)

uint16_t core_ptc_crc_calc(const uint8_t* data, size_t len)
{
    uint16_t crc = 0xFFFF;
    if(data == NULL)
    {
        return crc;
    }

    // TODO Implement crc handle
    return crc;
}

