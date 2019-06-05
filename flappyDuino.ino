#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

// CLK   --- Pin 2
// LIGHT --- Pin 3
// DIN   --- Pin 4
// D/C   --- Pin 5
// CS    --- Pin 6
// RST   --- Pin 7

Adafruit_PCD8544 display = Adafruit_PCD8544(2, 4, 5, 6, 7);

#include "Sprite.h"
#include "Chym.h"
#include "Bar.h"
#include "Light.h"

Chym player;
Bar bar; Bar bar2;
Light light;

int LIGHT_PIN = 3; // Digital pin 3 to Nokia LCD pin 7
int KNOCK_PIN = 12;

boolean clicked = false;
boolean startGame = true;

void loop(){}

void resetGame() {
  player.respawn();
  bar.setPos(15, 30);
  bar2.setPos(75, 20);
  light.game(LIGHT_PIN);
}

void reset(){
  int rTime = player.getTime();
  if(rTime == 30){
    if(clicked){
      resetGame();
    }
  }
  else{
    player.plusTime();
  }
}

void setup() {
  Serial.begin(9600);

  display.begin();
  display.setContrast(57);
  display.clearDisplay();
  display.display();

  pinMode(LIGHT_PIN, OUTPUT);
  pinMode(KNOCK_PIN, INPUT_PULLUP);

  digitalWrite(LIGHT_PIN, HIGH);
  
  resetGame();
  
  while(1) {
    getInput();
    player.update();
    bar.update(); bar2.update();
    drawLCD();
  }
}

void getInput() {
  int knock = digitalRead(KNOCK_PIN);
  if (knock == 0) { // push down
    clicked = true;
  } 
  else {
    clicked = false;
  }
}

void drawLCD() {
  display.clearDisplay();

  if(startGame){
    display.setTextSize(2);
    display.setCursor(25, 0);
    display.println("Old");
    display.setCursor(7, 16);
    display.println("Flappy");
    display.setCursor(19, 32);
    display.println("Bird");
    light.start(LIGHT_PIN);
    if(clicked){
      startGame = false;
      resetGame();
    }
    else{
      player.plusTime();
    }
  }

  else if (!player.isDead()) {
    int ht1 = bar.hitTest(player.getX(), player.getY());
    int ht2 = bar2.hitTest(player.getX(), player.getY());
    int die = ht1 + ht2;
    int htScore1 = bar.hitScore(player.getX());
    int htScore2 = bar2.hitScore(player.getX());
    int Score = htScore1 + htScore2;
    if (Score != 0){
      player.gameScore();
    }
    if (die == 1) {
        // game over
        player.die();
        light.resetLigth();
    }

    if (clicked) {
      player.flyUp();
    } 
    else {
      player.cancelJump();
    }
    player.render();
    
    bar.render(); bar2.render(); 
  } 
  else {
    long atb = player.getScore();
    atb = atb / DELAY_FRAME;
    display.setCursor(0, 0);
    display.setTextSize(2);
    display.println("Game   Over!!!");
    display.setTextSize(1);
    display.println();
    display.print("Score: ");
    display.println(atb);
    light.gameover(LIGHT_PIN);
    reset();
  }

  display.display();
}
