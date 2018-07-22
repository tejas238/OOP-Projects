//main.cpp file by Tejas Menon, CS202, last edited 8/14.
//Purpose: This file contains the tests for ADT functions within all_meetings
//         and also a display_menu function that displays continously until quit is requested


#include "all_meetings.h"

int main()
{
 all_meetings slack(1);
 int menu_opt = 0;
 while (menu_opt <5) {
  menu_opt = display_menu();
  if (menu_opt == 1) slack.add_meeting();
  if (menu_opt == 2) slack.add_response();
  if (menu_opt == 3) display_by_keyword(slack);
  if (menu_opt == 4) cout << slack;
 }
 return 0;
}

int display_menu()
{
 int menu_opt;
 cout << "\n\nHello user, please choose an option from the menu below:\n"
      << "1. Add a meeting to the list\n"
      << "2. Add a response from a user participating in a particular meeting\n"
      << "3. Display meetings by keyword\n"
      << "4. Display all meetings and their correspondence\n"
      << "5. Quit\n";
 cout << "Enter here: "; 
 cin >> menu_opt; cin.ignore(100,'\n');

 while (menu_opt < 1 || menu_opt >5) {
  cout << "Please re-enter this value\n";
  cin >> menu_opt; cin.ignore(100,'\n');
 }
 return menu_opt;
}

void display_by_keyword(all_meetings&slack) 
{
 char a_keyword[TEMP];
 cout << "Please enter the keyword you want to search by:\n";
 cin.getline(a_keyword,TEMP,'\n');
 keyword * temp = slack[a_keyword];
 if (temp) cout << *temp;
}

