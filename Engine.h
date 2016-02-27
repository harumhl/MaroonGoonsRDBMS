#ifndef ENGINE_H_
#define ENGINE_H_

#include <iostream>
#include <string>
#include "Relation.h"
#include "Tree.h"
#include "TreeNode.h"
#include "Condition.h"
using namespace std;

class Engine {
   public:
    Engine() {}
    void open(string filename);
    void close(string relation);
    void write(string relation, string filename = "Output.txt");
    void exit_(); //.
    void show(string relation);
    void show(Relation* the_relation);
    
    void createRelation(string relation, vector<Attribute*> attributes);
    void createRelation(Relation* relation);
    void dropRelation(string relation);
    void renameRelation(string relation, string new_name);
    
    void renameAttribute(string relation, int attribute_index, string new_name);
    
    void insertTuple(string relation, Tuple* tuple);
    void deleteTuple(string relation, int tuple_index);// WHAT SHOULD BE THE SECOND ARG?
    void updateTuple(Relation* relation, int attributeIndex, Tuple* tuple, string newData);
    
    Relation* select(string relation, vector<Attribute*> attributeName, Tree* tree);
    Relation* project(string relation, vector<Attribute*> attributeNames);
    Relation* union_(string relation1, string relation2);
    Relation* difference(string relation1, string relation2);
    Relation* crossProduct(string relation1, string relation2);
    Relation* naturalJoin(string relation1, string relation2);
    
    
    //helper functions
    bool    tupleExists(Relation* relation, Tuple* tuple);
    void    changeRelationName (int relation_index, string relation);
    string  relationName(int relation_index);
    int     findRelation (string relation); // returns the index in relations
    Relation* getRelation(int relation_index);
    vector<pair<int,int>> findSameAttributes (string relation1, string relation2);
    vector<pair<int,int>> tuplesInBoth(string rel1, string rel2, vector<string> searchData);
    
 private:
    vector<Relation*> relations;
    vector<Relation*> tempRelations; //The relations that will not be saved(views from algebra operations)
    int numRelations = 0;

    // helper functions
    vector<string>  tokenize (string input, char delimeter);
    pair<int,int>   findSameAttribute (string relation1, string relation2); // if found, return index of relation1, or else -1
    string          trimString (string str);
    string          toUpper (string str); // for Type type
    bool            isUnionCompatible (string relation1, string relation2);

    vector<Attribute*> findAttributes(string rel, vector<string> attNames, vector<int>& att_index);

};

#endif
