#include <Servo.h>
#include <math.h>
#include <NewPing.h>


#define bitkiYuksekligi 10
#define kol1Uzunlugu 10.5
#define kol2Uzunlugu 12.3


Servo servo1;
Servo servo2;

NewPing sonar (10, 11, 35);
//(triggerPin, echoPin, maxDistance)

float yatayMesafe = 0;

void pos0Hareket()
{
  /*
  Normal pozisyon
  */
  
  servo2.write(0);
  servo1.write(0);
}

void pos1Hareket(float MP_yatay,float MP_dikey)
{
  /*
  Bitkiye ilac puskurtmek icin gerekli pozisyon
  Merkez ve P noktasi arasindaki dikey ve yatay uzaklik
  */
  
  double MP = sqrt(MP_yatay*MP_yatay + MP_dikey*MP_dikey);
  double phi = atan(MP_dikey/MP_yatay) * 180/3.14159;
  double theta = acos((pow(kol1Uzunlugu,2)-pow(kol2Uzunlugu,2)+pow(MP,2))/(2*kol1Uzunlugu*MP)) * 180/3.14159;
  double beta = acos((pow(kol1Uzunlugu,2)+pow(kol2Uzunlugu,2)-pow(MP,2))/(2*kol1Uzunlugu*kol2Uzunlugu)) * 180/3.14159;   

  servo1.write(beta);
  servo2.write(180 - phi - theta);
  delay(100);
}

void setup()
{
  servo1.attach(3);
  servo2.attach(6);
  Serial.begin(9600);
} 

void loop()
{ 
  //Sensörden mesafeyi oku
  yatayMesafe = sonar.ping_cm();
  Serial.println(yatayMesafe);
  
  if (yatayMesafe == 0)
  {
    pos0Hareket();
  }
  else
  {
    pos1Hareket(yatayMesafe,bitkiYuksekligi);
  }
  delay(200);
  
}
