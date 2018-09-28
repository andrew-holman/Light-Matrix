#include <Time.h>
#include <LedControl.h>
#include <math.h>
#include <TimeLib.h>
#define PLAYERX 4

LedControl lc = LedControl(12, 11,10,4);

//Clock Variables
int turnOff = 1;
int tmpx = 32;
int tmpy = 0;
bool tmpz = false;
int currentHour = 0;
int currentMinute = 0;
int currentSecond = 0;
//Button Variables
int inButtonLeft = 2;
int inButtonRight = 3;
int button = 0;
int buttonCheck = 1;
//Game Variables
int stringMover = 32;
int adjustedCount = 0;
int count =0;
bool keepGoing = true;
int strDrawer = 1;
struct Rectangle{
  int col;
  int height;
  int width;
};
Rectangle pillars[5] = {{4, 3, 3},{11, 4, 3},{18, 2, 3},{25, 3, 3},{32, 2, 3}};
int yPosition = 5;

void setup() {
  Serial.begin(9600);
  lc.shutdown(0,false);
  lc.setIntensity(0,0);
  lc.clearDisplay(0);
  lc.shutdown(1, false);
  lc.setIntensity(1,0);
  lc.clearDisplay(1);
  lc.shutdown(2, false);
  lc.setIntensity(2,0);
  lc.clearDisplay(2);
  lc.shutdown(3, false);
  lc.setIntensity(3,0);
  lc.clearDisplay(3);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(inButtonLeft, INPUT_PULLUP);
  pinMode(inButtonRight, INPUT_PULLUP);
  randomSeed(14);
  setTime(19,22, 20,12,3,2018);
 
}

int powerLed(int x, int y, bool power){
  /*if(x > 31){
    x -= 32;
  }
  else if(x<0){
    x+=32;
  }*/
  if(x<=31 && x>=0){
    int address = (31-x) / 8;
    x = x%8;
    lc.setLed(address, y, x, power); 
  } 
}
int powerLed(int x, int y){
  if(x<=31 && x>=0){
    int address = (31-x) / 8;
    x = x%8;
    lc.setLed(address, y, x, true); 
  } 
}

void drawOne(int col, bool power){
  for(int i = 2; i < 6; i++){
    powerLed(col, i, power);
  }
  for(int i=-1; i<2; i++){
    powerLed(col+i, 6, power);
  }
  powerLed(col-1, 3, power);
}
void drawZero(int col,bool power){
  for(int i = 2; i<6; i++){
    powerLed(col+1, i, power);
    powerLed(col-1, i, power);
  }
  for(int i=-1; i<2; i++){
    powerLed(col+i, 6, power);
    powerLed(col+i, 2, power);
  }
}
void drawColon(int col, bool power){
  powerLed(col, 3, power);
  powerLed(col, 5, power);
}
void drawTwo(int col, bool power){
  for(int i=-1; i<2; i++){
    powerLed(col+i, 6, power);
    powerLed(col+i, 4, power);
    powerLed(col+i, 2, power);
  }
  for(int i=0; i<3; i++){
    powerLed(col+1, 2+i, power);
    powerLed(col-1, 4+i, power);
  }
}
void drawThree(int col, bool power){
  for(int i=-1; i<2; i++){
    powerLed(col+i, 6, power);
    powerLed(col+i, 4, power);
    powerLed(col+i, 2, power);
  }
  for(int i=2; i<6; i++){
    powerLed(col+1, i, power);
  }
  
}
void drawFour(int col, bool power){
  for(int i =2; i<=6; i++){
    powerLed(col+1, i, power);
  }
  for(int i =2; i<4; i++){
    powerLed(col-1, i, power);
  }
  for(int i=-1; i<2; i++){
    powerLed(col+i, 4, power);
  }
}
void drawFive(int col, bool power){
  for(int i=-1; i<2; i++){
    powerLed(col+i, 6, power);
    powerLed(col+i, 4, power);
    powerLed(col+i, 2, power);
  }
  for(int i=0; i<3; i++){
    powerLed(col-1, 2+i, power);
    powerLed(col+1, 4+i, power);
  }
}
void drawSix(int col, bool power){
  for(int i = 2; i<6; i++){
    powerLed(col-1, i, power);
  }
  for(int i=4; i<6; i++){
    powerLed(col+1, i, power);
  }
  for(int i=-1; i<2; i++){
    powerLed(col+i, 6, power);
    powerLed(col+i, 4, power);
    powerLed(col+i, 2, power);
  }
}
void drawSeven(int col, bool power){
  for(int i=2; i<=6; i++){
    powerLed(col+1,i, power);
  }
  for(int i=-1; i<2; i++){
    powerLed(col+i, 2, power);
  }
}
void drawEight(int col, bool power){
  for(int i=2; i<= 6; i++){
    powerLed(col-1, i, power);
    powerLed(col+1, i, power);
  }
  powerLed(col, 2, power);
  powerLed(col, 4, power);
  powerLed(col, 6, power);
}
void drawNine(int col, bool power){
  for(int i =2; i<=6; i++){
    powerLed(col+1, i, power);
  }
  for(int i=2; i<=4; i++){
    powerLed(col-1, i, power);
  }
  powerLed(col, 2, power);
  powerLed(col, 4, power);
}
void drawA(int col, bool power){
  for(int i =3; i<=6; i++){
    powerLed(col+3, i, power);
    powerLed(col, i, power);
  }
  powerLed(col+2, 2, power);
  powerLed(col+1, 2, power);
  powerLed(col+1, 4, power);
  powerLed(col+2, 4, power);
}
void drawB(int col, bool power){
  for(int i =2; i<=6; i++){
    powerLed(col, i, power);
  }
  for(int i=1; i<=2; i++){
    powerLed(col+i, 2, power);
    powerLed(col+i, 4, power);
    powerLed(col+i, 6, power);
  }
  powerLed(col+3, 3, power);
  powerLed(col+3, 5, power);
}
void drawC(int col, bool power){
  for(int i=1; i<=3; i++){
    powerLed(col+i, 2, power);
    powerLed(col+i,6, power);
  }
  for(int i=3; i<=5; i++){
    powerLed(col, i);
  }
}
void drawD(int col, bool power){
  for(int i=2; i<=6; i++){
    powerLed(col, i, power);
  }
  powerLed(col+1,2, power);
  powerLed(col+1,6, power);
  powerLed(col+2,3, power);
  powerLed(col+2,5, power);
  powerLed(col+3,4, power);
}
void drawE(int col, bool power){
  drawF(col, power);
  powerLed(col+1, 6, power);
  powerLed(col+2, 6, power);
  powerLed(col+3, 6, power);
  powerLed(col+3,4, power);
}
void drawF(int col, bool power){
  for(int i=1; i<=3; i++){
    powerLed(col+i,2, power);
    powerLed(col+i-1,4, power);
  }
  for(int i=2; i<7; i++){
    powerLed(col, i, power);
  }
  powerLed(col, 4, power);
}
void drawG(int col, bool power){
  for(int i=1; i<=2; i++){
    powerLed(col+i, 2, power);
    powerLed(col+i,6, power);
  }
  for(int i=3; i<=5; i++){
    powerLed(col, i, power);
  }
  powerLed(col+3, 5, power);
  powerLed(col+3,4, power);
  powerLed(col+2, 4, power);
  

}
void drawH(int col, bool power){
  for(int i=2; i<=6; i++){
    powerLed(col, i, power);
    powerLed(col+3,i, power);
  }
  powerLed(col+1, 4, power);
  powerLed(col+2, 4, power);
}
void drawI(int col, bool power){
  for(int i=2; i<=6; i++){
    powerLed(col+1,i, power);
    powerLed(col+2,i, power);
  }
  for(int i=0; i<=3; i++){
    powerLed(col+i,2, power);
    powerLed(col+i,6, power);
  }
}
void drawJ(int col, bool power){
  for(int i=3; i<=5; i++){
    powerLed(col+2,i, power);
  }
  for(int i=1; i<=3; i++){
    powerLed(col+i,2, power);
  }
  powerLed(col+1,6, power);
  powerLed(col,5, power);
}
void drawK(int col, bool power){
  for(int i=2; i<=6; i++){
    powerLed(col,i, power);
  }
  powerLed(col+1, 4, power);
  powerLed(col+2, 5, power);
  powerLed(col+2, 3, power);
  powerLed(col+3, 6, power);
  powerLed(col+3, 2, power);
}
void drawL(int col, bool power){
  for(int i=2; i<=6; i++){
    powerLed(col,i, power);
  }
  for(int i=0; i<=3; i++){
    powerLed(col+i,6, power);
  }
}
void drawM(int col, bool power){
  for(int i=2; i<=6; i++){
    powerLed(col,i, power);
    powerLed(col+3, i, power);
  }
  powerLed(col+1,3, power);
  powerLed(col+2,3, power);
}
void drawN(int col, bool power){
  for(int i=2; i<=6; i++){
    powerLed(col,i, power);
    powerLed(col+3, i, power);
  }
  powerLed(col+1,4, power);
  powerLed(col+2,5, power);
}
void drawO(int col, bool power){
  for(int i=3; i<=5; i++){
    powerLed(col, i, power);
    powerLed(col+3,i, power);
  }
  for(int i=1; i<=2; i++){
    powerLed(col+i, 2, power);
    powerLed(col+i, 6, power);
  }
}
void drawP(int col, bool power){
  for(int i=2; i<=6; i++){
    powerLed(col,i, power);
  }
  for(int i=1; i<=2; i++){
    powerLed(col+i, 2, power);
    powerLed(col+i, 4, power);
  }
  powerLed(col+3, 3, power);
}
void drawQ(int col, bool power){
  drawO(col, power);
  powerLed(col+3, 6, power);
  powerLed(col+2, 5, power);
}
void drawR(int col, bool power){
  for(int i=2; i<=6; i++){
    powerLed(col,i, power);
  }
  for(int i=1; i<=2; i++){
    powerLed(col+i, 2, power);
    powerLed(col+i-1, 4, power);
  }
  powerLed(col+2, 3, power);
  powerLed(col+2,5, power);
  powerLed(col+3,6, power);  
}
void drawS(int col, bool power){
  for(int i=1; i<=3; i++){
    powerLed(col+i, 2, power);
    powerLed(col+i, 4, power);
    powerLed(col+i, 6, power);
  }
  powerLed(col, 3, power);
  powerLed(col+3, 5, power);
}
void drawT(int col, bool power){
  for(int i=2; i<=6; i++){
    powerLed(col+1,i, power);
    powerLed(col+2,i, power);
  }
  for(int i=0; i<=3; i++){
    powerLed(col+i,2, power);
  }
}
void drawU(int col, bool power){
  for(int i=2; i<=5; i++){
    powerLed(col, i, power);
    powerLed(col+3,i, power);
  }
  for(int i=1; i<=2; i++){
    powerLed(col+i, 6, power);
  } 
}
void drawV(int col, bool power){
  for(int i=2; i<=4; i++){
    powerLed(col, i, power);
    powerLed(col+3,i, power);
  } 
  powerLed(col+1, 5, power);
  powerLed(col+3, 5, power);
  powerLed(col+2, 6, power);
}
void drawW(int col, bool power){
  for(int i=2; i<=6; i++){
    powerLed(col,i, power);
    powerLed(col+3, i, power);
  }
  powerLed(col+1,5, power);
  powerLed(col+2,5, power);
}
void drawX(int col, bool power){
  for(int i=0; i<=3;i++){
    powerLed(col+i,i+3, power);
    powerLed(col+3-i,i+3, power);
  }
}
void drawY(int col, bool power){
  for(int i=2; i<=3; i++){
    powerLed(col, i, power);
    powerLed(col+3,i, power);
  }  
  for(int i=1; i<=2; i++){
    powerLed(col+i, 4, power);
    powerLed(col+i, 5, power);
    powerLed(col+i, 6, power);
  }
}
void drawZ(int col, bool power){
  for(int i=0; i<=3; i++){
    powerLed(col+i, 3, power);
    powerLed(col+i, 6, power);
  } 
  for(int i=1; i<=2;i++){
    powerLed(col+3-i,i+3, power);
  }   
}
void drawBlock(int col, bool power){
  for(int i= 0; i<=2; i++){
    for(int j=2; j<=6; j++){
      powerLed(col+i, j, power);
    }
  }
}
void totalClear(){
  for(int i = 0; i<4; i++){
    lc.clearDisplay(i);
  }
}

void runChar(){
  drawOne(tmpx, true);
  drawZero(tmpx+4, true);
  drawColon(tmpx+7, true);
  drawTwo(tmpx+10, true);
  drawNine(tmpx+14, true);
  delay(500);
  totalClear();
  if(tmpx >= 31){
    tmpx=0;
  }
  else{
    tmpx++;
  }
}
void printNum(int num, int col, bool power){
  if(num == 0){
    drawZero(col, power);
  }
  else if(num == 1){
    drawOne(col, power);
  }
  else if(num == 2){
    drawTwo(col, power);
  }
  else if(num == 3){
    drawThree(col, power);
  }
  else if(num == 4){
    drawFour(col, power);
  }
  else if(num == 5){
    drawFive(col, power);
  }
  else if(num == 6){
    drawSix(col, power);
  }
  else if(num == 7){
    drawSeven(col, power);
  }
  else if(num == 8){
    drawEight(col, power);
  }
  else if(num == 9){
    drawNine(col, power);
  }
  else if(num == 10){
    drawBlock(col, power);
  }
  else{
    drawColon(col, power);
  }
}
int findNum(int num, int col, bool power){
  int tmpNum = num;
  int nbrDigits = 0;
  /*
   * boolean stillLooking = true;
   * tmpNum = num;
   */
  /* find number of digits -1 */
  while(tmpNum >= 10){
    tmpNum = tmpNum / 10;
    nbrDigits++;
  }
  /* print first digit */
  printNum(num /((int)pow(10, nbrDigits)), col, power);
  col+= 4;
  /* print remaining digits */
  nbrDigits--;
  for(int i = 0; i<= nbrDigits; i++){
    int part1 = (int)pow(10, nbrDigits-i+1);
    int part2 = (int)pow(10,nbrDigits-i);
    printNum(((int)(num%part1) / part2), col, power);
    col+=4;
  }
  return col;
}
int findWeekDay(int col, bool power){
  if(weekday() == 1){
    return drawString("SUN", col, power);
  }
  else if(weekday() == 2){
    return drawString("MON", col, power);
  }
  else if(weekday() == 3){
    return drawString("TUE", col, power);
  }
  else if(weekday() == 4){
    return drawString("WED", col, power);
  }
  else if(weekday() == 5){
    return drawString("THU", col, power);
  }
  else if(weekday() == 6){
    return drawString("FRI", col, power);
  }
  else if(weekday() == 7){
    return drawString("SAT", col, power);
  }
}
int findMonth(int col, bool power){
  if(month() == 1){
    return drawString("JAN", col, power);
  }
  else if(month() == 2){
    return drawString("FEB", col, power);
  }
  else if(month() == 3){
    return drawString("MAR", col, power);
  }
  else if(month() == 4){
    return drawString("APR", col, power);
  }
  else if(month() == 5){
    return drawString("MAY", col, power);
  }
  else if(month() == 6){
    return drawString("JUNE", col, power);
  }
  else if(month() == 7){
    return drawString("JULY", col, power);
  }
  else if(month() == 8){
    return drawString("AUG", col, power);
  }
  else if(month() == 9){
    return drawString("SEP", col, power);
  }
  else if(month() == 10){
    return drawString("OCT", col, power);
  }
  else if(month() == 11){
    return drawString("NOV", col, power);
  }
  else if(month() == 12){
    return drawString("DEC", col, power);
  }
}
int runDate(int col, bool power){
  col = findWeekDay(col, power);
  col+= 3;
  col = findNum(day(), col, power);
  col = findMonth(col, power);
  col+= 3;
  col = drawString("2018", col, power);
  return col;
  
}
void drawHour(int col, bool power){
  currentHour = hour();
  if(hour() < 10){
    col+=4;
  }
  findNum(hour(), col, power);
}
void drawMinute(int col, bool power){
  currentMinute = minute();
  if(minute() < 10){
    col+=4;
  }
  findNum(minute(), col, power);
}
void drawSecond(int col, bool power){
  currentSecond = second();
  if(second() < 10){
    col+=4;
  }
  findNum(second(), col, power);
}
void runClock(int col, bool power){
  drawHour(col, power);
  col+=7;
  drawColon(col, power);
  col+=3;
  drawMinute(col, power);
  col+=7;
  drawColon(col, power);
  col+=3;
  drawSecond(col, power);
}

void findCharacter(char c, int col, bool power){
  if(c == '0'){
    drawZero(col, power);
  }
  else if(c == '1'){
    drawOne(col, power);
  }
  else if(c == '2'){
    drawTwo(col, power);
  }
  else if(c == '3'){
    drawThree(col, power);
  }
  else if(c == '4'){
    drawFour(col, power);
  }
  else if(c == '5'){
    drawFive(col, power);
  }
  else if(c == '6'){
    drawSix(col, power);
  }
  else if(c == '7'){
    drawSeven(col, power);
  }
  else if(c == '8'){
    drawEight(col, power);
  }
  else if(c == '9'){
    drawNine(col, power);
  }
  else if(c == 'A'){
    drawA(col, power);
  }
  else if(c == 'B'){
    drawB(col, power);
  }
  else if(c == 'C'){
    drawC(col, power);
  }
  else if(c == 'D'){
    drawD(col, power);
  }
  else if(c == 'E'){
    drawE(col, power);
  }
  else if(c == 'F'){
    drawF(col, power);
  }
  else if(c == 'G'){
    drawG(col, power);
  }
  else if(c == 'H'){
    drawH(col, power);
  }
  else if(c == 'I'){
    drawI(col, power);
  }
  else if(c == 'J'){
    drawJ(col, power);
  }
  else if(c == 'K'){
    drawK(col, power);
  }
  else if(c == 'L'){
    drawL(col, power);
  }
  else if(c == 'M'){
    drawM(col, power);
  }
  else if(c == 'N'){
    drawN(col, power);
  }
  else if(c == 'O'){
    drawO(col, power);
  }
  else if(c == 'P'){
    drawP(col, power);
  }
  else if(c == 'Q'){
    drawQ(col, power);
  }
  else if(c == 'R'){
    drawR(col, power);
  }
  else if(c == 'S'){
    drawS(col, power);
  }
  else if(c == 'T'){
    drawT(col, power);
  }
  else if(c == 'U'){
    drawU(col, power);
  }
  else if(c == 'V'){
    drawV(col, power);
  }
  else if(c == 'W'){
    drawW(col, power);
  }
  else if(c == 'X'){
    drawX(col, power);
  }
  else if(c == 'Y'){
    drawY(col, power);
  }
  else if(c == 'Z'){
    drawZ(col, power);
  }
  else if(c==' '){
  }
  else{
    drawColon(col, power);
  }  
}
int drawString(String s, int col, bool power){
  for(int i=0; i < s.length(); i++){
    findCharacter(s[i], col, power);
    col+=5;
  }
  return col;
}
void finalClock(){
  button = digitalRead(inButtonLeft);
  if(button != HIGH){
    turnOff = turnOff*-1;
    delay(500);
    totalClear();
  }
  if(turnOff == 1){
    if(second() == 0){
      tmpz = true;
    }
    if(tmpz){
      tmpy = runDate(tmpx, true);
      delay(150);
      totalClear();
      tmpx--; 
      if(tmpy == 0){
        tmpz = false;
        tmpx =32;
      }
    }
    else{
      runClock(2, true);
      delay(975);
      if(second() != currentSecond){
        printNum(10, 21, false);
        printNum(10, 25, false);
      }
      if(minute() != currentMinute){
        printNum(10, 12, false);
        printNum(10, 16, false);
      }
      if(hour() != currentHour){
        printNum(10, 2, false);
        printNum(10, 6, false);
      }
    }
  }
  else{
    delay(975);
  } 
}
bool pushedLeftButton(int timeHeld){
  button = digitalRead(inButtonLeft);
  if(button == LOW){
    delay(timeHeld);
    button = digitalRead(inButtonLeft);
    if(button == LOW){
      return true;
    }
  }
  else{
    return false;
  }
}
bool pushedRightButton(int timeHeld){
  button = digitalRead(inButtonRight);
  if(button == LOW){
    delay(timeHeld);
    button = digitalRead(inButtonRight);
    if(button == LOW){
      return true;
    }
  }
  else{
    return false;
  }
}
void drawRectangle(Rectangle r){
  for(int i = 0; i < r.height; i++){
    powerLed(r.col, 7-i);
    powerLed(r.col+r.width-1, 7-i);
  }
  for(int i = 1; i<r.width; i++){
    powerLed(r.col+i, 7- (r.height-1));
  }
}
void drawRectangleFromTop(Rectangle r){
  for(int i = 0; i < 5-r.height; i++){
    powerLed(r.col, i);
    powerLed(r.col+r.width-1, i);
  }
  for(int i = 0; i<r.width; i++){
    powerLed(r.col+i, 5-(r.height));
  }
}
void isOver(Rectangle r){
  if((PLAYERX == r.col || (PLAYERX == r.col+r.width)) && (yPosition < r.height)){
      keepGoing = false;
  }
  if((PLAYERX == r.col || (PLAYERX == r.col+r.width)) && (8-yPosition < 5-r.height)){
    keepGoing = false;
  }
  for(int i = 0; i<r.width; i++){
    if((yPosition == (r.height))&& PLAYERX == r.col+i){
      keepGoing = false;
    }
    if((yPosition == (r.height)+3) && PLAYERX == r.col+i){
      keepGoing = false;
    }
  }
}
int makeBoard(){
  powerLed(PLAYERX, 7-yPosition+1);
  for(int i=0; i<=4; i++){
    isOver(pillars[i]);
    if(pillars[i].col + pillars[i].width <= 0){
      pillars[i].col = 32;
      pillars[i].height = (int)random(1, 6);
      count++;
    }
    drawRectangleFromTop(pillars[i]);
    drawRectangle(pillars[i]);
    pillars[i].col--;
  }
}
void finalRunGame(){
  while(keepGoing){
   makeBoard();
   int initialTime = millis();
    do{
      if(pushedLeftButton(60)){
        yPosition -=1;
        break;
      }
      else if(pushedRightButton(60)){
        yPosition += 1;
        break;
      }
      if(millis() - initialTime < 0){
        initialTime -= 1000;
      }
    }while(millis() - initialTime <= 150);
   totalClear();
 }
 totalClear();
 strDrawer = drawString("SCORE:", stringMover, true);
 delay(100);
 totalClear();
 stringMover--;
 if(strDrawer <= 0){
   findNum(count, 4, true);
   delay(2000);
   stringMover =32;
 }
 if(pushedLeftButton(200)){
    keepGoing = true;
    count = -6;
    yPosition = 4;
    pillars[0].height = 3;
    pillars[1].height = 3;
    pillars[2].height = 3;
    pillars[3].height = 3;
    pillars[4].height = 3;
    pillars[5].height = 3;
 }
}
void finalProgram(){
  if(buttonCheck == 1){
    finalClock();
  }
  else if(buttonCheck == -1){
    finalRunGame();
  }
  button = digitalRead(inButtonRight);
  button = digitalRead(inButtonLeft);
  if(digitalRead(inButtonRight) == LOW && digitalRead(inButtonLeft) == LOW){
    buttonCheck = buttonCheck *-1;
  }
}
void loop() {
  finalProgram();
}
