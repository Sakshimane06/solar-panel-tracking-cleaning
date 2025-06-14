#include <LiquidCrystal_I2C.h>
#include <virtuabotixRTC.h>

#define cleaningTime 9  //24hr clock
#define ldr1pin 34
#define ldr2pin 35

#define eastpin 18
#define westpin 19

#define spraypin 23
#define clean1pin 5
#define clean2pin 15

virtuabotixRTC myRTC(32, 33, 25); //CONNECTION SECUENCE ->SCL,SDA,RST->
// set the LCD number of columns and rows
int lcdColumns = 16;
int lcdRows = 2;
int ldr1, ldr2;
// set LCD address, number of columns and rows
// if you don't know your display address, run an I2C scanner sketch
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);  

void setup()
{
  // initialize LCD
  lcd.begin();                   
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print(" Solar Tracking");
  lcd.setCursor(0,1);
  lcd.print("  And Cleaning");
  delay(3000);
  lcd.clear();
  lcd.print("MODERN COLLEGE");
  lcd.setCursor(0,1);
  lcd.print("OF ENGG. PUNE");
  delay(3000);
  lcd.clear();
  pinMode(eastpin, OUTPUT);
  pinMode(westpin, OUTPUT);
  pinMode(clean1pin, OUTPUT);
  pinMode(clean2pin, OUTPUT);
  pinMode(spraypin, OUTPUT);
  digitalWrite(spraypin,HIGH);
  // Set the current date, and time in the following format:
  // seconds, minutes, hours, day of the week, day of the month, month, year
  //myRTC.setDS1302Time(0, 27, 14, 3, 8, 4, 2025);//uncomment this line to set date and command
  //myRTC.updateTime();//UPDATE TIME
  lcd.setCursor(8,0);
  myRTC.updateTime();//UPDATE TIME
  lcd.print("Time ");
  lcd.print(myRTC.hours);
  lcd.print(":");
  lcd.print(myRTC.minutes);
  lcd.print(":");
  lcd.print(myRTC.seconds);
}

void loop()
{
  lcd.clear(); 
  lcd.setCursor(0,0);
  ldr1 = analogRead(ldr1pin);
  ldr1 = ldr1 / 40;
  lcd.print("E ");
  lcd.print(ldr1);
  
  lcd.setCursor(0,1);
  ldr2 = analogRead(ldr2pin);
  ldr2 = ldr2 / 40;
  lcd.print("W ");
  lcd.print(ldr2);
  delay(200);

  if ((ldr1 - ldr2) > 20)
  {
    lcd.setCursor(5,0); lcd.print("<<");
    digitalWrite(eastpin, HIGH);
    digitalWrite(westpin, LOW);
    delay(200);
    digitalWrite(eastpin, LOW);
    digitalWrite(westpin, LOW);
    delay(500);
  }
  if ((ldr2 - ldr1) > 20)
  {
    lcd.setCursor(5,1); lcd.print("<<");
    digitalWrite(eastpin, LOW);
    digitalWrite(westpin, HIGH);
    delay(200);
    digitalWrite(eastpin, LOW);
    digitalWrite(westpin, LOW);
    delay(500);
  }
  lcd.setCursor(8,0);
  myRTC.updateTime();//UPDATE TIME
  lcd.print(myRTC.hours);
  lcd.print(":");
  lcd.print(myRTC.minutes);
  lcd.print(":");
  lcd.print(myRTC.seconds);
  lcd.print(" ");
  int h = myRTC.hours;
  int m = myRTC.minutes;
  int s = myRTC.seconds;
  if (h == cleaningTime & m == 04 & s == 0)
  {
    lcd.setCursor(5,1);
    lcd.print("TimeToClean");
    digitalWrite(spraypin, LOW);
    delay(2000);
    digitalWrite(spraypin, HIGH);
    delay(1000);
    digitalWrite(clean1pin, HIGH);
    digitalWrite(clean2pin, LOW);
    delay(52000);
    digitalWrite(clean1pin, LOW);
    digitalWrite(clean2pin, LOW);
    delay(1000);
    digitalWrite(clean1pin, LOW);
    digitalWrite(clean2pin, HIGH);
    delay(52000);
    digitalWrite(clean1pin, LOW);
    digitalWrite(clean2pin, LOW);
    delay(1000);
    lcd.setCursor(5,1);
    lcd.print("  Cleaned! ");
    delay(1000);
    lcd.clear();
  }
  delay(500);
}
