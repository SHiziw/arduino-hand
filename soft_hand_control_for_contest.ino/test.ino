const int ledCount = 10; // led总共的个数
String comdata = "";
int stp = 0;

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
    Serial.println(" turns on.");
    digitalWrite(ledPins[pin], LOW); 
  }else digitalWrite(ledPins[pin], HIGH);
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
  Serial.println("cmd is working");
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
    while(!stp){
      turnOn(plc, place[plc]);
      break;
    }    
  }
}

void hangOn(double time){
  while(!stp){
    delay(time);
    break;
  }
  while (Serial.available() > 0)  
  {
      comdata += char(Serial.read());
      delay(2);
  }
  if (comdata.length() > 0){
    if (comdata.equals("0050\r\n")){ //训练5
      comdata = "";
      stp = 1;
    }
    comdata = "";
  }
}

void f001(double rate){ /* 001排气 */
long cmd1[1][10] = {1,1,1,1,1,1,1,0,0,0};
Serial.println("f001 is ok");
handleCmd(cmd1[0]);
double peroid = 3000.0;
hangOn(peroid*rate);      
}

void f002(double rate){       /*002关停*/
long cmd1[1][10] = {0,0,0,0,0,0,0,0,0,0};
handleCmd(cmd1[0]);
double peroid = 1000.0;
hangOn(peroid*rate);
}

void f11(double rate){   /*五指同时伸展11*/
long cmd1[1][10] = {1,1,1,1,1,0,0,0,1,1};
handleCmd(cmd1[0]);
double peroid = 5000.0;
hangOn(peroid*rate);

}

void f12(double rate){  /*五指同时屈曲12*/
long cmd1[1][10] = {1,1,1,1,1,0,0,1,0,1};
handleCmd(cmd1[0]);
double peroid = 5000.0;
hangOn(peroid*rate);
}

void f13(double rate){     /*单指依次伸展13*/
  long cmd15[15][10] = {0,0,0,0,1,0,0,0,1,1,0,0,0,0,1,0,0,0,1,1,0,0,0,0,0,0,1,0,0,1,0,0,0,1,0,0,0,0,1,1,0,0,0,1,0,0,0,0,1,1,0,0,0,0,0,0,1,0,0,1,0,0,1,0,0,0,0,0,1,1,0,0,1,0,0,0,0,0,1,1,0,0,0,0,0,0,1,0,0,1,0,1,0,0,0,0,0,0,1,1,0,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,0,0,1,1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,0,0,0};
  for(int i = 0;i<16;i++){  //15 in total.
    handleCmd(cmd15[i]);
    double peroid = 1000.0; 
    hangOn(peroid*rate);
  }
}

void f14(double rate){
  long cmd15[15][10] = {0,0,0,0,1,0,0,1,0,1,0,0,0,0,1,0,0,1,0,1,0,0,0,0,0,0,1,0,0,1,0,0,0,1,0,0,0,1,0,1,0,0,0,1,0,0,0,1,0,1,0,0,0,0,0,0,1,0,0,1,0,0,1,0,0,0,0,1,0,1,0,0,1,0,0,0,0,1,0,1,0,0,0,0,0,0,1,0,0,1,0,1,0,0,0,0,0,1,0,1,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,0,1,0,0,1,1,0,0,0,0,0,0,1,0,1,1,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,1,0,0,0};
  for(int i = 0;i<16;i++){  //15 in total.
    handleCmd(cmd15[i]); 
    double peroid = 1000.0;
    hangOn(peroid*rate);
  }
}

void f15(double rate){
  long cmd15[8][10] = {0,0,0,0,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,0,0,1,1,1,0,0,0,1,1,0,1,1,1,0,0,0,0,1,1,1,1,1,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,0,0,0};
  for(int i = 0;i<16;i++){  //15 in total.
    handleCmd(cmd15[i]); 
    double peroid = 1000.0;
    hangOn(peroid*rate);
  }
}

void f16(double rate){
  long cmd15[8][10] = {0,0,0,0,1,0,0,1,0,1,0,0,0,1,1,0,0,1,0,1,0,0,1,1,1,0,0,1,0,1,0,1,1,1,0,0,0,1,0,1,1,1,1,0,0,0,0,1,0,1,1,1,0,0,0,0,0,1,0,1,1,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,1,0,0,0};
  for(int i = 0;i<16;i++){  //15 in total.
    handleCmd(cmd15[i]); 
    double peroid = 1000.0;
    hangOn(peroid*rate);
  }
}

void f21(double rate){  
long cmd1[1][10] = {1,1,1,1,1,0,0,1,0,1};
handleCmd(cmd1[0]);
double peroid = 3000.0;
hangOn(peroid*rate);
}

void f22(double rate){  
long cmd1[1][10] = {1,1,1,1,1,0,0,0,1,1};
handleCmd(cmd1[0]);
double peroid = 3000.0;
hangOn(peroid*rate);
}

void f31(double rate){  
long cmd1[1][10] = {1,1,1,1,1,1,0,0,1,1};
handleCmd(cmd1[0]);
double peroid = 4000.0;
hangOn(peroid*rate);
}

void f32(double rate){
  long cmd15[5][10] = {0,0,0,0,0,1,0,1,0,1,0,0,0,0,0,1,0,0,1,1,1,0,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,1,0,1,0,0,0,0,0,1,0,0,1,1};
  for(int i = 0;i<16;i++){  //15 in total.
    handleCmd(cmd15[i]); 
    double peroid = 1000.0;
    hangOn(peroid*rate);
  }
}

void f43(double rate){  
long cmd1[1][10] = {0,0,1,1,1,0,0,0,1,1};
handleCmd(cmd1[0]);
double peroid = 3000.0;
hangOn(peroid*rate);
}

void f43_2(double rate){  
long cmd1[1][10] = {1,1,0,0,0,0,0,1,0,1};
handleCmd(cmd1[0]);
double peroid = 500.0;
hangOn(peroid*rate);
}
};


class TrainingOne:controlBase{
public:
void letOn(double rate, int cycle){
f001(1.0);
f002(1.0);
for (int c=0; c<cycle+1; c++){
f11(rate);
f12(rate);
f13(rate);
f14(rate);
f15(rate);
f16(rate);
}
}
};

class TrainingTwo:controlBase{
public:
void letOn21(double rate){
f21(rate);
}
void letOn22(double rate){
f22(rate);
}
};

class TrainingThree:controlBase{
public:
void letOn(double rate){
f31(rate);
f32(rate);
}
};

class TrainingFour:controlBase{
public:
void letOn(double rate){
  f001(rate);
  f002(rate);
}
void letOn1041(double rate){
  f11(rate);
}
void letOn1042(double rate){
  f12(rate);
}
void letOn1043(double rate){
  f43(rate);
  f43_2(rate);
}
void letOn2041(double rate){
  f11(rate);
}
void letOn2042(double rate){
  f12(rate);
}
void letOn2043(double rate){
  f43(rate);
  f43_2(rate);
}
};

class TrainingFive:controlBase{
public:
void letOn(double rate){
stp = 0;
f001(1.0);
f002(1.0);
}
};

void setup()
{ stp = 0;
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
TrainingOne test1;
TrainingTwo test2;
TrainingThree test3;
TrainingFour test4;
TrainingFive test5;
  if (stp){ //训练5
   // comdata = "";
    test5.letOn(1.0);
  }

  while (Serial.available() > 0)  
  {
      comdata += char(Serial.read());
      delay(2);
  }
    if (comdata.length() > 0){
      if (comdata.equals("0010\r\n")){ //训练1
        comdata = "";
        test1.letOn(1.0, 3);
      }
      if (comdata.equals("0021\r\n")){ //训练2
        comdata = "";
        test2.letOn21(1.0);
      }
        if (comdata.equals("0022\r\n")){ //训练2
        comdata = "";
        test2.letOn22(1.0);
      }
      if (comdata.equals("0030\r\n")){ //训练3
        comdata = "";
        test3.letOn(1.0);
      }
      if (comdata.equals("0040\r\n")){ //训练4        
        comdata = "";
        test4.letOn(1.0);
      }
      if (comdata.equals("1041\r\n")){ //训练4
        comdata = "";
        test4.letOn1041(1.0);
      }
      if (comdata.equals("1042\r\n")){ //训练4
        comdata = "";
        test4.letOn1042(1.0);
      }
      if (comdata.equals("1043\r\n")){ //训练4
        comdata = "";
        test4.letOn1043(1.0);
      }      
      if (comdata.equals("2041\r\n")){ //训练4
        comdata = "";
        test4.letOn2041(1.0);
      }
      if (comdata.equals("2042\r\n")){ //训练4
        comdata = "";
        test4.letOn2042(1.0);
      }
      if (comdata.equals("2043\r\n")){ //训练4
        comdata = "";
        test4.letOn2043(1.0);
      }      
      comdata = "";
    }
  Serial.println("loop on");
  delay(2);



  

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