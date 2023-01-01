/**
 * @file    ptc.c
 * @brief   Protocol handle
 * @date    01 Jan 2023
 * 
 * @author Phat Nguyen <phat.nt@hotmail.com>
*/

#include "ptc.h"
#include <stdint.h>
#include <stdio.h>

uint32_t systick_ms(void);
void ptc_received(const uint8_t* data, size_t len);
void ptc_send_cb(const uint8_t* data, size_t len);

int ptc_example(void)
{
    ptc_init_t init = {
        .get_tick_ms = systick_ms,
        .recv_event = ptc_received,
        .send_event = ptc_send_cb
    };
    ptc_t ptc = ptc_init(&init);
    if(ptc == NULL)
    {
        /* init error */
        return;
    }

    /* Send data */
    uint8_t buf[] = {0x01, 0x02, 0x03, 0x04};
    size_t send_len = 4;
    ptc_state_t state =  ptc_send(ptc, buf, send_len);
    if(state != PTC_OK)
    {
        /* Send error */
        return;
    }

    while(1)
    {
        uint8_t data = uart_rx();

        /* Handle recieve data */
        state = ptc_handle(ptc, &data, 1);
        if(state != PTC_OK)
        {
            /* Receive error */
            return;
        }
    }
}
