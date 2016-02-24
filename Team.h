#ifndef TEAM_H_
#define TEAM_H_

#include <vector>
#include "Player.h"
using namespace std;

class Team {
  public:
    Team() {}
    
    void setPlayers (vector<Player*> ps) { players = ps; }
    vector<Player*> getPlayers() { return players; }
    Player* getPlayer(int i) { return players.at(i); }
    
    void addPlayer (Player* p) { players.push_back(p); }
    
  private:
    vector<Player*> players;
    int rank;
    // team's wins and losses
}
#endif
