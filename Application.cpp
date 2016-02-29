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
	/*cout<< "Main Menu!" << endl;
	cout << "Menu Options: " << endl;
	cout << "1) View Leagues" << endl;
	cout << "2) View Teams in League" << endl;
	cout << "3) View Players in a Team" << endl;
	cout << "4) Add League" << endl;
	cout << "5) Add Team" << endl;
	cout << "6) Add Players" << endl;


	cin >> user_choice;
	cout << endl;

	if(user_choice == 1) viewLeagues();
	if(user_choice == 2) viewTeams();
	if(user_choice == 3) viewPlayers();*/
	/*if(user_choice == 4)
	if(user_choice == 5)
	if(user_choice == 6)*/
}

void Application::viewLeagues(){
	//cout << "Here are all the Leagues:" << endl;
	/*for(int i = 0; i < relations.size(); i++)
		cout << relations[i] << endl;*/
	//string viewLeagues = "SHOW leagues" << endl;
	//Parser::splitInput(viewLeagues);
}

void Application::viewTeams(){ 
	/*string leagueName;
	cout << "Which League would you like to look at?" << endl;
	cin >> leagueName;
	cout << endl;

	string viewTeams = "SHOW " + leagueName;
	Parser::splitInput(viewTeams);*/

	//Engine::show(leagueName);
}

void Application::viewPlayers(){
	/*string teamName;
	cout<< "Which Team would you like to look at?" << endl;
	cin >> teamName;
	cout << endl;

	string viewPlayers = "SHOW " + teamName;
	Parser::splitInput(viewPlayers);*/

	//Engine::show(teamName);
}
