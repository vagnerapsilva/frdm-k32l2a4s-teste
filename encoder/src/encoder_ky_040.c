/*******************************************************************************
 *        TECNODEV TECNOLOGIA DE DESENVOLVIMENTIO DE SOFTWARE E SERVICOS       *
 *        TEL: (011) 4109-0577                 SITE: www.tecnodev.com.br       *
 * encoder_ky_040.c                                                            *
 *                                                                             *
 * Implementação do suporte ao encoder rotativo KY-040.                        *
 *                                                                             *
 * O arquivo inicializa um timer de 1 ms usando LPIT e processa alterações de  *
 * borda no sinal CLK do encoder dentro do interrupt handler TPM0.             *
 ******************************************************************************/
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

  // Identifica o módulo LPIT e o canal usado para gerar um intervalo de 1 ms.
#define ENCODER_LPIT_BASE   LPIT0
#define ENCODER_LPIT_CH     kLPIT_Chnl_0
#define LPIT_IRQ_HANDLER    LPIT0_IRQHandler
#define LPIT_IRQ_NUM        LPIT0_IRQn

/*******************************************************************************
 * Variables
 ******************************************************************************/

 // Contador de passos do encoder. Incrementado ou decrementado na interrupção.
volatile int32_t encoder_counter = 0;

// Estado anterior do pino CLK do encoder para detectar bordas.
volatile uint32_t last_clk_state = 0;

// Flag utilizada para avisar o loop principal que o valor mudou.
volatile bool print_flag = false;

/*******************************************************************************
 * Code
 ******************************************************************************/

 /**
  * Init_Timer_1ms
  *
  * Inicializa o temporizador LPIT para gerar uma interrupção periódica a cada
  * 1 milissegundo. Este timer pode ser usado para amostrar o encoder de forma
  * consistente ou para outras tarefas periódicas no aplicativo.
  */
void Init_Timer_1ms(void) {
    lpit_config_t lpitConfig;
    lpit_chnl_params_t lpitChannelConfig; // Configurações do canal de timer

    // Habilita o clock do periférico LPIT.
    CLOCK_EnableClock(kCLOCK_Lpit0);

    // Obtém a configuração padrão do LPIT e habilita operação durante debug.
    LPIT_GetDefaultConfig(&lpitConfig);
    lpitConfig.enableRunInDebug = true; // Permite manter o timer ativo ao pausar o debugger
    LPIT_Init(ENCODER_LPIT_BASE, &lpitConfig);

    // Configura o canal de timer para modo periódico com trigger interno.
    lpitChannelConfig.chainChannel = false;
    lpitChannelConfig.timerMode = kLPIT_PeriodicCounter;
    lpitChannelConfig.triggerSource = kLPIT_TriggerSource_Internal;
    lpitChannelConfig.triggerSelect = kLPIT_Trigger_TimerChn0;
    lpitChannelConfig.enableReloadOnTrigger = false;
    lpitChannelConfig.enableStopOnTimeout = false;
    lpitChannelConfig.enableStartOnTrigger = false;

    LPIT_SetupChannel(ENCODER_LPIT_BASE, ENCODER_LPIT_CH, &lpitChannelConfig);

    // Define o período do timer para 1 ms usando a frequência do clock do LPIT.
    uint32_t lpitSrcClock_Hz = CLOCK_GetIpFreq(kCLOCK_Lpit0);
    LPIT_SetTimerPeriod(ENCODER_LPIT_BASE, ENCODER_LPIT_CH, USEC_TO_COUNT(1000U, lpitSrcClock_Hz));

    // Habilita interrupção do canal e registra no NVIC.
    LPIT_EnableInterrupts(ENCODER_LPIT_BASE, kLPIT_Channel0TimerInterruptEnable);
    EnableIRQ(LPIT_IRQ_NUM);

    // Inicia a contagem periódica.
    LPIT_StartTimer(ENCODER_LPIT_BASE, ENCODER_LPIT_CH);
}

/**
 * TPM0_IRQHANDLER
 *
 * Trata a interrupção do TPM0. Lê o estado atual do pino CLK do encoder e
 * detecta mudanças de borda para contabilizar passos. O valor de encoder_counter
 * é incrementado ou decrementado conforme a direção de rotação.
 */
void TPM0_IRQHANDLER(void) {
    uint32_t intStatus;

    // Limpa todas as flags de interrupção do TPM0.
    intStatus = TPM_GetStatusFlags(TPM0_PERIPHERAL);
    TPM_ClearStatusFlags(TPM0_PERIPHERAL, intStatus);

    // Leitura do estado atual do sinal CLK do encoder.
    uint32_t current_clk_state = GPIO_PinRead(ENCODER_GPIO, CLK_PIN);

    // Detecta borda de transição no pino CLK.
    if (current_clk_state != last_clk_state) {
        if (current_clk_state == 0) {
            // Determina direção comparando DT com CLK.
            if (GPIO_PinRead(ENCODER_GPIO, DT_PIN) != current_clk_state) {
                encoder_counter++;
            }
            else {
                encoder_counter--;
            }

            // Mantém o contador dentro do intervalo válido para rotações circulares.
            if (encoder_counter > 16) {
                encoder_counter = 0;
            }
            else if (encoder_counter < 0) {
                encoder_counter = 16;
            }

            // Indica que o valor mudou e deve ser exibido ou processado.
            print_flag = true;
        }
    }

    last_clk_state = current_clk_state;

    /* Add for ARM errata 838869, affects Cortex-M4, Cortex-M4F
       Store immediate overlapping exception return operation might vector to incorrect interrupt. */
#if defined __CORTEX_M && (__CORTEX_M == 4U)
    __DSB();
#endif
}
