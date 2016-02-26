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
  string createTest = "CREATE TABLE Teams (id INTEGER, city VARCHAR(20), state VARCHAR(20)) PRIMARY KEY (id)";
  string insertTest = "INSERT INTO Students VALUES FROM (Mouse, 12345665, Mexico)";
  engine->open("input2.txt");
  engine->changeRelationName(0, "Students");
  engine->show("Students");
  vector<int> theVec;
// To test use the different hardcoded strings to parse first.
  //vector<Token> tokenvec0 = parser -> splitInput(createTest, theVec);
  vector<Token> tokenvec = parser->splitInput(insertTest, theVec);

  Executer* exec = new Executer();
  exec->execute(engine, tokenvec);
  engine->show("Students");
    //engine->show("projection");

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

