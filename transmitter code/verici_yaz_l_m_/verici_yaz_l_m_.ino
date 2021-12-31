
/*--------------------------------------------------------------------------------
 * Project Name: Smart Serum Measurement and Stimulation Device
 * Revision Date: 23.12.2021
 * Author: İrem Aksakal
 * -------------------------------------------------------------------------------
 */








#include <SPI.h>    //We add the standard SPI library for the nRF24L01.
#include "nRF24L01.h"
#include "RF24.h"



#include "HX711.h"

HX711 scale(A1, A0);

int gram = 0;




int veri = 0; //We define the pin to which the sensor is connected.

int data[1];           //We define an array named Data and specify the data to be sent.

#define ce 9
#define csn 10

RF24 radio(ce, csn);    //We define the CE and CSN pins that the RF24 library will use.
const uint64_t pipe = 0xE8E8F0F0E1LL; //We define a pipe address for communication with the buyer.

#define yesil 4
#define mavi 5
#define kirmizi 6
void setup(void) {
  Serial.begin(9600);          //We initiate serial communication to read the sent data.


  pinMode(yesil, OUTPUT);
  pinMode(kirmizi, OUTPUT);
  pinMode(mavi, OUTPUT);
  pinMode(ce, OUTPUT);
  pinMode(csn, OUTPUT);
  scale.setOffset(8459800);
  scale.setScale(100.99f);

  radio.begin();               //We initiate nRF24 communication.
  radio.openWritingPipe(pipe); //We set the address of the receiver to which the program will send data.

}

void loop(void) {
  digitalWrite(mavi, LOW);
 radio.write(data, sizeof(data)); //All the data in the data package will be transferred with the nRF24L module.
  veri++;
   if(veri == 10)
   {
    
  digitalWrite(mavi, HIGH);
  gram = scale.getGram(); 
  data [0] = gram ;  //Read the data in the data packet from the sensor.
  Serial.println(data [0]);        //The read data[0] can be displayed on the serial monitor.
  
veri=0;
   }
delay(10);
  if (gram > 10)
  {
    digitalWrite(kirmizi, LOW);
    digitalWrite(yesil, HIGH);
  
  }
  if (gram <= 10)
  {
    digitalWrite(kirmizi, HIGH);
    digitalWrite(yesil, LOW);
  
  }
