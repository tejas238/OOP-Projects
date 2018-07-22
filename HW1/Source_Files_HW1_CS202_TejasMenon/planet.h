//planet.h for HW1 by Tejas Menon, CS202, last edited 7/14.  
//Purpose: This file contains the class interface for planet and its self-similar derivatives rocky and gas.
//         Planet mainly stores all common variables between the two while each derived class modifies them uniquely.
//         Upcasting is in use in the planet class, where the next and previous pointers can point to either a rocky or a gas
#include "galaxy.h"

//This 'glue' node class holds together data members and functions for a rocky or gas planet and are set uniquely
//by its derivatives.
class planet: public namer
{
 public:
 planet();
 ~planet();
 planet(const planet &);
 int get_type(); //Returns an integer for the type of planet it is. 1 for rocky, 0 for gas and -1 for just a planet.
 planet *& next();
 planet *& prev();
 bool declare_life(); //Checks for a specific relationship between the data members to ascertain the chances for life
 
 protected:
 int type;
 char * planet_name; //randomely assigned planet name
 double distance_from_sun; //Stored in millions of km
 double temperature; //Stored in degrees Celsius
 double planet_mass; //Stored in multiples of E (Mass of Earth)
 char * atmosphere; //randomely assigned atmosphere
 bool rings; 
 int moons;
 planet * next_p;
 planet * prev_p;
};

//The rocky class is a derivative of planet and contains functions modify its planet variables
class rocky: public planet
{
 public:
 rocky();
 ~rocky();
 rocky(const rocky&);
 rocky(double distance_from_sun); //Initializes itself at a particular distance from the sun
 
 protected:
 void moons_and_rings(); //Function sets its moons and rings to a value typical of a rocky planet
};

//The gas class is a derivative of planet and contains functions to modify its planet variables
class gas: public planet
{
 public:
 gas();
 ~gas();
 gas(const gas&);
 gas(double distance_from_sun); //Initializes itself a particular distance from the sun
 
 protected:
 void moons_and_rings(); //Function sets its moons and rings to a value typical of a gas planet
};
