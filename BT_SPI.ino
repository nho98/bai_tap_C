//phần này em chưa demo được, em viết lý thuyết ạ
#define SCLK 2
#define SS 3
#define MOSI 5
#define MISO 6

void setup() {
  // put your setup code here, to run once:
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(5,OUTPUT);//chân MOSI, master out
  pinMode(6,INPUT);//chân MISO, master in
}

//khởi tạo SPI
void SPI_setup(){
  digitalWrite(2,LOW);//chọn chế độ SLK POL = 0
  digitalWrite(5,LOW);//chân MOSI master out, chưa có dữ liệu
  digitalWrite(3,HIGH);//Slave Select nằm ở mức cao khi chưa gửi dữ liệu 
}

//tạo xung clock dùng delay với chu kỳ 10us, còn phụ thuộc vào chip (UNO R3 ATMega328P 16MHz)
void CLOCK(){
  digitalWrite(2,HIGH);
  delayMicroseconds (5);
  digitalWrite(2,LOW);
  delayMicroseconds (5);
}

//chương trình gửi 1 byte = 8 bit
//chọn CHPA = 0
//MISO master out slave in, chân MISO = 5
void SPI_transmit_0(uint8_t data_t){
  uint8_t i = 0;
  uint8_t x = 0;
  digitalWrite(3,LOW);//kéo slave select (chân 3) về 0
  for(i = 0; i<8; i++){
    x = data_t&0x80;
    if(x>0)
      digitalWrite(5,HIGH);//có dữ liệu đi
    else
      digitalWrite(5,LOW);//gửi xong bit dữ liệu
    //có bit rồi mới dùng xung clock để đẩy
    CLOCK();
    data_t = data_t<<1;//dịch trái 1 bit, 01234567
  }
  //truyền xong thì kéo Slave Select (chân 3) lên 1 
  digitalWrite(3,HIGH);
}

//chế độ CPHA = 1
void SPI_transmit_1(uint8_t data_t){
  uint8_t i = 0;
  uint8_t x = 0;
  digitalWrite(3,LOW);//kéo slave select (chân 3) về 0
  for(i = 0; i<8; i++){
    CLOCK();//có xung clock rồi mới đẩy bit
    x = data_t&0x80;
    if(x>0)
      digitalWrite(5,HIGH);//có dữ liệu đi
    else
      digitalWrite(5,LOW);//gửi xong bit dữ liệu
    data_t = data_t<<1;//dịch trái 1 bit, 01234567
  }
  //truyền xong thì kéo Slave Select (chân 3) lên 1 
  digitalWrite(3,HIGH);
}

//chương trình nhận 1 byte
//CHPA = 0
void SPI_receive_0(uint8_t data_r){
  data_r = 0x00;//chưa có dữ liệu, reset các dữ liệu trước về none
  uint8_t i = 0;
  uint8_t tmp = 0; //biến tạm chứ giá trị đọc từ chân 6, MISO
  
  for(i = 0; i<8; i++){
    data_r = data_r<<1; //dịch 1 bit 0 vào để chứa giá trị đọc 
    tmp = digitalRead(6);//đọc giá trị tại chân 6, MISO
    data_r = data_r | tmp;//đưa 1 bit vào
    //có bit rồi mới dùng clock để đẩy
    CLOCK();
  }
  //truyền xong thì kéo Slave Select (chân 3) lên 1 
  digitalWrite(3,HIGH);
  return data_r;
}

void loop() {
  // put your main code here, to run repeatedly:
  uint8_t data_t = 0x81;
  uint8_t data_r = 0x33;
  Serial.begin(9600);
  SPI_transmit_0(data_t);
  //SPI_receive_0(data_r);
}
