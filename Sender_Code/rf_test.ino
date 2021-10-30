#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>

RF24 radio(7, 8);
const byte writer[] = "00001";
const byte reader[] = "00002";

char message[12] = "MyMess";
int temp = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  if(!radio.begin()) {
    Serial.println("FAILED");
    while(1);
  }
  radio.openWritingPipe(writer);
  radio.openReadingPipe(1, reader);
  radio.setPALevel(RF24_PA_MIN);
}
double thissens[4];
void loop() {
  // put your main code here, to run repeatedly:
  delay(5);
  radio.startListening();
  while(!radio.available()) {
    Serial.println("Waiting");
  }
  Serial.println("Done");
  radio.read(&temp, sizeof(temp));
  radio.stopListening();
  for(int i = 0; i < 4; i++) {
    thissens[i] = analogRead(i);
    thissens[i] = (0.0003974*thissens[i]*thissens[i])+(0.01294*thissens[i])+0.3412;
    Serial.print(thissens[i]);
  }
  Serial.println();
  radio.write(&thissens, sizeof(thissens));
}
