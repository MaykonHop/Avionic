//Biblioteca Para Uso Geral
#include "general_use.h"
#include "sensors.h"
#include "management_transmission.h"
#include "buzzer.h"
#include "ejection.h"

// Variáveis Globais

Altitude altBmp1(0,0,0); // Estrutura para manipular e calibrar dados de altitude do barômetro 1
Altitude altMS1(0,0,0); // Estrutura para manipular e calibrar dados de altitude do barômetro 2
//Altitude altBar3(0,0,0); // Estrutura para manipular e calibrar dados de altitude do barômetro 3

phobos_data_t SDdata; // Estrutura para armazenar dados de sensores e status
// Intanciando objetos dos sensores

Adafruit_BMP3XX bmp_1; // Barometro 1
MS_5803 MS_1; // Barometro 2
//Adafruit_BMP3XX bmp_3; // Barometro 3

Adafruit_BNO08x bno(BNO08X_RESET); // IMU(BNO08x)
sh2_SensorValue_t bnoSensorValue;  //Parte onde os dados de aceleração, giroscópio e magnetometro estão armazenados

Adafruit_ADXL375 adxl(ADXL_I2C); // ADXL375

TinyGPSPlus gps; // GPS

HardwareSerial gpsSerial(2); // Serial para o GPS
HardwareSerial loraSerial(1); // Serial para o LoRa

//dados de aceleração
float adxl_ax, adxl_ay, adxl_az; //aceleração em x, y e z do ADXL375
float adxl_calib[3] = {0,0,0}; //valores de calibração da aceleração do ADXL375
double adxl_abs_accel; //aceleração absoluta

float bno_ax, bno_ay, bno_az; //aceleração em x, y e z do IMU(BNO08x)
float bno_calib[3] = {0,0,0}; //valores de calibração da aceleração do IMU(BNO08x)

//dados do IMU exceto aceleração
float bno_mag_x, bno_mag_y, bno_mag_z; //magnetometro em x, y e z do IMU
float bno_gyro_x, bno_gyro_y, bno_gyro_z; //giroscópio em x, y e z do IMU

bool ApogeeEjected = false, MainEjected = false; // Flags para indicar a ejeção no apogeu e main
bool BarometerCompareFlag = false; //Flag utilizada para impedir que o setprevious seja atualizado constantemente, isto é, antes do tempo de comparação

unsigned long previousMillisBMP = millis();
unsigned long currentMillis = currentMillis;  
unsigned long previousMillisLoRa = millis();
unsigned long previousmillisBuzzer = millis();
unsigned long previousmillisApogee = millis();


const unsigned int LoRaStandbyTime = 2000*((8.0 * sizeof(phobos_data_t))/LoRaAirDataRate) + 130;

void setup() {
  Serial.begin(BAUDRATE); // Inicializa a comunicação serial para o monitor serial
  while (!Serial) delay(10); // Aguarda o monitor serial ser conectado
  
  pinMode(Apogeewire, OUTPUT); // Inicia o pino do Apogeu
  digitalWrite(Apogeewire, LOW); //Pino em Low

  pinMode(Mainwire, OUTPUT); // Inicia o pino do Main
  digitalWrite(Mainwire, LOW);//Pino em Low

  pinMode(Buzzer, OUTPUT); // Inicia o pino do buzzer
  digitalWrite(Buzzer, LOW); // Pino em Low
 
  initI2CSensors(bmp_1,MS_1,bno, adxl); //Inicializa todos os sensores I2C 

  BnosetReports(&bno);

  InitUARTSensors(gpsSerial, loraSerial); //Inicializa todos os sensores UART
  InitLoraModule(&loraSerial);  //Inicializa os pinos e limpa o buffer do lora
  InitSDModule(SD,SD_CS); 
  //initPorts(); //Inicializa todos os pinos usados no sistema
  bmp_1.readPressure();
  MS_1.readSensor();
  AccelCalibration(&adxl,adxl_calib,1000); //Calibra o ADXL375 e o IMU(BNO08x)

  //Calibra a altitude do barometro 1
 // altBmp1.setBarCalibration(bmp_1.readAltitude(SeaLevelHpa)); //Calibra a altitude do barometro 1
  altMS1.setBarCalibration(MS_1.readAltitude(SeaLevelHpa));
}

void loop() {

//Parte da utilização dos dados do adxl375 para possível TimeLock-----------------------------------------------------

  readAcceleration(&adxl,&SDdata,adxl_calib); //Leitura dos dados de aceleração do ADXL375
 
  adxl_abs_accel = sqrt(SDdata.accel_ax*SDdata.accel_ax + SDdata.accel_ay*SDdata.accel_ay + SDdata.accel_az*SDdata.accel_az); //Cálculo da aceleração absoluta para o TimeLock
 
  bool checkAdxlLockReturn = AdxlLock(adxl_abs_accel); //Verificação da aceleração para o AdxlLock

// Parte da aquisição dos dados dos barométricos anteriores que serão utilizados para comparação na ejeção---------------------------------------------------------

    if(!BarometerCompareFlag){

      readAltitudeBarometers(&bmp_1,&MS_1,&SDdata); //Leitura da apenas da altitude do barômetro 1
    //  altBmp1.setPreviousAltitude(SDdata.altitude_1); //Armazena a altitude da barometro 1 na estrutura que será utilizada para comparação na ejeção
      altMS1.setPreviousAltitude(SDdata.altitude_2);
    //  altBar3.setPreviousAltitude(SDdata.altitude_3);
      BarometerCompareFlag = true;
    
    }
    
    currentMillis = millis();

// Parte da utilização dos dados dos barométricos para ejeção---------------------------------------------------------
  
    if (currentMillis - previousMillisBMP >= BarometerStandbyTime) {

      if(checkAdxlLockReturn == false){

        ApogeeEjection(&altMS1,&MS_1,checkAdxlLockReturn, &ApogeeEjected);
        if(!ApogeeEjected){
          previousmillisApogee = millis();
        }
        if (currentMillis - previousmillisApogee > 10000)
        {
          MainEjection(&altMS1,&MS_1,ApogeeEjected,&MainEjected);
        }
        
        
      
      }
      

     // Serial.println("BarometerTime");
     // Serial.println(previousMillisBMP);
     // Serial.println(currentMillis);
      
      previousMillisBMP = currentMillis;

    //-------------------------------------------------------------------------------------------------------------------
    //Parte do SD--------------------------------------------------------------------------------------------------------

      readBNO08x(&bno,&SDdata); //Leitura dos dados de giroscópio e magnetometro do IMU (bno085x)

      readPressureAndTemperatureBarometers(&bmp_1,&MS_1,&SDdata); //Leitura da pressão e temperatura do barometro 1
      
      readGPS(gps,gpsSerial,&SDdata); //Leitura dos dados de GPS
      
      SDdata.first_ejection = ApogeeEjected; //Sinal se ocorrou ejeção de apogeu
      
      SDdata.second_ejection = MainEjected; //Sinal se ocorreu ejeção de main
      
      bool CheckSDReturn = checkSD(SD); //Verifica se o cartão SD está conectado
      
     WriteToSD(SD,&SDdata,"/data.txt", CheckSDReturn); //Escreve os dados no cartão SD

        BarometerCompareFlag = false;      
      //-------------------------------------------------------------------------------------------------------------------
    }

//Parte da transmissão de dados--------------------------------------------------------------------------------------

    if (currentMillis - previousMillisLoRa >= LoRaStandbyTime) {
      
      //Funções de Transmissão do LoRa vão aqui

      LoraBroadcastTransmit(&SDdata,&loraSerial); //Envia a estrutura SDdata para o receptor Lora na base

      //Serial.println("LoRaTime");
      //Serial.println(previousMillisLoRa);
      //Serial.println(currentMillis);

      previousMillisLoRa = currentMillis;

    }

  //Código morse do apogeu-------------------------------------------------------------------------------------------------
  
  if((currentMillis - previousmillisBuzzer >= BuzzerStandbyTime) && (SDdata.first_ejection && SDdata.second_ejection) && adxl_abs_accel < 3.0){
      
      MorseApogee(altBmp1.getMaxAltitude());
      previousmillisBuzzer = currentMillis;

    }
//-------------------------------------------------------------------------------------------------------------------  
}


