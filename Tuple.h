// COPIED EXACTLY FROM P1D2 on 2/16

#ifndef TUPLE_H_
#define TUPLE_H_

#include <string> 
#include <vector>
#include "Application.h"
using namespace std;

struct Tuple {
  public:
    enum TupleTypes { LEAGUE, TEAM, PLAYER };

    Tuple() {}
    Tuple(vector<string> newContents): contents(newContents) {}
    
    // Getters
    vector<string> getContents () { return contents; }
    string getContent(int i) { return contents.at(i); }
    Application* getApp() { return app; }
    TupleTypes getTupleType() { return type; }

    // Setter
    string dataPoint(int index) { return contents.at(index); }
    void setContents(vector<string> newContents) {contents = newContents;}
    void addData(string newData) {contents.push_back(newData);}
    void updateValue(int index, string newData) {contents[index]= newData;}
    void setApp (Application* newApp) { app = newApp; }
    void setTupleType (TupleTypes tt) { type = tt; }

    void changeContent(int i, string newContent) { contents.at(i) = newContent;}
    void addContent(string newContent) { contents.push_back(newContent); }
  
  private:
    vector<string> contents; // contents of each row
    Application* app; // pointer to either League, Team, or Player (where the data is coming from - for update)
    TupleTypes type;
};
#endif
