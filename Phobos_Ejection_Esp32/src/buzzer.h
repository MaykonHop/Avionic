#ifndef BUZZER_H
#define BUZZER_H

// Biblioteca do buzzer

// Pino do Buzzer (utilizei o mesmo pino da general_use)
#define Buzzer 14
#define BuzzerStandbyTime 5000
// Funções gerais de áudio
void Sucess();
void Fail();

// Som de identificação dos sensores
// Os sensores serão identificados pela "contagem" dos bips do buzzer
// Essa contagem segue a seguinte ordem:
// 2 - Barometro
// 3 - IMU
// 4 - Acelerometro
// 5 - GPS
// 6 - Lora
// 7 - SD

// Funções de feedback para sensores
void BarometerFail();
void BarometerSuccess();

void IMUFail();
void IMUSucess();

void AcelerometerFail();
void AcelerometerSucess();

void GPSFail();
void GPSSucess();

void LoraFail();
void LoraSucess();

void SDFail();
void SDSucess();

// Emitindo o apogeu por morse
void dot();
void dash();

void MorseNumber(int valor);

void MorseApogee(float apogeu);

#endif // BUZZER_H