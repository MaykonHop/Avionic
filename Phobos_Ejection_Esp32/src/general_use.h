#ifndef GENERAL_USE_H
#define GENERAL_USE_H

#include <Arduino.h>
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DEFINIÇÕES DE PINOS PARA ESP32 E CONSTANTES

/* O cartão SD funciona melhor se estiver conectado a 5V em vez de 3,3V
 Ordem dos pinos no módulo SD, a partir do GND:
 GND 3.3V 5V CS MOSI SCK MISO GND

*/

/*Pino do Reefing
  Pino onde está conectado; o segundo fio eve estar no GND
  Este pino deve ser configurado como saída; verifique se o pino escolhido não é apenas de entrada.
*/
#define Apogeewire 32

/* Pino do Pyrowire
 Pino onde o pyrowire está conectado; o segundo fio deve estar no GND.
 Este pino deve ser configurado como saída; verifique se o pino escolhido não é apenas de entrada.
*/
#define Mainwire 4 

// Definições para o sensor BNO08x
/*I2C Padrão do código  */
#define BNO08X_RESET -1

// Definições para o sensor ADXL375, BNO085x e BMP390L
/*I2C Padrão do código  */

// SDA 21 Standard SDA
// SCL 22 Standard SCL

// Constantes
#define BAUDRATE 9600 // Taxa de baud da comunicação serial

#define SeaLevelHpa 1013.25 // Pressão ao nível do mar em hPa

#define EstimatedApogee 10000 // Valor em metros, deve ser superior ao apogeu real, para evitar ruído do barômetro, se necessário

#define LoRaAirDataRate 2400 // Tempo de espera entre leituras do lora, em milissegundos

#define BarometerStandbyTime 30 // Tempo de espera entre leituras do barômetro, em milissegundos, para diferenciar a altitude anterior da atual

#define AccelerationLimit 10 // Limite de aceleração que pode ser atingido, em m/s², sem a necessidade de bloqueio temporal no sistema

#define TimeLock 1000 // Tempo de espera para o bloqueio temporal do sistema, em milissegundos

/**
 * @brief Inicializa os pinos usados no sistema
 * 
 * Inicializa os pinos usados no sistema, como o pino do M0, M1 do lora, pino dos skibs de 
 * apogeu e main e do buzzer. Além disso, coloca todos os pinos em low.
 * 
 * @return true para inicialização bem sucedida
 */

bool initPorts();

void BuzzerSound();


bool AdxlLock(double abs_accel);

/**
 * @class Altitude
 * @brief Classe para gerenciamento e processamento de dados de altitude usando um barômetro.
 */
class Altitude {
  private:
    int MaxAltitude = 0; // Altitude máxima registrada
    int CurrentAltitude = 0; // Altitude atual registrada
    int PreviousAltitude = 0; // Altitude da iteração anterior
    float BarCalibration = 0; // Calibração do barômetro
  public:
    /**
     * @brief Construtor da classe Altitude.
     *
     * Inicializa os valores da altitude máxima, atual e anterior, com valores padrão ou especificados.
     *
     * @param maxAltitude Altitude máxima inicial.
     * @param currentAltitude Altitude atual inicial.
     * @param previousAltitude Altitude anterior inicial.
     */
    Altitude(float maxAltitude = 0, float currentAltitude = 0, float previousAltitude = 0);

    /**
     * @brief Define a altitude máxima.
     *
     * Esta função define o valor da altitude máxima.
     * Apenas valores positivos de altitude são permitidos para evitar ruído do barômetro.
     *
     * @param maxAltitude A nova altitude máxima a ser definida.
     * @return Retorna `true` se a altitude máxima foi definida com sucesso.
     */
    bool setMaxAltitude(float maxAltitude);

    /**
     * @brief Define a altitude atual.
     *
     * Esta função define o valor da altitude atual.
     * Certifique-se de que o barômetro esteja calibrado antes de usar esta função.
     *
     * @param currentAltitude A nova altitude atual a ser definida.
     * @return Retorna `true` se a altitude atual foi definida com sucesso.
     */
    bool setCurrentAltitude(float currentAltitude);

    /**
     * @brief Define a altitude anterior.
     *
     * Esta função define o valor da altitude anterior.
     * Certifique-se de que o barômetro esteja calibrado antes de usar esta função.
     *
     * @param previousAltitude A nova altitude anterior a ser definida.
     * @return Retorna `true` se a altitude anterior foi definida com sucesso.
     */
    bool setPreviousAltitude(float previousAltitude);

    /**
     * @brief Define o valor de calibração barométrica.
     *
     * Esta função define o valor de calibração barométrica usado para cálculos de altitude.
     * O valor fornecido é multiplicado por -1 antes de ser armazenado.
     * Deve ser chamado apenas no início do programa para a calibração inicial ao nível do solo.
     *
     * @param calibration O valor de calibração fornecido pela função readAltitude do barômetro.
     * @return Retorna `true` se o valor de calibração foi definido com sucesso.
     */
    bool setBarCalibration(float calibration);

    /**
     * @brief Retorna a altitude máxima.
     *
     * Esta função retorna a altitude máxima registrada.
     * Certifique-se de chamar setMaxAltitude antes de usar esta função.
     *
     * @return A altitude máxima.
     */
    int getMaxAltitude();

    /**
     * @brief Retorna a altitude atual.
     *
     * Esta função retorna a altitude atual registrada.
     * Certifique-se de que o barômetro esteja calibrado e que setCurrentAltitude foi chamado antes de usar esta função.
     *
     * @return A altitude atual.
     */
    int getCurrentAltitude();

    /**
     * @brief Retorna a altitude anterior.
     *
     * Esta função retorna a altitude anterior registrada.
     * Certifique-se de chamar setPreviousAltitude antes de usar esta função.
     *
     * @return A altitude anterior.
     */
    int getPreviousAltitude();

    /**
     * @brief Retorna o valor de calibração barométrica.
     *
     * Esta função retorna o valor de calibração barométrica usado para cálculos de altitude.
     * Certifique-se de chamar setBarCalibration antes de usar esta função.
     *
     * @return O valor de calibração barométrica.
     */
    float getBarCalibration();
};

#endif // GENERAL_USE_H