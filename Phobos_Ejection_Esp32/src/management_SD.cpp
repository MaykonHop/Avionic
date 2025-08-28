#include "management_SD.h"
#include "buzzer.h"
void WriteToSD(fs::FS &fs, phobos_data_t *SDdata, const char *path, bool SDstatus) {
    if (!SDstatus) {
    //  Serial.println("Failed to connect to the SD card");
      return;
    } 
    
    File file = fs.open(path, FILE_APPEND);
    if (!file) {
      //  Serial.println("Failed to open file for appending");
        return;
    }
    
    // Check if file is empty and write headers if needed
    if (file.size() == 0) {
       // file.println("Temperatura_1 (°C),Pressão_1 (Pa),Altitude_1 (m),Temperatura_2 (°C),Pressão_2 (Pa),Altitude_2," 
       //             "(m),Pressure_3 (Pa),Altitude_3 (m),ax (m/s^2),""ay (m/s^2),az (m/s^2),gx (°/s),gy (°/s),gz (°/s),mag_x (uT ),mag_y (uT),mag_z (uT),accel_ax (m/s^2),accel_ay (m/s^2),"
       //             "accel_az (m/s^2),Latitude,Longitude,Reefing Ejetado?,Main Ejetado?");

       file.println("Temperatura_1 (°C),Pressão_1 (Pa),Altitude_1 (m),Temperatura_2 (°C),Pressão_2 (Pa),Altitude_2 (m),ax (m/s^2),""ay (m/s^2),az (m/s^2),gx (°/s),gy (°/s),gz (°/s),mag_x (uT ),mag_y (uT),mag_z (uT),accel_ax (m/s^2),accel_ay (m/s^2),"
                    "accel_az (m/s^2),Latitude,Longitude,Reefing Ejetado?,Main Ejetado?");
    }
    
    // Write sensor data in CSV format
    file.print(SDdata->temperature_1);
    file.print(",");
    file.print(SDdata->pressure_1);
    file.print(",");
    file.print(SDdata->altitude_1);
    file.print(",");

    file.print(SDdata->temperature_2);
    file.print(",");
    file.print(SDdata->pressure_2);
    file.print(",");
    file.print(SDdata->altitude_2);
    file.print(",");
/*
    file.print(SDdata->pressure_3);
    file.print(",");
    file.print(SDdata->altitude_3);
    file.print(",");
*/
    file.print(SDdata->ax);
    file.print(",");
    file.print(SDdata->ay);
    file.print(",");
    file.print(SDdata->az);
    file.print(",");

    file.print(SDdata->gx);
    file.print(",");
    file.print(SDdata->gy);
    file.print(",");
    file.print(SDdata->gz);
    file.print(",");

    file.print(SDdata->mag_x);
    file.print(",");
    file.print(SDdata->mag_y);
    file.print(",");
    file.print(SDdata->mag_z);
    file.print(",");

    file.print(SDdata->accel_ax);
    file.print(",");
    file.print(SDdata->accel_ay);
    file.print(",");
    file.print(SDdata->accel_az);
    file.print(",");

    file.print(SDdata->lat);
    file.print(",");
    file.print(SDdata->lon);
    file.print(",");

    file.print(SDdata->first_ejection ? "Sim" : "Não");
    file.print(",");
    file.print(SDdata->second_ejection ? "Sim" : "Não");
    file.print(",");

    file.print("\n");
    
    file.close();
  }

  bool checkSD(fs::FS &fs){

    uint8_t cardType = SD.cardType();             // Get the type of the SD card

  //  Serial.print("SD Card Type: ");               // Print a message indicating the type of SD card

    if (cardType == CARD_NONE) {                  // Check if no SD card is attached
     //   Serial.println("No SD card attached");    // Print an error message if no card is attached
        return false;
    }

    else if (cardType == CARD_MMC) {
      //  Serial.println("MMC");                    // Print "MMC" if the card type is MMC
    } 
    
    else if (cardType == CARD_SD) {
  //      Serial.println("SDSC");                   // Print "SDSC" if the card type is SDSC
    } 
    
    else if (cardType == CARD_SDHC) {
   //     Serial.println("SDHC");                   // Print "SDHC" if the card type is SDHC
    } 
    
    return true;
}
