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

void setup()
{

  for (int thisLed = 0; thisLed < ledCount; thisLed++)
  {
    pinMode(ledPins[thisLed], OUTPUT); // 循环设置，把对应的led都设置成输出
  }
}

void loop()
{

  for (int num = 0; num < ledCount; num++) // 熄灭所有led，不同的电路连接也会得到点亮所有led
  {
    digitalWrite(ledPins[num], HIGH);
  }

  for (int num = 0; num < ledCount; num++)
  {
    digitalWrite(ledPins[num], LOW); // 循环顺序点亮led然后等待200ms后熄灭
    delay(200);
    digitalWrite(ledPins[num], HIGH);
  }
}
