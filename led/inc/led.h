/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *        TECNODEV TECNOLOGIA DE DESENVOLVIMENTIO DE SOFTWARE E SERVICOS       *
 *        TEL: (011) 4109-0577                 SITE: www.tecnodev.com.br       *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

 /* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LED_H
#define __LED_H

/*******************************************************************************
 * Public API
 ******************************************************************************/

/*!
 * @brief Cycles through red, green, blue, and combined colors on the RGB LED
 *        driven by TPM0 channels kTPM_Chnl_2 (red), kTPM_Chnl_3 (green) and
 *        kTPM_Chnl_4 (blue), holding each color for a short delay.
 *
 * @note TPM0 must already be initialized (see TPM0_init()/BOARD_InitPeripherals)
 *       before calling this function.
 */
void LED_TestRgbColors(void);

#endif /* __LED_H */