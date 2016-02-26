// COPIED EXACTLY FROM P1D2 on 2/16

#ifndef TUPLE_H_
#define TUPLE_H_
#include <string> 
#include <vector>
#include "Application.h"
using namespace std;

enum TupleType { LEAGUE, TEAM, PLAYER };

struct Tuple {
  public:
    Tuple() {}
    Tuple(vector<string> newContents): contents(newContents) {}
    vector<string> getContents () { return contents; }
    string dataPoint(int index) { return contents.at(index); }
    void setContents(vector<string> newContents) {contents = newContents;}
    void addData(string newData) {contents.push_back(newData);}
    void updateValue(int index, string newData) {contents[index]= newData;}
  
  private:
    vector<string> contents; // contents of each row
    Application* app; // pointer to either League, Team, or Player (where the data is coming from - for update)
    TupleType tupleType;
};
#endif
