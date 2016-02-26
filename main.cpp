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