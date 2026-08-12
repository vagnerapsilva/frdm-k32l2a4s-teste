/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *        TECNODEV TECNOLOGIA DE DESENVOLVIMENTIO DE SOFTWARE E SERVICOS       *
 *        TEL: (011) 4109-0577                 SITE: www.tecnodev.com.br       *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include <stdio.h>
#include "light_sensor.h"
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

void light_sensor_test(void)
{
    uint32_t adc_value = 0;
    uint32_t voltage_mv = 0;
    ssd1306_Fill(Black);
    memset(MSG, 0xFF, 50);
    sprintf(MSG, " LIGHT SENSOR ");
    ssd1306_SetCursor(0, 0);
    ssd1306_WriteString(MSG, Font_7x10, White);
    ssd1306_UpdateScreen();

    while (1)
    {
        ADC16_SetChannelConfig(ADC0_PERIPHERAL, ADC0_CH0_CONTROL_GROUP, &ADC0_channelsConfig[0]);
        while (0U == (kADC16_ChannelConversionDoneFlag &
            ADC16_GetChannelStatusFlags(ADC0_PERIPHERAL, ADC0_CH0_CONTROL_GROUP)))
        {
        }
        adc_value = ADC16_GetChannelConversionValue(ADC0_PERIPHERAL, ADC0_CH0_CONTROL_GROUP);

        voltage_mv = (adc_value * 3300U) / 4095U; // Assuming a 3.3V reference and 12-bit ADC

        memset(MSG, 0xFF, 50);
        sprintf(MSG, "ADC Value: %lu", adc_value);
        ssd1306_SetCursor(0, 20);
        ssd1306_WriteString(MSG, Font_7x10, White);
        memset(MSG, 0xFF, 50);
        sprintf(MSG, "Voltage: %lu mV", voltage_mv);
        ssd1306_SetCursor(0, 30);
        ssd1306_WriteString(MSG, Font_7x10, White);
        ssd1306_UpdateScreen();

        //Aguarda um curto intervalo antes da próxima amostragem
        SDK_DelayAtLeastUs(200000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);

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