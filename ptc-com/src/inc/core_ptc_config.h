/**
 * @file    core_ptc_config.h
 * @brief   Core Protocol configure
 * @date    01 Jan 2023
 * 
 * @author  Phat Nguyen <phat.nt@hotmail.com>
*/

#ifndef _CORE_PTC_CONFIG_H_
#define _CORE_PTC_CONFIG_H_

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

#define CORE_PTC_RECV_TIMEOUT_ENABLE         (1)    /*!< Verify receive packet timeout */
                                                    /*!< 0: disable */
                                                    /*!< 1: enable */
#ifdef CORE_PTC_RECV_TIMEOUT_ENABLE
#define CORE_PTC_RECV_TIMEOUT_MS            (500)   /*!< ms */
#endif /* CORE_PTC_RECV_TIMEOUT_ENABLE */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _CORE_PTC_CONFIG_H_ */
