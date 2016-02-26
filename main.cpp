#include <iostream>
#include "Engine.h"
#include "League.h"
using namespace std;

int main() {
  Engine* engine = new Engine();
  Parser* parser = new Parser();
  
    cout << "Running" << endl;
    
  while (true) {
    string line;
    getline(cin, line);
   
      if (line == "q" || line == "quit") return 0;
      
    // parsing
   
    // executer
  }
}
