//project arduinochess gemaakt door Johan Hoeben en Niels Vervoort
#include <LiquidCrystal_I2C.h>
#include <ShiftDisplay.h>
#include <Wire.h>
LiquidCrystal_I2C lcd(0x27,16,2);
ShiftDisplay display(COMMON_CATHODE, 3);
int buzzer = 9;
int led1 = 8;
int led2 = 12;
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
int ctr1 = 599;
int ctr2 = 599;
int huidigspel = 0;
int speeltijd = 0;
int startpressed = 0;
int endpressed = 0;
int holdtime = 0;

void setup() {
  lcd.init();//initialize LCD
  lcd.clear();
  lcd.backlight(); //schakel backlight in
  pinMode(buzzer, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(resetbutton, INPUT);
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
  
  else if(game ==1){
    gewonnenzwart++;
  }
  else if(game == 3){
    gewonnenwit++;
  }
  else if(game == 4){
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
    Displaylcd(langstespel); // als we de timer met minuten gaan doen moet dit veranderd worden
    delay(5000);
    lcd.clear();
    lcd.print(String("avg game time:"));
    lcd.setCursor(0,1);
    Displaylcd(gemiddeldespeelduur);
    delay(5000);
    lcd.clear();
    if( gewonnenwit > gewonnenzwart) {
      lcd.print(String("white is winning"));
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
      lcd.print(String("black is winning"));
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

  while (statu == 0 && stat == 0){
    lcd.clear();
    statu = ctrwhite();
    if(statu == 0){
      stat = ctrblack();
    }
  }
  if(statu == 1){//wit verliest op tijd
    return 1;
  }
  
  else if(stat ==1){//zwart verliest op tijd
    return 2;
  }
  else if(statu == 3){// wit wint schaakmat
    return 3;
  }
  else if(stat == 3){//zwart wint schaakmat
    return 4;
  }
}

int ctrwhite(){
  int buttonstate1 = digitalRead(button1);
  lcd.clear();
  lcd.print(String("white to move"));
  int test = 0;
  while (buttonstate1 == LOW && ctr1 >= 0){
    buttonstate1 = digitalRead(button1);
    digitalWrite(led1,HIGH);
    Display(ctr1);
    delay(1000);
    huidigspel++;
    ctr1--;    
  }
  while(buttonstate1 == HIGH){
    buttonstate1 = digitalRead(button1);
    startpressed++;
    delay(1);    
  }
  if(startpressed > 3000){
    startpressed = 0;
    return 3;
  }
  startpressed = 0;

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
  lcd.clear();
  lcd.print(String("black to move"));
  while (buttonstate2 == LOW && ctr2 >= 0){
    buttonstate2 = digitalRead(button2);
    digitalWrite(led2,HIGH);
    Display(ctr2);
    delay(1000);
    huidigspel++;
    ctr2--;
  }
    while(buttonstate2 == HIGH){
    buttonstate2 = digitalRead(button2);
    startpressed++;
    delay(1);
  }
  if(startpressed > 3000){
    startpressed = 0;
    return 3;
  }

  startpressed = 0;
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
  lcd.clear();
  lcd.print(String("the game is"));
  lcd.setCursor(0,1);
  lcd.print(String("finished"));
  delay(3000);
  Displaylcd(huidigspel);
  lcd.clear();
  if(game == 2){
    lcd.print(String("white has won"));
    tone(buzzer, 1000, 5000);
    for(int i = 0; i<5;i++){
    digitalWrite(led1, HIGH);
    delay(500);
    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
    delay(500);
    digitalWrite(led2, LOW);
    }
  }
  else if(game ==1){
    lcd.print(String("black has won"));
    tone(buzzer, 1000, 5000);
    for(int i = 0; i<5;i++){
    digitalWrite(led1, HIGH);
    delay(500);
    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
    delay(500);
    digitalWrite(led2, LOW);
  }
  }

  else if(game == 3){
    lcd.print(String("white has won"));
    tone(buzzer, 1000, 5000);
    for(int i = 0; i<5;i++){
    digitalWrite(led1, HIGH);
    delay(500);
    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
    delay(500);
    digitalWrite(led2, LOW);
    }
  }
  else if(game == 4){
    lcd.print(String("black has won"));
    tone(buzzer, 1000, 5000);
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
  ctr1 = 599;
  ctr2 = 599;
  game = 0;
  statu = 0;
  stat = 0;
  lcd.clear();
  noTone(buzzer);
  huidigspel = 0;
}

void Displaylcd(int seconden){
  int minuten;
  if (seconden < 60)
  {
    lcd.print(String("0min ")+String(seconden)+ String("sec"));
  }
  else
  { 
    minuten = seconden / 60;
    seconden = seconden % 60;
    lcd.print(String(minuten) + String("min ") + String(seconden) + String("sec"));
  }
}
void Display(int seconden) {
  int minuten;
  if (seconden < 60)
  {
    display.show(seconden, 1000, ALIGN_RIGHT); // store number and show it for 400ms
    display.setDot(1, true); // add dot to stored number
    //display.show(1000); // show number with dot for 400ms
  }
  else
  { 
    //sec = 599
    minuten = seconden / 60; //min = 9
    seconden = seconden % 60;
    minuten = minuten * 100;
    minuten = minuten + seconden;
    display.show(minuten, 1000, ALIGN_RIGHT); // store number and show it for 400ms
    display.setDot(1, true); // add dot to stored number
    //display.show(1000); // show number with dot for 400ms
  }
}
  
