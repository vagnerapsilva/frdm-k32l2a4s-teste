#include "main.h"
#include "ssd1306.h"
#include "ssd1306_fonts.h"
#include <stdio.h>
#include <math.h>

/* Configurações do Display */
#include "ssd1306.h"

/* Variáveis do Encoder Rotativo */
volatile int32_t encoder_value = 0;
int32_t last_encoder_value = -1;
int32_t percentage = 0;

/* Protótipos das Funções */
void Draw_Round_ProgressBar(uint8_t x0, uint8_t y0, uint8_t radius, uint8_t thickness, uint8_t percent);
void Update_Interface(void);
void Read_Encoder(void);

/**
  * @brief  Desenha uma barra de progresso redonda pixel por pixel
  * @param  x0, y0: Centro do círculo
  * @param  radius: Raio externo da barra
  * @param  thickness: Espessura da barra (quantos pixels para dentro)
  * @param  percent: Valor de 0 a 100
  */
void Draw_Round_ProgressBar(uint8_t x0, uint8_t y0, uint8_t radius, uint8_t thickness, uint8_t percent) {
    if (percent > 100) percent = 100;

    // Converte a porcentagem para o ângulo final em radianos (360 graus = 2 * PI)
    // O mapeamento começa no topo (-PI/2) e gira no sentido horário
    float end_angle = ((float)percent / 100.0f) * (2.0f * M_PI) - (M_PI / 2.0f);
    float start_angle = -M_PI / 2.0f;

    // Desenha o fundo do círculo completo (guia cinza/suave) em formato tracejado ou fino
    for (float angle = start_angle; angle < (start_angle + 2.0f * M_PI); angle += 0.05f) {
        float x = (float)x0 + (float)radius * cosf(angle);
        float y = (float)y0 + (float)radius * sinf(angle);
        // Desenha apenas um pixel a cada 3 passos para criar um efeito de fundo elegante
        if (((int)(angle * 10) % 2) == 0) {
            ssd1306_DrawPixel((uint8_t)x, (uint8_t)y, White);
        }
    }

    // Desenha a barra de preenchimento real (com espessura)
    // Varre o ângulo do início até o ponto atual da porcentagem
    // O passo do ângulo (0.01) garante que não fiquem buracos entre os pixels
    for (float angle = start_angle; angle <= end_angle; angle += 0.01f) {
        float cos_a = cosf(angle);
        float sin_a = sinf(angle);

        // Preenche a espessura desenhando múltiplos anéis concêntricos
        for (uint8_t t = 0; t < thickness; t++) {
            uint8_t current_radius = radius - t;
            uint8_t x = (uint8_t)((float)x0 + (float)current_radius * cos_a);
            uint8_t y = (uint8_t)((float)y0 + (float)current_radius * sin_a);
            
            ssd1306_DrawPixel(x, y, White);
        }
    }
}

/**
  * @brief  Atualiza os elementos gráficos na tela
  */
void Update_Interface(void) {
    char txt_buffer[8];

    // Limpa o buffer interno da tela sem apagar de forma brusca
    ssd1306_Fill(Black);

    // Desenha a Barra Redonda: Centro (36, 32), Raio 26, Espessura de 4 pixels
    Draw_Round_ProgressBar(36, 32, 26, 4, percentage);

    // Formata o texto da porcentagem (Ex: "100%")
    snprintf(txt_buffer, sizeof(txt_buffer), "%ld%%", (long)percentage);

    // Centraliza e desenha o texto ao lado direito da barra redonda
    ssd1306_SetCursor(75, 24);
    ssd1306_WriteString(txt_buffer, Font_11x18, White);

    // Envia o buffer renderizado para o display físico via I2C
    ssd1306_UpdateScreen();
}

/**
  * @brief  Lê e processa os dados do Encoder (Chamar no loop ou interrupção)
  */
void Read_Encoder(void) {
    // Exemplo usando o Modo Encoder do TIMER do STM32 (TIMx->CNT)
    // Caso use leitura manual por GPIO (Interrupção), ajuste esta variável
    encoder_value = __HAL_TIM_GET_COUNTER(&htim2) / 2; // Dividido por 2 se o encoder der 2 pulsos por clique

    // Restringe os limites entre 0 e 100
    if (encoder_value < 0) {
        encoder_value = 0;
        __HAL_TIM_SET_COUNTER(&htim2, 0);
    } else if (encoder_value > 100) {
        encoder_value = 100;
        __HAL_TIM_SET_COUNTER(&htim2, 100 * 2);
    }

    percentage = encoder_value;
}

/**
  * @brief  Ponto de entrada do aplicativo
  */
int main(void) {
    // Inicialização do Hardware (Gerado automaticamente pelo STM32CubeMX)
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_I2C1_Init();
    MX_TIM2_Init(); // Configurado em Modo Encoder

    // Inicializa o display OLED SSD1306
    ssd1306_Init();
    
    // Inicia o Timer do Encoder
    HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_ALL);

    // Força a primeira renderização da tela
    Update_Interface();

    while (1) {
        // Atualiza a leitura do encoder
        Read_Encoder();

        // Só atualiza a tela se o valor tiver mudado (Evita flickering e uso excessivo do I2C)
        if (percentage != last_encoder_value) {
            last_encoder_value = percentage;
            Update_Interface();
        }

        HAL_Delay(10); // Pequeno delay para estabilidade do sistema
    }
}