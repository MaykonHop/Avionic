#ifndef MANAGEMENT_SD_H
#define MANAGEMENT_SD_H

// Bibliotecas para SD
#include "FS.h"
#include "SD.h"


// Definições do SD
#define SD_CS 5
// SD_MOSI 11
// SD_SCLK 12
// SD_MISO 13


/**
 * @brief Estrutura de dados para armazenar informações de sensores e status para o SD e enviar pelo LoRa.
 *
 * Esta estrutura é usada para coletar e armazenar vários tipos de dados de diferentes sensores e 
 * indicadores de status. Destina-se ao uso para registro de dados em um cartão SD e envio via LoRa.
 * 
 * A estrutura contém os seguintes campos:
 * 
 * - **Dados do BMP390**:
 *   - `temperature`: Leitura de temperatura do sensor BMP390 (em graus Celsius).
 *   - `pressure`: Leitura de pressão do sensor BMP390 (em Pascal).
 *   - `altitude`: Altitude calculada a partir do sensor BMP390 (em metros).
 * 
 * - **Dados do BNO085**:
 *   - `ax`: Aceleração no eixo X do sensor BNO085 (em m/s²).
 *   - `ay`: Aceleração no eixo Y do sensor BNO085 (em m/s²).
 *   - `az`: Aceleração no eixo Z do sensor BNO085 (em m/s²).
 *   - `gx`: Leitura do giroscópio no eixo X do sensor BNO085 (em graus por segundo).
 *   - `gy`: Leitura do giroscópio no eixo Y do sensor BNO085 (em graus por segundo).
 *   - `gz`: Leitura do giroscópio no eixo Z do sensor BNO085 (em graus por segundo).
 * 
 * - **Dados do ADXL375**:
 *   - `adxl_ax`: Aceleração no eixo X do sensor ADXL375 (em m/s²).
 *   - `adxl_ay`: Aceleração no eixo Y do sensor ADXL375 (em m/s²).
 *   - `adxl_az`: Aceleração no eixo Z do sensor ADXL375 (em m/s²).
 * 
 * - **Dados do GPS**:
 *   - `latitude`: Leitura de latitude do sensor GPS (em graus).
 *   - `longitude`: Leitura de longitude do sensor GPS (em graus).
 * 
 * - **Ejeção**:
 *   - `first_ejection`: Um indicador booleano que indica se o reefing foi ejetado (`true`) ou não (`false`).
 *     Quando `true`, indica que o reefing foi ejetado e os dados devem ser enviados ao cartão SD.
 *  
 *   - `second_ejection`: Um indicador booleano que indica se o pyrowire foi ejetado (`true`) ou não (`false`).
 *     Quando `true`, indica que o reefing e o pyrowire foi ejetado e os dados devem ser enviados ao cartão SD.
 */
#pragma pack(1)
typedef struct PhobosData {
    // Dados do Barometro_1
    float temperature_1;
    float pressure_1;
    float altitude_1;

    // Dados do Barometro_2
    
    float temperature_2;
    float pressure_2;
    float altitude_2;
    
    // Dados do Barometro_3
    /*
    float pressure_3;
    float altitude_3;
    */
    // Dados do IMU
    float ax;
    float ay;
    float az;
    float gx;
    float gy;
    float gz;
    float mag_x;
    float mag_y;    
    float mag_z;

    // Dados do Acelerômetro
    float accel_ax;
    float accel_ay;
    float accel_az;

    // Dados do GPS
    double lat;
    double lon;

    // Ejeção
    bool first_ejection = false; // Se true, indica que o Reefing foi ejetado e os dados são enviados ao cartão SD
    bool second_ejection = false; // Se true, indicia que a primeira ejeção já aconteceu e que pyrowire foi ejetado
} phobos_data_t;
#pragma pack()


void WriteToSD(fs::FS &fs, phobos_data_t *SDdata, const char *path, bool SDstatus);

bool checkSD(fs::FS &fs);


#endif // MANAGEMENT_SD_H