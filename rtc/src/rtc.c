/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *        TECNODEV TECNOLOGIA DE DESENVOLVIMENTIO DE SOFTWARE E SERVICOS       *
 *        TEL: (011) 4109-0577                 SITE: www.tecnodev.com.br       *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include <stdio.h>
#include "rtc.h"
#include "fsl_lpuart.h"
#include "ssd1306.h"
#include "ssd1306_fonts.h"
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
extern int16_t current_selection;

extern volatile int32_t last_encoder_counter;

/*******************************************************************************
* Code.
******************************************************************************/
int32_t ENCODER_LerGiro(void)
{
    int32_t ret = 0;

    int32_t encoder_value = (TPM1->CNT / 4); // Ajuste para a resolução do encoder
    int32_t delta = encoder_value - last_encoder_counter;
    if (delta != 0) {
        ret = current_selection + delta;
        last_encoder_counter = encoder_value;
    }

    return ret;
}

int32_t ENCODER_LerClique(void) {

    // Verifica o clique do botão físico de forma não-bloqueante
    if (GPIO_PinRead(ENCODER_GPIO, SW_PIN) == 0) {
        // Debounce simples via software para o botão físico
        SDK_DelayAtLeastUs(10000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);

        // Confirma se o botão continua pressionado pós-debounce
        if (GPIO_PinRead(ENCODER_GPIO, SW_PIN) == 0) {
            // Aguarda o usuário soltar o botão para não registrar múltiplos cliques
            while (GPIO_PinRead(ENCODER_GPIO, SW_PIN) == 0);
            return 1; // Botão pressionado
        }
    }
    return 0; // Botão não pressionado  

}

void ajustar_data_hora(rtc_datetime_t* dt) {
    edit_state_t estado = EDIT_DAY;
    bool atualiza_display = true;
    char buffer[32];

    // Variáveis para armazenar a leitura do encoder
    int32_t clique_encoder = 0;
    int32_t giro_encoder = 0;

    while (estado != EDIT_SAVE) {

        // 1. LEITURA DOS HARDWARES (Substitua pelas suas funções da FRDM-K32)
        // giro_encoder deve retornar: -1 (anti-horário), 1 (horário) ou 0 (parado)
        giro_encoder = ENCODER_LerGiro();
        current_selection = giro_encoder;
        // clique_encoder deve retornar: 1 se o botão foi pressionado, 0 se não
        clique_encoder = ENCODER_LerClique();

        // 2. PROCESSAMENTO DO BOTÃO (Mudança de Campo)
        if (clique_encoder) {
            clique_encoder = 0; // ZERA IMEDIATAMENTE a variável global/volátil
            estado++; // Avança para o próximo campo
            atualiza_display = true;
            clique_encoder = 0;
            // Delay simples para debounce do botão
            SDK_DelayAtLeastUs(100000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
        }

        // 3. PROCESSAMENTO DO GIRO (Alteração dos Valores)
        if (giro_encoder != 0) {
            atualiza_display = true;

            switch (estado) {
            case EDIT_DAY:
                dt->day += giro_encoder;
                if (dt->day < 1) dt->day = 31;
                if (dt->day > 31) dt->day = 1; // Simplificado (sem validação de mês bissexto)
                break;

            case EDIT_MONTH:
                dt->month += giro_encoder;
                if (dt->month < 1) dt->month = 12;
                if (dt->month > 12) dt->month = 1;
                break;

            case EDIT_YEAR:
                dt->year += giro_encoder;
                if (dt->year < 2000) dt->year = 2099;
                if (dt->year > 2099) dt->year = 2000;
                break;

            case EDIT_HOUR:
                dt->hour += giro_encoder;
                if (dt->hour > 23) dt->hour = 23; // Se for menor que 0, vira 255 (uint8_t)
                if (dt->hour == 255) dt->hour = 23;
                if (dt->hour > 23) dt->hour = 0;
                break;

            case EDIT_MINUTE:
                dt->minute += giro_encoder;
                if (dt->minute == 255) dt->minute = 59;
                if (dt->minute > 59) dt->minute = 0;
                break;

            default:
                break;
            }
            giro_encoder = 0; // Reseta a leitura do giro
        }

        // 4. ATUALIZAÇÃO DO DISPLAY SSD1306
        if (atualiza_display) {
            atualiza_display = false;

            // Limpa o buffer do display (Função típica da biblioteca SSD1306)
            ssd1306_Fill(Black);

            // Renderiza o título
            ssd1306_SetCursor(0, 0);
            ssd1306_WriteString("Ajustar Data/Hora", Font_7x10, White);

            // Formata a string de Data: DD/MM/AAAA
            snprintf(buffer, sizeof(buffer), "Data: %02d/%02d/%04d", dt->day, dt->month, dt->year);
            ssd1306_SetCursor(0, 20);
            ssd1306_WriteString(buffer, Font_7x10, White);

            // Formata a string de Hora: HH:MM
            snprintf(buffer, sizeof(buffer), "Hora: %02d:%02d", dt->hour, dt->minute);
            ssd1306_SetCursor(0, 35);
            ssd1306_WriteString(buffer, Font_7x10, White);

            // Desenha um indicador visual (sublinhado ou seta) no campo ativo
            // Baseado no espaçamento da Font_7x10 (7 pixels de largura por caractere)
            ssd1306_SetCursor(0, 50);
            switch (estado) {
            case EDIT_DAY:    ssd1306_WriteString("Ajustando: DIA", Font_7x10, White); break;
            case EDIT_MONTH:  ssd1306_WriteString("Ajustando: MES", Font_7x10, White); break;
            case EDIT_YEAR:   ssd1306_WriteString("Ajustando: ANO", Font_7x10, White); break;
            case EDIT_HOUR:   ssd1306_WriteString("Ajustando: HORA", Font_7x10, White); break;
            case EDIT_MINUTE: ssd1306_WriteString("Ajustando: MIN", Font_7x10, White); break;
            default: break;
            }

            // Atualiza o display físico com os novos dados do buffer
            ssd1306_UpdateScreen();
        }
    }
    /* RTC time counter has to be stopped before setting the date & time in the TSR register */
    RTC_StopTimer(RTC);
    // Salva os dados no periférico RTC da FRDM-K32 aqui se necessário
    RTC_SetDatetime(RTC, dt);
    RTC_StartTimer(RTC);
}

void ajustar_rtc(void)
{
    rtc_datetime_t date;
    RTC_GetDatetime(RTC, &date);
    ajustar_data_hora(&date);
    RTC_SetDatetime(RTC, &date);
}

void mostrar_data_hora(void)
{
    rtc_datetime_t date;
    char buffer[32];
    bool sair = false;

    while (!sair) {
        // Lê a data/hora atual do RTC
        RTC_GetDatetime(RTC, &date);

        // Leitura do encoder
        int32_t clique_encoder = ENCODER_LerClique();

        if (clique_encoder) {
            sair = true; // Sai ao pressionar o botão
        }

        // Atualiza o display SSD1306
        ssd1306_Fill(Black);

        // Título
        ssd1306_SetCursor(0, 0);
        ssd1306_WriteString("Data e Hora Atual", Font_7x10, White);

        // Formata e exibe Data: DD/MM/AAAA
        snprintf(buffer, sizeof(buffer), "Data: %02d/%02d/%04d", date.day, date.month, date.year);
        ssd1306_SetCursor(0, 20);
        ssd1306_WriteString(buffer, Font_7x10, White);

        // Formata e exibe Hora: HH:MM:SS
        snprintf(buffer, sizeof(buffer), "Hora: %02d:%02d:%02d", date.hour, date.minute, date.second);
        ssd1306_SetCursor(0, 35);
        ssd1306_WriteString(buffer, Font_7x10, White);

        // Instrução de saída
        ssd1306_SetCursor(0, 50);
        ssd1306_WriteString("Clique para sair", Font_7x10, White);

        // Atualiza o display
        ssd1306_UpdateScreen();

        // Delay pequeno para não sobrecarregar a CPU
        SDK_DelayAtLeastUs(100000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
    }
}

void menu_data_hora(void)
{
    menu_state_t menu_estado = MENU_MOSTRAR;
    bool sair_menu = false;
    int32_t giro_encoder = 0;
    int32_t clique_encoder = 0;

    while (!sair_menu) {
        // Leitura do encoder
        giro_encoder = ENCODER_LerGiro();
        current_selection = giro_encoder;
        clique_encoder = ENCODER_LerClique();

        // Processamento do giro para navegar entre as opções
        if (giro_encoder != 0) {
            menu_estado += giro_encoder;

            // Wrap-around das opções
            if (menu_estado < MENU_MOSTRAR) {
                menu_estado = MENU_SAIR;
            }
            if (menu_estado > MENU_SAIR) {
                menu_estado = MENU_MOSTRAR;
            }
        }

        // Processamento do clique
        if (clique_encoder) {
            switch (menu_estado) {
            case MENU_MOSTRAR:
                mostrar_data_hora();
                break;
            case MENU_AJUSTAR:
                ajustar_rtc();
                break;
            case MENU_SAIR:
                sair_menu = true;
                break;
            default:
                break;
            }
            clique_encoder = 0;
            // Delay para debounce
            SDK_DelayAtLeastUs(100000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
        }

        // Atualiza o display SSD1306
        ssd1306_Fill(Black);

        // Título
        ssd1306_SetCursor(0, 0);
        ssd1306_WriteString("Menu Data/Hora", Font_7x10, White);

        // Opção 1: Mostrar
        ssd1306_SetCursor(0, 20);
        if (menu_estado == MENU_MOSTRAR) {
            ssd1306_WriteString("> Mostrar", Font_7x10, White);
        }
        else {
            ssd1306_WriteString("  Mostrar", Font_7x10, White);
        }

        // Opção 2: Ajustar
        ssd1306_SetCursor(0, 32);
        if (menu_estado == MENU_AJUSTAR) {
            ssd1306_WriteString("> Ajustar", Font_7x10, White);
        }
        else {
            ssd1306_WriteString("  Ajustar", Font_7x10, White);
        }

        // Opção 3: Sair
        ssd1306_SetCursor(0, 44);
        if (menu_estado == MENU_SAIR) {
            ssd1306_WriteString("> Sair", Font_7x10, White);
        }
        else {
            ssd1306_WriteString("  Sair", Font_7x10, White);
        }

        // Instrução de uso
        ssd1306_SetCursor(0, 56);
        ssd1306_WriteString("Gire/Clique para selecionar", Font_7x10, White);

        // Atualiza o display
        ssd1306_UpdateScreen();

        // Delay pequeno para não sobrecarregar a CPU
        SDK_DelayAtLeastUs(100000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
    }
}