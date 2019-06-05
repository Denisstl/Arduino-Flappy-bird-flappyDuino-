class Bar {

Chym player;

private:
  int x; 
  int y;
  int delayFrame;
  int moveSpeed;
  
public:   
  Bar() {
    delayFrame = 0;
    x = 0; y = 0;
    moveSpeed = 2;
  }
  
  void setPos(int sx, int sy) {
    x = sx; y = sy;
  }
  
  void render() {
    display.drawBitmap(x, y - 30, bar_top, 8, 20, 1);
    display.drawBitmap(x, y + 10, bar_bottom, 8, 20, 1);
  }

  void update() {
    delayFrame++;
    if (delayFrame == DELAY_FRAME) {
      
      x -= moveSpeed;
      if (x < -20) x = 95;
      
      delayFrame = 0;
    }
  }
  
  int hitTest(int tx, int ty) {
    int hitX = ((tx >= (x - 14)) && (tx <= (x + 2)))?1:0;
    int hitY = ((ty <= (y - 11)) || ((ty + 12) >= (y + 11)))?1:0;
    if (hitX != 0) {
      return hitY;
    }
    return 0;
  }

  int hitScore(int tsx) {
    int hitSX = (tsx >= x && tsx <= (x + moveSpeed - 1))?1:0;
    return hitSX;
  }

};
