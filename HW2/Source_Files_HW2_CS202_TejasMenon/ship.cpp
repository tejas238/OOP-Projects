//ship.cpp for HW2 by Tejas Menon, CS202, last edited 7/26.
//Purpose: This file contains the class implementation for the spaceship class and
//         is mainly an input class that sets its properties based on the values from
//         the client. Also personalizes its misc superclass to values appropriate of a spaceship
  
#include "planet.h"

//Changes the x and y values based on the input reqested from the client. Uses the stored speed to determine the 
//time travelled
bool spaceship::move_with_input()
{
 char menu_opt;
 double magnitude;
 cout << "You can move around this solar system using the four WASD keys preceeded by a number\n"
      << "indicating the distance in millions of km you want to travel in that direction. Example key specifications:\n"
      << "\"10 W\" = travel 10 million km ahead\n"
      << "\"10 A\" = travel 10 million km left\n"
      << "\"10 D\" = travel 10 million km right\n"
      << "\"10 S\" = travel 10 million km behind\n"
      << "\"0 Q\" to quit (move to the next solar system\n\n";
 cout << "Note that the planet chosen depends on two factors, the distance of it from the spaceship and also the planet mass (GM/(R^2))\n"
      << "Enter here: ";
 cin >> magnitude >> menu_opt;
 menu_opt = toupper(menu_opt);
 cin.ignore(100,'\n');
 while (menu_opt != 'W' && menu_opt != 'A' && menu_opt != 'S' && menu_opt != 'D' && menu_opt != 'Q') 
 {
  cout << "Please re-enter a correct operation:\n";
  cin >> magnitude >> menu_opt;
  menu_opt = toupper(menu_opt);
  cin.ignore(100,'\n');
 }
 if (menu_opt == 'W') y += magnitude;
 if (menu_opt == 'A') x -= magnitude;
 if (menu_opt == 'S') y -= magnitude; 
 if (menu_opt == 'D') x += magnitude;
 if (menu_opt == 'Q') return 0; 
 cout << "\nSpaceship (" << x << "," << y << ")" << endl;
 long int time_taken = magnitude/linear_vel;
 cout << "\nYou travelled for " << time_taken << " hours\n";
 my_time += time_taken;
 return 1;
}

//Sets the speed that the user wants to traverse the galaxy at
void spaceship::move_with_speed()
{
 double speed;
 cout << "Please enter a speed that your spaceship will travel at. (in millions of km per hour)\n"
      << "Recommended values are between 0.02 (20,000 km per hour) and 0.1 (100,000 km per hour)\n"
      << "Enter here: ";
 cin >> speed;
 cin.ignore(100,'\n');
 while (speed <=0) 
 {
  cout << "Please re-enter a positive value" << endl;
  cin >> speed;
  cin.ignore(100,'\n');
 }
 linear_vel = speed;
 cout << "The speed has been set!\n\n";
}

//sets the mass of the spaceship for the calculation of force later in the program
void spaceship::move_with_mass()
{
 double mass;
 cout << "Please enter the mass in kilograms of the spaceship.\n"
      << "Enter here: ";
 cin >> mass;
 cin.ignore(100,'\n');
 while (mass <=0) 
 {
  cout << "Please re-enter a positive value" << endl;
  cin >> mass;
  cin.ignore(100,'\n');
 }
 body_mass = mass;
 cout << "The mass has been set!\n\n";
}


