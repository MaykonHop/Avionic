#include "sensors.h"
#include "general_use.h"
#include "buzzer.h"
#include "management_transmission.h"

bool initI2CSensors(Adafruit_BMP3XX &bmp_1,MS_5803 &MS_1,Adafruit_BNO08x &bno, Adafruit_ADXL375 &adxl) {
    // Inicializa os Barômetros
   
    if (!bmp_1.begin_I2C(BMP_I2C)) {
       Serial.println("Erro: Falha ao iniciar Barometro_1");
        BarometerFail();
        return false;
    } else BarometerSuccess();

    bmp_1.setTemperatureOversampling(BMP3_OVERSAMPLING_2X);
    bmp_1.setPressureOversampling(BMP3_OVERSAMPLING_16X);
    bmp_1.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_15);
    bmp_1.setOutputDataRate(BMP3_ODR_200_HZ);
    

  if (MS_1.initializeMS_5803()) {
    Serial.println( "MS5803 CRC check OK." );
  } 
  else {
   Serial.println( "MS5803 CRC check FAILED!" );
  }

    // Inicializa a IMU
    
    if (!bno.begin_I2C(BNO_I2C)) {
        Serial.println("Erro: Falha ao iniciar BNO085");
        IMUFail();
        return false;
    } else IMUSucess();

    // Inicializa o Acelerômetro
    if (!adxl.begin(ADXL_I2C)) {
        Serial.println("Erro: Falha ao iniciar ADXL375");
       // AcelerometerFail();

        return false;
    } else {
      Serial.println("AcelerometerSucess()");
    }//AcelerometerSucess();

    return true;
}

bool InitUARTSensors(HardwareSerial &gpsSerial, HardwareSerial &loraSerial) {
  // Inicializa o GPS
    gpsSerial.begin(GPS_BAUD);

    while (!gpsSerial){
        //    Serial.println("Erro: Falha ao iniciar GPS");
        delay(10);
    }

    GPSSucess();
    //---------------------------------------------------------------
    // Inicializa o LoRa
    loraSerial.begin(LORA_BAUD,SERIAL_8N1,LORA_RX,LORA_TX);
    while (!loraSerial){
        //    Serial.println("Erro: Falha ao iniciar LoRa");
        delay(10);
    }
    //---------------------------------------------------------------
   
    return true;
}

bool InitLoraModule(HardwareSerial *loraSerial) {
 
  pinMode(LORA_M0, OUTPUT);
	pinMode(LORA_M1, OUTPUT);
  digitalWrite(LORA_M0, LOW);
	digitalWrite(LORA_M1,HIGH);
  delay(50);

  uint8_t buffer[4];

  loraSerial->write(0xC1);
  loraSerial->write(0x01);
  loraSerial->write(0x01);
  delay(10);
	loraSerial->readBytes(buffer, 4);

  if(buffer[0] != 0xC1){
    LoraFail();
    return false;
  } else LoraSucess();

  loraSerial->write("AT+RESET");
  //String reset = loraSerial->readString();
  //Serial.println("RESET");
  //Serial.println(reset);
  delay(50);

  digitalWrite(LORA_M0, LOW);
	digitalWrite(LORA_M1,LOW);
  delay(50);

  return true;
}
bool InitSDModule(SDFS &SD,const uint8_t chipSelect) {

     // Serial.println("SD CARD Test");               // Print a message indicating the start of the SD card test

     if (!SD.begin(chipSelect)){                       // Attempt to initialize the SD card
   //    Serial.println("Card Mount Failed");      // Print an error message if the card mount fails
       SDFail();
       return false;
   }
   SDSucess();
   return true;
}  


void readPressureAndTemperatureBarometers(Adafruit_BMP3XX *bmp_1,MS_5803 *MS_1 ,phobos_data_t *SDdata) {

    SDdata->pressure_1 = bmp_1->readPressure();
    SDdata->temperature_1 = bmp_1->readTemperature();
    SDdata->temperature_2 = MS_1->temperature();
    SDdata->pressure_2 = MS_1->pressure();
}

void readAltitudeBarometers(Adafruit_BMP3XX *bmp_1,MS_5803 *MS_1,phobos_data_t *SDdata) {
    MS_1->readSensor();

    SDdata->altitude_1 = bmp_1->readAltitude(SeaLevelHpa);

    SDdata->altitude_2 = MS_1->readAltitude(SeaLevelHpa);

}

void readBNO08x(Adafruit_BNO08x *bno08x, phobos_data_t *SDdata) {
    
    sh2_SensorValue_t sensorValue;

    if (bno08x->wasReset()) {
      //  Serial.print("sensor was reset ");
        BnosetReports(bno08x);
      }

      if (!bno08x->getSensorEvent(&sensorValue)) {
        return;
      }  

      switch (sensorValue.sensorId) {

        case SH2_ACCELEROMETER:
          /*
          Serial.print("Accelerometer - x: ");
          Serial.print(sensorValue.un.accelerometer.x);
          Serial.print(" y: ");
          Serial.print(sensorValue.un.accelerometer.y);
          Serial.print(" z: ");
          Serial.println(sensorValue.un.accelerometer.z);
          */

          SDdata->ax = sensorValue.un.accelerometer.x;
          SDdata->ay = sensorValue.un.accelerometer.y;
          SDdata->az = sensorValue.un.accelerometer.z;

          break;

        case SH2_GYROSCOPE_CALIBRATED:
          /*
          Serial.print("Gyro - x: ");
          Serial.print(sensorValue.un.gyroscope.x);
          Serial.print(" y: ");
          Serial.print(sensorValue.un.gyroscope.y);
          Serial.print(" z: ");
          Serial.println(sensorValue.un.gyroscope.z);
*/
          SDdata->gx = sensorValue.un.gyroscope.x;
          SDdata->gy = sensorValue.un.gyroscope.y;
          SDdata->gz = sensorValue.un.gyroscope.z;

          break;

        case SH2_MAGNETIC_FIELD_CALIBRATED:
          /*
          Serial.print("Magnetic Field - x: ");
          Serial.print(sensorValue.un.magneticField.x);
          Serial.print(" y: ");
          Serial.print(sensorValue.un.magneticField.y);
          Serial.print(" z: ");
          Serial.println(sensorValue.un.magneticField.z);
          */
          SDdata->mag_x = sensorValue.un.magneticField.x;
          SDdata->mag_y = sensorValue.un.magneticField.y;
          SDdata->mag_z = sensorValue.un.magneticField.z;

          break;
      

          default:
    //      Serial.print("Unknown sensor event: ");
          Serial.println(sensorValue.sensorId);
          break;
         
    }

}

void readGPS(TinyGPSPlus &gps, HardwareSerial &gpsSerial ,phobos_data_t *SDdata){

  while (gpsSerial.available() > 0) {
    gps.encode(gpsSerial.read());
  }

if(gps.location.isUpdated()) {
  
 // Serial.println("Latitude:");
 // Serial.println(gps.location.lat(), 16);
 // Serial.println("Longitude:");
 // Serial.println(gps.location.lng(), 16);

  SDdata->lat = gps.location.lat();
  SDdata->lon = gps.location.lng();
}

}

void readAcceleration(Adafruit_ADXL375 *adxl, phobos_data_t *SDdata,float calibAdxl[3]) {
  
    sensors_event_t adxlEvent;

    adxl->getEvent(&adxlEvent);
    
    // Accelerometer data from ADXL375
    SDdata->accel_ax = adxlEvent.acceleration.x - calibAdxl[0];
    SDdata->accel_ay = adxlEvent.acceleration.y - calibAdxl[1];
    SDdata->accel_az = adxlEvent.acceleration.z - calibAdxl[2];

}

void AccelCalibration(Adafruit_ADXL375 *adxl,float adxl_calib[3], int n) {
     
  float sumx = 0;
  float sumy = 0;
  float sumz = 0;
 
  sensors_event_t event;

  for(int i = 0; i<n; i++) {

    adxl->getEvent(&event);
    
    sumx += event.acceleration.x;
    sumy += event.acceleration.y;
    sumz += event.acceleration.z;
    
    }

    float calib_x = sumx/n;
    float calib_y = sumy/n;
    float calib_z = sumz/n;

    adxl_calib[0] = calib_x;
    adxl_calib[1] = calib_y;
    adxl_calib[2] = calib_z;
    
}
void BnosetReports(Adafruit_BNO08x *bno08x) {

  //  Serial.println("Setting desired reports");
    
    if (!bno08x->enableReport(SH2_ACCELEROMETER)) {
  //    Serial.println("Could not enable accelerometer");
    }
    
    if (!bno08x->enableReport(SH2_GYROSCOPE_CALIBRATED)) {
  //    Serial.println("Could not enable gyroscope");
    }
    
    if (!bno08x->enableReport(SH2_MAGNETIC_FIELD_CALIBRATED)) {
  //    Serial.println("Could not enable magnetic field calibrated");
    }
 
}
