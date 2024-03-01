#include <Adafruit_MLX90614.h> // ir temp.

// voor display
#include <U8g2lib.h> 
#include <Wire.h>


#include <Adafruit_Sensor.h> // bme680
#include "Adafruit_BME680.h"

// eind voor display

Adafruit_MLX90614 mlx = Adafruit_MLX90614();
Adafruit_BME680 bme; // I2C

//U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ 24, /* data=*/ 22, /* reset=*/ U8X8_PIN_NONE);   // All Boards without Reset of the Display


float temp_a;
float temp_o;

int timer_1 = 10000; // timer voor de millis functie. 


void setup() {

Serial.begin(9600);
u8g2.begin();
mlx.begin(); // start de ir thermometer
bme.begin();


bme.setTemperatureOversampling(BME680_OS_8X); // voor de BME680
bme.setHumidityOversampling(BME680_OS_2X);
bme.setPressureOversampling(BME680_OS_4X);
bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
bme.setGasHeater(320, 150); // 320*C for 150 ms

if (!bme.begin()) {
  Serial.println("Could not find a valid BME680 sensor, check wiring!");
  while (1);
}

}

void loop() {
Serial.println(millis());
bme.performReading();


float temp_a = mlx.readAmbientTempC();
float temp_o = mlx.readObjectTempC();
int lettertype_grootte = 2;

Serial.print("Luchtvochtigheid: ");
Serial.println(bme.humidity);

Serial.print("Luchtdruk: ");
Serial.print(bme.pressure);
Serial.println(" hPa");



delay(500);

for (int i = 0; i < 255; i++) {
  
  if (i % 2 ==0 ) {
    scherm_2();  }
  else {
    scherm_3(temp_a, temp_o);
  }


delay(1000);

}

//scherm_3(temp_a, temp_o);

// if (millis() > 10000) {
//   scherm_2();
// }
// else {
// displa_y(temp_a, temp_o, lettertype_grootte);
// }


}



void displa_y(float temp_a, float temp_o, int lettertype_grootte) {
static const unsigned char image_Temperature_16x16_bits[] U8X8_PROGMEM = {0x00,0x00,0x00,0x00,0x80,0x00,0x40,0x01,0x40,0x01,0x40,0x01,0x40,0x01,0x40,0x01,0x40,0x01,0x20,0x02,0xe0,0x03,0xe0,0x03,0xc0,0x01,0x00,0x00,0x00,0x00,0x00,0x00};
u8g2.clearBuffer();		// clear the internal memory

//u8g2.setFont(u8g2_font_10x20_me);
u8g2.setFont(u8g2_font_10x20_tf);
u8g2.setBitmapMode(1);  // mischien niet nodig?
u8g2.drawFrame(0, 1, 128, 64);
u8g2.drawFrame(0, 38, 128, 26);
u8g2.drawFrame(0, 1, 128, 26);

u8g2.setCursor(5, 21); // blok om de temp aan te geven.
u8g2.print(temp_a);
u8g2.print(" \xb0"); // print graden teken.
u8g2.print("C");

u8g2.setCursor(5, 57);
u8g2.print(temp_o);
u8g2.print(" \xb0");
u8g2.print("C");

u8g2.drawXBMP( 107, 44, 16, 16, image_Temperature_16x16_bits);
u8g2.drawXBMP( 107, 8, 16, 16, image_Temperature_16x16_bits);


u8g2.sendBuffer();					// transfer internal memory to the display
delay(400);  
}

void scherm_2() { // Weergeef: vier vakken met vier textstrings
u8g2.clearBuffer();		// clear the internal memory

u8g2.setBitmapMode(1);
u8g2.setFontMode(1);
u8g2.drawFrame(0, 0, 128, 64);
u8g2.drawFrame(0, 0, 64, 64);
u8g2.setFont(u8g2_font_profont22_tr);
u8g2.setCursor(5, 21);
u8g2.print(bme.humidity);

u8g2.setFont(u8g2_font_profont22_tr);
u8g2.drawStr(9, 55, "aaa");
u8g2.setFont(u8g2_font_profont22_tr);
u8g2.drawStr(73, 55, "bbb");
u8g2.setFont(u8g2_font_profont22_tr);
u8g2.drawStr(73, 25, "ccc");
u8g2.drawLine(0, 32, 127, 32);
u8g2.sendBuffer();					// transfer internal memory to the display

}

void scherm_3(float temp_a, float temp_o) {
u8g2.clearBuffer();		// clear the internal memory
u8g2.setBitmapMode(1);
u8g2.setFontMode(1);
u8g2.drawFrame(0, 0, 128, 64);
u8g2.drawLine(1, 32, 128, 32);
u8g2.setFont(u8g2_font_4x6_tr);

u8g2.setCursor(2, 8); // blok om de temp aan te geven.
u8g2.print("888");

u8g2.setFont(u8g2_font_4x6_tr);
u8g2.drawStr(2, 40, "111");
u8g2.setFont(u8g2_font_profont22_tr);

u8g2.setCursor(3, 59); // blok om de temp aan te geven.
u8g2.print(temp_o);

u8g2.setCursor(3, 27);
u8g2.print(bme.gas_resistance / 1000.0);


u8g2.setFont(u8g2_font_profont22_tr);
u8g2.drawStr(71, 59, "444");

u8g2.setFont(u8g2_font_unifont_t_symbols);
u8g2.setCursor(71, 27); // blok om de temp aan te geven.
u8g2.print("KOhms");




u8g2.sendBuffer();					// transfer internal memory to the display

}

// void scherm_3() {


  
