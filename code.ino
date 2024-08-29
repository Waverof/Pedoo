#include <MPU6050_tockn.h>    //khai bao thu vien cb gia toc
#include <Wire.h>             //khai bao thu vien giao tiep I2C
#include "LCD_1602.h"         //Khai bao thu vien LCD
MPU6050 mpu6050(Wire);        //Dat ten cho cam bien
float ax, ay, az, a, g;
float ax_old, ay_old , az_old;
int step_count = 0;
int tam = 1;
float distanceinonestep = 71;
long timer = 0;

void setup() {
  pinMode(6, INPUT_PULLUP); //Khai bao nut nhan
  Wire.begin();             //Khoi tao giao tiep I2C
  lcd1602_init();
  lcd1602_set(1, 0);
  lcd1602_string("DANG KHOI DONG"); //Hien thi len LCD dong chu "KHOI DONG"
  lcd1602_set(2, 5);
  lcd1602_string("MODULE");
  mpu6050.begin();        //Khoi dong module
  mpu6050.calcGyroOffsets(true);  //Can bang cam bien moi lan chay lai chuong trinh
  //Nếu tham số truyền vào là FALSE thì cảm biến sẽ lấy thông số trước đó
}
void loop() {
  mpu6050.update();
  if (millis() - timer > 300) {
    //Delay sau mỗi lần lấy giá trị. Sử dụng hàm millis chứ không dùng hàm delay của IDE
    //hàm millis chạy trên TIMER0

    ax = mpu6050.getAccX();
    ay = mpu6050.getAccY();
    az = mpu6050.getAccZ();
    g = sqrt(ax * ax + ay * ay + az * az);
    a = g - sqrt(ax_old * ax_old + ay_old * ay_old + az_old * az_old);
    if ( a > 0.3)
    {
      step_count++;
      tam = step_count - 1;
      if (digitalRead(6) == 0)
      {
        tam = 0;
        step_count = 0;
      }
      lcd1602_com(LCD_CLEAR);
      lcd1602_set(1, 0);
      lcd1602_string("So Buoc :");
      lcd1602_datas2(2, 0, tam);
      lcd1602_datas(2, 6, a);
    }
    ax_old = ax;  /* Cap nhat gia tri cu cua gia toc truc x,y,z */
    ay_old = ay;
    az_old = az;
    timer = millis();
  }
}
