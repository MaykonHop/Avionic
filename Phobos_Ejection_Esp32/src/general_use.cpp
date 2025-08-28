#include "general_use.h"
#include "management_transmission.h"
#include "buzzer.h"
#include "sensors.h"

bool initPorts(){

  pinMode(Apogeewire, OUTPUT); // Inicia o pino do Apogeu
  digitalWrite(Apogeewire, LOW); //Pino em Low

  pinMode(Mainwire, OUTPUT); // Inicia o pino do Main
  digitalWrite(Mainwire, LOW);//Pino em Low

  pinMode(Buzzer, OUTPUT); // Inicia o pino do buzzer
  digitalWrite(Buzzer, LOW); // Pino em Low

  delay(40);
  return true;

}

Altitude :: Altitude(float maxAltitude,float currentAltitude, float previousAltitude) {
  setMaxAltitude(maxAltitude); 
  setCurrentAltitude(currentAltitude);
  setPreviousAltitude(previousAltitude);
}

bool Altitude :: setMaxAltitude(float maxAltitude) {
    if(maxAltitude >= 0 && maxAltitude <= EstimatedApogee) {
        MaxAltitude = maxAltitude;
        return true;
    }
    return false;
}

bool Altitude :: setPreviousAltitude(float previousAltitude) {
    if(previousAltitude >= 0) {
        PreviousAltitude = previousAltitude + BarCalibration;
        return true;
    }
    return false;
}

bool Altitude :: setCurrentAltitude(float currentAltitude) {
    if(currentAltitude >= 0) {
        CurrentAltitude = currentAltitude + BarCalibration;
        return true;
    }
    return false;
}

bool Altitude :: setBarCalibration(float calibration){
  BarCalibration = calibration * (-1);
  return true;
}

//Métodos Get
int Altitude :: getMaxAltitude() {
    return MaxAltitude;
} 

int Altitude :: getCurrentAltitude() {
    return CurrentAltitude;
}

int Altitude :: getPreviousAltitude() {
    return PreviousAltitude;
}

float Altitude :: getBarCalibration(){
  return BarCalibration;
}

void BuzzerSound() {

    tone(Buzzer,262,200); //DO
    delay(200);
    tone(Buzzer,294,300); //RE
    delay(200);
    tone(Buzzer,330,300); //MI
    delay(200);
    tone(Buzzer,349,300); //FA
    delay(300);
    tone(Buzzer,349,300); //FA
    delay(300);
    tone(Buzzer,349,300); //FA
    delay(300);
    tone(Buzzer,262,100); //DO
    delay(200);
    tone(Buzzer,294,300); //RE
    delay(200);   
    tone(Buzzer,262,100); //DO
    delay(200);
    tone(Buzzer,294,300); //RE
    delay(300);
    tone(Buzzer,294,300); //RE
    delay(300);
    tone(Buzzer,294,300); //RE
    delay(300);
    tone(Buzzer,262,200); //DO
    delay(200);
    tone(Buzzer,392,200); //SOL
    delay(200);
    tone(Buzzer,349,200); //FA
    delay(200);
    tone(Buzzer,330,300); //MI
    delay(300);
    tone(Buzzer,330,300); //MI
    delay(300);
    tone(Buzzer,330,300); //MI
    delay(300);
    tone(Buzzer,262,200); //DO
    delay(200);
    tone(Buzzer,294,300); //RE
    delay(200);
    tone(Buzzer,330,300); //MI
    delay(200);
    tone(Buzzer,349,300); //FA
    delay(300);
    tone(Buzzer,349,300); //FA
    delay(300);
    tone(Buzzer,349,300); //FA
    delay(300);
}

bool AdxlLock(double abs_accel){
  
    if(abs_accel > AccelerationLimit){
      return true;
    }
    else{
      return false;
    }
}

