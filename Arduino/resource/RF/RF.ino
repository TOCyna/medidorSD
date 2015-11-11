/**
 * An Mirf example which copies back the data it recives.
 *
 * Pins:
 * Hardware SPI:
 * MISO -> 12
 * MOSI -> 11
 * SCK -> 13
 *
 * Configurable:
 * CE -> 8
 * CSN -> 7
 *
 */
#include <SoftwareSerial.h>
#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>

// Variable to hold input and output char of messages
char str;

void setup(){
  Serial.begin(9600);
  
  /*
   * Set the SPI Driver.
   */
  Mirf.spi = &MirfHardwareSpi;
  
  /*
   * Setup pins / SPI.
   */
  Mirf.init();
  
  /*
   * Configure reciving address.
   */
  Mirf.setRADDR((byte *)"serv1");
  
  /*
   * Set the payload length, payload on client and server must be the same.
   */
  Mirf.payload = sizeof(str);

   
  /*
   * To change channel:
   * 
   * Mirf.channel = 10;
   *
   * NB: Make sure channel is legal in your area.
   */

  /*
   * Write config then power up reciver.
   */
  Mirf.config();

  Serial.println("Ready..."); 
}

void loop(){   
  // Recive and Print
  if(!Mirf.isSending() && Mirf.dataReady()){
    Mirf.getData((byte *) &str);
    Serial.print(str);
  }

  // Read and Send
  if(Serial.available()) {
    Mirf.setTADDR((byte *)"serv2");
    str = Serial.read();
    
    // Send
    Mirf.send((byte *)&str);
    
    // Wait everything be sent
    while(Mirf.isSending());
  }
}
