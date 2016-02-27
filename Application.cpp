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
	cout << "4) Add League" << endl;
	cout << "5) Add Team" << endl;
	cout << "6) Add Players" << endl;


	cin >> user_choice;
	cout << endl;

	/*if(user_choice == 1) 
	if(user_choice == 2)
	if(user_choice == 3)
	if(user_choice == 4)
	if(user_choice == 5)
	if(user_choice == 6)*/
}
