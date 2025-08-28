// Para ejeção
#include "ejection.h"
bool ApogeeWireEjection(){
  
    delay(EjectionDelay); //Delay configurável para a Ejeção do Paraquedas
    digitalWrite(Apogeewire,HIGH);
    delay(1000); //Delay apenas para deixar que a ejeção ocorra e depois deixa o pino em Low
    digitalWrite(Apogeewire,LOW);
  
    return true;
  }
  
  bool MainWireEjection(){
    
    delay(EjectionDelay);//Delay configurável para a Ejeção do Paraquedas
    digitalWrite(Mainwire,HIGH);
    delay(1000); //Delay apenas para deixar que a ejeção ocorra e depois deixa o pino em Low
    digitalWrite(Mainwire,LOW);
  
    return true;
  }
  
static bool isBarometerFaulty(float currentAltitude, float previousAltitude, float otherAltitude, float previousOtherAltitude, float divergenceThreshold, float minDelta) {
   
  // Check non-finite (NaN or INF)
    if (!isfinite(currentAltitude)) {
      Serial.println("Barometer reading is not finite");
      return true;
    }
  /*
    // Check stuck or flat-line reading
    if (fabs(currentAltitude - previousAltitude) < minDelta) {
      Serial.println("Barometer reading is stuck or flat-line");
      return true;
    }
    */

    // Check divergence between sensors
    if (isfinite(otherAltitude) && fabs(currentAltitude - otherAltitude) > divergenceThreshold) {
        // Optional: use rate of change to guess which is faulty
        float delta1 = fabs(currentAltitude - previousAltitude);
        float delta2 = fabs(otherAltitude - previousOtherAltitude);
        Serial.print("Divergence between barometers: ");
        Serial.print(delta1);
        Serial.print(" vs ");
        Serial.println(delta2);
        if (delta1 < delta2) return true;
    }

    Serial.println("No fault detected");

    return false; // No fault detected
}
    bool ApogeeEjection(Altitude* alt_bar1,MS_5803* MS_1,bool AdxlLockVar, bool *isEjected){ 

      if (AdxlLockVar) {
          return false;
      }

      if(*isEjected){
        return false;
      }
      //Sets current altitude through barometeric reading
      MS_1->readSensor();
      alt_bar1->setCurrentAltitude(MS_1->readAltitude(SeaLevelHpa));
    
      //Printing out readings, for debugging purposes,comment out when not needed
    /*  
      Serial.println("Current altitude bar1: " + String(alt_bar1->getCurrentAltitude()));
      Serial.println("Max altitude bar1: " + String(alt_bar1->getMaxAltitude()));
      Serial.println("Previous altitude bar1: " + String(alt_bar1->getPreviousAltitude()));
     
    
      //Printing out readings, for debugging purposes,comment out when not needed
      Serial.println("MaxAltitude bar1 :" + String(alt_bar1->getMaxAltitude()));
      Serial.println("Current altitude bar1: " + String(alt_bar1->getCurrentAltitude()));
      Serial.println("Max - current altitude bar1:" + String(alt_bar1->getMaxAltitude() - alt_bar1->getCurrentAltitude()));
    */
    
      //If the difference between the maximum altitude and the current altitude exceeds a predefined threshold/limit (`EjectionAltitude`), the ejection mechanism is triggered
      if((alt_bar1->getMaxAltitude() - alt_bar1->getCurrentAltitude()) > EjectionAltitudeVariation)
      {
        //Prints out that the ejection mechanism is triggered, for debugging purposes,comment out when not needed
        //Serial.println(" Apogee Ejection");
        //Turns on the pin which will cause the pyrowire to eject the parachute
        ApogeeWireEjection();
        *isEjected = true;
        return true;
      }
    
      //If the maximum altitude is less than the current altitude, the maximum altitude is updated
    
      else if (alt_bar1->getPreviousAltitude() <= alt_bar1->getCurrentAltitude() && alt_bar1->getMaxAltitude() < alt_bar1->getCurrentAltitude()) {
          alt_bar1->setMaxAltitude(alt_bar1->getCurrentAltitude());
          return false;
      }     
      
      return false;  
    }
  
    bool MainEjection (Altitude* alt_bar1,MS_5803* MS_1,bool ApogeeEjectionVar, bool *isEjected) {
      if (!ApogeeEjectionVar) {
          return false;    
      }

      if(*isEjected){
        return false;
      }
      //Sets current altitude through barometeric reading
      MS_1->readSensor();
      alt_bar1->setCurrentAltitude(MS_1->readAltitude(SeaLevelHpa));
    
      //Printing out readings, for debugging purposes,comment out when not needed
     // Serial.println("Current altitude bar1: " + String(alt_bar1->getCurrentAltitude()));
     
      //If the difference between the maximum altitude and the current altitude exceeds a predefined threshold/limit (`EjectionAltitude`), the ejection mechanism is triggered
      if((alt_bar1->getCurrentAltitude()) <= MainEjectionAltitude){
          MainWireEjection();
      //    Serial.println("Main Ejection");
          *isEjected = true;
          return true;
        }
      return false;
    }