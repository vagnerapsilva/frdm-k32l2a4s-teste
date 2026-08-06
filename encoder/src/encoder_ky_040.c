/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *        TECNODEV TECNOLOGIA DE DESENVOLVIMENTIO DE SOFTWARE E SERVICOS       *
 *        TEL: (011) 4109-0577                 SITE: www.tecnodev.com.br       *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include "encoder_ky_040.h"

#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "fsl_gpio.h"
#include "fsl_port.h"
#include "fsl_lpit.h"
#include "board.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "peripherals.h"
#include "board.h"
#include "app.h"
#include "fsl_tpm.h"
 /*******************************************************************************
  * Definitions
  ******************************************************************************/
  // Definições de Pinos e Periféricos


#define ENCODER_LPIT_BASE   LPIT0
#define ENCODER_LPIT_CH     kLPIT_Chnl_0
#define LPIT_IRQ_HANDLER    LPIT0_IRQHandler
#define LPIT_IRQ_NUM        LPIT0_IRQn
  /*******************************************************************************
   * Prototypes
   ******************************************************************************/

   /*******************************************************************************
   * Variables
   ******************************************************************************/
   // Variáveis globais voláteis (modificadas na interrupção)
volatile int32_t encoder_counter = 0;
volatile uint32_t last_clk_state = 0;
volatile bool print_flag = false;

/*******************************************************************************
 * Code
 ******************************************************************************/

 // // Inicialização dos pinos GPIO
 // void Init_Encoder_Pins(void) {
 //     CLOCK_EnableClock(kCLOCK_PortA);

 //     PORT_SetPinMux(ENCODER_PORT, CLK_PIN, kPORT_MuxAsGpio);
 //     PORT_SetPinMux(ENCODER_PORT, DT_PIN, kPORT_MuxAsGpio);
 //     PORT_SetPinMux(ENCODER_PORT, SW_PIN, kPORT_MuxAsGpio);

 //     gpio_pin_config_t input_config = { kGPIO_DigitalInput, 0 };
 //     GPIO_PinInit(ENCODER_GPIO, CLK_PIN, &input_config);
 //     GPIO_PinInit(ENCODER_GPIO, DT_PIN, &input_config);
 //     GPIO_PinInit(ENCODER_GPIO, SW_PIN, &input_config);
 // }

 // Inicialização do Timer (LPIT) para 1 milissegundo utilizando a fsl_lpit.h v2.1.1
void Init_Timer_1ms(void) {
    lpit_config_t lpitConfig;
    lpit_chnl_params_t lpitChannelConfig; // Corrigido para o tipo correto da sua lib

    // 1. Configura a fonte de clock para o periférico LPIT

    CLOCK_EnableClock(kCLOCK_Lpit0);

    // 2. Inicializa o módulo básico do LPIT
    LPIT_GetDefaultConfig(&lpitConfig);
    lpitConfig.enableRunInDebug = true; // Permite que o timer continue rodando ao pausar o debugger
    LPIT_Init(ENCODER_LPIT_BASE, &lpitConfig);

    // 3. Preenche a estrutura com os enums exatos contidos na sua fsl_lpit.h
    lpitChannelConfig.chainChannel = false;
    lpitChannelConfig.timerMode = kLPIT_PeriodicCounter;
    lpitChannelConfig.triggerSource = kLPIT_TriggerSource_Internal;
    lpitChannelConfig.triggerSelect = kLPIT_Trigger_TimerChn0; // Ajustado para o enum da sua lib
    lpitChannelConfig.enableReloadOnTrigger = false;                   // Campo existente na sua struct
    lpitChannelConfig.enableStopOnTimeout = false;                   // Campo existente na sua struct
    lpitChannelConfig.enableStartOnTrigger = false;                   // Começa a decrementar imediatamente

    // 4. Configura o canal do timer
    LPIT_SetupChannel(ENCODER_LPIT_BASE, ENCODER_LPIT_CH, &lpitChannelConfig);

    // 5. Calcula e define o período para 1ms
    uint32_t lpitSrcClock_Hz = CLOCK_GetIpFreq(kCLOCK_Lpit0);
    LPIT_SetTimerPeriod(ENCODER_LPIT_BASE, ENCODER_LPIT_CH, USEC_TO_COUNT(1000U, lpitSrcClock_Hz));

    // 6. Habilita a interrupção do canal e no NVIC do Cortex-M
    LPIT_EnableInterrupts(ENCODER_LPIT_BASE, kLPIT_Channel0TimerInterruptEnable);
    EnableIRQ(LPIT_IRQ_NUM);

    // 7. Inicia a contagem do Timer
    LPIT_StartTimer(ENCODER_LPIT_BASE, ENCODER_LPIT_CH);
}



/* TPM0_IRQn interrupt handler */
void TPM0_IRQHANDLER(void) {
    uint32_t intStatus;
    /* Reading all interrupt flags of status register */
    intStatus = TPM_GetStatusFlags(TPM0_PERIPHERAL);
    TPM_ClearStatusFlags(TPM0_PERIPHERAL, intStatus);

    /* Place your code here */


    // Leitura rápida dos pinos
    uint32_t current_clk_state = GPIO_PinRead(ENCODER_GPIO, CLK_PIN);

    // Verifica se houve mudança na borda do sinal CLK
    if (current_clk_state != last_clk_state) {
        if (current_clk_state == 0) {
            if (GPIO_PinRead(ENCODER_GPIO, DT_PIN) != current_clk_state) {
                encoder_counter++;
            }
            else {
                encoder_counter--;
            }
            // 3. Mantém o efeito carrossel infinito entre as 3 opções
            if (encoder_counter >= TOTAL_OPCOES) {
                encoder_counter = OPCAO_1;
            }
            else if (encoder_counter < 0) {
                encoder_counter = OPCAO_3;
            }
            print_flag = true; // Sinaliza ao loop principal para imprimir o valor atualizado
        }
    }

    last_clk_state = current_clk_state;

    /* Add for ARM errata 838869, affects Cortex-M4, Cortex-M4F
       Store immediate overlapping exception return operation might vector to incorrect interrupt. */
#if defined __CORTEX_M && (__CORTEX_M == 4U)
    __DSB();
#endif
}
