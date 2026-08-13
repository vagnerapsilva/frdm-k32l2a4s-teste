/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *        TECNODEV TECNOLOGIA DE DESENVOLVIMENTIO DE SOFTWARE E SERVICOS       *
 *        TEL: (011) 4109-0577                 SITE: www.tecnodev.com.br       *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include <stdio.h>
#include "usart.h"
#include "fsl_lpuart.h"
#include "ssd1306.h"
#include "encoder_ky_040.h" // Driver do encoder rotativo KY-040
#include "peripherals.h"
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
uint8_t rxbuff[64] = { 0 };

/*******************************************************************************
* Code.
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


void usart_one_wire_test(void)
{
    uint32_t baudRate;
    uint32_t baudReg = LPUART0->BAUD;
    uint32_t osr = ((baudReg & LPUART_BAUD_OSR_MASK) >> LPUART_BAUD_OSR_SHIFT) + 1U;
    uint32_t sbr = (baudReg & LPUART_BAUD_SBR_MASK) >> LPUART_BAUD_SBR_SHIFT;

    // Evita divisão por zero
    if (sbr != 0) {
        baudRate = LPUART0_CLOCK_SOURCE / (osr * sbr);
    }
    else {
        baudRate = 0;
    }
    ssd1306_Fill(Black);
    memset(MSG, 0xFF, 50);
    sprintf(MSG, "Usart 0 Baud(%ld)", baudRate);
    ssd1306_SetCursor(0, 0);
    ssd1306_WriteString(MSG, Font_7x10, White);
    ssd1306_UpdateScreen();

    // while (1) {
    //     // if (print_flag) {
    //     //     print_flag = false;
    //     sprintf(MSG, "Encoder: %.6ld", TPM0->CNT);
    //         ssd1306_SetCursor(2, 25);
    //         ssd1306_WriteString(MSG, Font_7x10, White);
    //         ssd1306_UpdateScreen();
    //     //}
    // }

    LPUART_EnableHalfDuplex(LPUART0);
    LPUART_SetToTransmitMode(LPUART0);
    SDK_DelayAtLeastUs(100000, 48000000); // Delay for 100ms (assuming a 48 MHz clock)
    LPUART_WriteBlocking(LPUART0, txbuff, sizeof(txbuff) - 1);
    // 2. RECEIVE MODE DATA IN
    LPUART_SetToReceiveMode(LPUART0);

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
        //Aguarda um curto intervalo antes da próxima amostragem
        SDK_DelayAtLeastUs(200000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);

        // Verifica o clique do botão físico de forma não-bloqueante
        if (GPIO_PinRead(ENCODER_GPIO, SW_PIN) == 0) {
            // Debounce simples via software para o botão físico
            SDK_DelayAtLeastUs(10000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);

            // Confirma se o botão continua pressionado pós-debounce
            if (GPIO_PinRead(ENCODER_GPIO, SW_PIN) == 0)
                __NVIC_SystemReset(); // Reinicia o microcontrolador    
            //break; // Sai do loop de teste do giroscópio
        }
    }

}