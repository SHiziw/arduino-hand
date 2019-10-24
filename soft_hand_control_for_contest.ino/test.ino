const int ledCount = 10; // led总共的个数

int ledPins[] = {
    13,
    12,
    11,
    10,
    9,
    8,
    7,
    6,
    5,
    4,
}; // 对应的led引脚





class controlBase{
public:
int place[10];

void turnOn(int pin, int plc){          //turn on port pin, on status plc.
  Serial.println("turnOn");
  if(plc == 1){
    digitalWrite(ledPins[pin], HIGH); 
  }else digitalWrite(ledPins[pin], LOW);
}

void handleCmd(int series){   //get the command code, like 1010101010, from port 1 to 10.
  place[0] = series / 1 % 10;
  place[1] = series / 10 % 10;
  place[2] = series / 100 % 10;
  place[3] = series / 1000 % 10;
  place[4] = series / 10000 % 10;
  place[5] = series / 100000 % 10;
  place[6] = series / 1000000 % 10;
  place[7] = series / 10000000 % 10;
  place[8] = series / 100000000 % 10;
  place[9] = series / 1000000000 % 10;  
  for(int plc=0; plc++; plc<ledCount){
    turnOn(plc, place[plc]);
  }
}

void hangOn(double time){
  delay(time);
}

};



class TainingOne:controlBase{
public:
void releasePressure(int peroid){ /* 001排气 */
handleCmd(1111111000);
hangOn(peroid);      
}

void halt(int peroid){       /*002关停*/
handleCmd(0000000000);
hangOn(peroid);
}


void extend5tg(int peroid){   /*五指同时伸展11*/
handleCmd(0000000000);
hangOn(peroid);

}



void contract5tg(int peroid){  /*五指同时屈曲12*/
handleCmd(0000000000);
hangOn(peroid);

}
void extend1ob(int peroid){     /*单指依次伸展13*/
handleCmd(0000000000); //1
hangOn(peroid);
handleCmd(0000000000); //2
hangOn(peroid);
handleCmd(0000000000);  //3
hangOn(peroid);
handleCmd(0000000000);  //4
hangOn(peroid);

}
void contract5ob(){


}

void contractThumb(){


}
};

void setup()
{
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  for (int thisLed = 0; thisLed < ledCount; thisLed++)
  {
    pinMode(ledPins[thisLed], OUTPUT); // 循环设置，把对应的led都设置成输出
  }
}

void loop()
{




  TainingOne test;
  test.halt(1000);

  /*for (int num = 0; num < ledCount; num++) // 熄灭所有led，不同的电路连接也会得到点亮所有led
  {
    digitalWrite(ledPins[num], HIGH);
  }

  for (int num = 0; num < ledCount; num++)
  {
    digitalWrite(ledPins[num], LOW); // 循环顺序点亮led然后等待200ms后熄灭
    delay(200);
    digitalWrite(ledPins[num], HIGH);
  }*/
}