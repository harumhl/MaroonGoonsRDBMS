#include <iostream>
#include "Engine.h"
#include "League.h"
using namespace std;

void help();
int main() {
  Engine* engine = new Engine();
  Parser* parser = new Parser();
  
    cout << "Running" << endl;
    
  while (true) {
    string line;
    getline(cin, line);
   
      // temp
      if      (line == "q" || line == "quit") return 0;
      else if (line == "h" || line == "help") help();
      
    // parsing
   
    // executer
  }
}
void help() {
    
}