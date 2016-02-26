// COPIED EXACTLY FROM P1D2 on 2/16

#ifndef ATTRIBUTE_H_
#define ATTRIBUTE_H_
#include <string> 
using namespace std;

enum Type {VARCHAR, INTEGER, ENUM};
static string EnumStrings[] = {"VARCHAR", "INTEGER", "ENUM"};

class Attribute {
  public:

    Attribute(Type type, string value, bool primary, int size) : type(type), value(value), primary(primary), size(size) {};
    Attribute(Type t, string s): type(t), name(s) {}
    Attribute() {}
    Type getType() { return type; }
    string getName() { return name; }
    string getTypeStr() { return EnumStrings[type]; }
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
