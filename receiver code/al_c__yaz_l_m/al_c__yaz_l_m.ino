
/*---------------------------------------------------------------------------------
 * Project Name: Smart Serum Measurement and Stimulation Device
 * Revision Date: 23.12.2021
 * Author: İrem Aksakal
 * -------------------------------------------------------------------------------

 */



#include <SPI.h>
#include "nRF24L01.h"      //The main library of the nRF24L01.
#include "RF24.h"


int data[1];          //We define an array named Data and specify the data to be sent.


RF24 radio (9, 10);  //We define the CE and CSN pins of the nRF24L module.


const uint64_t pipe = 0xE8E8F0F0E1LL;  //We define the pipe address for communication with the transmitter.




#include <LiquidCrystal.h>


//               (Rs, E, D4, D5, D6 ,D7)
LiquidCrystal lcd(7 , 6, 5 , 4 , 3 , 2);
int kirmizi = A3;
int mavi = A4;
int yesil = A5;
int buzzer = A0;
int buton_pin = A1;
int buton;
int ses=0;

int serum_bos = 50;
int serum_dolu;
int ilk_gelen = 1;
int serum_agirlik = 0;

void setup() {

  pinMode(kirmizi, OUTPUT);
  pinMode(mavi,  OUTPUT);
  pinMode(yesil,  OUTPUT);
  pinMode(buzzer,  OUTPUT);
  pinMode(buton,  INPUT);

  Serial.begin(9600);             //We initiate serial communication.

  lcd.begin(16, 2);

  radio.begin();                  //We initiate nRF24 communication.
  radio.openReadingPipe(1, pipe); //We set the address of the receiver to which the program will send data.
  radio.startListening();




}

void loop() {

  digitalWrite(mavi, HIGH);
 Serial.println(data[0]);         //Show incoming data on serial monitor.

  buton = digitalRead(buton_pin);
  if (radio.available () ) {

    radio.read(data, sizeof(data));  //Read incoming data
    Serial.println(data[0]);         //Show incoming data on serial monitor.

    if (ilk_gelen == 1)
    {
      serum_dolu = data[0]-22 ;
      ilk_gelen = 0;
    }
    digitalWrite(mavi, LOW);
     serum_agirlik = data[0]-22 ;
  int yuzde = map(abs(serum_agirlik), 0, serum_dolu, 0, 100);

  if (buton == HIGH)
  {
 
  lcd.print("Ses OFF");
    ses++;
    delay(500);
    if(ses>1)
    ses=0;
  }
if (yuzde <10){
  lcd.setCursor (0, 0);
  lcd.println(" Serum  Doluluk ");
  lcd.setCursor (0, 1);
  lcd.print("Serum Dolu");
}

    
if (ses==0 && yuzde <20 )
  {
  lcd.setCursor (9, 1);
  lcd.print("Ses ON ");

int bekle = map(abs(yuzde), 0, 9, 0, 200);

  
    digitalWrite(yesil, LOW);
    digitalWrite(kirmizi, HIGH);
    digitalWrite(buzzer, HIGH);
    delay (100);
    digitalWrite(kirmizi, LOW);
    digitalWrite(buzzer, LOW);
    delay (bekle);
  }
if (ses==1 && yuzde <20)
  {
  lcd.setCursor (9, 1);
  lcd.print("Ses OFF");
  
int bekle = map(abs(yuzde), 0, 9, 0, 200);
    digitalWrite(yesil, LOW);
    digitalWrite(kirmizi, HIGH);
    delay (100);
    digitalWrite(kirmizi, LOW);
    delay (bekle);
  
  }

 
if (yuzde >=20)
{
  
    digitalWrite(yesil, HIGH);
}

  }
 


}
