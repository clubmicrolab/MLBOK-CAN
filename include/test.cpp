
#include <SPI.h> 
#include "mcp2515_can.h"
const int SPI_CS_PIN = 10;
mcp2515_can CAN(SPI_CS_PIN);

void setup() {
  Serial.begin(9600); 
  
  while (CAN_OK != CAN.begin(CAN_500KBPS)) {             
        Serial.println("CAN init fail, retry...");
        delay(100);
    }
  Serial.println("CAN init ok!");
  delay(100); 
}
void loop() {
      unsigned char msg[2] ={'F', '9'}; // front
      CAN.sendMsgBuf(0x01, 0, 2, msg);
}