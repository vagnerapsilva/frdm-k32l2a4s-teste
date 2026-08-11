/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *        TECNODEV TECNOLOGIA DE DESENVOLVIMENTIO DE SOFTWARE E SERVICOS       *
 *        TEL: (011) 4109-0577                 SITE: www.tecnodev.com.br       *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

 /* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FXOS_8700CQ_H
#define __FXOS_8700CQ_H
#include <stdio.h>
#include "board.h"
#include "fsl_debug_console.h"
#include "fsl_lpi2c.h"
#include "fsl_fxos.h"

  // Definições do barramento I2C da FRDM-K32L2
#define FXOS8700CQ_I2C_ADDRESS    0x1E // Endereço I2C padrão do FXOS8700CQ
#define ACCEL_I2C_MASTER_BUFFER_SIZE 1
#define ACCEL_I2C_PERIPHERAL LPI2C0
#define ACCEL_I2C_CLOCK_FREQ CLOCK_GetIpFreq(kCLOCK_Lpi2c0)

// Definições do periférico I2C da FRDM-K32L2 (Ajuste conforme seu Config Tools)
#define BOARD_FXOS_I2C_BASE LPI2C0
#define BOARD_FXOS_I2C_CLOCK_FREQ CLOCK_GetIpFreq(kCLOCK_Lpi2c0)

extern void FXOS_8700CQ(void);

#endif /* __FXOS_8700CQ_H */