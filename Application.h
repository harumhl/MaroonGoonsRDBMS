// Base class for League, Team, and Player class
// So Tuple objects can point to any of them as necessary

#ifndef APPLICATION_H_
#define APPLICATION_H_

class Application {
  public:
    Application() {}
    void mainMenu();
    
    void viewLeagues();
    void viewTeams();
    void viewPlayers();
    
    void addLeague();
    void addTeam();
    void addPlayer();
};
#endif
