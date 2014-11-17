/*
  SD card basic file example
 
 This example shows how to create and destroy an SD card file   
 The circuit:
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4
 
 created   Nov 2010
 by David A. Mellis
 modified 9 Apr 2012
 by Tom Igoe
 
 This example code is in the public domain.
     
 */
#include <SD.h>

File myFile;
int readStatus = 0;

void setup()
{
 // Open serial communications and wait for port to open:
  Serial.begin(9600);
   while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }


  Serial.print("Initializing SD card...");
  // On the Ethernet Shield, CS is pin 4. It's set as an output by default.
  // Note that even if it's not used as the CS pin, the hardware SS pin 
  // (10 on most Arduino boards, 53 on the Mega) must be left as an output 
  // or the SD library functions will not work. 
  pinMode(8, OUTPUT);

  if (!SD.begin(8)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

  if (SD.exists("alice4.bin")) {
    Serial.println("alice4.bin exists.");
    
  }
  else {
    Serial.println("alice3.bin doesn't exist.");
  }
DDRC = DDRC | B00001111;    //set analog pins 0-3 as digital outputs


}

void loop()

{
  byte toPort;
  File musicfile = SD.open("alice5.bin");
  while(readStatus != -1){
   readStatus = musicfile.read();
   //Serial.println(readStatus);
   toPort = byte(readStatus);
   PORTC = B00001111 & toPort;
  delayMicroseconds(80);  
  }
  
  musicfile.close();
}
