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

#include "fsl_tpm.h"

void TPM0_Quadrature_Init(void) {
    tpm_config_t tpmInfo;

    /* Seleciona a fonte de clock para o TPM (Ex: 48MHz IRC48M ou OSCERCLK) */
    //CLOCK_SetTpmClock(1U);
    CLOCK_EnableClock(kCLOCK_Tpm0);
    /* Inicializa as configurações padrão do TPM */
    TPM_GetDefaultConfig(&tpmInfo);

    /* Configura o prescaler se necessário (geralmente kTPM_Prescale_Divide_1) */
    tpmInfo.prescale = kTPM_Prescale_Divide_128;
    TPM_Init(TPM0, &tpmInfo);

    /* Define o valor máximo do contador (Modulo) */
    TPM0->MOD = 255; // Contador de 0 a 255 (8 bits)

    /* Configura o Hardware para Modo Quadrature usando os canais 0 e 1 */
    /* QDCTRL: QUADEN=1 (Habilita), ENCMODE=0 (Modo Quadrature Count) */
    TPM0->QDCTRL = TPM_QDCTRL_QUADEN_MASK;

    /* Habilita a interrupção por Overflow do Contador (TOIE) se quiser monitorar limites */
    TPM_EnableInterrupts(TPM0, kTPM_TimeOverflowInterruptEnable);

    /* Ativa a interrupção no NVIC do Cortex-M0+ */
    EnableIRQ(TPM0_IRQn);

    /* Inicializa a contagem do timer */
    TPM_StartTimer(TPM0, kTPM_SystemClock);
}


/* TPM0_IRQn interrupt handler */
void TPM0_IRQHANDLER(void) {
    uint32_t intStatus;
    /* Reading all interrupt flags of status register */
    intStatus = TPM_GetStatusFlags(TPM0_PERIPHERAL);

    /* Verifica se a interrupção foi por Overflow */
   // if ((intStatus & kTPM_TimeOverflowFlag) == kTPM_TimeOverflowFlag) {
        /* Lógica para descobrir se o contador estourou subindo ou descendo */
         /* Verifica a direção atual no registrador QDCTRL */
        if (TPM0->QDCTRL & TPM_QDCTRL_QUADIR_MASK)
        {
            encoder_counter++;    /* Incrementou além de 65535 (Sentido horário) */
        }
        else
        {
            encoder_counter--;    /* Decrementou abaixo de 0 (Sentido anti-horário) */
        }
        print_flag = true;
        TPM_ClearStatusFlags(TPM0_PERIPHERAL, intStatus);
   // }
    /* Place your code here */

    /* Add for ARM errata 838869, affects Cortex-M4, Cortex-M4F
       Store immediate overlapping exception return operation might vector to incorrect interrupt. */
#if defined __CORTEX_M && (__CORTEX_M == 4U)
    __DSB();
#endif
}


/**
 * TPM0_IRQHANDLER
 *
 * Trata a interrupção do TPM0. Lê o estado atual do pino CLK do encoder e
 * detecta mudanças de borda para contabilizar passos. O valor de encoder_counter
 * é incrementado ou decrementado conforme a direção de rotação.
//  */
// void TPM0_IRQHANDLER(void) {
//     uint32_t intStatus;

//     // Limpa todas as flags de interrupção do TPM0.
//     intStatus = TPM_GetStatusFlags(TPM0_PERIPHERAL);
//     TPM_ClearStatusFlags(TPM0_PERIPHERAL, intStatus);

//     // Leitura do estado atual do sinal CLK do encoder.
//     uint32_t current_clk_state = GPIO_PinRead(ENCODER_GPIO, CLK_PIN);

//     // Detecta borda de transição no pino CLK.
//     if (current_clk_state != last_clk_state) {
//         if (current_clk_state == 0) {
//             // Determina direção comparando DT com CLK.
//             if (GPIO_PinRead(ENCODER_GPIO, DT_PIN) != current_clk_state) {
//                 encoder_counter++;
//             }
//             else {
//                 encoder_counter--;
//             }

//             // Mantém o contador dentro do intervalo válido para rotações circulares.
//             // if (encoder_counter > 16) {
//             //     encoder_counter = 0;
//             // }
//             // else if (encoder_counter < 0) {
//             //     encoder_counter = 16;
//             // }

//             // Indica que o valor mudou e deve ser exibido ou processado.
//             print_flag = true;
//         }
//     }

//     last_clk_state = current_clk_state;

//     /* Add for ARM errata 838869, affects Cortex-M4, Cortex-M4F
//        Store immediate overlapping exception return operation might vector to incorrect interrupt. */
// #if defined __CORTEX_M && (__CORTEX_M == 4U)
//     __DSB();
// #endif
// }
