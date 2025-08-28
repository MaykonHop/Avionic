#ifndef EJECTION_H
#define EJECTION_H

#include "general_use.h"
#include "sensors.h"

#define EjectionAltitudeVariation 20 // Diferença entre a altitude máxima e a atual, em metros, onde ocorre a ejeção do pyrowire

#define MainEjectionAltitude 465 // Altura em metros em que ocorre o acionamento do skib main

#define EjectionDelay 1000 // Tempo de espera para a ejeção do pyrowire, em milissegundos

#define DivergenceThreshold 50 // Divergência em metros de leitura entre os dois barômetros

#define MinCurrentMinusPreviousVariation 0.2 //Tenta ver se o barômetro não travou em uma altitude especifica, em metros

bool ApogeeWireEjection();

bool MainWireEjection();

//bool ApogeeEjection(Altitude* alt_bar1,Altitude* alt_bar2,Adafruit_BMP3XX* bmp1,MS_5803* MS_1,bool AdxlLockVar, bool *isEjected);
    bool ApogeeEjection(Altitude* alt_bar1,MS_5803* MS_1,bool AdxlLockVar, bool *isEjected);
//bool MainEjection (Altitude* alt_bar1,Altitude* alt_bar2,Adafruit_BMP3XX* bmp1,MS_5803* MS_1,bool ApogeeEjectionVar, bool *isEjected);
    bool MainEjection (Altitude* alt_bar1,MS_5803* MS_1,bool ApogeeEjectionVar, bool *isEjected);

#endif 