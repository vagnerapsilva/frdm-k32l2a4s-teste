/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *        TECNODEV TECNOLOGIA DE DESENVOLVIMENTIO DE SOFTWARE E SERVICOS       *
 *        TEL: (011) 4109-0577                 SITE: www.tecnodev.com.br       *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include "fxas_21002c.h"

 /*******************************************************************************
  * Definitions
  ******************************************************************************/

  /*******************************************************************************
   * Prototypes
   ******************************************************************************/

   /*******************************************************************************
   * Variables
   ******************************************************************************/
fxas_handle_t fxasHandle;
fxas_config_t fxasConfig;
fxas_data_t sensorData;
/*******************************************************************************
 * Code
 ******************************************************************************/

 // Função adaptadora para Envio I2C exigida pelo fxas_config_t
status_t FXAS_I2C_Send(uint8_t deviceAddress, uint32_t subAddress, uint8_t subaddressSize, uint32_t txBuff)
{
    uint8_t data = (uint8_t)txBuff;
    lpi2c_master_transfer_t xfer = { 0 };

    xfer.slaveAddress = deviceAddress;
    xfer.direction = kLPI2C_Write;
    xfer.subaddress = subAddress;
    xfer.subaddressSize = subaddressSize;
    xfer.data = &data;
    xfer.dataSize = 1;
    xfer.flags = kLPI2C_TransferDefaultFlag;

    return LPI2C_MasterTransferBlocking(BOARD_FXAS_I2C_BASE, &xfer);
}

// Função adaptadora para Recepção I2C exigida pelo fxas_config_t
status_t FXAS_I2C_Receive(uint8_t deviceAddress, uint32_t subAddress, uint8_t subaddressSize, uint8_t* rxBuff, uint8_t rxBuffSize)
{
    lpi2c_master_transfer_t xfer = { 0 };

    xfer.slaveAddress = deviceAddress;
    xfer.direction = kLPI2C_Read;
    xfer.subaddress = subAddress;
    xfer.subaddressSize = subaddressSize;
    xfer.data = rxBuff;
    xfer.dataSize = rxBuffSize;
    xfer.flags = kLPI2C_TransferDefaultFlag;
    status_t i2c_status = LPI2C_MasterTransferBlocking(BOARD_FXAS_I2C_BASE, &xfer);
    return i2c_status;

    // return LPI2C_MasterTransferBlocking(BOARD_FXAS_I2C_BASE, &xfer);
}

status_t FXAS_21002c_Init(void)
{
    status_t result;
    // 1. Configurar o periférico I2C da FRDM-K32L2 (Ajuste conforme seu Config Tools)
    BOARD_FXAS_I2C_BASE->MCR |= LPI2C_MCR_MEN_MASK;
    // 2. Vincular as funções de leitura/escrita I2C criadas ao Config do Sensor
    fxasConfig.I2C_SendFunc = FXAS_I2C_Send;
    fxasConfig.I2C_ReceiveFunc = FXAS_I2C_Receive;

    // 3. Definir parâmetros operacionais usando os Enums do seu fsl_fxas.h
    fxasConfig.I2C_SendFunc = FXAS_I2C_Send;
    fxasConfig.I2C_ReceiveFunc = FXAS_I2C_Receive;
    fxasConfig.fsrdps = kFXAS_Gfsr_2000DPS;      // Fundo de escala de 2000 graus por segundo
    fxasConfig.odr = kFXAS_Godr_100Hz;        // Taxa de amostragem de 100 Hz
    fxasConfig.fifo = kFXAS_FIFO_Disabled;     // Sem uso de memória FIFO interna

    // 4. Executar rotina de inicialização do driver (valida WHO_AM_I e acorda o sensor)
    result = FXAS_Init(&fxasHandle, &fxasConfig);
    if (result != kStatus_Success)
    {
        //PRINTF("\r\nFalha catastrófica ao tentar comunicar com o FXAS21002C!\r\n");
        while (1);
    }
    //PRINTF("\r\nSensor FXAS21002C detectado e inicializado com sucesso!\r\n");
    return result;

}
