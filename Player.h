#ifndef PLAYER_H_
#define PLAYER_H_

#include <vector>
#include "Application.h"
using namespace std;

class Player : public Application {
  public:
    Player() {}
    Player (string n, int a, string tn = "", string p = "")
        : name(n), age(a), teamName(tn), position(p) {}
    
    void setName (string n) { name = n; }
    void setAge  (int a)    { age = a; }
    void setTeamName (string tn) { teamName = tn; }
    void setPotision (string p) { position = p; }
    
    string getName () { return name; }
    int    getAge () { return age; }
    string getTeamName () { return teamName; }
    string getPosition () { return position; }
    
  private:
    string name;
    int    age;
    string teamName;
    string position;
    // how are we going to keep different sport player's personal stats?
    // i.e. football: rush yard, baseball: hits, etc.
};
#endif
