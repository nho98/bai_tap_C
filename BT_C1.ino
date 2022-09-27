/*
Ý tưởng: đưa lệnh k.tra trạng thái nút nhấn vào trong vòng lặp 8 LED
nếu nút nhấn thay đổi trạng thái thì thoát vòng lặp

Hiện tại: chưa chuyển chế độ ngay lập tức khi nhấn nút 
trạng thái được cập nhật (độ trễ 100) nhưng phải đợi vòng for chạy hoàn tất 8 LED
(trễ 8,2 s mới thực thi)
- Chưa tìm được cú pháp hợp lý để xử lý thoát vòng for.
- Phần cứng còn bị nhiễu tín hiệu input D10, D12
*/

int pinLed[] = {2,3,4,5,6,7,8,9};
const int nut1 = 10;
const int nut2 = 12;
boolean a=0, a1=0;
boolean b=0, b1=0;

void kt_nut1()
{
  if(digitalRead(nut1) == HIGH)
  {
    a = !a;
    while(digitalRead(nut1) == HIGH)
    delay(100);
  }
}

void kt_nut2()
{
  if(digitalRead(nut2) == HIGH)
  {
    b = !b;
    while(digitalRead(nut2) == HIGH)
    delay(100);
  }
}

void tatLed()
{
  for(int i=0; i<8; i++)
    digitalWrite(pinLed[i], LOW);
}

void delayAndCheck()
{  
  if((a==1)&&(b==1))
  {
    static int chay2 = 0;
    for(chay2=0; chay2<8; chay2++)          //chay 8 LED
    {
      for(int i=0; i<10; i++)                
      {
        digitalWrite(pinLed[chay2], HIGH);  
        delay(100);
        a1=a;
        kt_nut1();
        kt_nut2();
        Serial.println("-----");
        Serial.println(a);
        Serial.println(b);
        if(a!=a1)
        {
            tatLed();
            break;
        }
      }
      for(int i=0; i<10; i++)
      {
        digitalWrite(pinLed[chay2], LOW); 
        delay(100); 
        kt_nut1();
        kt_nut2();
        a1=a;
        Serial.println("-----");
        Serial.println(a);
        Serial.println(b);
        if(a!=a1)
        {
            tatLed();
            break;
        }
      }
      }
    }
  else if((a==0)&&(b==0))
  {
    static int chay1=0;
    for(chay1=0; chay1<8; chay1++)       //khi chạy lần 2 thì ko tắt được led cuối, tăng 8 -> 9 thì mất thêm 1s, 
      {
        for(int i=0; i<5; i++)          
        {
          digitalWrite(pinLed[chay1], HIGH);
          digitalWrite(pinLed[chay1-1], LOW);
          delay(100);
          b1=b;
          kt_nut1();
          kt_nut2();
          Serial.println("-----");
          Serial.println(a);
          Serial.println(b);
          if(b!=b1)
          {
            tatLed();
            break;
          }
        }
      }
  }
  else
  {
    tatLed();
    Serial.println("-----");
    Serial.println(a);
    Serial.println(b);
  }
}

void setup() {
  Serial.begin(38400);
  pinMode(nut1, INPUT);
  pinMode(nut2, INPUT);
  for(int i=0; i<8; i++)
    pinMode(pinLed[i], OUTPUT);
}

void loop() {
//  trangthai1 = digitalRead(nut1);
//  trangthai2 = digitalRead(nut2);
  Serial.print("a= ");
  Serial.println(a);
  Serial.print("b= ");
  Serial.println(b);
  delay(100);
  kt_nut1();
  kt_nut2();
  delayAndCheck();
}
