#ifndef LEAGUE_H_
#define LEAGUE_H_

#include <vector>
#include "Application.h"
#include "Team.h"
using namespace std;

class League : public Application {
  public:
    League() {}
    
    void setTeams (vector<Team*> ts) { teams = ts; }
    vector<Team*> getTeams() { return teams; }
    Team* getTeam(int i) { return teams.at(i); }
    
    void addTeam (Team* t) { teams.push_back(t); }
    
  private:
    vector<Team*> teams;
};
#endif
