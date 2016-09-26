//
// Saucer.h
//
 
#include "EventCollision.h"
#include "Object.h"
 
#define SAUCERSOFT_CHAR '^'

class SaucerSoft : public df::Object {
 
 private:
  void moveToStart();
  void out();
  void hit(const df::EventCollision *p_c);

 public:
  SaucerSoft();
  int eventHandler(const df::Event *p_e);
  void draw();
};
