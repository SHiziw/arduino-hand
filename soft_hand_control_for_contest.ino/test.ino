const int ledCount = 10; // led总共的个数
String comdata = "";
long cmd;
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
  if(plc == 1){
    Serial.print(pin);
    Serial.println("is HIGH");
    digitalWrite(ledPins[pin], HIGH); 
  }else digitalWrite(ledPins[pin], LOW);
}

void handleCmd(long series){   //get the command code, like 1010101010, from port 1 to 10.
  place[9] = series / 1 % 10;
  place[8] = series / 10 % 10;
  place[7] = series / 100 % 10;
  place[6] = series / 1000 % 10;
  place[5] = series / 10000 % 10;
  place[4] = series / 100000 % 10;
  place[3] = series / 1000000 % 10;
  place[2] = series / 10000000 % 10;
  place[1] = series / 100000000 % 10;
  place[0] = series / 1000000000 % 10;
  /*place[0] = series / 1 % 10;
  place[1] = series / 10 % 10;
  place[2] = series / 100 % 10;
  place[3] = series / 1000 % 10;
  place[4] = series / 10000 % 10;
  place[5] = series / 100000 % 10;
  place[6] = series / 1000000 % 10;
  place[7] = series / 10000000 % 10;
  place[8] = series / 100000000 % 10;
  place[9] = series / 1000000000 % 10;*/  
  for(int plc=0; plc<ledCount; plc++){
    turnOn(plc, place[plc]);
  }
}

void hangOn(double time){
  delay(time);
}

void releasePressure(int peroid){ /* 001排气 */
cmd = 1111111000;
handleCmd(cmd);
hangOn(peroid);      
}

void halt(int peroid){       /*002关停*/
cmd = 0;
handleCmd(cmd);
hangOn(peroid);
}

void extend5tg(int peroid){   /*五指同时伸展11*/
handleCmd(cmd);
hangOn(peroid);

}

void contract5tg(int peroid){  /*五指同时屈曲12*/
handleCmd(cmd);
hangOn(peroid);

}

void extend1ob(int peroid){     /*单指依次伸展13*/
cmd =  0 ;      //1
handleCmd(cmd); 
hangOn(peroid);
cmd =  0 ;      //2
handleCmd(cmd); 
hangOn(peroid);
cmd =  0 ;      //3
handleCmd(cmd); 
hangOn(peroid);
cmd =  0 ;      //4
handleCmd(cmd); 
hangOn(peroid);

}

void contract5ob(){


}

void contractThumb(){


}
};


class TainingOne:controlBase{
public:
void letOn(int peroid){
releasePressure(peroid);

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
String comdat = "11";
    if (comdat.equals("101")) {
      Serial.println(comdat);
    }

  while (Serial.available() > 0)  
  {
      comdata += char(Serial.read());
      delay(2);
  }
    if (comdata.length() > 0){
      if (comdata.equals("1001\r\n")){ //训练1
        TainingOne test1;
        test1.letOn(1000);
      }
      comdata = "";
    }
  



  

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