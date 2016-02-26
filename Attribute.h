// COPIED EXACTLY FROM P1D2 on 2/16

#ifndef ATTRIBUTE_H_
#define ATTRIBUTE_H_

#include <string> 
using namespace std;

class Attribute {
  public:
    enum Type {VARCHAR, INTEGER, ENUM};
    string EnumStrings[3] = {"VARCHAR", "INTEGER", "ENUM"};
    
    Attribute() {}
    Attribute(Type t, string s): type(t), name(s) {}
    Attribute(Type type, string value, bool primary, int size)
        : type(type), value(value), primary(primary), size(size) {};
    
    // Getters
    Type getType() { return type; }
    string getName() { return name; }
    string getTypeStr() { return EnumStrings[type]; }
    
    // Setters
    void setType(Type t) { type = t; }
    void setName(string s) { name = s; }

  private:
    Type type;
    string name;
    string value;
    int size;
    bool primary;


};
#endif
