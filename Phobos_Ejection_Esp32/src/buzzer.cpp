// Biblioteca para os sensores
#include "sensors.h"
#include "buzzer.h"
// Musica para caso o sensor estaja funcionando
void Sucess(){

    tone(Buzzer,262,600); 
    delay(200);
    tone(Buzzer, 330, 400);
    delay(200);
    tone(Buzzer, 392, 400);
    delay(200);
    tone(Buzzer, 523, 600);
    noTone(Buzzer);

    delay(300);

    tone(Buzzer,262,600); 
    delay(200);
    tone(Buzzer, 330, 400);
    delay(200);
    tone(Buzzer, 392, 400);
    delay(200);
    tone(Buzzer, 523, 600);
    noTone(Buzzer);

    delay(1000);
}

// Musica para caso o sensor esteja com falha
void Fail(){
    tone(Buzzer, 750, 1000);
    delay(500);
    noTone(Buzzer);
    delay(200);

    tone(Buzzer, 750, 1000);
    delay(500);
    noTone(Buzzer);
    delay(200);

    tone(Buzzer, 750, 1000);
    delay(500);
    noTone(Buzzer);
    delay(200);

    delay(1000);
}

// Conferindo os sensores 
void BarometerFail(){

    // O barometro fara dois bips antes de indicar sucesso ou falha
    tone(Buzzer,300,700); 
    delay(300);
    tone(Buzzer, 400, 500);
    delay(1000);

    Fail();
}

void BarometerSuccess(){
    // Som do barometro 
    tone(Buzzer,300,700); 
    delay(300);
    tone(Buzzer, 400, 500);
    delay(1000);

    Sucess();
}

// IMU
void IMUFail(){
    // Tres bips
    tone(Buzzer,300,700); 
    delay(300);
    tone(Buzzer, 400, 500);
    delay(300);
    tone(Buzzer, 500, 500);
    delay(750);

    Fail();
}

void IMUSucess(){
    tone(Buzzer,300,700); 
    delay(300);
    tone(Buzzer, 400, 500);
    delay(300);
    tone(Buzzer, 500, 500);
    delay(750);

    // Sucesso
    Sucess();
}


// Acelerometro
void AcelerometerFail(){
     // Quatro bips
    tone(Buzzer,300,700); 
    delay(300);
    tone(Buzzer, 400, 500);
    delay(300);
    tone(Buzzer, 500, 500);
    delay(300);
    tone(Buzzer, 600, 500);
    delay(750);

    Fail();
}

void AcelerometerSucess(){
    tone(Buzzer,300,700); 
    delay(300);
    tone(Buzzer, 400, 500);
    delay(300);
    tone(Buzzer, 500, 500);
    delay(300);
    tone(Buzzer, 600, 500);
    delay(750);

    Sucess();
}

// GPS
void GPSFail(){
    // Cinco bips
    tone(Buzzer,300,700); 
    delay(300);
    tone(Buzzer, 400, 500);
    delay(300);
    tone(Buzzer, 500, 500);
    delay(300);
    tone(Buzzer, 600, 500);
    delay(300);
    tone(Buzzer, 700, 500);
    delay(750);

    Fail();
}

void GPSSucess(){
    tone(Buzzer,300,700); 
    delay(300);
    tone(Buzzer, 400, 500);
    delay(300);
    tone(Buzzer, 500, 500);
    delay(300);
    tone(Buzzer, 600, 500);
    delay(300);
    tone(Buzzer, 700, 500);
    delay(750);

    Sucess();
}

// Lora
void LoraFail(){
    // Seis bips
    tone(Buzzer,300,700); 
    delay(300);
    tone(Buzzer, 400, 500);
    delay(300);
    tone(Buzzer, 500, 500);
    delay(300);
    tone(Buzzer, 600, 500);
    delay(300);
    tone(Buzzer, 700, 500);
    delay(300);
    tone(Buzzer, 800, 500);
    delay(750);

    Fail();
}

void LoraSucess(){
    tone(Buzzer,300,700); 
    delay(300);
    tone(Buzzer, 400, 500);
    delay(300);
    tone(Buzzer, 500, 500);
    delay(300);
    tone(Buzzer, 600, 500);
    delay(300);
    tone(Buzzer, 700, 500);
    delay(300);
    tone(Buzzer, 800, 500);
    delay(750);

    Sucess();
}

// Modulo SD
void SDFail(){
    // Seis bips
    tone(Buzzer,300,700); 
    delay(300);
    tone(Buzzer, 400, 500);
    delay(300);
    tone(Buzzer, 500, 500);
    delay(300);
    tone(Buzzer, 600, 500);
    delay(300);
    tone(Buzzer, 700, 500);
    delay(300);
    tone(Buzzer, 800, 500);
    delay(300);
    tone(Buzzer, 900, 500);
    delay(750);

    Fail();
}

void SDSucess(){
    tone(Buzzer,300,700); 
    delay(300);
    tone(Buzzer, 400, 500);
    delay(300);
    tone(Buzzer, 500, 500);
    delay(300);
    tone(Buzzer, 600, 500);
    delay(300);
    tone(Buzzer, 700, 500);
    delay(300);
    tone(Buzzer, 800, 500);
    delay(300);
    tone(Buzzer, 900, 500);
    delay(750);

    Sucess();
}

// Morse
// Os numeros em morse sao compostos de cinco - e .
// Neste código, cada . sera 50 ms
// Cada - é o triplo do ponto, portanto sera 150 ms
#define DOT 50
#define DASH 150

void dot(){
  tone(Buzzer, 600, DOT);
  delay(DOT);
  noTone(Buzzer);
  delay(DOT);
}

void dash(){
  tone(Buzzer, 600, DASH);
  delay(DASH);
  noTone(Buzzer);
  delay(DOT);
}

// Espaço entre - e . são 50 ms
// Espaço entre numeros são 150 ms
// 0	-----
// 1	.----
// 2	..---
// 3	...--
// 4	....-
// 5	.....
// 6	-....
// 7	--...
// 8	---..
// 9	----.
void MorseNumber(int valor){
    switch(valor){
        case 0:
            dash();
            dash();
            dash();
            dash();
            dash();
            delay(DASH);
            
            break;

        case 1:
            dot();
            dash();
            dash();
            dash();
            dash();
            delay(DASH);

            break;

        case 2:
            dot();
            dot();
            dash();
            dash();
            dash();
            delay(DASH);

            break;

        case 3:
            dot();
            dot();
            dot();
            dash();
            dash();
            delay(DASH);

            break;
            
        case 4:
            dot();
            dot();
            dot();
            dot();
            dash();
            delay(DASH);

            break;

        case 5:
            dot();
            dot();
            dot();
            dot();
            dot();
            delay(DASH);

            break;
        case 6:
            dot();
            dot();
            dot();
            dot();
            dash();
            delay(DASH);

            break;

        case 7:
            dot();
            dot();
            dot();
            dash();
            dash();
            delay(DASH);

            break;

        case 8:
            dot();
            dot();
            dash();
            dash();
            dash();
            delay(DASH);

            break;

        case 9:
            dot();
            dash();
            dash();
            dash();
            dash();
            delay(DASH);

            break;   
    }
    return;
}

void MorseApogee(float apogee){
    // Primeiro cria um vetor morse, onde cada casa e um numero do apogeu 
    int aux = (int)apogee, i = 0, lenght = 0;
    int *morse = NULL;
    while(aux > 0){
        i++;
        aux /= 10;
    }
    lenght = i;
    aux = apogee;
    morse = (int*)malloc(i*sizeof(int));
    while(aux > 0){
        i--;
        morse[i] = aux%10;
        aux /= 10;
    }

    // Vamos para o terceiro loop while! (Esse é provavlmente o pior código que eu ja fiz)
    while(i<lenght){
        MorseNumber(morse[i]);
        i++;
    }

    free(morse);

    return;
}
