#ifndef PLAYER_H_
#define PLAYER_H_

#include <vector>
#include "Application.h"
using namespace std;

class Player : public Application {
  public:
    Player() {}
    
  private:
    string name;
    int    age;
    string teamname;
    string position;
    // how are we going to keep different sport player's personal stats?
    // i.e. football: rush yard, baseball: hits, etc.
};
#endif
