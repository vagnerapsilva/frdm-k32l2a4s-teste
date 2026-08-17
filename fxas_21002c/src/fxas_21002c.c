
/*******************************************************************************
 * TECNODEV TECNOLOGIA DE DESENVOLVIMENTIO DE SOFTWARE E SERVICOS
 * TEL: (011) 4109-0577                 SITE: www.tecnodev.com.br
 *
 * fxas_21002c.c
 *
 * Adaptador de driver e função de teste para o giroscópio FXAS21002C
 * na placa FRDM-K32L2A4S usando LPI2C para comunicação e SSD1306 para exibição.
 *
 * Este módulo fornece:
 *  - funções de envio e recepção I2C exigidas pelo driver FXAS.
 *  - rotina de inicialização do sensor FXAS21002C.
 *  - função de teste que lê dados do sensor e os mostra no display OLED.
 ******************************************************************************/

#include "fxas_21002c.h"
#include "encoder_ky_040.h"
#include "ssd1306.h"
#include "ssd1306_fonts.h"


 /*******************************************************************************
  * Variables
  ******************************************************************************/

  // Handle de estado mantido pelo driver FXAS para operações posteriores.
fxas_handle_t fxasHandle;

// Configurações que serão copiadas pelo driver FXAS durante a inicialização.
fxas_config_t fxasConfig;

// Estrutura que recebe os dados brutos lidos do giroscópio.
fxas_data_t sensorData;

/*******************************************************************************
 * Code
 ******************************************************************************/

 /**
  * FXAS_I2C_Send
  *
  * Callback exigida pelo driver FXAS para escrever um único byte em um
  * registrador do dispositivo via I2C.
  *
  * @param deviceAddress  Endereço I2C do dispositivo.
  * @param subAddress     Endereço do registrador interno do sensor.
  * @param subaddressSize Tamanho do sub-endereço em bytes.
  * @param txBuff         Byte de dados a ser enviado (armazenado como uint32_t
  *                       pela assinatura do driver).
  * @return status_t      Resultado da transferência I2C.
  */
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

/**
 * FXAS_I2C_Receive
 *
 * Callback exigida pelo driver FXAS para ler múltiplos bytes de um
 * registrador do dispositivo via I2C.
 *
 * @param deviceAddress  Endereço I2C do dispositivo.
 * @param subAddress     Endereço do registrador interno do sensor.
 * @param subaddressSize Tamanho do sub-endereço em bytes.
 * @param rxBuff         Buffer onde os dados recebidos serão armazenados.
 * @param rxBuffSize     Número de bytes a serem lidos.
 * @return status_t      Resultado da transferência I2C.
 */
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
}

/**
 * FXAS_21002c_Init
 *
 * Inicializa o barramento I2C e configura o sensor FXAS21002C.
 *
 * 1. Habilita o módulo LPI2C da placa.
 * 2. Associa as callbacks de I2C ao driver FXAS.
 * 3. Define fundo de escala, taxa de atualização e uso de FIFO.
 * 4. Executa FXAS_Init para validar a comunicação e acordar o sensor.
 *
 * @return status_t Resultado da inicialização.
 */
status_t FXAS_21002c_Init(void)
{
    status_t result;

    // Habilita o periférico I2C da FRDM-K32L2.
    BOARD_FXAS_I2C_BASE->MCR |= LPI2C_MCR_MEN_MASK;

    // Vincula as funções de escrita/leitura I2C ao driver do sensor.
    fxasConfig.I2C_SendFunc = FXAS_I2C_Send;
    fxasConfig.I2C_ReceiveFunc = FXAS_I2C_Receive;

    // Define parâmetros principais de operação do giroscópio.
    fxasConfig.fsrdps = kFXAS_Gfsr_2000DPS;      // Fundo de escala de 2000 dps.
    fxasConfig.odr = kFXAS_Godr_100Hz;           // Saída de dados a 100 Hz.
    fxasConfig.fifo = kFXAS_FIFO_Disabled;       // FIFO interno desativado.

    // Inicializa o sensor e verifica se a comunicação foi bem sucedida.
    result = FXAS_Init(&fxasHandle, &fxasConfig);
    if (result != kStatus_Success)
    {
        // Em caso de erro grave, trava aqui para facilitar depuração.
        while (1);
    }

    return result;
}

/**
 * teste_Giroscopio
 *
 * Rotina de demonstração que inicializa o giroscópio FXAS21002C, lê
 * continuamente os eixos X/Y/Z e exibe os valores no display SSD1306.
 *
 * O loop principal também verifica se o botão do encoder foi pressionado
 * para encerrar o teste.
 */
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
            // Lê todos os dados do sensor em um único pacote.
            result = FXAS_ReadSensorData(&fxasHandle, &sensorData);

            if (result == kStatus_Success)
            {
                // Monta valores de 16 bits a partir dos registradores MSB/LSB.
                int16_t xRaw = (int16_t)((sensorData.gyroXMSB << 8) | sensorData.gyroXLSB);
                int16_t yRaw = (int16_t)((sensorData.gyroYMSB << 8) | sensorData.gyroYLSB);
                int16_t zRaw = (int16_t)((sensorData.gyroZMSB << 8) | sensorData.gyroZLSB);

                // Converte os valores brutos em graus por segundo.
                float xDegPerSec = FXAS_FormatFloat(xRaw, fxasConfig.fsrdps);
                float yDegPerSec = FXAS_FormatFloat(yRaw, fxasConfig.fsrdps);
                float zDegPerSec = FXAS_FormatFloat(zRaw, fxasConfig.fsrdps);

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

            // Aguarda 200 ms antes de ler novamente.
            SDK_DelayAtLeastUs(200000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);

            // Verifica se o botão do encoder foi pressionado para sair do teste.
            if (GPIO_PinRead(ENCODER_GPIO, SW_PIN) == 0)
            {
                for (volatile int i = 0; i < 200000; i++);
                if (GPIO_PinRead(ENCODER_GPIO, SW_PIN) == 0)
                {
                    __NVIC_SystemReset();
                }
            }
        }
    }
}
