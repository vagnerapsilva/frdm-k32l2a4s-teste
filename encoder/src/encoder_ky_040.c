/*******************************************************************************
 *        TECNODEV TECNOLOGIA DE DESENVOLVIMENTIO DE SOFTWARE E SERVICOS       *
 *        TEL: (011) 4109-0577                 SITE: www.tecnodev.com.br       *
 * encoder_ky_040.c                                                            *
 *                                                                             *
 * Implementação do suporte ao encoder rotativo KY-040.                       *
 *                                                                             *
 * Este arquivo encapsula a lógica de leitura do encoder mecânico, o monitor- *
 * amento do seu botão de pressão e a atualização visual de um indicador de     *
 * progresso em um display SSD1306. O objetivo principal é transformar o giro   *
 * do encoder em um valor escalonado de 0 a 100, utilizado para controlar uma   *
 * barra circular e mostrar a porcentagem na tela.                              *
 *                                                                             *
 * O módulo usa o periférico TPM em modo quadratura para capturar a rotação do  *
 * encoder e o botão SW_PIN para detectar clique. O valor lido é processado em  *
 * tempo real no laço principal e, quando há mudança, a interface gráfica é      *
 * renderizada novamente no display.                                            *
 *                                                                             *
 * Fluxo geral do arquivo:                                                     *
 *   1. Inicializa o timer do módulo TPM em modo quadratura.                   *
 *   2. Intercepta o evento de overflow/rotação do encoder na interrupção.      *
 *   3. Atualiza o contador e sinaliza mudança para o laço principal.          *
 *   4. O laço principal lê o valor do contador e converte em percentual.      *
 *   5. Desenha a barra circular e o texto percentual no SSD1306.               *
 *                                                                             *
 * Observação: a lógica atual combina leitura por hardware e renderização em     *
 * software para propor um protótipo funcional de menu/controle, mas ainda pode *
 * sofrer ajustes finos de calibração conforme a resolução física do encoder.   *
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
#include "ssd1306.h"
#include "ssd1306_fonts.h"
#include <math.h>

 /*******************************************************************************
  * Definitions
  ******************************************************************************/


  /*******************************************************************************
   * Variables
   ******************************************************************************/
   /*
    * A estrutura de estado deste módulo é composta por variáveis globais porque:
    *   - a interrupção precisa atualizar o valor de rotação sem depender do loop;
    *   - a rotina principal precisa consultar o estado atual de forma simples;
    *   - a tela precisa refletir o último valor convertido para porcentagem.
    */

    /* Valor bruto de leitura do encoder convertido em escala interna da aplicação. */
volatile int32_t encoder_value = 0;

/* Armazena o último valor processado para detectar variação e evitar re-renderização redundante. */
int32_t last_encoder_value = -1;

/* Percentual da barra de progresso, mapeado de 0 a 100. */
int32_t percentage = 0;

/*
 * Contador incremental de passos do encoder.
 * A interrupção incrementa ou decrementa esse valor conforme a direção da rotação.
 */
volatile int32_t encoder_counter = 0;

/*
 * Histórico do estado anterior do clock.
 * Embora o código atual não use essa variável diretamente em lógica de borda, ela
 * representa o conceito clássico de detecção de transição do sinal do encoder.
 */
volatile uint32_t last_clk_state = 0;

/*
 * Sinaliza ao laço principal que houve mudança no estado do encoder.
 * Funciona como um gatilho para disparar atualização da interface gráfica.
 */
volatile bool print_flag = false;


/*******************************************************************************
 * Protótipos das Funções
 ******************************************************************************/
void Draw_Round_ProgressBar(uint8_t x0, uint8_t y0, uint8_t radius, uint8_t thickness, uint8_t percent);
void Update_Interface(void);
void Read_Encoder(void);

/*******************************************************************************
 * Code
 ******************************************************************************/




 /*******************************************************************************
  * @brief Inicializa o módulo TPM em modo quadratura para capturar rotação do encoder.
  *
  * A rotina configura o periférico TPM0 para operar em modo de contagem por quadratura,
  * que é um padrão comum em encoders rotativos. Essa técnica usa duas saídas em fase
  * defasada (normalmente CLK e DT) para detectar a direção da rotação e o número de
  * passos. A contagem é ajustada para que o software consiga interpretar eventos sem
  * precisar ler diretamente os pinos em tempo real a cada iteração.
  *
  * No Kinetis, o TPM pode ser usado em modo quadratura com o registrador QDCTRL. O bit
  * QUADEN habilita a funcionalidade e a direção da contagem pode ser inferida por meio
  * do bit QUADIR. O módulo também recebe uma configuração de prescaler para reduzir a
  * resolução do clock e manter o processamento estável.
  *******************************************************************************/
void TPM0_Quadrature_Init(void) {
    tpm_config_t tpmInfo;

    /* Habilita o clock do periférico TPM0. */
    CLOCK_EnableClock(kCLOCK_Tpm0);

    /* Carrega a configuração padrão do periférico antes de personalizar. */
    TPM_GetDefaultConfig(&tpmInfo);

    /*
     * Prescaler reduz a frequência do contador para estabilizar a leitura do encoder.
     * Um valor maior diminui a sensibilidade ao ruído e evita contagens excessivas.
     */
    tpmInfo.prescale = kTPM_Prescale_Divide_128;
    TPM_Init(TPM0, &tpmInfo);

    /*
     * Define o módulo do contador.
     * Com MOD = 255, o contador opera em um intervalo de 0 a 255 e pode gerar eventos
     * de overflow quando se desloca de um extremo para o outro.
     */
    TPM0->MOD = 255;

    /*
     * Habilita o modo quadratura.
     * QDCTRL_QUADEN_MASK ativa a funcionalidade de contagem por quadratura,
     * enquanto ENCMODE define o comportamento da contagem.
     */
    TPM0->QDCTRL = TPM_QDCTRL_QUADEN_MASK;

    /*
     * Habilita interrupção por overflow.
     * Essa interrupção permite tratar variações e direção da rotação no firmware.
     */
    TPM_EnableInterrupts(TPM0, kTPM_TimeOverflowInterruptEnable);

    /* Ativa a interrupção do TPM no NVIC. */
    EnableIRQ(TPM0_IRQn);

    /* Inicia a contagem do timer. */
    TPM_StartTimer(TPM0, kTPM_SystemClock);
}


/*******************************************************************************
 * @brief Manipula a interrupção do periférico TPM0.
 *
 * A função é chamada sempre que o TPM gera evento de interrupção. Neste módulo, a
 * rotação do encoder é tratada como uma contagem por quadratura, em que a direção da
 * leitura pode ser inferida pelo bit QUADIR do registro QDCTRL.
 *
 * Em termos práticos:
 *   - se QUADIR indica rotação em um sentido, o contador é incrementado;
 *   - se a rotação é no sentido oposto, o contador é decrementado;
 *   - a flag print_flag informa ao laço principal que o valor mudou e que a UI deve
 *     ser renderizada novamente.
 *
 * Essa abordagem evita que o processo principal precise bloquear ou fazer polling
 * contínuo do pino do encoder, mantendo o firmware mais responsivo e eficiente.
 *******************************************************************************/
void TPM0_IRQHANDLER(void) {
    uint32_t intStatus;

    /* Obtém as flags de interrupção pendentes do módulo TPM0. */
    intStatus = TPM_GetStatusFlags(TPM0_PERIPHERAL);

    /*
     * A lógica de direção é definida pelo bit QUADIR.
     * Quando este bit está ativo, a contagem está ocorrendo em um sentido;
     * quando está inativo, o sentido é oposto.
     */
    if (TPM0->QDCTRL & TPM_QDCTRL_QUADIR_MASK)
    {
        /* Sentido horário: o contador cresce. */
        encoder_counter++;
    }
    else
    {
        /* Sentido anti-horário: o contador decresce. */
        encoder_counter--;
    }

    /* Informa ao laço principal que houve alteração no estado do encoder. */
    print_flag = true;

    /* Limpa a flag de interrupção para liberar o periférico para novos eventos. */
    TPM_ClearStatusFlags(TPM0_PERIPHERAL, intStatus);

    /*
     * A instrução __DSB() é mantida como referência do errata do ARM para dispositivos
     * Cortex-M4/CM4F em casos de sobreposição de pilha de exceção.
     */
#if defined __CORTEX_M && (__CORTEX_M == 4U)
    __DSB();
#endif
}




/*******************************************************************************
 * @brief Desenha a barra circular de progresso com base na porcentagem atual.
 *
 * A função usa geometria trigonométrica para converter um valor percentual em um arco
 * circular. O centro da barra é definido por (x0, y0), o raio pelos pixels externos e
 * a espessura pela profundidade do traço em direção ao centro do círculo.
 *
 * A lógica é composta por dois passos:
 *   1. o fundo do círculo é desenhado como guia visual;
 *   2. um arco crescente é desenhado até o ângulo correspondente à porcentagem.
 *
 * O uso de sin() e cos() permite que cada ponto do círculo seja calculado em coordenadas
 * cartesianas, facilitando a varredura do arco de forma contínua.
 *******************************************************************************/
void Draw_Round_ProgressBar(uint8_t x0, uint8_t y0, uint8_t radius, uint8_t thickness, uint8_t percent) {
    if (percent > 100) percent = 100;

    /*
     * Converte o percentual em um ângulo final.
     * A escala começa em -90° e percorre 360° no sentido horário.
     * O cálculo faz a barra crescer a partir do topo do círculo.
     */
    float end_angle = ((float)percent / 100.0f) * (2.0f * M_PI) - (M_PI / 2.0f);
    float start_angle = -M_PI / 2.0f;

    /* Primeiro, desenha um fundo circular para servir de referência visual. */
    for (float angle = start_angle; angle < (start_angle + 2.0f * M_PI); angle += 0.05f) {
        float x = (float)x0 + (float)radius * cosf(angle);
        float y = (float)y0 + (float)radius * sinf(angle);

        /* Desenha apenas parte dos pixels para criar um efeito mais leve e elegante. */
        if (((int)(angle * 10) % 2) == 0) {
            ssd1306_DrawPixel((uint8_t)x, (uint8_t)y, White);
        }
    }

    /*
     * Em seguida, traça o arco ativo da barra até o ângulo definido pela porcentagem.
     * A espessura é produzida desenhando vários raios concêntricos internos.
     */
    for (float angle = start_angle; angle <= end_angle; angle += 0.01f) {
        float cos_a = cosf(angle);
        float sin_a = sinf(angle);

        for (uint8_t t = 0; t < thickness; t++) {
            uint8_t current_radius = radius - t;
            uint8_t x = (uint8_t)((float)x0 + (float)current_radius * cos_a);
            uint8_t y = (uint8_t)((float)y0 + (float)current_radius * sin_a);

            ssd1306_DrawPixel(x, y, White);
        }
    }
}

/*******************************************************************************
 * @brief Atualiza a interface gráfica da tela OLED com a porcentagem atual.
 *
 * A função limpa o framebuffer do SSD1306, redesenha a barra circular e centraliza
 * o valor numérico da porcentagem dentro do círculo. O texto é renderizado com a fonte
 * 11x18 para melhorar legibilidade e peso visual da interface.
 *******************************************************************************/
void Update_Interface(void) {
    char txt_buffer[8];
    int text_len;
    int text_width;
    int text_x;
    int text_y;

    /* Redefine o conteúdo da tela para um estado limpo antes de desenhar a nova imagem. */
    ssd1306_Fill(Black);

    /* Desenha a barra circular com o percentual atual armazenado em 'percentage'. */
    Draw_Round_ProgressBar(36, 32, 26, 4, percentage);

    /*
     * Formata a percentual em texto como "100%".
     * O buffer foi dimensionado para 8 bytes para comportar números até 999% e o sinal %.
     */
    snprintf(txt_buffer, sizeof(txt_buffer), "%d%%", (int)percentage);
    text_len = strlen(txt_buffer);
    text_width = text_len * 11; /* Aproximação da largura da fonte 11x18. */
    text_x = 36 - (text_width / 2);
    text_y = 32 - (18 / 2);

    /* Posiciona o texto em torno do centro do círculo. */
    ssd1306_SetCursor((uint8_t)text_x, (uint8_t)text_y);
    ssd1306_WriteString(txt_buffer, Font_11x18, White);

    /* Envia o buffer para o display físico. */
    ssd1306_UpdateScreen();
}

/*******************************************************************************
 * @brief Lê o valor atual do encoder e converte para o intervalo 0..100.
 *
 * A leitura usa o contador do periférico TPM1 e divide por 4 para refletir a resolução
 * do encoder. Esse ajuste é comum quando cada clique do encoder produz 4 pulsos no timer
 * ou quando a contagem interna demanda uma escala menor para uso em UI.
 *
 * Depois da leitura, os limites são ajustados para impedir valores negativos ou acima de
 * 100%, evitando que a barra fique fora da escala da interface.
 *******************************************************************************/
void Read_Encoder(void) {
    /*
     * Leitura do valor bruto do encoder.
     * O ajuste por 4 foi definido para mapear a resolução observada do hardware.
     */
    encoder_value = (TPM1->CNT / 4);

    /* Limita o contador inferior em zero. */
    if (encoder_value < 0) {
        encoder_value = 0;
        TPM1->CNT = 0;
    }
    else if (encoder_value > 100) {
        /* Limita o contador superior em 100%. */
        encoder_value = 100;
        TPM1->CNT = 100 * 4;
    }

    /* Atualiza a variável global usada pela interface. */
    percentage = encoder_value;
}



/*******************************************************************************
 * @brief Função de teste do encoder e do botão de pressão.
 *
 * Este laço principal implementa um modo de validação simples do hardware:
 *   - lê o valor atual do encoder em tempo real;
 *   - atualiza a UI apenas quando o percentual muda;
 *   - verifica o botão do encoder (SW_PIN) com debounce simples;
 *   - reinicia o sistema quando o botão é pressionado e liberado.
 *
 * O objetivo é servir como ponto de ensaio para confirmar que o encoder está gerando
 * variações consistentes, que a barra circular acompanha o valor corretamente e que o
 * botão de clique funciona sem múltiplos disparos por ruído ou bouncing.
 *******************************************************************************/
void teste_encoder(void)
{
    while (1)
    {
        /* Atualiza a leitura do encoder a cada ciclo de execução. */
        Read_Encoder();

        /*
         * Só redesenha a tela quando o valor efetivamente mudou.
         * Isso evita flicker, reduz uso de I2C e melhora a responsividade geral.
         */
        if (percentage != last_encoder_value) {
            last_encoder_value = percentage;
            Update_Interface();
        }

        /* Pequeno atraso para estabilizar a leitura do hardware. */
        SDK_DelayAtLeastUs(10000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);

        /*
         * Verifica pressionamento do botão do encoder.
         * A rotina faz duas leituras com debounce para evitar disparos falsos.
         */
        if (GPIO_PinRead(ENCODER_GPIO, SW_PIN) == 0) {
            SDK_DelayAtLeastUs(10000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);

            if (GPIO_PinRead(ENCODER_GPIO, SW_PIN) == 0) {
                /* Espera o usuário soltar o botão para registrar um único clique. */
                while (GPIO_PinRead(ENCODER_GPIO, SW_PIN) == 0);

                /*
                 * A ação final de teste aqui é reiniciar o sistema.
                 * Em um projeto final, essa chamada poderia disparar outra rotina,
                 * como confirmar seleção, abrir menu ou executar uma ação específica.
                 */
                __NVIC_SystemReset();
            }
        }
    }
}