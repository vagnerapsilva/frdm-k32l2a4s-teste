
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
#include "fsl_fxas.h" // Driver do sensor FXAS21002
#include "fsl_lpi2c.h"  // Driver do I2C do K32L2
#include "fxas_21002c.h"
#include "encoder_ky_040.h" // Driver do encoder rotativo KY-040
#include <stdio.h>
 /*******************************************************************************
  * Definitions
  ******************************************************************************/
#define HWTIMER_PERIOD      10000U

  /*******************************************************************************
   * Prototypes
   ******************************************************************************/

   /*******************************************************************************
    * Variables
    ******************************************************************************/
volatile uint16_t SampleEventFlag;
uint8_t txbuff[] = "Usart polling example\r\nBoard will send back received characters\r\n";
uint8_t rxbuff[64] = { 0 };




/*******************************************************************************
 * Code
 ******************************************************************************/

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

static void HW_Timer_init(void)
{
    /* Configure the SysTick timer */
    SysTick_Config(SystemCoreClock / HWTIMER_PERIOD);
}

void SysTick_Handler(void)
{
    SampleEventFlag = 1;
}


// Renderiza o menu no Terminal Serial
void Display_Menu(void) {
    // Limpa a tela do terminal serial simulando um display

    ssd1306_Fill(Black);
    memset(MSG, 0xFF, 50);
    sprintf(MSG, "--MENU DE TESTES--");
    ssd1306_SetCursor(2, 0);
    ssd1306_WriteString(MSG, Font_7x10, White);
    memset(MSG, 0xFF, 50);
    sprintf(MSG, "%s Usart ", (encoder_counter == OPCAO_1) ? "->[X]" : "  [ ]");
    ssd1306_SetCursor(2, 12);
    ssd1306_WriteString(MSG, Font_7x10, White);
    memset(MSG, 0xFF, 50);
    sprintf(MSG, "%s Usb ", (encoder_counter == OPCAO_2) ? "->[X]" : "  [ ]");
    ssd1306_SetCursor(2, 22);
    ssd1306_WriteString(MSG, Font_7x10, White);
    memset(MSG, 0xFF, 50);
    sprintf(MSG, "%s Giroscopio ", (encoder_counter == OPCAO_3) ? "->[X]" : "  [ ]");
    ssd1306_SetCursor(2, 32);
    ssd1306_WriteString(MSG, Font_7x10, White);
    ssd1306_UpdateScreen();

}

void teste_Giroscopio(void)
{
    status_t result;
    result = FXAS_21002c_Init();
    if (result == kStatus_Success)
    {
        ssd1306_Fill(Black);
        memset(MSG, 0xFF, 50);
        sprintf(MSG, "LIB FRDM-K32L2A4S");
        ssd1306_SetCursor(0, 0);
        ssd1306_WriteString(MSG, Font_7x10, White);
        ssd1306_UpdateScreen();
        while (1)
        {
            // Ler pacote completo de dados brutos (Eixos X, Y e Z de uma só vez)
            result = FXAS_ReadSensorData(&fxasHandle, &sensorData);

            if (result == kStatus_Success)
            {
                // Combinar os pares de registradores de 8 bits em variáveis com sinal de 16 bits
                int16_t xRaw = (int16_t)((sensorData.gyroXMSB << 8) | sensorData.gyroXLSB);
                int16_t yRaw = (int16_t)((sensorData.gyroYMSB << 8) | sensorData.gyroYLSB);
                int16_t zRaw = (int16_t)((sensorData.gyroZMSB << 8) | sensorData.gyroZLSB);

                // Converter valores inteiros puros para graus por segundo utilizando a função nativa do driver
                float xDegPerSec = FXAS_FormatFloat(xRaw, fxasConfig.fsrdps);
                float yDegPerSec = FXAS_FormatFloat(yRaw, fxasConfig.fsrdps);
                float zDegPerSec = FXAS_FormatFloat(zRaw, fxasConfig.fsrdps);

                // Exibir os dados tratados no terminal serial da placa
                sprintf(MSG, "Giroscopio (dps)");
                ssd1306_SetCursor(2, 12);
                ssd1306_WriteString(MSG, Font_7x10, White);
                ssd1306_UpdateScreen();

                sprintf(MSG, "X: %6.2f", xDegPerSec);
                ssd1306_SetCursor(30, 25);
                ssd1306_WriteString(MSG, Font_7x10, White);
                ssd1306_UpdateScreen();

                sprintf(MSG, "Y: %6.2f", yDegPerSec);
                ssd1306_SetCursor(30, 35);
                ssd1306_WriteString(MSG, Font_7x10, White);
                ssd1306_UpdateScreen();

                sprintf(MSG, "Z: %6.2f", zDegPerSec);
                ssd1306_SetCursor(30, 45);
                ssd1306_WriteString(MSG, Font_7x10, White);
                ssd1306_UpdateScreen();
            }
            else
            {
                sprintf(MSG, "ERROR READING");
                ssd1306_SetCursor(2, 10);
                ssd1306_WriteString(MSG, Font_7x10, White);
                ssd1306_UpdateScreen();
            }

            //Aguarda um curto intervalo antes da próxima amostragem
            SDK_DelayAtLeastUs(200000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);

            // Verifica o clique do botão físico de forma não-bloqueante
            if (GPIO_PinRead(ENCODER_GPIO, SW_PIN) == 0) {
                // Debounce simples via software para o botão físico
                for (volatile int i = 0; i < 200000; i++);

                // Confirma se o botão continua pressionado pós-debounce
                if (GPIO_PinRead(ENCODER_GPIO, SW_PIN) == 0)
                    break; // Sai do loop de teste do giroscópio
            }
        }
    }
}

// Processa a ação da opção escolhida após o clique do botão
void Execute_Menu_Option(void) {
    //PRINTF("\r\n>>> Executando: ");
    switch (encoder_counter) {
    case OPCAO_1:
        //PRINTF("Opcao 1 Selecionada! Iniciando sistema...\r\n");
        break;
    case OPCAO_2:
        //PRINTF("Opcao 2 Selecionada! Abrindo configuracoes...\r\n");
        break;
    case OPCAO_3:
        teste_Giroscopio();
        break;
    default:
        break;
    }
    // Aguarda um momento para o usuário ler a mensagem na tela
    // for (volatile int i = 0; i < 3000000; i++);
    // menu_changed = true; // Força o redesenho do menu após a execução
}
/*!
 * @brief Main function
 */

int main(void)
{


    char MSG[50] = { 0 };
    /* Init board hardware. */
    BOARD_InitHardware();
    BOARD_InitPeripherals();
    ssd1306_Init();

    //HW_Timer_init();
    // Apply Half-Duplex Overrides
    LPUART_EnableHalfDuplex(LPUART0);

    LPUART_SetToTransmitMode(LPUART0);
    SDK_DelayAtLeastUs(100000, 48000000); // Delay for 100ms (assuming a 48 MHz clock)
    LPUART_WriteBlocking(LPUART0, txbuff, sizeof(txbuff) - 1);
    // 2. RECEIVE MODE DATA IN
    LPUART_SetToReceiveMode(LPUART0);

    ssd1306_Fill(Black);
    memset(MSG, 0xFF, 50);
    sprintf(MSG, "LIB FRDM-K32L2A4S");
    ssd1306_SetCursor(1, 0);
    ssd1306_WriteString(MSG, Font_7x10, White);
    ssd1306_UpdateScreen();

    encoder_counter = 0;

    last_clk_state = GPIO_PinRead(ENCODER_GPIO, CLK_PIN);






    /* Add user custom codes below */
    while (1)
    {

        // LPUART_SetToReceiveMode(LPUART0);
         //SDK_DelayAtLeastUs(100000, 48000000); // Delay for 100ms (assuming a 48 MHz clock)
         // This will block until a byte is received over the single wire
        // LPUART_ReadBlocking(LPUART0, &rxbuff[0], 1);
        // LPUART_SetToTransmitMode(LPUART0);
         // Process data...
        // SDK_DelayAtLeastUs(100000, 48000000); // Delay for 100ms (assuming a 48 MHz clock)
        // if (rxbuff[0] != 0) {
        //     sprintf(MSG, "RX_byte: 0x%02X", rxbuff[0]);
        //     ssd1306_SetCursor(2, 10);
        //     ssd1306_WriteString(MSG, Font_7x10, White);
        //     ssd1306_UpdateScreen();
        // }
        // rxbuff[0] = 0;
        USB_DeviceTasks();


        // O loop principal fica livre e apenas processa a exibição dos dados
        if (print_flag) {
            print_flag = false;
            Display_Menu();
        }

        // Verifica o clique do botão físico de forma não-bloqueante
        if (GPIO_PinRead(ENCODER_GPIO, SW_PIN) == 0) {
            // Debounce simples via software para o botão físico
            for (volatile int i = 0; i < 200000; i++);

            // Confirma se o botão continua pressionado pós-debounce
            if (GPIO_PinRead(ENCODER_GPIO, SW_PIN) == 0) {
                Execute_Menu_Option();
    
                // Aguarda o usuário soltar o botão para não registrar múltiplos cliques
                while (GPIO_PinRead(ENCODER_GPIO, SW_PIN) == 0);
                print_flag = true; // Força a atualização do menu após a execução da opção
            }
        }


    }
}
