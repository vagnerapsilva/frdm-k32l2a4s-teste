/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "board.h"
#include "fsl_tsi_v4.h"
#include "app.h"
#include "fsl_lptmr.h"
#include "display_lib.h"
#include "tsi_v4_normal.h"
#include "peripherals.h"
#include "encoder_ky_040.h"
#include "fsl_intmux.h"
#include "ssd1306.h"
#include "ssd1306_fonts.h"
 /*******************************************************************************
  * Definitions
  ******************************************************************************/

  /*******************************************************************************
   * Prototypes
   ******************************************************************************/

   /*******************************************************************************
    * Variables
    ******************************************************************************/
tsi_calibration_data_t buffer;

/*******************************************************************************
 * Code
 ******************************************************************************/
void TSI0_IRQHandler(void)
{
    if (TSI_GetMeasuredChannelNumber(TSI0) == BOARD_TSI_ELECTRODE_1)
    {
        uint16_t counter = TSI_GetCounter(TSI0);
        if (counter > (uint16_t)(buffer.calibratedData[BOARD_TSI_ELECTRODE_1] * (1.0F + TOUCH_DELTA_PERCENT)))
        {
            // LED_TOGGLE(); /* Toggle the touch event indicating LED */
            memset(MSG, 0xFF, 50);
            sprintf(MSG, "Tsi value: %d", counter);
            ssd1306_SetCursor(1, 53);
            ssd1306_WriteString(MSG, Font_7x10, White);
            ssd1306_UpdateScreen();
        }
    }

    /* Clear flags */
    TSI_ClearStatusFlags(TSI0, kTSI_EndOfScanFlag);
    TSI_ClearStatusFlags(TSI0, (uint32_t)kTSI_OutOfRangeFlag);
    SDK_ISR_EXIT_BARRIER;
}

/*!
 * @brief Main function
 */
void teste_tsi_v4_normal(void)
{
    volatile uint32_t i = 0;
    tsi_config_t tsiConfig_normal = { 0 };
    lptmr_config_t lptmrConfig;
    memset((void*)&lptmrConfig, 0, sizeof(lptmrConfig));

    TPM_StopTimer(TPM0_PERIPHERAL);
    TPM_Deinit(TPM0_PERIPHERAL);

    TPM_StopTimer(TPM1_PERIPHERAL);
    TPM_Deinit(TPM1_PERIPHERAL);

    INTMUX_Init(INTMUX0);
    INTMUX_EnableInterrupt(INTMUX0, 0, TSI0_IRQn);
    /* Configure LPTMR */
    /*
     * lptmrConfig.timerMode = kLPTMR_TimerModeTimeCounter;
     * lptmrConfig.pinSelect = kLPTMR_PinSelectInput_0;
     * lptmrConfig.pinPolarity = kLPTMR_PinPolarityActiveHigh;
     * lptmrConfig.enableFreeRunning = false;
     * lptmrConfig.bypassPrescaler = true;
     * lptmrConfig.prescalerClockSource = kLPTMR_PrescalerClock_1;
     * lptmrConfig.value = kLPTMR_Prescale_Glitch_0;
     */
    LPTMR_GetDefaultConfig(&lptmrConfig);
    /* TSI default hardware configuration for normal mode */
    TSI_GetNormalModeDefaultConfig(&tsiConfig_normal);

    /* Initialize the LPTMR */
    LPTMR_Init(LPTMR0, &lptmrConfig);
    /* Initialize the TSI */
    TSI_Init(TSI0, &tsiConfig_normal);

    /* Set timer period */
    LPTMR_SetTimerPeriod(LPTMR0, USEC_TO_COUNT(LPTMR_USEC_COUNT, LPTMR_SOURCE_CLOCK));

    NVIC_EnableIRQ(TSI0_IRQn);
    TSI_EnableModule(TSI0, true); /* Enable module */

    display_init();
    display_clear();
    /*********  CALIBRATION PROCESS ************/
    memset((void*)&buffer, 0, sizeof(buffer));
    TSI_Calibrate(TSI0, &buffer);
    /* Print calibrated counter values */
    for (i = 0U; i < FSL_FEATURE_TSI_CHANNEL_COUNT; i++)
    {
        display_add_line("Cal ch %d: %d", i, buffer.calibratedData[i]);

        if ((i % 4U) == 3U || i == (FSL_FEATURE_TSI_CHANNEL_COUNT - 1U))
        {
            display_render("TSI Normal mode");
            SDK_DelayAtLeastUs(500000U, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
            display_clear();
        }
    }

    /********** SOFTWARE TRIGGER SCAN USING POLLING METHOD ********/
    display_clear();
    // display_add_line("TSI_V4 Normal mode");
    //display_add_line("Polling scan");
    TSI_EnableHardwareTriggerScan(TSI0, false); /* Enable software trigger scan */
    TSI_DisableInterrupts(TSI0, kTSI_EndOfScanInterruptEnable);

    TSI_ClearStatusFlags(TSI0, kTSI_EndOfScanFlag);
    TSI_SetMeasuredChannelNumber(TSI0, BOARD_TSI_ELECTRODE_1);
    TSI_StartSoftwareTrigger(TSI0);
    while (!(TSI_GetStatusFlags(TSI0) & kTSI_EndOfScanFlag))
    {
    }
    display_add_line("Poll ch %d: %d", BOARD_TSI_ELECTRODE_1, TSI_GetCounter(TSI0));

    TSI_ClearStatusFlags(TSI0, kTSI_EndOfScanFlag);
    TSI_SetMeasuredChannelNumber(TSI0, BOARD_TSI_ELECTRODE_2);
    TSI_StartSoftwareTrigger(TSI0);
    while (!(TSI_GetStatusFlags(TSI0) & kTSI_EndOfScanFlag))
    {
    }
    display_add_line("Poll ch %d: %d", BOARD_TSI_ELECTRODE_2, TSI_GetCounter(TSI0));
    display_render("TSI Polling scan");
    //Aguarda um curto intervalo antes da próxima amostragem
    while (1) {
        // Verifica o clique do botão físico de forma não-bloqueante
        if (GPIO_PinRead(ENCODER_GPIO, SW_PIN) == 0) {
            // Debounce simples via software para o botão físico
            SDK_DelayAtLeastUs(200000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);

            // Confirma se o botão continua pressionado pós-debounce
            if (GPIO_PinRead(ENCODER_GPIO, SW_PIN) == 0)
                break; // Sai do loop infinito e retorna ao menu principal
        }
    }

    display_clear();
    TSI_ClearStatusFlags(TSI0, kTSI_EndOfScanFlag);
    TSI_ClearStatusFlags(TSI0, (uint32_t)kTSI_OutOfRangeFlag);

    /********** SOFTWARE TRIGGER SCAN USING INTERRUPT METHOD ********/
    //display_add_line("Interrupt scan");
    TSI_EnableInterrupts(TSI0, kTSI_GlobalInterruptEnable);
    TSI_EnableInterrupts(TSI0, kTSI_EndOfScanInterruptEnable);
    TSI_ClearStatusFlags(TSI0, kTSI_EndOfScanFlag);
    TSI_SetMeasuredChannelNumber(TSI0, BOARD_TSI_ELECTRODE_1);
    TSI_StartSoftwareTrigger(TSI0);
    while (TSI_IsScanInProgress(TSI0))
    {
    }
    display_add_line("IRQ ch %d: %d", BOARD_TSI_ELECTRODE_1, TSI_GetCounter(TSI0));

    TSI_SetMeasuredChannelNumber(TSI0, BOARD_TSI_ELECTRODE_2);
    TSI_StartSoftwareTrigger(TSI0);
    while (TSI_IsScanInProgress(TSI0))
    {
    }
    display_add_line("IRQ ch %d: %d", BOARD_TSI_ELECTRODE_2, TSI_GetCounter(TSI0));

    /********** HARDWARE TRIGGER SCAN ********/
    display_add_line("Hardware scan");
    display_add_line("Touch pad %s", PAD_TSI_ELECTRODE_1_NAME);
    display_render("TSI Interrupt scan");
    TSI_EnableModule(TSI0, false);
    TSI_EnableHardwareTriggerScan(TSI0, true);
    TSI_EnableInterrupts(TSI0, kTSI_GlobalInterruptEnable);
    TSI_EnableInterrupts(TSI0, kTSI_EndOfScanInterruptEnable);
    TSI_ClearStatusFlags(TSI0, kTSI_EndOfScanFlag);
    /* Select BOARD_TSI_ELECTRODE_1 as detecting electrode. */
    TSI_SetMeasuredChannelNumber(TSI0, BOARD_TSI_ELECTRODE_1);
    TSI_EnableModule(TSI0, true);
    LPTMR_ClearStatusFlags(LPTMR0, (uint32_t)kLPTMR_TimerCompareFlag);
    LPTMR_StartTimer(LPTMR0); /* Start LPTMR triggering the TSI scan. */
    //Aguarda um curto intervalo antes da próxima amostragem
    while (1) {
        // Verifica o clique do botão físico de forma não-bloqueante
        if (GPIO_PinRead(ENCODER_GPIO, SW_PIN) == 0) {
            // Debounce simples via software para o botão físico
            SDK_DelayAtLeastUs(200000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);

            // Confirma se o botão continua pressionado pós-debounce
            if (GPIO_PinRead(ENCODER_GPIO, SW_PIN) == 0)
                break; // Sai do loop infinito e retorna ao menu principal
        }
    }

    /* Disable all timer-driven activity before leaving the test. */
    TSI_EnableModule(TSI0, false);
    NVIC_DisableIRQ(TSI0_IRQn);
    LPTMR_StopTimer(LPTMR0);
    LPTMR_Deinit(LPTMR0);
    __NVIC_SystemReset();
}
