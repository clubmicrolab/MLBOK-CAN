#include "Thrust.h"
int DIR = 1;//directia initiala se considera inainte
void mvForward(int speed){
  //digitalWrite(ENPIN, HIGH);
  delay(100);
  int speedToMotor = map(speed, 0, 10, 0, 255);
  if(DIR==1){
      digitalWrite(DIRPIN_F, HIGH);//seteaza directia de rotatie
      digitalWrite(DIRPIN_B, LOW); 
      analogWrite(ENPIN, abs(speedToMotor)); //seteaza viteza motorului
  }
  else{
    DIR=1; //daca se doreste schimbarea directiei, incetineste pana la 0, apoi schimba polaritatea motorului
    analogWrite(ENPIN, 0);
    digitalWrite(DIRPIN_F, HIGH);
    digitalWrite(DIRPIN_B, LOW);
    delay(100);
    analogWrite(ENPIN, abs(speedToMotor));

  }
      Serial.println(speed);  
} 
//analog rotirea in directia inversa
void mvBackward(int speed){
    //digitalWrite(ENPIN, HIGH);
    delay(100);
  int speedToMotor = map(speed, 0, 10, 0, 255);
        if(DIR==0){
        digitalWrite(DIRPIN_F, LOW);
        digitalWrite(DIRPIN_B, HIGH);
        analogWrite(ENPIN, abs(speedToMotor));
        }
  else{
    DIR=0;
    analogWrite(ENPIN, 0);
    digitalWrite(DIRPIN_F, LOW);
    digitalWrite(DIRPIN_B, HIGH);
    delay(100);
    analogWrite(ENPIN, abs(speedToMotor));

  }
}
//daca nu vin mesaje de viteza pe CAN, opreste
void stop(){
  analogWrite(ENPIN, 0);
  delay(100);
  //digitalWrite(ENPIN, LOW);
  digitalWrite(DIRPIN_B, LOW);
  digitalWrite(DIRPIN_F, LOW);
}