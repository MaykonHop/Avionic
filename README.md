# Avionic

Olá! Bem-vindo ao repositório **Avionic**!

Este projeto foi desenvolvido pela Kosmos Rocketry por minha parte e com  **Emanoel Henmerson**, **Eduardo Krezesinski**, e principalmente  **Gustavo Rohrhricht** com sua profunda contribuição nesse código mesmo e  como suporte com  sua **biblioteca para o módulo E22 LoRa** e em seu código **Deimos_Avionic** . Agradeço profundamente por todo o trabalho nesse projeto.

Este repositório contém os arquivos para testar os sensores utilizados no projeto, além do código completo responsável pela ejeção do paraquedas do foguete Phobos, usando um microcontrolador [ESP32](https://docs.platformio.org/en/latest/boards/espressif32/esp32dev.html). A lista atualizada de sensores utilizados está apresentada abaixo. Pode ser de grande auxílio o [PINOUT ESP32](https://www.reddit.com/r/esp32/comments/1h6otb3/how_to_know_which_pin_supports_pull_updown/).

---

## BMP390L
<p align="justify">
  O BMP390L é o sensor atualmente usado para leituras de pressão atmosférica e altitude. Ele desempenha um papel essencial na determinação do momento ideal para a ejeção do paraquedas.
</p>

- [Biblioteca BMP390L](https://github.com/adafruit/Adafruit_BMP3XX)  
- [Datasheet BMP390L](https://www.mouser.com/pdfDocs/bst-bmp390l-ds001.pdf)

### Conexão com ESP32

- **VCC** - 5V  
- **GND** - GND  
- **SDA** - 21  
- **SCL** - 22

---

## MS5803-01BA
<p align="justify">
  O MS5803-01BA é o segundo sensor atualmente usado para leituras de pressão atmosférica e altitude. Ele desempenha um papel essencial na determinação do momento ideal para a ejeção do paraquedas junto com o BMP390L.
</p>

- [Biblioteca MS5803-01BA](https://github.com/millerlp/MS5803_01)  
- [Datasheet MS5803-01BA](https://www.te.com/commerce/DocumentDelivery/DDEController?Action=showdoc&DocId=Data+Sheet%7FMS5803-01BA%7FB3%7Fpdf%7FEnglish%7FENG_DS_MS5803-01BA_B3.pdf%7FCAT-BLPS0038)

### Conexão com ESP32

- **VCC** - 3,3V  
- **GND** - GND  
- **SDA** - 13  
- **SCL** - 15  
- **CS** - 3,3V  
- **PS** - 3,3V

---

## LoRa (E22-900T33S)
<p align="justify">
  O EBYTE E22-900T33S é o módulo LoRa utilizado para transmissão de dados a longa distância, garantindo a comunicação entre a estação terrestre e o foguete.
</p>

- [Biblioteca E22](https://github.com/gustavorohricht/E22-Lora-library)  
- [Datasheet E22](https://www.ebyte.com/en/downpdf.aspx?id=1596)

### Conexão com ESP32

- **VCC** - 5V  
- **GND** - GND  
- **TX** - 26  
- **RX** - 27  
- **M0** - 25  
- **M1** - 33

---

## BNO085x
<p align="justify">
  O BNO085x é um sensor avançado utilizado para medir aceleração, rotação e orientação nos eixos x, y e z, substituindo o MPU6050 por resultados mais precisos.
</p>

- [Biblioteca BNO085x](https://github.com/adafruit/Adafruit_BNO08x)  
- [Datasheet BNO085x](https://www.mouser.com/datasheet/2/1480/BNO080_085_Datasheet-3196201.pdf)

### Conexão com ESP32

- **VCC** - 3,3V  
- **GND** - GND  
- **SDA** - 21  
- **SCL** - 22

---

## GPS Neo M8 V2
<p align="justify">
  O Neo M8 V2 é o novo módulo GPS, oferecendo posicionamento mais preciso em comparação ao Neo 6M. Ele fornece dados de latitude e longitude essenciais para a recuperação do foguete.
</p>

- [Biblioteca GPS](https://github.com/mikalhart/TinyGPSPlus)  
- [Datasheet Neo M8](https://content.u-blox.com/sites/default/files/NEO-M8-FW3_DataSheet_UBX-15031086.pdf)

### Conexão com ESP32

- **VCC** - 5V  
- **GND** - GND  
- **TX** - 16  
- **RX** - 17  

---

## Leitor de Cartão Micro SD
<p align="justify">
  O leitor de cartão SD é utilizado para armazenar todos os dados coletados pelos sensores, como altitude, pressão, aceleração e coordenadas GPS. Além disso, registra se a ativação do fio pirotécnico para ejeção do paraquedas foi bem-sucedida.
</p>

- **Importante:** Certifique-se de que o cartão SD esteja formatado como **FAT32** antes de utilizá-lo, caso contrário, não funcionará.

- [Biblioteca FS](https://github.com/espressif/arduino-esp32/tree/master/libraries/FS/src)  
- [Biblioteca SD](https://github.com/espressif/arduino-esp32/tree/master/libraries/SD/src)

### Conexão com ESP32

- **VCC** - 3,3V  
- **GND** - GND  
- **CS** - 5  
- **MOSI** - 23  
- **SCLK** - 18  
- **MISO** - 19

---

## ADXL375
<p align="justify">
  O ADXL375 é um acelerômetro de baixo consumo de energia que mede acelerações nos eixos x, y e z. Ele é utilizado para complementar as leituras de aceleração em regimes em que o BNO085x não suportaria.
</p>

- [Biblioteca ADXL375](https://github.com/adafruit/Adafruit_ADXL375)  
- [Datasheet ADXL375](https://www.analog.com/media/en/technical-documentation/data-sheets/ADXL375.PDF)

### Conexão com ESP32

- **CS** - 3,3V  
- **VS** - 3,3V  
- **GND** - GND  
- **SDA** - 21  
- **SCL** - 22  
- **SDO** - GND

---
