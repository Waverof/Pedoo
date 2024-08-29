/*
   NOI CAC CHAN THEO SO DO SAU:
    ARDUINO   |     LCD
   CHAN 8     ->    D4
   CHAN 9     ->    D5
   CHAN 10    ->    D6
   CHAN 11    ->    D7
   CHAN 12    ->    RS
   CHAN 13    ->    E
   CHAN GND   ->    RW
*/
#define     LCD_CURSOR_OFF          0X0C    //Hien thi man hinh D=1, tat con tro C=0,tat nhay con tro B=0
#define     LCD_BLINK_CURSOR_ON     0X0F    //Hien thi man hinh D=1, bat con tro C=1,bat nhay con tro B=1
#define     LCD_TURN_ON             0X0C    //Lenh Bat LCD nay giong nhu LCD_CURSOR_OFF
#define     LCD_TURN_OFF            0X08    //Lenh Tat LCd
#define     LCD_RETURN_HOME         0X02    //Tro ve dong dau tien, cot dau tien
#define     LCD_ENTRY_MODE_SET      0X04    //
#define     LCD_UNDERLINE_ON        0X0E    //Gach chan ky tu
#define     LCD_MOVE_CURSOR_LEFT    0X10    //Di chuyen con tro sang trai
#define     LCD_MOVE_CURSOR_RIGHT   0X14    //Di chuyen con tro sang phai
#define     LCD_SHIFT_LEFT          0X18    //Dich noi dung sang trai
#define     LCD_SHIFT_RIGHT         0X1E    //Dich noi dung sang phai
#define     LCD_CLEAR               0X01    //Xoa LCD

void lcd1602_init_write(unsigned char a)
{
  delay(5);
  PORTB = PORTB & (~(1 << PB4));     // CHAN RS = RW = PB4 = 0
  PORTB = a >> 4;
  PORTB = PORTB | (1 << PB5);     // CHAN E=PB5=1
  delayMicroseconds(300);
  PORTB = PORTB & (~(1 << PB5));  //CHAN E=PB5 =0
}
void lcd1602_com(unsigned char lcd_com)
{
  delay(5);                       //Delay de kiem tra xem co bao ban cua lcd co khong
  unsigned char temp;
  temp = lcd_com & 0xF0;          //Lay 4 bit dau
  PORTB = temp >> 4;
  PORTB = PORTB & (~(1 << PB4));  //Cho RS = PB4 = 0 se ghi vao thanh ghi IR 4 bit dau de ra lenh cho LCD
  PORTB = PORTB | (1 << PB5);     //CHAN E=PB5 = 1 Cho phep lenh vao chan D4-->D7
  delayMicroseconds(300);
  PORTB = PORTB & (~(1 << PB5));  //Ngat cho phep lenh vao chan D4-->D7
  delayMicroseconds(300);

  temp = (lcd_com << 4) & 0xF0;   //Lay 4 bit cuoi tuong tu 4 bit dau
  PORTB = temp >> 4;
  PORTB = PORTB & (~(1 << PB4));
  PORTB = PORTB | (1 << PB5);
  delayMicroseconds(300);
  PORTB = PORTB & (~(1 << PB5));
}
void lcd1602_init()
{
  DDRB = 0b00111111;
  delayMicroseconds(300);
  lcd1602_init_write(0x30);
  delayMicroseconds(300);
  lcd1602_init_write(0x30);
  delayMicroseconds(300);
  lcd1602_init_write(0x30);
  delayMicroseconds(300);
  lcd1602_init_write(0x20);
  delayMicroseconds(300);
  lcd1602_com(LCD_TURN_ON);
  delayMicroseconds(300);
  lcd1602_com(0x28);              //cau hinh che do 4 bit DL=0, 2 dong hien thi N=1, front ky tu 5x7 F=0
  delayMicroseconds(300);
  lcd1602_com(LCD_CLEAR);         //xoa lcd
  delayMicroseconds(300);
}
void lcd1602_string(const char *cy)
{
  while (*cy)
  {
    delay(5);                   //delay de kiem tra xem co bao ban cua lcd co khong
    unsigned char temp;
    temp = *cy & 0xF0;
    PORTB = temp >> 4;             //Lay duoc 4 bit dau cua du lieu gan vao PORTB
    PORTB = PORTB | (1 << PB4); //thiet lap rs=1, rw=0 de du lieu tu chan PORTB truyen vao LCD,che do ghi vao DR, DR chua du lieu
    PORTB = PORTB | (1 << PB5); //cho phep D4-->D7
    delayMicroseconds(300);
    PORTB = PORTB & (~(1 << PB5)); //khong cho phep
    delayMicroseconds(300);     //tao delay de LCD nhan cac bit du lieu tiep theo, neu khong thi du lieu se bi mat

    temp = (*cy << 4) & 0xF0;   //thuc hien tuong tu nhu vay voi 4 bit cuoi
    PORTB = temp >> 4;
    PORTB = PORTB | (1 << PB4); //thiet lap rs=1, rw=0 de du lieu tu chan PORTB truyen vao LCD, che do ghi vao DR, DR chua du lieu
    PORTB = PORTB | (1 << PB5); //cho phep D4-->D7
    delayMicroseconds(300);
    PORTB = PORTB & (~(1 << PB5)); //khong cho phep
    cy++;                       //nhan cac chuoi tiep theo cho den het chuoi
  }
  delayMicroseconds(300);
}
void lcd1602_data(unsigned char data)
{
  delay(5);                   //delay de kiem tra xem co bao ban cua lcd co khong
  unsigned char temp;
  temp = data & 0xF0;
  PORTB = temp >> 4;          //Lay duoc 4 bit dau cua du lieu gan vao PORTB
  PORTB = PORTB | (1 << PB4); //thiet lap rs=1, rw=0 de du lieu tu chan PORTB truyen vao LCD,che do ghi vao DR, DR chua du lieu
  PORTB = PORTB | (1 << PB5); //cho phep D4-->D7
  delayMicroseconds(300);
  PORTB = PORTB & (~(1 << PB5)); //khong cho phep
  delayMicroseconds(300);     //tao delay de LCD nhan cac bit du lieu tiep theo, neu khong thi du lieu se bi mat

  temp = (data << 4) & 0xF0;  //thuc hien tuong tu nhu vay voi 4 bit cuoi
  PORTB = temp >> 4;
  PORTB = PORTB | (1 << PB4); //thiet lap rs=1, rw=0 de du lieu tu chan PORTB truyen vao LCD, che do ghi vao DR, DR chua du lieu
  PORTB = PORTB | (1 << PB5); //cho phep D4-->D7
  delayMicroseconds(300);
  PORTB = PORTB & (~(1 << PB5)); //khong cho phep
}
void lcd1602_set(unsigned char row, unsigned char colum)
{
  switch (row)
  {
    case 1:
      lcd1602_com(0x80 + colum);  //0x80 la hang 1 cot 1
      break;
    case 2:
      lcd1602_com(0xC0 + colum);  //0xC0 la hang 2 cot 1
      break;
  }
}

void lcd1602_datas(unsigned char row, unsigned char colum, double data)
{
  lcd1602_set(row, colum);

  if (data > 0) {
    lcd1602_data(0x30 + (int)(data / 1));
    lcd1602_string(".");
    lcd1602_data(0x30 + (int)(data * 10) % 10);
    lcd1602_data(0x30 + (int)(data * 100) % 10);
  }
  if (data < 0) {
    lcd1602_string("-");
    lcd1602_data(0x30 + (int)((-data) / 1));
    lcd1602_string(".");
    lcd1602_data(0x30 + (int)((-data) * 10) % 10);
    lcd1602_data(0x30 + (int)((-data) * 100) % 10);
  }
}
void lcd1602_datas2(unsigned char row, unsigned char colum, double data)
{
  lcd1602_set(row, colum);
  lcd1602_data(0x30 + (int)(data / 100));
  lcd1602_data(0x30 + (int)(data / 10) % 10);
  lcd1602_data(0x30 + (int)(data / 1) % 10);


}
