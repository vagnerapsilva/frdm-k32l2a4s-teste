/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *        TECNODEV TECNOLOGIA DE DESENVOLVIMENTIO DE SOFTWARE E SERVICOS       *
 *        TEL: (011) 4109-0577                 SITE: www.tecnodev.com.br       *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include "fxos_8700cq.h"
#include "math.h"
#include "ssd1306.h"
#include "ssd1306_fonts.h"
#include "encoder_ky_040.h" // Driver do encoder rotativo KY-040
/*******************************************************************************
 * Definitions
 ******************************************************************************/
 /* Upper bound and lower bound angle values. These constants are declared for
  * potential angle filtering and are not currently enforced in the demo loop.
  */
#define ANGLE_UPPER_BOUND 85U
#define ANGLE_LOWER_BOUND 5U

  /*******************************************************************************
   * Prototypes
   ******************************************************************************/

   /*******************************************************************************
   * Variables
   ******************************************************************************/
volatile int16_t xAngle = 0;
volatile int16_t yAngle = 0;

/* Possible I2C addresses for the FXOS8700CQ device. The demo scans these
 * until the sensor responds. */
const uint8_t g_accel_address[] = { 0x1CU, 0x1DU, 0x1EU, 0x1FU };

/* Shared buffer used by LPI2C transfers. */
uint8_t ACCEL_I2C_masterBuffer[ACCEL_I2C_MASTER_BUFFER_SIZE];

/*******************************************************************************
 * I2C configuration and transfer descriptors
 ******************************************************************************/
const lpi2c_master_config_t ACCEL_I2C_masterConfig = {
  .enableMaster = true,
  .enableDoze = true,
  .debugEnable = false,
  .ignoreAck = false,
  .pinConfig = kLPI2C_2PinOpenDrain,
  .baudRate_Hz = 100000,
  .busIdleTimeout_ns = 0,
  .pinLowTimeout_ns = 0,
  .sdaGlitchFilterWidth_ns = 0,
  .sclGlitchFilterWidth_ns = 0,
  .hostRequest = {
    .enable = false,
    .source = kLPI2C_HostRequestExternalPin,
    .polarity = kLPI2C_HostRequestPinActiveHigh
  }
};
lpi2c_master_transfer_t ACCEL_I2C_masterTransfer = {
  .flags = kLPI2C_TransferDefaultFlag,
  .slaveAddress = 0,
  .direction = kLPI2C_Write,
  .subaddress = 0,
  .subaddressSize = 1,
  .data = ACCEL_I2C_masterBuffer,
  .dataSize = 1
};




/**
 * @brief Send data to an LPI2C slave device.
 *
 * Builds a transfer descriptor and executes a blocking transfer over the
 * specified LPI2C peripheral.
 */
status_t BOARD_LPI2C_Send(LPI2C_Type* base,
    uint8_t deviceAddress,
    uint32_t subAddress,
    uint8_t subAddressSize,
    uint8_t* txBuff,
    uint8_t txBuffSize)
{
    lpi2c_master_transfer_t xfer;

    xfer.flags = kLPI2C_TransferDefaultFlag;
    xfer.slaveAddress = deviceAddress;
    xfer.direction = kLPI2C_Write;
    xfer.subaddress = subAddress;
    xfer.subaddressSize = subAddressSize;
    xfer.data = txBuff;
    xfer.dataSize = txBuffSize;

    return LPI2C_MasterTransferBlocking(base, &xfer);
}

/**
 * @brief Read data from an LPI2C slave device.
 *
 * Builds a transfer descriptor and executes a blocking read from the
 * specified LPI2C peripheral.
 */
status_t BOARD_LPI2C_Receive(LPI2C_Type* base,
    uint8_t deviceAddress,
    uint32_t subAddress,
    uint8_t subAddressSize,
    uint8_t* rxBuff,
    uint8_t rxBuffSize)
{
    lpi2c_master_transfer_t xfer;

    xfer.flags = kLPI2C_TransferDefaultFlag;
    xfer.slaveAddress = deviceAddress;
    xfer.direction = kLPI2C_Read;
    xfer.subaddress = subAddress;
    xfer.subaddressSize = subAddressSize;
    xfer.data = rxBuff;
    xfer.dataSize = rxBuffSize;

    return LPI2C_MasterTransferBlocking(base, &xfer);
}
/**
 * @brief Write a single byte to the FXOS8700CQ device.
 *
 * This wrapper uses the board-specific I2C instance configured for the
 * accelerometer sensor.
 */
status_t BOARD_Accel_I2C_Send(uint8_t deviceAddress, uint32_t subAddress, uint8_t subaddressSize, uint32_t txBuff)
{
    uint8_t data = (uint8_t)txBuff;

    return BOARD_LPI2C_Send(BOARD_ACCEL_I2C_BASEADDR, deviceAddress, subAddress, subaddressSize, &data, 1);
}

/**
 * @brief Read bytes from the FXOS8700CQ device.
 */
status_t BOARD_Accel_I2C_Receive(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subaddressSize, uint8_t* rxBuff, uint8_t rxBuffSize)
{
    return BOARD_LPI2C_Receive(BOARD_ACCEL_I2C_BASEADDR, deviceAddress, subAddress, subaddressSize, rxBuff, rxBuffSize);
}

/**
 * @brief Initialize the accelerometer's I2C interface.
 */
/**
 * @brief Initialize the accelerometer's I2C interface.
 */
void BOARD_Accel_I2C_Init(void)
{
    LPI2C_MasterInit(ACCEL_I2C_PERIPHERAL, &ACCEL_I2C_masterConfig, ACCEL_I2C_CLOCK_FREQ);
}

/**
 * @brief Main demo routine for the FXOS8700CQ sensor.
 *
 * Initializes the sensor over I2C, reads the configured dynamic range,
 * converts accelerometer readings to angles, and prints the results to
 * the SSD1306 display.
 */
void FXOS_8700CQ(void)
{
    fxos_handle_t fxosHandle = { 0 };
    fxos_data_t sensorData = { 0 };
    fxos_config_t config = { 0 };
    uint8_t sensorRange = 0;
    uint8_t dataScale = 0;
    int16_t xData = 0;
    int16_t yData = 0;
    uint8_t i = 0;
    uint8_t array_addr_size = 0;
    status_t result = kStatus_Fail;

    /* I2C initialize */
    BOARD_Accel_I2C_Init();
    /* Configure the I2C function */
    config.I2C_SendFunc = BOARD_Accel_I2C_Send;
    config.I2C_ReceiveFunc = BOARD_Accel_I2C_Receive;

    /* Scan the potential FXOS8700CQ I2C addresses and initialize the device
     * on the first successful response. */
    array_addr_size = sizeof(g_accel_address) / sizeof(g_accel_address[0]);
    for (i = 0; i < array_addr_size; i++)
    {
        config.slaveAddress = g_accel_address[i];
        result = FXOS_Init(&fxosHandle, &config);
        if (result == kStatus_Success)
        {
            break;
        }
    }

    /* Display the detected device address on the OLED screen. */
    ssd1306_Fill(Black);
    memset(MSG, 0xFF, 50);
    sprintf(MSG, "FXOS_8700CQ(0x%02X) OK", config.slaveAddress);
    ssd1306_SetCursor(0, 0);
    ssd1306_WriteString(MSG, Font_7x10, White);
    ssd1306_UpdateScreen();

    if (result != kStatus_Success)
    {
        /* Initialization failed; show an error message and halt this routine. */
        ssd1306_Fill(Black);
        memset(MSG, 0xFF, 50);
        sprintf(MSG, "Sensor device initialize failed!");
        ssd1306_SetCursor(0, 0);
        ssd1306_WriteString(MSG, Font_7x10, White);
        ssd1306_UpdateScreen();
        SDK_DelayAtLeastUs(1000000, 48000000); // Delay for 1000ms (assuming a 48 MHz clock)
        return;
    }

    /* Read the accelerometer dynamic range register to determine the selected
     * g-range for later conversion of raw data to engineering units. */
    if (FXOS_ReadReg(&fxosHandle, XYZ_DATA_CFG_REG, &sensorRange, 1) != kStatus_Success)
    {
        return;
    }

    if (sensorRange == 0x00)
    {
        dataScale = 2U; /* ±2g range */
    }
    else if (sensorRange == 0x01)
    {
        dataScale = 4U; /* ±4g range */
    }
    else if (sensorRange == 0x10)
    {
        dataScale = 8U; /* ±8g range */
    }
    else
    {
        /* Unsupported range code; leaving dataScale as zero may cause incorrect
         * angle values. */
    }

    while (1)
    {
        /* Read the latest accelerometer sample from the FXOS8700CQ. */
        if (FXOS_ReadSensorData(&fxosHandle, &sensorData) != kStatus_Success)
        {
            return;
        }

        /* Combine the MSB and LSB bytes for X and Y acceleration. The raw data
         * is 14-bit left-justified; dividing by 4 shifts the value into a signed
         * 14-bit representation. */
        xData = (int16_t)((uint16_t)((uint16_t)sensorData.accelXMSB << 8) | (uint16_t)sensorData.accelXLSB) / 4U;
        yData = (int16_t)((uint16_t)((uint16_t)sensorData.accelYMSB << 8) | (uint16_t)sensorData.accelYLSB) / 4U;

        /* Convert raw data to angle (normalize to 0-90 degrees). No negative angles. */
        xAngle = (int16_t)floor((double)xData * (double)dataScale * 90 / 8192);
        if (xAngle < 0)
        {
            xAngle *= -1;
        }
        yAngle = (int16_t)floor((double)yData * (double)dataScale * 90 / 8192);
        if (yAngle < 0)
        {
            yAngle *= -1;
        }
        /* Output the computed angle values to the OLED display. */
        sprintf(MSG, "x= %2d y = %2d\r\n", xAngle, yAngle);
        ssd1306_SetCursor(10, 35);
        ssd1306_WriteString(MSG, Font_7x10, White);
        ssd1306_UpdateScreen();

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