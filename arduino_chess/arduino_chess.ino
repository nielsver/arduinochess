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
  int botton = 0;
  int game = 0;
  int statu = 0;
  int stat = 0;
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


void loop() { 

    while(botton == 0)
  {
    botton = statistieken();
  }
  while(game == 0){
    game = spelen()
  }
  finish();
}
int statistieken() {
  /* display statistieken + press reset(startbotton) to play if start botton is pressed return 1 else 0 */
}
int spelen() {
  /* als een timer op nul staat of als een speler een knop meer dan 5 seconden duwt return 1 + extra informatie. anders return 0 met daarvoor de code om de timer een seconde te laten zakken of als de knop is ingedrukt van speler wisselen
  hierin kan nog een extra functie worden gemaakt van timer wit en timer zwart ook enzo hangt af wat het makkelijst is*/ 

  while (statu != 1 || stat != 1){
    statu = ctrwhite();
    stat = ctrblack();
  }
  
  
}
void finish() {
  /* 5 seconde durende animatie ofzo te tonen wie gewonnen is + aan te tonen dat het spel gedaan is */
}
int ctrwhite(){
  while (btnstate != HIGH || ctr1 = 0){
    ctr1--;
  }
  if( ctr1 > 0){
    return 0;
  }
  else {
    return 1;
  }
  
}
int ctrblack(){
  while (btnstate != HIGH || ctr1 = 0){
    ctr2--;
  }
  if(ctr2 > 0) {
    return 0;
  }
  else {
    return 1;
  }

} 
  
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
  
