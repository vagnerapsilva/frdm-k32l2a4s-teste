/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *        TECNODEV TECNOLOGIA DE DESENVOLVIMENTIO DE SOFTWARE E SERVICOS       *
 *        TEL: (011) 4109-0577                 SITE: www.tecnodev.com.br       *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

 /* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FXAS_21002C_H
#define __FXAS_21002C_H
#include <stdio.h>
#include "board.h"
#include "fsl_debug_console.h"
#include "fsl_lpi2c.h"
#include "fsl_fxas.h"

  // Definições do barramento I2C da FRDM-K32L2
#define FXAS21002_I2C_ADDRESS    0x20 // Endereço I2C padrão do FXAS21002

// Declaração das estruturas necessárias
extern fxas_handle_t fxasHandle;
extern fxas_config_t fxasConfig;
extern fxas_data_t sensorData;

// Definições do periférico I2C da FRDM-K32L2 (Ajuste conforme seu Config Tools)
#define BOARD_FXAS_I2C_BASE LPI2C0
#define BOARD_FXAS_I2C_CLOCK_FREQ CLOCK_GetIpFreq(kCLOCK_Lpi2c0)

extern status_t FXAS_21002c_Init(void);

#endif /* __FXAS_21002C_H */