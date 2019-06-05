class Light {

private:
  int speedLigth = 3;
  int pause = 30;
  int pause2 = 8;
  int startPause2 = pause2;
  int times = 2;
  int startTimes = times;
  int times2 = 2;
  int startTimes2 = times2;
  int times3 = 8; // skaits reiz 2  (times3 = times3 * 2)
  int startTimes3 = times3;
  int brighter = 255;
  int startBrighter = brighter;
  int darker = 100;
  int startDarker = darker;

  int speedLigth2 = 3;
  int brighter2 = 200;
  int startBrighter2 = brighter2;
  int darker2 = 50;
  int startDarker2 = darker2;

  boolean lightEnd = false;
  
public:
void start(int pin) {
  if(pause > 0){
    analogWrite(pin, 255);
    pause--;
  }
  
  
  else if(brighter >= (startDarker - speedLigth + 1) && times > 0) {
    if(brighter < startDarker){
      brighter = startDarker;
    }
    analogWrite(pin, brighter);
    brighter = brighter - speedLigth;
  }
  
  else if(darker <= (startBrighter + speedLigth - 1) && times > 0) {
    if(darker > startBrighter){
      darker = startBrighter;
    }
    analogWrite(pin, darker);
    darker = darker + speedLigth;
  }
  
  else if(times > 0) {
    times--;
    brighter = startBrighter;
    darker = startDarker;
  }
  
  
  else if(brighter >= (startDarker - speedLigth + 1) && times2 > 0) {
    if(brighter < startDarker){
      brighter = startDarker;
    }
    analogWrite(pin, brighter);
    brighter = brighter - speedLigth;
  }
  
  else if(times2 > 0) {
    times2--;
    brighter = startBrighter;
    darker = startDarker;
  }
  
  
  else if(times3 == startTimes3 && pause2 > 0) {
    analogWrite(pin, 255);
    pause2--;
  }
  
  else if(times3 == 0 && pause2 > 0) {
    analogWrite(pin, 255);
    pause2 = pause2 - (startPause2 / 2);
    lightEnd = true;
  }
  
  else if((times3 % 2) == 0 && pause2 > 0) {
    analogWrite(pin, 255);
    pause2--;
  }
  
  else if((times3 % 2) == 1 && pause2 > 0) {
    analogWrite(pin, 0);
    pause2 = pause2 - 2;
  }
  
  if(pause2 == 0) {
    times3--;
    pause2 = startPause2;
  }
  
  
  if(lightEnd) {
    times = startTimes;
    times2 = startTimes2;
    times3 = startTimes3;
    lightEnd = false;
  }
}

void game(int pin) {
  analogWrite(pin, 0);
}

void gameover(int pin) {
  if(darker2 <= (startBrighter2 + speedLigth2 - 1)) {
    if(darker2 > startBrighter2){
      darker2 = startBrighter2;
    }
    analogWrite(pin, darker2);
    darker2 = darker2 + speedLigth2;
  }
  else if(brighter2 >= (startDarker2 - speedLigth2 + 1)) {
    if(brighter2 < startDarker2){
      brighter2 = startDarker2;
    }
    analogWrite(pin, brighter2);
    brighter2 = brighter2 - speedLigth2;
  }
  else{
    brighter2 = startBrighter2;
    darker2 = startDarker2;
  }
}
void resetLigth(){
  brighter2 = startBrighter2;
  darker2 = startDarker2;
}

};
