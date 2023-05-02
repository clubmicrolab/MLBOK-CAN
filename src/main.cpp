#include <Arduino.h>

#include <SPI.h>
#include "mcp2515_can.h"
#include "Thrust.h"

enum msg_type
{
  RX,
  TX
};
struct CAN_Message
{
  unsigned char payload[MAX_PAYLOAD_SZ];
  msg_type type;
}; //structura care va contine toata informatia dintr-un mesaj

CAN_Message CAN_Matrix[MAX_MODULES]; //matrice care va contine toate mesajele de pe retea

mcp2515_can CAN(SPI_CS_PIN); // Seteaza pin-ul de Chip Select

void setup()
{
  //initializarea pinilor care vor fi folositi
  //pinMode(PWMPIN, OUTPUT);
  pinMode(ENPIN, OUTPUT);
  pinMode(DIRPIN_F, OUTPUT);
  pinMode(DIRPIN_B, OUTPUT);
  digitalWrite(DIRPIN_F, LOW);
  digitalWrite(DIRPIN_B, LOW);
  digitalWrite(ENPIN, LOW);
  //inserarea in matricea CAN a propriului ID si informatie
  unsigned char self_buf[] = {0, 0};
  CAN_Matrix[ID].payload[0] = self_buf[0];
  CAN_Matrix[ID].payload[1] = self_buf[1];
  CAN_Matrix[ID].type = TX;

  Serial.begin(9600);

  while (!Serial)
  {
  };

  while (CAN_OK != CAN.begin(CAN_500KBPS))
  { // initiaza bus-ul de CAN
    Serial.println("CAN init fail, retry...");
    delay(100);
  }
  Serial.println("CAN init ok!");
  delay(100);
}
int time = millis();
void loop()
{
  digitalWrite(ENPIN, LOW);
  unsigned char len = 0;
  unsigned char buf[MAX_PAYLOAD_SZ];
  if (CAN_MSGAVAIL == CAN.checkReceive())
  {                            // verifica daca sunt date pe CAN
    CAN.readMsgBuf(&len, buf); // citeste datele,  len: lungimea, buf: mesajul
    if (buf[0] == 'F')
    { //daca primul byte din buf este 'F', mergi inainte
      if (buf[1] == 'M')
        mvForward(10); //daca al doilea byte este M, mergi cu viteza 10 (maxima)
      else
        mvForward(buf[1]); //daca nu, mergi cu viteza egala cu al doilea byte
      time = millis();
    } //analog functioneaza rotirea inversa
    else if (buf[0] == 'B')
    {
      if (buf[1] == 'M')
        mvBackward(10);
      else
        mvBackward(buf[1]);
      time = millis();
    }
    CAN_Matrix[CAN.getCanId()].type = RX;
    CAN_Matrix[CAN.getCanId()].payload[0] = buf[0];
    Serial.println("ID, Type, Payload[0], Payload[1]");
    for (int i = 0; i < MAX_MODULES; i++)
    {
      Serial.print(i);
      Serial.print(" ");
      Serial.print(CAN_Matrix[i].type);
      Serial.print(" ");
      Serial.print(CAN_Matrix[i].payload[0]);
      Serial.print(" ");
      Serial.print(CAN_Matrix[i].payload[1]);
      Serial.println();
    }
  }
  else if (millis() - time > 100)
  {
    stop();
    time = millis();
  }
  //else stop();
}