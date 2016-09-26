//
// Saucer.h
//
 
#include "EventCollision.h"
#include "Object.h"
 
#define SAUCER_CHAR '*'

class Saucer : public df::Object {
 
 private:
  void moveToStart();
  void out();
  void hit(const df::EventCollision *p_c);
  df::Color color;
 public:
  Saucer();
  int eventHandler(const df::Event *p_e);
  void setColor(df::Color newColor);
  void draw();
};
