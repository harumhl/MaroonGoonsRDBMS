//takes the returned "Tokens" from parser.h and calls the functions from the engine that correspond with the inputs

#ifndef TOKEN_H_
#define TOKEN_H_

#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
using namespace std;

class Token{
  public:
    enum TokenTypes { FROM, SEMICOLON, LEFTPAREN, RIGHTPAREN, COMMA, EQUALSIGN, LEFTBRACE,
                      RIGHTBRACE, LEFTARROW, TABLE, PRIMARY, KEY, SET, NUMBER, INTO, 
                      UPDATE, INSERT, VALUES, RELATION, DELETE, WHERE, VARCHAR, INTEGER, ENUM,
                      CLOSE, WRITE, EXIT, SHOW, CREATE, PKEY, UNION, DIFF, PRODUCT, OPEN,
                      GEQ, LITERAL, PROJECT, RENAME, IDENTIFIER, SELECT, EQ, NEQ, LT, GT, LEQ, BOR, BAND };
    
    Token() {}
    Token(TokenTypes type, string value) : type(type), value(value) {}
    
    // Getters
    TokenTypes getTokenType() { return type; }
    string  getValue() { return value; }
    int     getNumValue() { return atoi(value.c_str()); }
    
  private:
    TokenTypes type;
    string value;
};
#endif
