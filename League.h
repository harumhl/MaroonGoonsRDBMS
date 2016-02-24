#include <vector>
#include "Team.h"
using namespace std;

class League {
  public:
    League() {}
    
    void setTeam (vector<Team*> ts) { teams = ts; }
    vector<Team*> getTeams() { return teams; }
    Team* getTeam(int i) { return teams.at(i); }
    
    void addTeam (Team* t) { teams.push_back(t); }
    
  private:
    vector<Team*> teams;
}
