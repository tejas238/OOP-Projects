//galaxy.cpp for HW2 by Tejas Menon, CS202, last edited 7/26. 
//Purpose: This file contains the class implementations for the galaxy class, which is the highest order class,
//         and also class implementations for its containing sol_sys objects. Another utility class this 
//         file contains functions for is the misc class, which dedicates random textual output such as 
//         names and atmosphere types to sol_sys' and planets. Additionally the misc class also serves as the 
//         orientation of the planet in x and y space and therefore with the change in time, depending on their
//         properties, the planets change these values appropriately. The classes that inherit the misc class are the 
//         planet class and also the sol_sys and spaceship class.

#include "planet.h"

misc::misc(): body_mass(0),my_time(0),linear_vel(0),initial_angle(0),angular_vel(0),x(0),y(0),distance_from_sun(0)  {} //no dynamic variables

//copy constructor
misc::misc(const misc&from): body_mass(from.body_mass),my_time(from.my_time),linear_vel(from.linear_vel),initial_angle(from.initial_angle),angular_vel(from.angular_vel),x(from.x),y(from.y),distance_from_sun(from.distance_from_sun) {}

//Initializes the position of the planet (function ran when planets are made). 
bool misc::initialize_pos()
{
 if (!distance_from_sun) return 0;
 double in_degrees = rand()%360;
 initial_angle = double(in_degrees/360)*2*M_PI; //the M_PI constant from <cmath>
 linear_vel = double(rand()%2500)/10000 + 0.05;
 angular_vel = linear_vel/(distance_from_sun); //radians
 x = cos(initial_angle)*distance_from_sun; //x and y in millions of km
 y = sin(initial_angle)*distance_from_sun;
 return 1;
}

//updates the position based on the time difference between the current misc object and the passed in source
bool misc::update_pos(const misc&source)
{
 if (!x || !y) return 0;
 long int time_diff = source.my_time - my_time;
 initial_angle = initial_angle + angular_vel*time_diff; //calculates the new initial angle
 x = cos(initial_angle)*distance_from_sun;
 y = sin(initial_angle)*distance_from_sun;
 return 1;
}

//finds the force between the current object and the source- a value that depends on the mass
//of the source and its distance from the current object. The state of show decides whether 
//to output this data or not. Uses the power function from <cmath>
double misc::find_force(const misc&source,double mass,bool show)
{
 if (!x || !y) return 0; 
 double x_separation = source.x - x;
 double y_separation = source.y - y;
 double separation = sqrt(pow(x_separation,2)+pow(y_separation,2));
 double force = (mass/(pow(separation*pow(10,6),2)))*pow(10,13)*5.972*source.body_mass; //GMm/r^2 (Newton's law of gravitation). 5.972*10^6 converts mass to kg
 if (show) 
 {
  cout << "\nDistance between the spaceship and the planet with the highest gravitational pull : " << separation << " million km\n";
  cout << "Force between the spaceship and the planet: " << force << " Newtons (G = -6.64*10^-11)\n\n";
 }
 return force;
}

//Displays the motion characteristics of the mass (spaceship, planet or sol_sys) in a line
void misc::display_inline()
{
 cout << angular_vel << " " << initial_angle << " " << x << " " << y << endl;
}

 
//This sole function for the class accepts a char* array that contains "planet", "sun", "gas" or "rocky"
//and for these 'types' copies back a random output to the passed in argument. It uses an external data file
//for the output
bool misc::get_random(char *& type)
{
 int line; //the line to be copied from
 char temp[TEMP]; 
 ifstream file_in;
 file_in.open("HW1_data.txt");
 if (!file_in || !type || (strcmp(type,"planet") && strcmp(type,"sun") && strcmp(type,"gas") && strcmp(type,"rocky"))) return 0; //invalidates other input
 if (!strcmp(type,"sun")) line = rand()%23 + 3; //any value between 3 and 26 copied to line
 if (!strcmp(type,"planet")) line = rand()%24 + 29;
 if (!strcmp(type,"gas")) line = rand()%8 + 56;
 if (!strcmp(type,"rocky")) line = rand()%8 + 67;
 while(line--) 
 {
  file_in.getline(temp,TEMP,'\n'); //copies that line into temp
 }
 delete[]type; //reassigns the output
 type = new char[strlen(temp)+1]; 
 strcpy(type,temp);
 return 1;
}

//Create a galaxy with a random number of sol_sys between 1 and 8. 
//Also makes planets for them automatically
galaxy::galaxy() 
{
 size = rand()%7+1;
 list = new sol_sys[size];
 for (int i=0;i<size;++i) 
 {
  list[i].make_planets();
 }
}

//Copy constructor for a galaxy.
//Calls the copy_sol_sys function from each sol_sys on the source
galaxy::galaxy(const galaxy & source)
{
 size = source.size;
 list = new sol_sys[size];
 for(int i=0;i<size;++i)
 {
  list[i].copy_sol_sys(source.list[i]);
 }
}

//Searches for life in each sol_sys and returns true if found for any
bool galaxy::search_for_life()
{
 if (!list) return 0;
 bool check = 0;
 for(int i=0;i<size;++i)
 {
  if (list[i].search_for_life()) check = 1;
 }
 return check;
}

//traverses all the sol_sys' in the galaxy and calls its traveral function.
//sets the spaceship to appropriate values first
bool galaxy::traverse_galaxy(spaceship & source)
{
 if (!list) return 0;
 source.move_with_speed();
 source.move_with_mass();
 cout << "Visiting all solar systems in order:\n" << endl;
 for(int i=0;i<size;++i)
 {
  cout << "Solar system "<< i+1 << " \n\n";
  list[i].traverse_sol_sys(source);
 }
 cout << "All solar systems in this galaxy have been visited. Hope you found the one with life!" << endl;
 return 1;
}

//Calls appropriate destructors for each element of list
galaxy::~galaxy()
{
 if (list) delete[]list;
}

//Creates a sol_sys initializing all variables to NULL. 
//Doesn't make planets at this point as the intention might be
//to copy a sol_sys
sol_sys::sol_sys(): sun_name(NULL),rear(NULL) {} 

//copy constructor calls the copy_sol_sys function
sol_sys::sol_sys(const sol_sys & source)
{
 copy_sol_sys(source);
}

//Wrapper for the recursive copy_sol_sys function. Sun information from 
//the source is copied over first
bool sol_sys::copy_sol_sys(const sol_sys & source)
{
 if (rear || !source.rear) return 0;
 sun_name = new char[strlen(source.sun_name)]; strcpy(sun_name,source.sun_name);
 sun_radius = source.sun_radius;
 sun_mass = source.sun_mass;
 num_of_planets = source.num_of_planets;
 planet * temp;
 if ((source.rear)->get_type()) temp = new rocky(*reinterpret_cast<rocky*>(source.rear));
 else temp = new gas(*reinterpret_cast<gas*>(source.rear));
 rear = temp;
 copy_sol_sys((source.rear)->next(),source.rear);
 rear->next() = temp;
 rear = temp;
 return 1;
}

//Recursive copy function for all planets in source's sol_sys. Uses the get_type()
//function to ascertain the type (gas or rocky) prior to the compile time downcasting.
//Casting is required as each derived class copy constructor only accepts its object reference.
void sol_sys::copy_sol_sys(planet *source,planet *source_rear)
{
 if (source == source_rear) return;
 if (source->get_type()) rear->next() = new rocky(*reinterpret_cast<rocky*>(source));
 else rear->next() = new gas(*reinterpret_cast<gas*>(source));
 rear = rear->next();
 copy_sol_sys(source->next(),source_rear);
}

//Wrapper decides a random number of planets (rocky or gas) for the current sol_sys and creates sun information.
//Also calls a recursive make_planets version to create this predecided number of planets
bool sol_sys::make_planets() 
{
 if (rear) return 0; //if planets are already present
 char *sun = new char[TEMP];
 strcpy(sun,"sun");
 get_random(sun); //gets a random sun name 
 sun_name = new char[strlen(sun)+1];
 strcpy(sun_name,sun); //copies it over
 sun_radius = double(rand()%600)/100+0.3; //sun_radius in millions of km
 sun_mass = double(rand()%600)/100+0.1; //sun mass in solar masses (R)
 num_of_planets= rand()%15+2; //Decides the number of planets between 2 and 17
 planet * temp = NULL;
 make_planets(rand()%70+sun_radius,num_of_planets,temp); //calls its recursive secondary
 delete[]sun;
 return 1;
}

//Recursive function creates successive planets (rocky or gas) at increasing distances from the sun.
//Stops when planets_left is zero. Also randomizes the planet type skewed by the distance from the sun
void sol_sys::make_planets(double distance_from_sun,int planets_left,planet * temp)
{
 if (!planets_left) {
  rear->next() = temp;
  return;
 }
 bool check = 0;
 int dice_roll = rand()%10+1; //A rocky planet is most LIKELY if distance is less than 250 (not a certainty). Same with a gas planet.
 if ((distance_from_sun<250 && dice_roll<10)||(distance_from_sun>=250 && dice_roll==10)) check = 1;
 if (check && rear) rear->next() = new rocky(distance_from_sun); 
 else if (!check && rear) rear->next() = new gas(distance_from_sun);
 else if (check && !rear) rear = new rocky(distance_from_sun);
 else if (!check && !rear) rear = new gas(distance_from_sun);
 if (rear->next()) rear = rear->next();
 else temp = rear;
 make_planets(rand()%70+distance_from_sun,--planets_left,temp); //passes a higher distance from the sun + some range.
}

//Wrapper function for the recursive search_for_life() that displays sun information for the current sol_sys
//and assigns an order to display the planets in order.
bool sol_sys::search_for_life()
{
 if (!rear) return 0;
 int order = 1;
 cout << "For this Solar System, here are the sun details:\n";
 cout << "Sun Name: " << sun_name << endl;
 cout << "Sun Radius: " << sun_radius << " million km" << endl;
 cout << "Sun Mass: " << sun_mass << " Solar Masses (1S = 333,000 E)" << endl;
 cout << "Number of planets in this star system: " << num_of_planets << endl; 
 cout << "Here are the planets in this system and information about their chances of life:\n\n";
 return search_for_life(rear->next(),order);
} 

//Recursive function calls the declare_life function on each planet and returns true if any 
//of the planets find life.
bool sol_sys::search_for_life(planet*head,int order)
{
 cout << order <<":" << endl;
 bool check = head->declare_life();
 if (head == rear) return check;
 return search_for_life(head->next(),++order) +check;
}

//traverses the solar system, each time updating the ship passed by value. This is so that the changes made to
//ship in this function do not hold in other sol_sys'.
bool sol_sys::traverse_sol_sys(spaceship ship)
{
 if (!rear) return 0;
 cout << "Welcome to this solar system. Here are the sun details:\n";
 cout << "Sun Name: " << sun_name << endl;
 cout << "Sun Radius: " << sun_radius << " million km\n\n";
 cout << "To move around in the solar system, use the functions listed below.\n"
      << "Remember to use appropriate values as the planets will move distances depending on the time elapsed due to the\n"
      << "the speed you specified\n\n";
 while (ship.move_with_input()) //user did not quit
 {
  double largest_force = 0;
  cout << "Here are the details about each planet after the time taken to travel\n\n";
  cout << "Angular Velocity|Initial Angle|X coord|y coord|\n\n";
  display_largest_force(ship,rear->next(),largest_force);
 }
 cout << "Thank you for visiting! Let's check the next one...\n\n";
 return 1;
}

//Recursively displays the planet currently exerting the largest force on ship, and every time the spaceship
//is moved, this function is run
void sol_sys::display_largest_force(spaceship & ship,planet *head,double &largest_force)
{
 head->update_pos(ship); //the change of my_time in the ship is propagated to all planets in all sol_sys
 double force = head->find_force(ship,false);
 head->display_inline();
 if (force > largest_force) 
 {
  largest_force = force;
  if (head == rear) //if the last planet exerted most force
  {
   head->find_force(ship,true);
   head->declare_life();
  }
 }
 if (head == rear) return;
 display_largest_force(ship,head->next(),largest_force);
 if (force == largest_force) 
 {
  head->find_force(ship,true);
  head->declare_life();
 }
 return;
}
 
//Recursive destructor implemented for a planet
sol_sys::~sol_sys()
{
 if (sun_name) delete[]sun_name; 
 if (rear) {
  planet * hold = rear->next();
  rear->next() = NULL;
  delete hold;
 }
}
