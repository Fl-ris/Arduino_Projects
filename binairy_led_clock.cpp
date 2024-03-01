#include <Arduino.h>
#include <CD74HC4067.h>
#include <Ds1302.h>


char intbin(byte, byte);
int knop1();
int knop2();
void klokreset(int, int);
void led_test();

CD74HC4067 mux(4, 5, 6, 7); // de pinnen van de mux chip (S0, S1, S2, S3)
int signaalpin1 = 13;



Ds1302 rtc(8, 9, 10);  // RST, CLK, DAT

int switchpin1 = 11;  // switch is connected to pin 2
int val1;             // variable for reading the pin status
int buttonstate1;     // variable to hold the button state
int knopklik1 = 0;    // how many times the button has been pressed

int switchpin2 = 12;  // switch is connected to pin 2
int val2;             // variable for reading the pin status
int buttonstate2;     // variable to hold the button state
int knopklik2 = 0;
int knopklik3 = 0; // tijdelijke knop.

int hour;
int minute;

unsigned long tijdoud = 0;
const long interval1 = 500;
const long interval2 = 80;

  
int pin1 = 1; // minuut pin 100000 = 32 min
int pin2 = 1; // minuut pin 010000
int pin3 = 1; // minuut pin 001000
int pin4 = 1; // minuut pin 000100
int pin5 = 1; // minuut pin 000010
int pin6 = 1; // minuut pin 000001

int pin7 = 1; // uur pin 10000 = 16 uur
int pin8 = 1; // uur pin 01000 = 8 uur enz.
int pin9 = 1; // uur pin 00100
int pin10 = 1;// uur pin 00010
int pin11 = 1;// uur pin 00001




void setup() {
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
  pinMode(pin4, OUTPUT);
  pinMode(pin5, OUTPUT);
  pinMode(pin6, OUTPUT);

  pinMode(pin7, OUTPUT);
  pinMode(pin8, OUTPUT);
  pinMode(pin9, OUTPUT);
  pinMode(pin10, OUTPUT);
  pinMode(pin11, OUTPUT);

  pinMode(11, INPUT_PULLUP);  // schakelaar 1
  pinMode(12, INPUT_PULLUP);  // schakelaar 2

  buttonstate1 = digitalRead(switchpin1);  // voor knop 1.
  buttonstate2 = digitalRead(switchpin2);  // voor knop 2.


  rtc.init();

  if (1 < 2) {
    Serial.println("RTC is gestopt. Tijd instellen...");
    Ds1302::DateTime dt = { // de tijd instellen
                            .year = 11,
                            .month = Ds1302::MONTH_AUG,
                            .day = 22,
                            .hour = 1,
                            .minute = 59,
                            .second = 30,
                            .dow = Ds1302::DOW_TUE

    };

    rtc.setDateTime(&dt);
  }
  Serial.begin(9600);
}

void loop() {                           // hoofdprogramma.
  unsigned long tijdhuidig = millis();  // voor de timer met millis() zonder delay().
  Ds1302::DateTime now;

  rtc.getDateTime(&now);

  //if(digitalRead(11) == 0) {klokreset(1, 2); }

  int mtijd = now.minute;  // de tijd in minuten die naar de leds gedaan moet worden.
  int htijd = now.hour;
  intbin(mtijd, htijd);

  String getal3 = String(233, BIN);  // test voor ander manier van b10 naar b2.

  if (rtc.isHalted()) { Serial.println("HALT..."); }

//led_test();
for(int i = 255; i = 0; i--) { analogWrite(A1, i); delay(1);}
//analogWrite(A1, 110);
//digitalWrite(A1, HIGH);

  knop1();  // hoevaak is knop 1 aangeklikt?
  knop2();  // hoevaak is knop 2 aangeklikt?

  if (knopklik1 >= 1) { // het programma om de klok in te stellen. 
    knopklik3 = knopklik2;
    if (knopklik1 == 1) { // de minuten worden ingesteld hier.
    Serial.println("minuten selecteren... ");
    while (knopklik1 == 1){
    klokreset(minute, hour);
      minute = knopklik2;  
      Serial.print(knopklik2);
     // return 0;
    }
}
    if (knopklik1 >= 2) { // de uren worden hier ingesteld.
      Serial.println("Selecteer uren... ");
      Serial.print(knopklik3);
      klokreset(minute, hour);
      hour = knopklik3 - minute;
      if (knopklik1 == 3) { // de eerste knop is ingedruk om de selectie te bevestigen.
        klokreset(minute, hour);
        knopklik1 = 0;
        knopklik2 = 0;
      }
    }
  }


/*
  if (tijdhuidig - tijdoud >= interval1) {
    Serial.print("minuten: ");
    Serial.println(now.minute);
    Serial.print("Uren: ");
    Serial.println(now.hour);
    Serial.print("knopklik1: ");
    Serial.print(knopklik1);
    tijdoud = tijdhuidig;
  }
*/

}

char intbin(byte x, byte y) { // de functie om van decimale getallen (de tijd) binaire getallen te maken. het is een array van 8 bits.
  //for(byte i = 4; i <= 59; i++ ) {
  byte minuut = x;
  byte uur = y;


  char binair[9] = { 0 };  // voor minuten
  minuut += 128;
  itoa(minuut, binair, 2);
 // char binair2 = { binair + 1 };
  // Serial.println(binair2[6]);
  //Serial.println(binair);

  char binair3[9] = { 0 };  // voor uur
  uur += 128;
  itoa(uur, binair3, 2);
 // char binair4 = { binair2 + 1 };

  int a = binair[7];  // Minuten leds: de index [7] verwijst bijvoorbeeld naar 0101010(1). index begint bij 0.
  int b = binair[6];
  int c = binair[5];
  int d = binair[4];
  int e = binair[3];
  int f = binair[2];


  int g = binair3[3];  // uren leds
  int h = binair3[4];
  int i = binair3[5];
  int j = binair3[6];
  int k = binair3[7];

  //Serial.println(b);
  // Serial.println(binair3);
  // Serial.println(binair3[0]);

  if (a == 49) {  // voor de minuten.
    digitalWrite(pin6, HIGH);
  } else {
    digitalWrite(pin6, LOW);
  }

  if (b == 49) {
    digitalWrite(pin5, HIGH);
  } else {
    digitalWrite(pin5, LOW);
  }
  if (c == 49) {
    digitalWrite(pin4, HIGH);
  } else {
    digitalWrite(pin4, LOW);
  }
  if (d == 49) {
    digitalWrite(pin3, HIGH);
  } else {
    digitalWrite(pin3, LOW);
  }
  if (e == 49) {
    digitalWrite(pin2, HIGH);
  } else {
    digitalWrite(pin2, LOW);
  }
  if (f == 49) {
    digitalWrite(pin1, HIGH);
  } else {
    digitalWrite(pin1, LOW);
  }
  //}

// experiment mux (uren):

/*
  if (g == 49) {  // voor de uren
    digitalWrite(pin7, HIGH); // 16 uur
  } else {
    digitalWrite(pin7, LOW);
  }

  if (h == 49) {
    digitalWrite(pin8, HIGH);
  } else {
    digitalWrite(pin8, LOW);
  }
  if (i == 49) {
    digitalWrite(pin9, HIGH);
  } else {
    digitalWrite(pin9, LOW);
  }
  if (j == 49) {
    digitalWrite(pin10, HIGH);
  } else {
    digitalWrite(pin10, LOW);
  }
  if (k == 49) {
    digitalWrite(pin11, HIGH);
  } else {
    digitalWrite(pin11, LOW);
  }
}
*/
//Serial.println(signalpin1);
Serial.println(k);
digitalWrite(signaalpin1, HIGH);
mux.channel(3);

  if (g == 49) {  // voor de uren
    digitalWrite(pin7, HIGH); // 16 uur
  } else {
    digitalWrite(pin7, LOW);
  }

  if (h == 49) {
    digitalWrite(pin8, HIGH);
  } else {
    digitalWrite(pin8, LOW);
  }
  if (i == 49) {
    digitalWrite(pin9, HIGH);
  } else {
    digitalWrite(pin9, LOW);
  }
  if (j == 49) {
    digitalWrite(pin10, HIGH);
  } else {
    digitalWrite(pin10, LOW);
  }
  if (k == 49) {
    
    digitalWrite(signaalpin1, HIGH);
    mux.channel(3);
    
  } else {
    mux.channel(3);
    digitalWrite(signaalpin1, LOW);
  }
}


void led_test() {
  for (int i = 2; i <= 7; i++) {
      digitalWrite(i, HIGH);
      delay(30);
      digitalWrite(i, LOW);
      
  }
  for (int i = 62; i <= 66; i++) {
        digitalWrite(i, HIGH);
        delay(30);
        digitalWrite(i, LOW);
    }
  for (int y = 66; y >= 62; y--) {
    digitalWrite(y, HIGH);
        delay(30);
        digitalWrite(y, LOW);
  }
  for (int y = 7; y >= 2; y--) {
    digitalWrite(y, HIGH);
        delay(30);
        digitalWrite(y, LOW);
  }

}


void klokreset(int minute, int hour) {

  rtc.init();

  if (1 < 2) {
    Serial.println("RTC is gestopt. Tijd instellen...");
    Ds1302::DateTime dt = { // de tijd instellen
                            .year = 11,
                            .month = Ds1302::MONTH_AUG,
                            .day = 22,
                            .hour = hour,
                            .minute = minute,
                            .second = 00,
                            .dow = Ds1302::DOW_TUE

    };

    rtc.setDateTime(&dt);
  }
  Ds1302::DateTime now;

  rtc.getDateTime(&now);
}


int knop1() {                      // knop 1 is geklikt.
  val1 = digitalRead(switchpin1);  // read input value and store it in val
  if (val1 != buttonstate1) {      // the button state has changed!
    if (val1 == LOW) {             // check if the button is pressed
      knopklik1++;                 // increment the buttonPresses variable
    }
  }
  buttonstate1 = val1;
}

int knop2() {                      // knop 2 is geklikt.
  val2 = digitalRead(switchpin2);  // read input value and store it in val
  if (val2 != buttonstate2) {      // the button state has changed!
    if (val2 == LOW) {             // check if the button is pressed
      knopklik2++;                 // increment the buttonPresses variable
    }
  }
  buttonstate2 = val2;
}