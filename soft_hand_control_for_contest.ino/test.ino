const int ledCount = 10; // led总共的个数
String comdata = "";
long cmd[20][10];
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

void handleCmd(long *series){   //get the command code, like 1010101010, from port 1 to 10.
  place[9] = series[9];
  place[8] = series[8];
  place[7] = series[7];
  place[6] = series[6];
  place[5] = series[5];
  place[4] = series[4];
  place[3] = series[3];
  place[2] = series[2];
  place[1] = series[1];
  place[0] = series[0];

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

void f001(int peroid){ /* 001排气 */
cmd[0][10] = {1,1,1,1,1,1,1,0,0,0};
handleCmd(cmd[1]);
hangOn(peroid);      
}

void f002(int peroid){       /*002关停*/
cmd[0][10] = {0,0,0,0,0,0,0,0,0,0};
handleCmd(cmd[1]);
hangOn(peroid);
}

void f11(int peroid){   /*五指同时伸展11*/
cmd[0][10] = {0,0,0,0,0,0,0,0,0,0};
handleCmd(cmd[1]);
hangOn(peroid);

}

void f12(int peroid){  /*五指同时屈曲12*/
cmd[0][10] = {0,0,0,0,0,0,0,0,0,0};
handleCmd(cmd[1]);
hangOn(peroid);

}

void f13(int peroid){     /*单指依次伸展13*/
  cmd[15][10] = {};
  for(int i = 0;i<16;i++){  //15 in total.
    handleCmd(cmd[i]); 
    hangOn(peroid);
  }
}

void f14(int peroid){
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

void f15(int peroid){
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

void f16(int peroid){
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

void f21(int peroid){  
cmd = 0;
handleCmd(cmd);
hangOn(peroid);

}

void f22(int peroid){  
cmd = 0;
handleCmd(cmd);
hangOn(peroid);

}
void f31(int peroid){  
cmd = 0;
handleCmd(cmd);
hangOn(peroid);

}

void f32(int peroid){
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

void f43(int peroid){  
cmd = 0;
handleCmd(cmd);
hangOn(peroid);

}

void f44(int peroid){  
cmd = 0;
handleCmd(cmd);
hangOn(peroid);

}
};


class TrainingOne:controlBase{
public:
void letOn(int peroid){
f001(peroid);
}
};

class TrainingTwo:controlBase{
public:
void letOn(int peroid){
f001(peroid);
}
};

class TrainingThree:controlBase{
public:
void letOn(int peroid){
f001(peroid);
}
};

class TrainingFour:controlBase{
public:
void letOn(int peroid){
f001(peroid);
}
};

class TrainingFive:controlBase{
public:
void letOn(int peroid){
f001(peroid);
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
      if (comdata.equals("0010\r\n")){ //训练1
        TrainingOne test1;
        test1.letOn(1000);
      }
      if (comdata.equals("0020\r\n")){ //训练2
        TrainingTwo test2;
        test2.letOn(1000);
      }
      if (comdata.equals("0030\r\n")){ //训练3
        TrainingTwo test3;
        test3.letOn(1000);
      }
      if (comdata.equals("0040\r\n")){ //训练4
        TrainingTwo test4;
        test4.letOn(1000);
      }
      if (comdata.equals("0050\r\n")){ //训练5
        TrainingTwo test5;
        test5.letOn(1000);
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