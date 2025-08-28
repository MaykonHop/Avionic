#ifndef SENSORS_H
#define SENSORS_H

// Bibliotecas para os sensores

//Bibliotecas Gerais
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include "general_use.h"
//***************************/
//Biliotecas dos Barometros

//BMP3XX
#include <Adafruit_BMP3XX.h>
//MS5803-01BA
#include "MS5803_01.h"
//***************************/
//Bibliotecas dos IMUs

//BNO08x
#include <Adafruit_BNO08x.h>
#include "sh2_SensorValue.h"
//ADXL375
#include <Adafruit_ADXL375.h>
//***************************/  
//Bibliotecas do GPS

#include <TinyGPSPlus.h>
//***************************/
//Bibliotecas do SD

#include "management_SD.h"
//***************************/

//Constantes
#define BNO_RESET -1

// Endereços I2C dos sensores

#define ADXL_I2C 0x53

#define BNO_I2C 0x4B

#define BMP_I2C 0x77

// Constantes de Baudrate

#define GPS_BAUD 9600

#define LORA_BAUD 9600

//Função de Inicialização sensores I2C
bool initI2CSensors(Adafruit_BMP3XX &bmp_1,MS_5803 &MS_1,Adafruit_BNO08x &bno, Adafruit_ADXL375 &adxl);

//Função de Inicialização sensores UART
bool InitUARTSensors(HardwareSerial &gpsSerial, HardwareSerial &loraSerial);

//Inicialização dos pinos do Lora

bool InitLoraModule(HardwareSerial *loraSerial);

//Inicialização do módulo SD
bool InitSDModule(SDFS &SD,const uint8_t chipSelect);
//Função de configuração dos reports do BNO
void BnosetReports(Adafruit_BNO08x *bno08x);

//Leitura dos dados dos sensores

//Leitura dos dados do BNO
void readBNO08x(Adafruit_BNO08x *bno08x, phobos_data_t *SDdata);

//Leitura dos dados de Pressão e Temperatura dos Barometros
void readPressureAndTemperatureBarometers(Adafruit_BMP3XX *bmp_1,MS_5803 *MS_1 ,phobos_data_t *SDdata);

//Leitura dos dados de altitude dos Barometros
void readAltitudeBarometers(Adafruit_BMP3XX *bmp_1,MS_5803 *MS_1,phobos_data_t *SDdata);

//Leitura dos dados da aceleração do ADXL375
void readAcceleration(Adafruit_ADXL375 *adxl, phobos_data_t *SDdata,float calibAdxl[3]);

//Função de calibração da aceleração do ADXL375
void AccelCalibration(Adafruit_ADXL375 *adxl,float adxl_calib[3], int n);

//Leitura dos dados do GPS
void readGPS(TinyGPSPlus &gps, HardwareSerial &gpsSerial ,phobos_data_t *SDdata);

#endif // SENSOR_H