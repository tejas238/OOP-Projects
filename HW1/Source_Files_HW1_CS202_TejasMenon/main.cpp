//main.cpp for HW1 by Tejas Menon, CS202, last edited 7/14.
//Purpose: This file contains the client interface for galaxy creation in application software.
//         A game scenario is chosen to test the galaxy creation and search_for_life functions.
#include "planet.h"

int main()
{
 bool check =0;
 int menu_opt;
 srand(time(NULL)); //Uniquely seeds the random number generator each time the program is run
 galaxy Milky_Way;
 cout << "\n\nWelcome to the Milky-Way galaxy explorer! There are fabled tales of a life harboring blue planet\n"
      << "somewhere within the deep reaches of the galaxy's innumerable star systems and you my friend, are\n"
      << "our only hope to finding it!\n\nWe are aware you have been working on an incredible scanner that finds critical information regarding all planets\n"
      << "within a galaxy and even finds possibilities of life! It is time for you to put your invention to the test\n"
      << "and find where this blue planet lies at last.\n\n"
      << "Choose an option to proceed:\n"
      << "1.Run the scanner\n"
      << "2.Refuse the offer\n\n"
      << "Enter here:";
 cin >> menu_opt;
 cin.ignore(100,'\n');
 while(menu_opt != 1 && menu_opt != 2) 
 {
  cout << "Invalid input. Please re-enter" << endl;
  cin >> menu_opt;
  cin.ignore(100,'\n'); 
 }
 if (menu_opt == 1) check = Milky_Way.search_for_life();
 if (check) cout << "CONGRATS, YOU HAVE FOUND THE PLANET WITH LIFE! CHECK THE ENTRIES ABOVE TO FIND IT" << endl;
 else if (menu_opt == 1) cout << "The scanner couldn't identify the habitable planet. See if ./a.out fixes the scanner" << endl; 
 return 0;
}
