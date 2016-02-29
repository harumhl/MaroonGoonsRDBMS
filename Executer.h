#ifndef EXECUTE_H_
#define EXECUTE_H_

#include <vector>
#include "Engine.h"
#include "Token.h"
#include "Parser.h"
using namespace std;

class Executer {
  public:
	Executer() {}
    void execute(Engine* engine, vector<Token> workToDo);
    void start();
    void program();
    void command();
    void query();
    void create();
    void delete_();
    Relation* expr();
    Relation* atomicExpr();
    Relation* rename();
    Relation* project();
    Relation* combine(Relation* relation);
    vector<Attribute*> getAttributeList();
    void expect(Token::TokenTypes type);
    void nextToken();
    void setToken();
    void insert();
    bool lookAhead(Token::TokenTypes type);
    bool atEnd();//returns true if the current token is the last
    
    vector<Token> tokens;
    Token token;
    int currentIndex;
    Relation* tempRelation;
  private:
    Engine* engine;

};

#endif
