

/*
Four bit music player by Aleks Zosuls Nov 2014 using code
 created   Nov 2010
 by David A. Mellis and
 modified 9 Apr 2012
 by Tom Igoe
 
 This example code is in the public domain.

 Program reads a binary file from a flash card and plays it out of the
 lower nibble of port C. Note, these are usually analog input pins <0:4>.
 A companion file was written in MATLAB that decodes an m4a file and converts it
 to four bit music. The high nibble is not used
 
 The circuit:
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 8
 

     
 */
#include <SD.h>
#include <SPI.h>

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
  // or the SD library functions will not work. Aleks used the Sparkfun micro
  //SD shield which uses pin 8 as CS
  pinMode(4, OUTPUT);

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
 
DDRC = DDRC | B00001111;    //set analog pins 0-3 as digital outputs


}

void loop()
{
  //if flie exists run the output loop
  if (SD.exists("lana1.bin")) {
    Serial.println("lana1.bin exists."); //tell us it worked
    byte toPort;
    File musicfile = SD.open("lana1.bin");  //open music file
    
    while(readStatus != -1){  //loop until at end of music file
     readStatus = musicfile.read();
     //Serial.println(readStatus);
     toPort = byte(readStatus);  //cast byte as binary
     PORTC = B00001111 & toPort; //write lower nibble on portc use mask to protect high nibble
    delayMicroseconds(80);  //hand adjusted delay that sets sample update rate
    } //end of read status while loop
    musicfile.close();  //always close your file io
    }  //end of if exists block
  else {  //tell us if the file doesnt exist
    Serial.println("the file requested doesn't exist on the SD card.");
    }
// sit in an endless loop because we dont want to hear this song forever
while(1){
}
    
}
