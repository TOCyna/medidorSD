/**
 * An Mirf example which copies back the data it recives.
 *
 * 1-GND
 * 2-3.3V
 * 3-CE
 * 4-CSN
 * 5-SCK
 * 6-MOSI
 * 7-MISO
 * 8-IRQ
 *
 * Pins:
 * Hardware SPI:
 * 7-MISO -> 12
 * 6-MOSI -> 11
 * 5-SCK  -> 13
 *
 * Configurable:
 * 3-CE   -> 9
 * 4-CSN  -> 10
 *
 */
#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>

// Variable to hold input and output char of messages
char str;
char myAddress[] = "serv1";
char destinAddress[] = "serv2";

void setup(){
  Serial.begin(9600);
  
  /*
   * Set the SPI Driver.
   */
  Mirf.spi = &MirfHardwareSpi;
  Mirf.cePin = 9;
  Mirf.csnPin = 10;
  /*
   * Setup pins / SPI.
   */
  Mirf.init();
  
  /*
   * Configure reciving address.
   */
  Mirf.setRADDR((byte *)myAddress);
  
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
  Mirf.setTADDR((byte *)destinAddress);

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
    // Read char from serial
    str = Serial.read();
    
    // Send char
    Mirf.send((byte *)&str);
    
    // Wait everything be sent
    while(Mirf.isSending());
  }
}
