
/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "peripherals.h"

#include "board.h"
#include "app.h"

#include "fsl_lpuart.h"
#include "peripherals.h"
#include "ssd1306.h"
#include "ssd1306_fonts.h"
#include <stdio.h>
 /*******************************************************************************
  * Definitions
  ******************************************************************************/

  /*******************************************************************************
   * Prototypes
   ******************************************************************************/

   /*******************************************************************************
    * Variables
    ******************************************************************************/

uint8_t txbuff[] = "Usart polling example\r\nBoard will send back received characters\r\n";
uint8_t rxbuff[20] = { 0 };

/*******************************************************************************
 * Code
 ******************************************************************************/
 /*!
  * @brief Main function
  */

void LPUART_EnableHalfDuplex(LPUART_Type* base)
{
    /* Enable Single-Wire mode: TXDIR will now dictate pin state */
    base->CTRL |= LPUART_CTRL_LOOPS_MASK; // Enable loop mode
    base->CTRL |= LPUART_CTRL_RSRC_MASK;  // Select Single-wire mode (source TX pin)

    /* Set the peripheral default state to Receiver Mode */
    base->CTRL &= ~LPUART_CTRL_TXDIR_MASK; // TXDIR = 0 (Input/Rx Mode)
}


void LPUART_SetToTransmitMode(LPUART_Type* base)
{
    /* 1. Ensure any ongoing receive operations are clear */
    base->CTRL &= ~LPUART_CTRL_RE_MASK;    // Disable receiver temporarily


    /* 2. Switch pin direction to Output */
    base->CTRL |= LPUART_CTRL_TXDIR_MASK;  // TXDIR = 1 (Output/Tx Mode)

    /* 3. Re-enable transmitter */
    base->CTRL |= LPUART_CTRL_TE_MASK;     // Ensure TE is set
}

void LPUART_SetToReceiveMode(LPUART_Type* base)
{
    /* 1. Ensure the transmission buffer is completely empty before switching */
    while (!(base->STAT & LPUART_STAT_TC_MASK))
    {
        // Wait for Transmission Complete flag
    }

    /* 2. Switch pin direction back to Input */
    base->CTRL &= ~LPUART_CTRL_TXDIR_MASK; // TXDIR = 0 (Input/Rx Mode)

    /* 3. Re-enable receiver */
    base->CTRL |= LPUART_CTRL_RE_MASK;     // Re-enable RE
}

int main(void)
{
    char MSG[50] = { 0 };
    /* Init board hardware. */
    BOARD_InitHardware();
    BOARD_InitPeripherals();
    ssd1306_Init();

    // Apply Half-Duplex Overrides
    LPUART_EnableHalfDuplex(LPUART0);

    LPUART_SetToTransmitMode(LPUART0);
    SDK_DelayAtLeastUs(100000, 48000000); // Delay for 100ms (assuming a 48 MHz clock)
    LPUART_WriteBlocking(LPUART0, txbuff, sizeof(txbuff) - 1);
    // 2. RECEIVE MODE DATA IN
    LPUART_SetToReceiveMode(LPUART0);

    ssd1306_Fill(Black);
    memset(MSG, 0xFF, 50);
    sprintf(MSG, "Usart polling test");
    ssd1306_SetCursor(1, 0);
    ssd1306_WriteString(MSG, Font_7x10, White);
    ssd1306_UpdateScreen();

    /* Add user custom codes below */
    while (1)
    {

        LPUART_SetToReceiveMode(LPUART0);
        SDK_DelayAtLeastUs(100000, 48000000); // Delay for 100ms (assuming a 48 MHz clock)
        // This will block until a byte is received over the single wire
        LPUART_ReadBlocking(LPUART0, &rxbuff[0], 1);
        LPUART_SetToTransmitMode(LPUART0);
        // Process data...
        SDK_DelayAtLeastUs(100000, 48000000); // Delay for 100ms (assuming a 48 MHz clock)
        if (rxbuff[0] != 0) {
            sprintf(MSG, "RX_byte: 0x%02X", rxbuff[0]);
            ssd1306_SetCursor(2, 10);
            ssd1306_WriteString(MSG, Font_7x10, White);
            ssd1306_UpdateScreen();
        }
        rxbuff[0] = 0;
    }
}
