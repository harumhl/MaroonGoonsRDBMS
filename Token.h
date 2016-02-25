//takes the returned "Tokens" from parser.h and calls the functions from the engine that correspond with the inputs

#ifndef TOKEN_H_
#define TOKEN_H_

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Token{
  public:
    Token() {}
    enum TokenTypes { FROM, SEMICOLON, LEFTPAREN, RIGHTPAREN, COMMA, EQUALSIGN, LEFTBRACE, 
                      RIGHTBRACE, LEFTARROW, TABLE, PRIMARY, KEY, SET, NUMBER, INTO, 
                      UPDATE, INSERT, VALUES, RELATION, DELETE, WHERE, VARCHAR, INTEGER,
                      CLOSE, WRITE, EXIT, SHOW, CREATE, PKEY, UNION, DIFF, PRODUCT, OPEN,
                      GEQ, LITERAL, PROJECT, RENAME, IDENTIFIER, SELECT, EQ, NEQ, LT, GT, LEQ, BOR, BAND };
    string TypeString[46] = { "FROM", "SEMICOLON", "LEFTPAREN", "RIGHTPAREN", "COMMA", "EQUALSIGN", "LEFTBRACE",
        "RIGHTBRACE", "LEFTARROW", "TABLE", "PRIMARY", "KEY", "SET", "NUMBER", "INTO",
        "UPDATE", "INSERT", "VALUES", "RELATION", "DELETE", "WHERE", "VARCHAR", "INTEGER",
        "CLOSE", "WRITE", "EXIT", "SHOW", "CREATE", "PKEY", "UNION", "DIFF", "PRODUCT", "OPEN",
        "GEQ", "LITERAL", "PROJECT", "RENAME", "IDENTIFIER", "SELECT", "EQ", "NEQ", "LT", "GT", "LEQ", "BOR", "BAND" };
    
    Token(TokenTypes type, string value) : type(type), value(value) {};
    TokenTypes getTokenType(){ return type; }
    string getValue(){ return value; }
    string getTokenStr(int i) { return TypeString[i]; } // pass TokenTypes as argument
    
  private:
    TokenTypes type;
    string value;
  
};

#endif
