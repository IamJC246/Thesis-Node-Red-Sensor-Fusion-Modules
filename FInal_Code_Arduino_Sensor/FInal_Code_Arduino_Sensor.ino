//#include <nRF24L01.h>
#include <RF24.h>
#define PIN_CE  7
#define PIN_CSN 8

int rawData;

uint8_t pipeNumber;
uint8_t payloadSize;

const uint64_t pipeNum = 0x7878787879; //ADDRESS

RF24 radio(PIN_CE, PIN_CSN);

void setup() 
{

  pinMode(A1, INPUT); //SENSOR 1
  pinMode(A2, INPUT); //SENSOR 2
  
//  pinMode(A3, INPUT); //potentiometer 1
//  pinMode(A4, INPUT); //potentiometer 2
  
  pinMode(2, OUTPUT); //GREEN LED
  pinMode(3, OUTPUT); //YELLOW LED
  pinMode(4, OUTPUT); //RED LED
  pinMode(5, OUTPUT); //BUZZER

  Serial.begin(9600);

  //RF transceiver settings
  radio.begin();
  radio.setChannel(5);
  radio.setDataRate (RF24_1MBPS);
  radio.setPALevel(RF24_PA_HIGH);
  radio.enableDynamicPayloads();
  radio.startListening();
  radio.openWritingPipe(pipeNum);

}

void loop() 
{
  //********===SENSOR 1 & DATA ACQUISITION AND CONVERSION===********//
  
  int sensorValue = analogRead(A1); //sensor 1
//  int sensorValue = analogRead(A3); //potentiometer 1
  //double voltage1 = sensorValue * (5.0 / 1023.0); 

  char cstr[8];
  int final1 = itoa(sensorValue, cstr, 10);

  //********===SENSOR 2 & DATA ACQUISITION AND CONVERSION===********//

  int sensorValue2 = analogRead(A2); //sensor 2
//  int sensorValue2 = analogRead(A4); //potentiometer 2
  //double voltage1 = sensorValue2 * (5.0 / 1023.0); 

  char cstr2[8];
  int final2 = itoa(sensorValue2, cstr2, 10);

  //********===Data Compilation===********//

  const char text[] = "Hello World";
  radio.write(&text, sizeof(text));
  
//  int data[] = {343, 141};
//  
//
//  //********===VERIFICATION & DATA TRANSMISSION===********//
//    
// radio.write(data, sizeof(data));
 
 delay(505);

 //********===alarm system===********//

  int rawData1 = analogRead(A1); //sensor 1
  int rawData2 = analogRead(A2); //sensor 2
//  int rawData1 = analogRead(A3); //potentiometer 1
//  int rawData2 = analogRead(A4); //potentiometer 2
  
  if(rawData1 > rawData2) //A comparator that compares and would pick the highest value
  {
    rawData = rawData1;
  }
  
  else if(rawData1 < rawData2)
  {
    rawData = rawData2;
  }
  
  else if(rawData1 = rawData2)
  {
    rawData = rawData1;
  }
  else
  {
    
  }
  //================================//
  
  if(rawData <= 300)
  {
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    delay(100);
  }
  
  else if(rawData > 300 && rawData <= 800)
  {
    digitalWrite(2, LOW);
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    delay(100);
  }
  
  else if(rawData > 800)
  {
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    delay(100);
  }
  
  else
  {
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    delay(100);
  }

  Serial.print("sensor 1: ");   //uncomment this to verify data
  Serial.print(rawData1);
  Serial.print("|");
  Serial.print("sensor 2: ");
  Serial.print(rawData2);
  Serial.print("|");
  Serial.print("Highest value: ");
  Serial.println(rawData);
//  
  delay(500); // Wait for 500 millisecond(s)
}
