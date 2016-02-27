#include <iostream>
#include "Engine.h"
#include "Executer.h"
#include "League.h"
#include <stdio.h>
#include <stdlib.h>
#include "Parser.h"
#include "Token.h"
#include <fstream>
#include <string>
#include <vector>
using namespace std;

void help();
int main() {
  Engine* engine = new Engine();
  Executer* executer = new Executer();  
  Parser* parser = new Parser();

  string q1 = "a <- Project (Animal, Number) Students;";
  string q2 = "a <- rename (Animal, Species) Students";
  string createTest = "CREATE TABLE Teams (id INTEGER, favnum INTEGER, state INTEGER) PRIMARY KEY (id)";
  string insertTest = "INSERT INTO Students VALUES FROM (Mouse, 12345665, Mexico)";
  string insertTest2 = "INSERT INTO Mammals VALUES FROM (Mouse, 12345665, Mexico)";
  engine->open("input2.txt");
  engine->changeRelationName(0, "Students");
  engine->show("Students");
  engine->open("input.txt");
  engine->changeRelationName(1, "Mammals");
  //engine->show("Mammals");
  vector<int> theVec;
// To test use the different hardcoded strings to parse first.
  //vector<Token> tok = parser->splitInput(q1);
  vector<Token> tok = parser->splitInput(insertTest2);
  vector<Token> tokenvec = parser->splitInput(insertTest);
  vector<Token> tokenvec0 = parser->splitInput(q2);

  Executer* exec = new Executer();
  exec->execute(engine, tokenvec);
  exec->execute(engine, tok);
  exec->execute(engine, tokenvec0);
  for(int i = 0; i < tok.size(); i++){
	  //cout << "tok value: " << tok.at(i).getValue() << "\t" << tok.at(i).getTokenType() << endl;
  }
  cout << endl;
  for(int j =0; j < tokenvec.size(); j++){
	  //cout << "token value: " << tokenvec.at(j).getValue() << "\t" << tokenvec.at(j).getTokenType() << endl;
  }
  engine->show("Students");
  //engine->show("Mammals");
  //engine->show("Teams");
  //engine->show("projection");
  //engine->show("Students");

    /*cout << "Running" << endl;
    
    while (true) {
    string line;
    getline(cin, line);
   
      // temp
      if      (line == "q" || line == "quit") return 0;
      else if (line == "h" || line == "help") help();
      
    // parsing
      vector<int> conditions;
      parser->splitInput (line, conditions);
      // create condition tree
   
    // executer
      executer->execute (engine, parser->getTokenVector().at(0)); // NOT ALWAYS ZERO!
  }*/
}
void help() {
    cout << "\"open <filename w/ extension>\"" << " to open a relation" << endl;
    cout << "\"show <relation name>\"" << " to display a relation" << endl;
}

