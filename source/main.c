
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
#include <stdio.h>
 /*******************************************************************************
  * Definitions
  ******************************************************************************/
#define HWTIMER_PERIOD      10000U
  // Definições do barramento I2C da FRDM-K32L2
#define FXAS21002_I2C_ADDRESS    0x20 // Endereço I2C padrão do FXAS21002

// Declaração das estruturas necessárias
fxas_handle_t fxasHandle;
fxas_config_t fxasConfig;
fxas_data_t sensorData;
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

static void HW_Timer_init(void)
{
    /* Configure the SysTick timer */
    SysTick_Config(SystemCoreClock / HWTIMER_PERIOD);
}

void SysTick_Handler(void)
{
    SampleEventFlag = 1;
}

#include <stdio.h>
#include "board.h"
#include "fsl_debug_console.h"
#include "fsl_lpi2c.h"
#include "fsl_fxas.h"

// Definições do periférico I2C da FRDM-K32L2 (Ajuste conforme seu Config Tools)
#define BOARD_FXAS_I2C_BASE LPI2C0
#define BOARD_FXAS_I2C_CLOCK_FREQ CLOCK_GetIpFreq(kCLOCK_Lpi2c0)

// Função adaptadora para Envio I2C exigida pelo fxas_config_t
status_t FXAS_I2C_Send(uint8_t deviceAddress, uint32_t subAddress, uint8_t subaddressSize, uint32_t txBuff)
{
    uint8_t data = (uint8_t)txBuff;
    lpi2c_master_transfer_t xfer = { 0 };

    xfer.slaveAddress = deviceAddress;
    xfer.direction = kLPI2C_Write;
    xfer.subaddress = subAddress;
    xfer.subaddressSize = subaddressSize;
    xfer.data = &data;
    xfer.dataSize = 1;
    xfer.flags = kLPI2C_TransferDefaultFlag;

    return LPI2C_MasterTransferBlocking(BOARD_FXAS_I2C_BASE, &xfer);
}

// Função adaptadora para Recepção I2C exigida pelo fxas_config_t

status_t FXAS_I2C_Receive(uint8_t deviceAddress, uint32_t subAddress, uint8_t subaddressSize, uint8_t* rxBuff, uint8_t rxBuffSize)
{
    lpi2c_master_transfer_t xfer = { 0 };

    xfer.slaveAddress = deviceAddress;
    xfer.direction = kLPI2C_Read;
    xfer.subaddress = subAddress;
    xfer.subaddressSize = subaddressSize;
    xfer.data = rxBuff;
    xfer.dataSize = rxBuffSize;
    xfer.flags = kLPI2C_TransferDefaultFlag;
    status_t i2c_status = LPI2C_MasterTransferBlocking(BOARD_FXAS_I2C_BASE, &xfer);
    return i2c_status;

   // return LPI2C_MasterTransferBlocking(BOARD_FXAS_I2C_BASE, &xfer);
}



int main(void)
{
    status_t result;

    char MSG[50] = { 0 };
    /* Init board hardware. */
    BOARD_InitHardware();
    BOARD_InitPeripherals();
    ssd1306_Init();

    HW_Timer_init();
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



    // 2. Vincular as funções de leitura/escrita I2C criadas ao Config do Sensor
    fxasConfig.I2C_SendFunc = FXAS_I2C_Send;
    fxasConfig.I2C_ReceiveFunc = FXAS_I2C_Receive;

    // 3. Definir parâmetros operacionais usando os Enums do seu fsl_fxas.h
    fxasConfig.I2C_SendFunc = FXAS_I2C_Send;
    fxasConfig.I2C_ReceiveFunc = FXAS_I2C_Receive;
    fxasConfig.fsrdps = kFXAS_Gfsr_2000DPS;      // Fundo de escala de 2000 graus por segundo
    fxasConfig.odr = kFXAS_Godr_100Hz;        // Taxa de amostragem de 100 Hz
    fxasConfig.fifo = kFXAS_FIFO_Disabled;     // Sem uso de memória FIFO interna

    // 4. Executar rotina de inicialização do driver (valida WHO_AM_I e acorda o sensor)
    result = FXAS_Init(&fxasHandle, &fxasConfig);
    if (result != kStatus_Success)
    {
        //PRINTF("\r\nFalha catastrófica ao tentar comunicar com o FXAS21002C!\r\n");
        while (1);
    }
    //PRINTF("\r\nSensor FXAS21002C detectado e inicializado com sucesso!\r\n");


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
            sprintf(MSG, "Giroscópio (dps)");
            ssd1306_SetCursor(2, 10);
            ssd1306_WriteString(MSG, Font_7x10, White);
            ssd1306_UpdateScreen();

            sprintf(MSG, "X: %6.2f", xDegPerSec);
            ssd1306_SetCursor(2, 20);
            ssd1306_WriteString(MSG, Font_7x10, White);
            ssd1306_UpdateScreen();

            sprintf(MSG, "Y: %6.2f",  yDegPerSec);
            ssd1306_SetCursor(2, 30);
            ssd1306_WriteString(MSG, Font_7x10, White);
            ssd1306_UpdateScreen();
            
            sprintf(MSG, "Z: %6.2f",  zDegPerSec);
            ssd1306_SetCursor(2, 40);
            ssd1306_WriteString(MSG, Font_7x10, White);
            ssd1306_UpdateScreen();
        }
        else
        {
            sprintf(MSG, "Erro durante a requisição de leitura do barramento.\r\n");
            ssd1306_SetCursor(2, 10);
            ssd1306_WriteString(MSG, Font_7x10, White);
            ssd1306_UpdateScreen();
        }

        // Aguarda um curto intervalo antes da próxima amostragem
        SDK_DelayAtLeastUs(200000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);

    }
}
