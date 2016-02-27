#ifndef RELATION_H_
#define RELATION_H_

#include <string>
#include <vector>
#include <iostream>
#include "Attribute.h"
#include "Tuple.h"
using namespace std;

class Relation {
  public:
    Relation() {}
    Relation(string s, vector<Attribute*> attr): name(s), attributes(attr) {}

    // Getters
    string  getName() { return name; }
    vector<Attribute*> getAttributes() { return attributes; }
    vector<Tuple*> getTuples() { return tuples; }
    Attribute* getAttribute(int i) { return attributes.at(i); }
    Tuple* getTuple(int i) { return tuples.at(i); }
    
    // Setters
    void setName (string newName) { name = newName; }
    void setAttributes(vector<Attribute*> av) { attributes = av; }
    void setTuples(vector<Tuple*> tv) { tuples = tv; }
    
    // Add or Remove tuples
    void addTuple(Tuple* t) { tuples.push_back(t); }
    void removeTuple(int i) { tuples.erase( tuples.begin()+i ); } 
    
    int findAttribute(string name){
    	int index = -1;
    	for(int i = 0; i < attributes.size(); i++){
    		if(attributes.at(i)->getName() == name)
    			return i;
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
