#include "Relation.h"
#include "Tuple.h"
#include "Application.h"

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

int menu = 0;
int user_choice = 0;

void Application::mainMenu()
{
	cout<< "Main Menu!" << endl;
	cout << "Menu Options: " << endl;
	cout << "1) View Leagues" << endl;
	cout << "2) View Teams in League" << endl;
	cout << "3) View Players in a Team" << endl;
	cout << "4) Add League(s)" << endl;
	cout << "5) Add Team(s)" << endl;
	cout << "6) Add Players(s)" << endl;


	cin >> user_choice;
	cout << endl;

	if(user_choice == 1) viewLeagues();
	if(user_choice == 2) viewTeams();
	if(user_choice == 3) viewPlayers();
	if(user_choice == 4) addLeague();
	if(user_choice == 5) addTeam();
	if(user_choice == 6) addPlayer();
}
