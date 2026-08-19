/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *        TECNODEV TECNOLOGIA DE DESENVOLVIMENTIO DE SOFTWARE E SERVICOS       *
 *        TEL: (011) 4109-0577                 SITE: www.tecnodev.com.br       *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

 /* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ENCODER_KY_040_H
#define __ENCODER_KY_040_H
#include <stdio.h>
#include "board.h"
#include "fsl_debug_console.h"
#include "fsl_lpi2c.h"
#include "fsl_fxas.h"

#define ENCODER_PORT        PORTA
#define ENCODER_GPIO        GPIOA
#define CLK_PIN             16U
#define DT_PIN              15U
#define SW_PIN              17U

// Estados do Menu
typedef enum {
    OPCAO_1 = 0,
    OPCAO_2,
    OPCAO_3,
    TOTAL_OPCOES
} menu_options_t;

extern volatile int32_t encoder_counter;
extern volatile uint32_t last_clk_state;
extern volatile bool print_flag;
extern void teste_encoder(void);


#endif /* __ENCODER_KY_040_H */
