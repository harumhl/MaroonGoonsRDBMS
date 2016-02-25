#ifndef TEAM_H_
#define TEAM_H_

#include <vector>
#include "Application.h"
#include "Player.h"
using namespace std;

class Team : public Application {
  public:
    Team() {}
    Team (vector<Player*> ps, int r = -1) : players(ps), rank(r) {}
    
    void setPlayers (vector<Player*> ps) { players = ps; }
    void setRank (int r) { rank = r; }
    
    vector<Player*> getPlayers() { return players; }
    Player* getPlayer(int i) { return players.at(i); }
    int getRank() { return rank; }
    
    void addPlayer (Player* p) { players.push_back(p); }
    
  private:
    vector<Player*> players;
    int rank;
    // team's wins and losses
};
#endif
