
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
#include "fxas_21002c.h"
#include "fxos_8700cq.h"
#include "light_sensor.h"
#include "rtc.h"
#include "crc.h"
#include "rng.h"
#include "encoder_ky_040.h" // Driver do encoder rotativo KY-040
#include "usart.h" // Driver do USART
#include "led.h" // Driver do LED RGB
#include "fsl_mmcau.h"
#include "mmcau_api.h" // Driver do MMCAU
#include <stdio.h>
#include <stdbool.h>
 /*******************************************************************************
  * Definitions
  ******************************************************************************/
#define HWTIMER_PERIOD      10000U

  /*******************************************************************************
   * Prototypes
   ******************************************************************************/
   // Declaração das funções de ação do menu
void action_placeholder(void) { /* Código da ação aqui */ }
/********************************************************************************
 *  Variables
******************************************************************************/
volatile uint16_t SampleEventFlag;

extern char MSG[50];
// Definições do Display (SSD1306)
#define NUM_ITEMS 16
#define VISIBLE_LINES 4
#define FONT_HEIGHT 10


// Estrutura para os itens do menu
typedef struct {
    char name[20];
    void (*callback)(void); // Função executada ao clicar no item
} MenuItem;


// Array com os 16 itens do menu
MenuItem menu[NUM_ITEMS] = {
    {"Usart one wire", usart_one_wire_test},
    {"Usb CDC       ", action_placeholder},
    {"Giroscopio    ", teste_Giroscopio},
    {"Acelerometro  ", FXOS_8700CQ},
    {"Light Sensor  ", light_sensor_test},
    {"Push Buttons  ", action_placeholder},
    {"Led RGB       ", LED_TestRgbColors},
    {"RTC           ", menu_data_hora},
    {"Cryptografia  ", teste_mmcau},
    {"Crc           ", teste_crc},
    {"Rng           ", teste_rng},
    {"Ssd1306       ", action_placeholder},
    {"Diagnostico   ", action_placeholder},
    {"Economia Eng  ", action_placeholder},
    {"Contraste     ", action_placeholder},
    {"Sair          ", action_placeholder}
};

// Variáveis de controle do Menu
int16_t current_selection = 0;
int16_t scroll_offset = 0;
volatile int32_t last_encoder_counter = 0;

/*******************************************************************************
 * Code
 ******************************************************************************/

// static void HW_Timer_init(void)
// {
//     /* Configure the SysTick timer */
//     SysTick_Config(SystemCoreClock / HWTIMER_PERIOD);
// }

// void SysTick_Handler(void)
// {
//     SampleEventFlag = 1;
// }




//----------------------------------------------------------------------------------------------------------------------

/**
 * @brief Atualiza e renderiza o menu no display SSD1306
 */
void Menu_Display_Update(void) {
    ssd1306_Fill(Black);

    sprintf(MSG, "LIB FRDM-K32L2A4S");
    ssd1306_SetCursor(1, 0);
    ssd1306_WriteString(MSG, Font_7x10, White);


    for (int i = 0; i < VISIBLE_LINES; i++) {
        // Calcula o índice real do item baseado na janela de rolagem
        int item_index = scroll_offset + i;
        if (item_index >= NUM_ITEMS) break;

        // Define a posição Y inicial (Ex: linha 0 = 0px, linha 1 = 12px para dar espaçamento)
        uint16_t y_pos = i * (FONT_HEIGHT + 1);

        ssd1306_SetCursor(0, (y_pos + 15));

        // Se for o item selecionado, adiciona um indicador visual (Ex: ">" ou cor invertida)
        if (item_index == current_selection) {
            ssd1306_WriteString("> ", Font_7x10, 0); // 1 = Cor Branca / Ativa
            ssd1306_WriteString(menu[item_index].name, Font_7x10, 0);
        }
        else {
            ssd1306_WriteString("  ", Font_7x10, 1);
            ssd1306_WriteString(menu[item_index].name, Font_7x10, 1);
        }
    }

    ssd1306_UpdateScreen();
}

/**
 * @brief Ajusta o item selecionado do menu e atualiza a rolagem
 * @param new_selection índice do item selecionado pelo encoder
 */
void Menu_SetSelection(int16_t new_selection) {
    if (new_selection < 0) {
        new_selection = 15;
    }
    else if (new_selection >= NUM_ITEMS) {
        new_selection = 0;//NUM_ITEMS - 1;
    }

    current_selection = new_selection;

    if (current_selection < scroll_offset) {
        scroll_offset = current_selection;
    }
    else if (current_selection >= scroll_offset + VISIBLE_LINES) {
        scroll_offset = current_selection - VISIBLE_LINES + 1;
    }

    Menu_Display_Update();
}



/*!
 * @brief Main function
 */
int main(void)
{
    /* Init board hardware. */
    BOARD_InitHardware();
    BOARD_InitPeripherals();
    
    ssd1306_Init();
    
    //HW_Timer_init();
    
    ssd1306_Fill(Black);
    memset(MSG, 0xFF, 50);
    sprintf(MSG, "LIB FRDM-K32L2A4S");
    ssd1306_SetCursor(1, 0);
    ssd1306_WriteString(MSG, Font_7x10, White);
    ssd1306_UpdateScreen();
    
    //Init_Timer_1ms();
    encoder_counter = 0;


    Menu_SetSelection(0);

    /* Add user custom codes below */
    while (1)
    {
        USB_DeviceTasks();

        // O loop principal fica livre e apenas processa a exibição dos dados
        // if (print_flag) {
        //     print_flag = false;
        int32_t encoder_value = (TPM1->CNT / 4); // Ajuste para a resolução do encoder
        int32_t delta = encoder_value - last_encoder_counter;
        if (delta != 0) {
            Menu_SetSelection(current_selection + delta);
            last_encoder_counter = encoder_value;
        }
        //}

        // Verifica o clique do botão físico de forma não-bloqueante
        if (GPIO_PinRead(ENCODER_GPIO, SW_PIN) == 0) {
            // Debounce simples via software para o botão físico
            SDK_DelayAtLeastUs(10000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);

            // Confirma se o botão continua pressionado pós-debounce
            if (GPIO_PinRead(ENCODER_GPIO, SW_PIN) == 0) {
                // Aguarda o usuário soltar o botão para não registrar múltiplos cliques
                while (GPIO_PinRead(ENCODER_GPIO, SW_PIN) == 0);
                //Execute_Menu_Option();
                if (menu[current_selection].callback != NULL) {
                    menu[current_selection].callback(); // Executa a função associada
                }
                // print_flag = true; // Força a atualização do menu após a execução da opção
            }
        }


    }
}
