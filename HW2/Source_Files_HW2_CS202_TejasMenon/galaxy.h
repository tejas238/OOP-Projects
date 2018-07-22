//galaxy.h for HW2 by Tejas Menon, CS202, last edited 7/26.
//Purpose: This file contains the class interfaces for the galaxy class, its containing sol_sys list and the spaceship class.
//         The utility class misc is also defined here and the inheritance relationship between it,
//         sol_sys and spaceship defined. 

#define _USE_MATH_DEFINES //for the pi constant
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>

using namespace std;

const int TEMP = 1000;

//This class contains few functions and is critical for the random textual outputs and position information required
//for this program. It is publically defined as a parent for a sol_sys, every planet and the spaceship
class misc
{
 public:
 misc();
 misc(const misc&);
 bool initialize_pos(); //randomize initial angle, angular velocity and use these to set an x and y depending on the planet's distance from the sun
 bool update_pos(const misc&); //updates the position based on the time difference between it and the passed in object
 double find_force(const misc&,double mass,bool show); //Returns the gravitational pull of the planet depending on its mass and distance from the passed in misc object
 void display_inline(); //displays the position properties in line for a table like evaluation

 protected:
 long int my_time; //time elapsed since traversal within a particular sol_sys began. Starts at 0 hours.
 double linear_vel; //the straight line speed of the body in millions of km per hour
 double body_mass; //the mass of the body (for spaceships)
 double distance_from_sun; //in millions of km
 double x; //in millions of km
 double y; 
 float angular_vel; //The angle that a planet moves through every hour (in radians)
 double initial_angle; //The initial random angle that a planet needs to be in its orbit.
 bool get_random(char *& type); //The type of random request is passed in as type and it is modified by the function to return the random output
};

//This class in essence adds to the functions of misc to specialize its values for a spaceship depending on user input
class spaceship: public misc
{
 public:
 bool move_with_input(); //updates the time and position to cover the specified distance 
 void move_with_speed(); //Sets the linear velocity in millions of km per hour of the spaceship
 void move_with_mass(); //sets the mass in kg of the spaceship
};


//This class stores the entire list of sol_sys' and its planets. It allows for performing a particular
//function across several sol_sys'
class galaxy {

 public:
 galaxy();
 galaxy(const galaxy&);
 ~galaxy();

 bool search_for_life(); //Searches for life at all sol_sys'
 bool traverse_galaxy(spaceship &); //traverses over all sol_sys' calling the specific traverse_sol_sys() function passing in the spaceship

 //No child can access other sol_sys' 
 private:
 class sol_sys * list;
 int size;
};

//This central class performs all data binding and structural functions on its planets and also
//defines the sun as a part of itself. 
class sol_sys: public misc  {
 
 public:
 sol_sys();
 sol_sys(const sol_sys&);
 ~sol_sys();
 bool make_planets(); //The make_planets() creates the CLL of planets
 bool search_for_life(); //Wrapper function for the recursive search_for_life()
 bool copy_sol_sys(const sol_sys&); //Copies a sol_sys. It is called by the copy constructor
 bool traverse_sol_sys(spaceship); //traverses the sol_sys and displays the most 'attracting' planet in the vicinity depending of the movement of the spaceship requested

 protected: //information about the sun should be available to all derived planets
 char * sun_name;
 double sun_radius; //Stored in millions of km
 double sun_mass; //In Solar Masses. (Mass of 1 sun)
 int num_of_planets;
 class planet * rear; //last planet
 
 private:
 void make_planets(double distance_from_sun,int planets_left,planet * temp); //makes planets at increasing distances from the sun until planets_left reaches zero
 void copy_sol_sys(planet * source,planet * source_rear); //Recursively copies the CLL from source
 bool search_for_life(planet*, int order); //Recursively searches for life on all the planets of the sol_sys and displays them by 'order'.
 void display_largest_force(spaceship &,planet * head,double &largest_force); //Recursively traverses all planets and displays the one exerting most force
};
