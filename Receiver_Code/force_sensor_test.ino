#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>

#include <SoftwareSerial.h>
#include <SPI.h>
#include <SD.h>



//SoftwareSerial bluetooth(7, 8);

const byte reader[] = "00001";
const byte writer[] = "00002";

RF24 radio(3, 2);

const int chipSelect = 10;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1);
  }
  Serial.println("card initialized.");
  //bluetooth.begin(9600);
  if(!radio.begin()) {
    Serial.println("FAILED");
    while(1);
  }
  pinMode(8, INPUT_PULLUP);
  radio.openWritingPipe(writer);
  radio.openReadingPipe(1, reader);
  radio.setPALevel(RF24_PA_MIN);
}
int val;
int temp = 1;
int count = 0;
double thissens[4];
double thatsens[4];
bool pressed = false;
double startTime;
void loop() {
  Serial.println(digitalRead(8));
  if(digitalRead(8) == 0) {
    pressed = true;
    Serial.println("Pressed");
    startTime = millis();
  }
  if(pressed) {
    File dataFile = SD.open("DATA.txt", FILE_WRITE);
  radio.stopListening();
  
  if(millis()-startTime < 40340) {
     radio.write(&temp, sizeof(temp));
     radio.startListening();
     for(int i = 0; i < 4; i++) {
      thissens[i] = analogRead(i);
      thissens[i] = (0.0003974*thissens[i]*thissens[i])+(0.01294*thissens[i])+0.3412;
     }
     while(!radio.available()) {
       Serial.println("Waiting");
     }
     Serial.println("Done");
     radio.read(&thatsens, sizeof(thatsens));
     for(int i = 0; i < 4; i++) {
      dataFile.print(thissens[i]);
      dataFile.print(" ");
      Serial.print(thissens[i]);
      Serial.print(" ");
     }
     dataFile.println(" ");
     Serial.println(" ");
     for(int i = 0; i < 4; i++) {
      dataFile.print(thatsens[i]);
      dataFile.print(" ");
      Serial.print(thatsens[i]);
      Serial.print(" ");
     }
     dataFile.println(" ");
     Serial.println(" ");
  }
  else {
    Serial.println("Done");
    while(1);
  }
  dataFile.close();
  }  
}
