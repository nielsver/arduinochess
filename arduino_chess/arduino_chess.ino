#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
int latch=9;  //74HC595  pin 9 STCP
int clock=10; //74HC595  pin 10 SHCP
int data=8;   //74HC595  pin 8 DS
int buzzer = 5;
int led1 = 7;
int led2 = 6;
int button1 = 2;
int button2 = 3;
int resetbutton = 13;
int aantalspellen = 0;
int gemiddeldespeelduur = 0;
int meestgewonnen;
int langstespel;


unsigned char table[]=
{0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c
,0x39,0x5e,0x79,0x71,0x00};

void setup() {
  lcd.init();//initialize LCD
  lcd.clear();
  lcd.backlight(); //schakel backlight in
  pinMode(latch,OUTPUT);
  pinMode(clock,OUTPUT);
  pinMode(data,OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(resetbutton, INPUT);
}
void Display(unsigned char num)
{

  digitalWrite(latch,LOW);
  shiftOut(data,clock,MSBFIRST,table[num]);
  digitalWrite(latch,HIGH);
  
}
void testbutton() {
  int buttonstate = digitalRead(button1);
  if(buttonstate == HIGH) {
  tone(buzzer, 1000);
  delay(1000);
  noTone(buzzer);
  }
}
void toonstatistieken() {
  
}

void loop() { 
  // begin met toonstatistieken tot je de resetknop(startknop) indrukt 
  //int spelgedaan = 0, als het spel echt gedaan is wordt die 1 en gaat de functie eindevanspel() in 
  //als je op de resetknop druk dan kom je terug bij toonstatistieken terecht en dan moet je nog eens op de resetknop drukken omo het spel opnieuw te starten
  //je hebt 2 funties witaanzet en zwartaanzet
  //while(timer > 0 && drukknop == LOW)
  
  
  
  /*Display(1);
  delay(500);
  Display(2);
  delay(500);
  Display(3);
  delay(500);
  Display(4);
  delay(500);
  Display(5);
  delay(500);
  Display(6);
  delay(500);
  Display(7);
  delay(500);
  Display(8);
  delay(500);
  Display(9);
  delay(500);
  testbutton();
  tone(buzzer, 1000);
  delay(1000);
  noTone(buzzer);
  digitalWrite(led1, HIGH);
  delay(1000);
  digitalWrite(led2, HIGH);
  delay(1000);*/
  
}
