//galaxy.h for HW1 by Tejas Menon, CS202, las edited 7/14.
//Purpose: This file contains the class interfaces for the galaxy class and its containing sol_sys list.
//         The utility class namer is also defined here and the inheritance relationship between it and 
//         sol_sys is established.
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <cctype>

using namespace std;

const int TEMP = 1000;

//This class contains only one function, but is critical for the random textual outputs required
//for this program. It is publically defined as a parent for a sol_sys and also every planet. 
class namer 
{
 public:
 namer();

 //This function can only be requested by its derived classes.
 protected:
 bool get_random(char *& type); //The type of random request is passed in as type and it is modified by the function to return the random output
};

//This class stores the entire list of sol_sys' and its planets. It allows for performing a particular
//function across several sol_sys'
class galaxy {

 public:
 galaxy();
 galaxy(const galaxy&);
 ~galaxy();

 bool search_for_life(); //Searches for life at all sol_sys'

 //No child can access other sol_sys' 
 private:
 class sol_sys * list;
 int size;
};

//This central class performs all data binding and structural functions on its planets and also
//defines the sun as a part of itself. 
class sol_sys: public namer  {
 
 public:
 sol_sys();
 sol_sys(const sol_sys&);
 ~sol_sys();
 bool make_planets(); //The make_planets() creates the DLL of planets
 bool search_for_life(); //Wrapper function for the recursive search_for_life()
 bool copy_sol_sys(const sol_sys&); //Copies a sol_sys. It is called by the copy constructor

 protected: //information about the sun should be available to all derived planets
 char * sun_name;
 double sun_radius; //Stored in millions of km
 double sun_mass; //In Solar Masses. (Mass of 1 sun)
 int num_of_planets;
 class planet * head;
 class planet * tail;
 
 private:
 void make_planets(double distance_from_sun,int planets_left); //makes planets at increasing distances from the sun until planets_left reaches zero
 void copy_sol_sys(planet * source); //Recursively copies the DLL from source
 bool search_for_life(planet*, int order); //Recursively searches for life on all the planets of the sol_sys and displays them by 'order'.
};
