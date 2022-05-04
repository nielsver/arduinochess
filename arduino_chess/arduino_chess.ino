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
int resetbutton = 11;
int aantalspellen = 0;
int gemiddeldespeelduur = 0;
int gewonnenwit= 0;
int gewonnenzwart = 0;
int langstespel = 0;
int game = 0;
int i = 0;
int statu = 0;
int stat = 0;
int ctr1 = 3600;
int ctr2 = 3600;
int huidigspel = 0;
int speeltijd = 0;


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

void loop() { 
  reset();
  statistieken();
  aantalspellen++;
  while(game == 0){
    game = spelen();
  }
  speeltijd = speeltijd + huidigspel;
  if (langstespel < huidigspel){
    langstespel = huidigspel;
  }
  gemiddeldespeelduur = speeltijd / aantalspellen;
  if(game == 2){
    gewonnenwit++;
  }
  else{
    gewonnenzwart++;
  }
  finish(game, huidigspel);
}

void statistieken() {
  /* display statistieken + press reset(startbotton) to play if start botton is pressed return 1 else 0 */
    
    lcd.clear();
    lcd.print(String("games played: ") + String(aantalspellen));
    delay(5000);
    lcd.clear();
    lcd.print(String("longest game: "));
    lcd.setCursor(0,1);
    lcd.print(String(langstespel) + String(" seconds")); // als we de timer met minuten gaan doen moet dit veranderd worden
    delay(5000);
    lcd.clear();
    lcd.print(String("avg game time:"));
    lcd.setCursor(0,1);
    lcd.print(String(gemiddeldespeelduur) + String(" seconds"));
    delay(5000);
    lcd.clear();
    if( gewonnenwit > gewonnenzwart) {
      lcd.print(String("white has won: "));
      lcd.setCursor(0,1);
      lcd.print(String(gewonnenwit)+String("-")+String(gewonnenzwart)); //eventueel 63%w/r
      delay(5000);
    }
    else if(gewonnenwit == gewonnenzwart) {
      lcd.print(String("games are tied:"));
      lcd.setCursor(0,1);
      lcd.print(String(gewonnenwit)+String("-")+String(gewonnenzwart));
      delay(5000);
    }
    else {
      lcd.print(String("black has won:"));
      lcd.setCursor(0,1);
      lcd.print(String(gewonnenzwart)+String("-")+String(gewonnenwit));
      delay(5000);
    }
    int y = 0;
    while (y == 0){
      int resetbuttonstate = digitalRead(resetbutton);
      lcd.clear();
      lcd.print(String("press start"));
      delay(100);
      if(resetbuttonstate == HIGH)
      {
        y = 1;
        lcd.clear();
      }
    } 
}

int spelen() {
  /* als een timer op nul staat of als een speler een knop meer dan 5 seconden duwt return 1 + extra informatie. anders return 0 met daarvoor de code om de timer een seconde te laten zakken of als de knop is ingedrukt van speler wisselen
  hierin kan nog een extra functie worden gemaakt van timer wit en timer zwart ook enzo hangt af wat het makkelijst is*/ 

  while (statu != 1 || stat != 1){
    statu = ctrwhite();
    stat = ctrblack();
  }
  if(statu == 1){
    return 2;
  }
  else {
    return 1;
  }
}

int ctrwhite(){
  int buttonstate1 = digitalRead(button1);
  lcd.print(String("wit aan zet"));
  while (buttonstate1 != HIGH || ctr1 != 0){
    int buttonstate1 = digitalRead(button1);
    
    digitalWrite(led1,HIGH);
    //Display(ctr1);
    delay(1000);
    huidigspel++;
    ctr1--;
    
  }
  if( ctr1 > 0){
    digitalWrite(led1, LOW);
    lcd.clear();
    return 0;
  }
  else {
    return 1;
  }
  
}
int ctrblack(){
  int buttonstate2 = digitalRead(button2);
  lcd.print(String("zwart aan zet"));
  while (button2 != HIGH || ctr1 == 0){
    int buttonstate2 = digitalRead(button2);
    
    digitalWrite(led2,HIGH);
    //Display(ctr2);
    delay(1000);
    huidigspel++;
    ctr2--;
  }
  if(ctr2 > 0) {
    digitalWrite(led2, LOW);
    lcd.clear();
    return 0;
  }
  else {
    return 1;
  }

} 
  
void finish(int game, int huidigspel) {
  lcd.print(String("het spel is gedaan"));
  delay(2000);
  lcd.print(String("speeltijd: ") + String(huidigspel) + String("seconden"));
  lcd.clear();
  if(game == 2){
    lcd.print(String("white has won!!!"));
    tone(buzzer, 1000);
    for(int i = 0; i<5;i++){
    digitalWrite(led1, HIGH);
    delay(500);
    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
    delay(500);
    digitalWrite(led2, LOW);
    }
  }
  else{
    lcd.print(String("black has won!!!"));
    tone(buzzer, 1000);
    for(int i = 0; i<5;i++){
    digitalWrite(led1, HIGH);
    delay(500);
    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
    delay(500);
    digitalWrite(led2, LOW);
  }
  }
 

  
  /* 5 seconde durende animatie ofzo te tonen wie gewonnen is + aan te tonen dat het spel gedaan is */
}

void reset(){
  game = 0;
  statu = 0;
  stat = 0;
  lcd.clear();
  noTone(buzzer);
  huidigspel = 0;
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
  
