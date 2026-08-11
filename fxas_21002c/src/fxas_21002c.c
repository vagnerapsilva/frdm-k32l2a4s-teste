/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *        TECNODEV TECNOLOGIA DE DESENVOLVIMENTIO DE SOFTWARE E SERVICOS       *
 *        TEL: (011) 4109-0577                 SITE: www.tecnodev.com.br       *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include "fxas_21002c.h"
#include "encoder_ky_040.h"
#include "ssd1306.h"
#include "ssd1306_fonts.h"
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

void teste_Giroscopio(void)
{
    status_t result;
    result = FXAS_21002c_Init();
    if (result == kStatus_Success)
    {
        ssd1306_Fill(Black);
        memset(MSG, 0xFF, 50);
        sprintf(MSG, "LIB FRDM-K32L2A4S");
        ssd1306_SetCursor(0, 0);
        ssd1306_WriteString(MSG, Font_7x10, White);
        ssd1306_UpdateScreen();
        while (1)
        {
            // Ler pacote completo de dados brutos (Eixos X, Y e Z de uma só vez)
            result = FXAS_ReadSensorData(&fxasHandle, &sensorData);

            if (result == kStatus_Success)
            {
                // Combinar os pares de registradores de 8 bits em variáveis com sinal de 16 bits
                int16_t xRaw = (int16_t)((sensorData.gyroXMSB << 8) | sensorData.gyroXLSB);
                int16_t yRaw = (int16_t)((sensorData.gyroYMSB << 8) | sensorData.gyroYLSB);
                int16_t zRaw = (int16_t)((sensorData.gyroZMSB << 8) | sensorData.gyroZLSB);

                // Converter valores inteiros puros para graus por segundo utilizando a função nativa do driver
                float xDegPerSec = FXAS_FormatFloat(xRaw, fxasConfig.fsrdps);
                float yDegPerSec = FXAS_FormatFloat(yRaw, fxasConfig.fsrdps);
                float zDegPerSec = FXAS_FormatFloat(zRaw, fxasConfig.fsrdps);

                // Exibir os dados tratados no terminal serial da placa
                sprintf(MSG, "Giroscopio (dps)");
                ssd1306_SetCursor(2, 12);
                ssd1306_WriteString(MSG, Font_7x10, White);
                ssd1306_UpdateScreen();

                sprintf(MSG, "X: %6.2f", xDegPerSec);
                ssd1306_SetCursor(30, 25);
                ssd1306_WriteString(MSG, Font_7x10, White);
                ssd1306_UpdateScreen();

                sprintf(MSG, "Y: %6.2f", yDegPerSec);
                ssd1306_SetCursor(30, 35);
                ssd1306_WriteString(MSG, Font_7x10, White);
                ssd1306_UpdateScreen();

                sprintf(MSG, "Z: %6.2f", zDegPerSec);
                ssd1306_SetCursor(30, 45);
                ssd1306_WriteString(MSG, Font_7x10, White);
                ssd1306_UpdateScreen();
            }
            else
            {
                sprintf(MSG, "ERROR READING");
                ssd1306_SetCursor(2, 10);
                ssd1306_WriteString(MSG, Font_7x10, White);
                ssd1306_UpdateScreen();
            }

            //Aguarda um curto intervalo antes da próxima amostragem
            SDK_DelayAtLeastUs(200000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);

            // Verifica o clique do botão físico de forma não-bloqueante
            if (GPIO_PinRead(ENCODER_GPIO, SW_PIN) == 0) {
                // Debounce simples via software para o botão físico
                for (volatile int i = 0; i < 200000; i++);

                // Confirma se o botão continua pressionado pós-debounce
                if (GPIO_PinRead(ENCODER_GPIO, SW_PIN) == 0)
                    break; // Sai do loop de teste do giroscópio
            }
        }
    }
}
