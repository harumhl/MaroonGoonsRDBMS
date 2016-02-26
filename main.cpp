#include <iostream>
#include "Engine.h"
#include "Executer.h"
#include "League.h"
using namespace std;

void help();
int main() {
  Engine* engine = new Engine();
  Parser* parser = new Parser();
  Executer* executer = new Executer();
  
    cout << "Running" << endl;
    
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
  }
}
void help() {
    cout << "\"open <filename w/ extension>\"" << " to open a relation" << endl;
    cout << "\"show <relation name>\"" << " to display a relation" << endl;
}



/*
#include <stdio.h>
#include <stdlib.h>
#include "Parser.h"
#include "Token.h"
#include "Executer.h"
#include "Engine.h"
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
/*
 *

using namespace std;
int main(){

	Engine* engine = new Engine();
    Parser* parse1 = new Parser();
    string q1 = "a <- Project (Animal, Number) Students;";
    string q2 = "a <- rename (Animal, Species) Students";
    engine->open("input2.txt");
    engine->changeRelationName(0, "Students");
    engine->show("Students");
    vector<int> theVec;

    vector<Token> tokenvec = parse1->splitInput(q2, theVec);
    /*for(int i = 0; i < tokenvec.size(); i++){
        cout << tokenvec.at(i).getValue() << "/t " << tokenvec.at(i).getTokenStr(tokenvec.at(i).getTokenType())<< endl;
    }

    Executer* exec = new Executer();
    exec->execute(engine, tokenvec);
    engine->show("Students");
    //engine->show("projection");
}*/
