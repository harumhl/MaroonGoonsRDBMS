#ifndef RELATION_H_
#define RELATION_H_
#include "Attribute.h"
#include "Tuple.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Relation {
  public:
    Relation(string s, vector<Attribute*> attr): name(s), attributes(attr) {}
    Relation() {}
    
    string  getName() { return name; }
    vector<Attribute*> getAttributes() { return attributes; }
    vector<Tuple*> getTuples() { return tuples; }
    Attribute* getAttribute(int i) { return attributes.at(i); }
    Tuple* getTuple(int i) { return tuples.at(i); }
    int getColumns() {return attributes.size();}
    
    void setName (string newName) { name = newName; }
    void setAttributes(vector<Attribute*> av) { attributes = av; }
    void setTuple(vector<Tuple*> tv) { tuples = tv; }
    
    void addTuple(Tuple* t) { tuples.push_back(t); }
    void removeTuple(int i) { tuples.erase( tuples.begin()+i ); } 
    
    int findAttribute(string name){
    	int index = -1;
    	for(int i = 0; i < attributes.size(); i++){
    		if(attributes.at(i)->getName() == name)
    			index = i;
    	}
    	return index;
    }
  private:
    string name;
    vector<Attribute*> attributes;
    vector<Tuple*> tuples;
    // Do not confuse those two vectors as attributes are titles of each COLUMN whereas tuples are contents of each ROW
};
#endif
