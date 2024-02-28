#include <OneWire.h>
#include <DallasTemperature.h>
#include <LittleFS.h>

// Data wire is plugged into pin 2 on the Arduino
#define ONE_WIRE_BUS 2


// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);




void setup(void)
{

  // start serial port
  Serial.begin(9600);
  Serial.println("Start temp en licht");
  // Start up the library
  sensors.begin(); 
  pinMode(A0, INPUT);
  pinMode(2, OUTPUT);
  int licht1 = analogRead(A0);  
  

}
void loop(void)
{ 
 
//licht();
temp();
//lamp();


}


int licht() {

Serial.println(analogRead(A0));
return 0;
}


float temp() {

unsigned long tijd = ((millis() / 1000) / 60);

sensors.requestTemperatures(); // Send the command to get temperatures  // call sensors.requestTemperatures() to issue a global temperature
Serial.print(tijd);
Serial.print(": ");
Serial.println(sensors.getTempCByIndex(0)); // Why "byIndex"? You can have more than one IC on the same bus. 0 refers to the first IC on the wire
delay(60000);
return 0;

}

void lamp() {


digitalWrite(2, HIGH);
delay(30);
digitalWrite(2, LOW);
delay(20);
digitalWrite(2, HIGH);

}


