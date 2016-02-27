// The parser will have a function called Parse() that will return a value of type Token(token.h). Token.h will essentially just be
// a value type that will have private values we assign. It really shouldn't have any functions only members.
#ifndef PARSER_H_
#define PARSER_H_

#include "Token.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;
class Parser{
  public:
    Parser() {currentIndex = 0;}
    Parser(string query) : query(query) {currentIndex = 0;}
    vector<Token> getTokens(){return tokens;}
    string getQuery(){ return query; }
    vector<Token> splitInput(string query);
    Token recognizeToken(string input);
    string skipChars(int distance);
    vector< vector<Token> > getTokenVector(){ return vtokens; }
    void tokenVector(vector<Token> tokens);

    vector<int> getCondition() { return conditions; }
    int getCondition(int i) { return conditions.at(i); }
    
  private:
    string query;
    vector< vector<Token> > vtokens;
    int currentIndex;
    string::iterator iter;
    vector<Token> tokens;
    string symbols1[12] = {"<", ">", "{", "}", "+", "-", "*", ";", "(", ")", ",", "="};
    string symbols2[7] = {"==", "!=", "<=", ">=", "<-", "||", "&&"};
    vector<int> conditions; // Keeps starting index positions from tokens for generating condition tree
    
    void setToken();
    void increment();
    string toUpper(string str);

  
};

#endif
