/*******************************************************************************
 *        TECNODEV TECNOLOGIA DE DESENVOLVIMENTIO DE SOFTWARE E SERVICOS       *
 *        TEL: (011) 4109-0577                 SITE: www.tecnodev.com.br       *
 * led.c                                                                       *
 *                                                                             *
 * Implementação do teste das cores do LED RGB controlado por PWM (TPM0).     *
 ******************************************************************************/
#include "fsl_device_registers.h"
#include "fsl_common.h"
#include "fsl_tpm.h"
#include "board.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "peripherals.h"
#include "app.h"
#include "led.h"
#include "ssd1306.h"
#include "ssd1306_fonts.h"

 /*******************************************************************************
  * Definitions
  ******************************************************************************/
#define LED_TEST_DELAY_US (500000U)

  /*******************************************************************************
   * Variables
   ******************************************************************************/



   /*******************************************************************************
    * Code
    ******************************************************************************/

    /*!
     * @brief Sets the duty cycle (0-100%) of the red, green and blue PWM channels.
     */
static void LED_SetColor(uint8_t redPercent, uint8_t greenPercent, uint8_t bluePercent)
{
    TPM_UpdatePwmDutycycle(TPM0_PERIPHERAL, TPM0_LEDRGB_RED_CHANNEL, kTPM_EdgeAlignedPwm, redPercent);
    TPM_UpdatePwmDutycycle(TPM0_PERIPHERAL, TPM0_LEDRGB_GREEN_CHANNEL, kTPM_EdgeAlignedPwm, greenPercent);
    TPM_UpdatePwmDutycycle(TPM0_PERIPHERAL, TPM0_LEDRGB_BLUE_CHANNEL, kTPM_EdgeAlignedPwm, bluePercent);

    sprintf(MSG, "Red: %0.3d", redPercent);
    ssd1306_SetCursor(30, 25);
    ssd1306_WriteString(MSG, Font_7x10, White);

    sprintf(MSG, "Green: %0.3d", greenPercent);
    ssd1306_SetCursor(30, 35);
    ssd1306_WriteString(MSG, Font_7x10, White);

    sprintf(MSG, "Blue: %0.3d", bluePercent);
    ssd1306_SetCursor(30, 45);
    ssd1306_WriteString(MSG, Font_7x10, White);
    ssd1306_UpdateScreen();
}

void LED_TestRgbColors(void)
{
    TPM_StartTimer(TPM0_PERIPHERAL, kTPM_SystemClock);

    ssd1306_Fill(Black);

    /* Draw title */
    ssd1306_SetCursor(0, 0);
    ssd1306_WriteString("Led_RGB Test", Font_7x10, White);

    /* Draw separator */
    ssd1306_Line(0, 12, 127, 12, White);

    ssd1306_UpdateScreen();
    static const struct
    {
        uint8_t red;
        uint8_t green;
        uint8_t blue;
    } colors[] = {
        { 100U, 0U,   0U   }, /* Red */
        { 0U,   100U, 0U   }, /* Green */
        { 0U,   0U,   100U }, /* Blue */
        { 100U, 100U, 0U   }, /* Yellow */
        { 0U,   100U, 100U }, /* Cyan */
        { 100U, 0U,   100U }, /* Magenta */
        { 100U, 100U, 100U }, /* White */
        { 0U,   0U,   0U   }  /* Off */
    };

    for (size_t i = 0U; i < (sizeof(colors) / sizeof(colors[0])); i++)
    {
        LED_SetColor(colors[i].red, colors[i].green, colors[i].blue);
        SDK_DelayAtLeastUs(LED_TEST_DELAY_US, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
    }
    TPM_StopTimer(TPM0_PERIPHERAL);
    __NVIC_SystemReset();
}
