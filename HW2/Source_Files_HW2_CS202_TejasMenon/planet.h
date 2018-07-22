//planet.h for HW2 by Tejas Menon, CS202, last edited 7/26.  
//Purpose: This file contains the class interface for planet and its self-similar derivatives rocky and gas.
//         Planet mainly stores all common variables between the two while each derived class modifies them uniquely.
//         Upcasting is in use in the planet class, where the next and previous pointers can point to either a rocky or a gas.
//         The pure virtual function of planet allows calling a separate find force function in a rocky or gas at runtime
#include "galaxy.h"

//This 'glue' node class holds together data members and functions for a rocky or gas planet and are set uniquely
//by its derivatives. All poisition information from misc is inherited
class planet: public misc
{
 public:
 planet();
 ~planet();
 planet(const planet &);
 int get_type(); //Returns an integer for the type of planet it is. 1 for rocky, 0 for gas and -1 for just a planet.
 planet *& next();
 bool declare_life(); //Checks for a specific relationship between the data members to ascertain the chances for life
 virtual double find_force(const misc&,bool show) = 0;
 
 protected:
 int type;
 char * planet_name; //randomely assigned planet name
 double temperature; //Stored in degrees Celsius
 double planet_mass; //Stored in multiples of E (Mass of Earth)
 char * atmosphere; //randomely assigned atmosphere
 bool rings; //contains rings or not
 int moons; //Number of moons
 planet * next_p; //next planet in the CLL
};

//The rocky class is a derivative of planet and contains functions modify its planet variables
class rocky: public planet
{
 public:
 rocky();
 ~rocky();
 rocky(const rocky&);
 rocky(double distance_from_sun); //Initializes itself at a particular distance from the sun
 virtual double find_force(const misc&,bool show); //Calls the find force function for its misc passing in the planet mass that is unique to rocky and gas
 
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
 virtual double find_force(const misc&,bool show); //Calls the find force function for its misc 
 
 protected:
 void moons_and_rings(); //Function sets its moons and rings to a value typical of a gas planet
};
