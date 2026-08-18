/*******************************************************************************
 *        TECNODEV TECNOLOGIA DE DESENVOLVIMENTIO DE SOFTWARE E SERVICOS       *
 *        TEL: (011) 4109-0577                 SITE: www.tecnodev.com.br       *
 * rng.c                                                                       *
 *                                                                             *
 * Implementação do driver do gerador de números aleatórios (RNG).            *
 ******************************************************************************/
#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "fsl_common.h"
#include "fsl_trng.h"
#include "board.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "peripherals.h"
#include "app.h"
#include "rng.h"
#include "ssd1306.h"
#include "ssd1306_fonts.h"
#include "encoder_ky_040.h" // Driver do encoder rotativo KY-040

 /*******************************************************************************
  * Definitions
  ******************************************************************************/
#define TRNG_EXAMPLE_RANDOM_NUMBER 3

  /*******************************************************************************
   * Variables
   ******************************************************************************/



   /*******************************************************************************
    * Code
    ******************************************************************************/

void teste_rng(void)
{
    status_t status;
    uint32_t data[TRNG_EXAMPLE_RANDOM_NUMBER];

    trng_config_t trngConfig;


    ssd1306_Fill(Black);
    sprintf(MSG, "Teste RNG %d", TRNG_EXAMPLE_RANDOM_NUMBER);
    ssd1306_SetCursor(1, 0);
    ssd1306_WriteString(MSG, Font_7x10, White);
    ssd1306_Line(0, 12, 127, 12, White);
    ssd1306_UpdateScreen();
    // 1. Carrega as configurações padrão do TRNG
    TRNG_GetDefaultConfig(&trngConfig);
    status = TRNG_Init(TRNG0, &trngConfig);

    SDK_DelayAtLeastUs(10000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
    status = TRNG_GetRandomData(TRNG0, data, sizeof(data));

    if (kStatus_Success == status)
    {
        /* Print data*/
        for (uint32_t i = 0; i < TRNG_EXAMPLE_RANDOM_NUMBER; i++)
        {
            sprintf(MSG, "Rand_%lu=0x%08lX", (unsigned long)i, (unsigned long)data[i]);
            ssd1306_SetCursor(1, 20 + (i * 12));
            ssd1306_WriteString(MSG, Font_7x10, White);
            ssd1306_UpdateScreen();
        }
    }
    else
    {
        ssd1306_Fill(Black);
        sprintf(MSG, "TRNG failed: %ld", (long)status);
        ssd1306_SetCursor(1, 20);
        ssd1306_WriteString(MSG, Font_7x10, White);
        sprintf(MSG, "MCTL: 0x%08lX", (unsigned long)TRNG_PERIPHERAL->MCTL);
        ssd1306_SetCursor(1, 32);
        ssd1306_WriteString(MSG, Font_7x10, White);
        ssd1306_UpdateScreen();
    }

    //Aguarda um curto intervalo antes da próxima amostragem
    SDK_DelayAtLeastUs(200000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
    while (1)
    {
        // Verifica o clique do botão físico de forma não-bloqueante
        if (GPIO_PinRead(ENCODER_GPIO, SW_PIN) == 0) {
            // Debounce simples via software para o botão físico
            for (volatile int i = 0; i < 200000; i++);

            // Confirma se o botão continua pressionado pós-debounce
            if (GPIO_PinRead(ENCODER_GPIO, SW_PIN) == 0)
                __NVIC_SystemReset(); // Reinicia o microcontrolador
            //break; // Sai do loop de teste do giroscópio

        }
    }
}