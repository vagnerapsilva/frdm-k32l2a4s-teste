/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *        TECNODEV TECNOLOGIA DE DESENVOLVIMENTIO DE SOFTWARE E SERVICOS       *
 *        TEL: (011) 4109-0577                 SITE: www.tecnodev.com.br       *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

 /* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TSI_V4_NORMAL_H
#define __TSI_V4_NORMAL_H
/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*${macro:start}*/
/* Available PAD names on board */
#define PAD_TSI_ELECTRODE_1_NAME "E1"

/* TSI indication leds for electrode 1/2 */
#define LED_INIT()   LED_RED_INIT(LOGIC_LED_OFF)
#define LED_TOGGLE() LED_RED_TOGGLE()

/* LLWU module wakeup source index for TSI module */
#define LLWU_TSI_IDX 4U

/* Get source clock for LPTMR driver */
#define LPTMR_SOURCE_CLOCK CLOCK_GetFreq(kCLOCK_LpoClk)
/* Define LPTMR microseconds counts value */
#define LPTMR_USEC_COUNT (230000U)
/* Define the delta percentage to caculate delta value */
#define TOUCH_DELTA_PERCENT (3.5F / 100.0F)
/*${macro:end}*/

extern void teste_tsi_v4_normal(void);
#endif /* __TSI_V4_NORMAL_H */