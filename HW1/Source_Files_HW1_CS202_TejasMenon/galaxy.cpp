//galaxy.cpp for HW1 by Tejas Menon, CS202, last edited 7/14. 
//Purpose: This file contains the class implementations for the galaxy class, which is the highest order class,
//         and also class implementations for its containing sol_sys objects. Another utility class this 
//         file contains functions for is the namer class, which dedicates random textual output such as 
//         names and atmosphere types to sol_sys' and planets.

#include "planet.h"

namer::namer() {} //no dynamic variables

//This sole function for the class accepts a char* array that contains "planet", "sun", "gas" or "rocky"
//and for these 'types' copies back a random output to the passed in argument. It uses an external data file
//for the output
bool namer::get_random(char *& type)
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

//Calls appropriate destructors for each element of list
galaxy::~galaxy()
{
 if (list) delete[]list;
}

//Creates a sol_sys initializing all variables to NULL. 
//Doesn't make planets at this point as the intention might be
//to copy a sol_sys
sol_sys::sol_sys(): sun_name(NULL),head(NULL),tail(NULL) {} 

//copy constructor calls the copy_sol_sys function
sol_sys::sol_sys(const sol_sys & source)
{
 copy_sol_sys(source);
}

//Wrapper for the recursive copy_sol_sys function. Sun information from 
//the source is copied over first
bool sol_sys::copy_sol_sys(const sol_sys & source)
{
 if (head) return 0;
 sun_name = new char[strlen(source.sun_name)]; strcpy(sun_name,source.sun_name);
 sun_radius = source.sun_radius;
 sun_mass = source.sun_mass;
 num_of_planets = source.num_of_planets;  
 copy_sol_sys(source.head);
 return 1;
}

//Recursive copy function for all planets in source's sol_sys. Uses the get_type()
//function to ascertain the type (gas or rocky) prior to the compile time downcasting.
//Casting is required as each derived class copy constructor only accepts its object reference.
void sol_sys::copy_sol_sys(planet *source)
{
 if (!source) return;
 planet * hold = tail;
 if (source->get_type()) tail = new rocky(*reinterpret_cast<rocky*>(source));
 else tail = new gas(*reinterpret_cast<gas*>(source));
 if (!head) head = tail;
 else 
 {
  hold->next() = tail; 
  tail->prev() = hold;
 }
 copy_sol_sys(source->next());
}

//Wrapper decides a random number of planets (rocky or gas) for the current sol_sys and creates sun information.
//Also calls a recursive make_planets version to create this predecided number of planets
bool sol_sys::make_planets() 
{
 if (head) return 0; //if planets are already present
 char *sun = new char[TEMP];
 strcpy(sun,"sun");
 get_random(sun); //gets a random sun name 
 sun_name = new char[strlen(sun)+1];
 strcpy(sun_name,sun); //copies it over
 sun_radius = double(rand()%600)/100+0.3; //sun_radius in millions of km
 sun_mass = double(rand()%600)/100+0.1; //sun mass in solar masses (R)
 num_of_planets= rand()%15+2; //Decides the number of planets between 2 and 17
 make_planets(rand()%70+sun_radius,num_of_planets); //calls its recursive secondary
 delete[]sun;
 return 1;
}

//Recursive function creates successive planets (rocky or gas) at increasing distances from the sun.
//Stops when planets_left is zero. Also randomizes the planet type skewed by the distance from the sun
void sol_sys::make_planets(double distance_from_sun,int planets_left)
{
 if (!planets_left) return; //no planets to make left
 planet*hold = tail;
 int dice_roll = rand()%10+1; //A rocky planet is most LIKELY if distance is less than 250 (not a certainty). Same with a gas planet.
 if ((distance_from_sun<250 && dice_roll<10)||(distance_from_sun>=250 && dice_roll==10)) tail = new rocky(distance_from_sun); 
 else tail = new gas(distance_from_sun);
 if (!head) head=tail;
 else {
  hold->next()=tail;
  tail->prev()=hold;
 }
 make_planets(rand()%70+distance_from_sun,--planets_left); //passes a higher distance from the sun + some range.
}

//Wrapper function for the recursive search_for_life() that displays sun information for the current sol_sys
//and assigns an order to display the planets in order.
bool sol_sys::search_for_life()
{
 if (!head) return 0;
 int order = 1;
 cout << "For this Solar System, here are the sun details:\n";
 cout << "Sun Name: " << sun_name << endl;
 cout << "Sun Radius: " << sun_radius << " million km" << endl;
 cout << "Sun Mass: " << sun_mass << " Solar Masses (1S = 333,000 E)" << endl;
 cout << "Number of planets in this star system: " << num_of_planets << endl; 
 cout << "Here are the planets in this system and information about their chances of life:\n\n";
 return search_for_life(head,order);
} 

//Recursive function calls the declare_life function on each planet and returns true if any 
//of the planets find life.
bool sol_sys::search_for_life(planet*head,int order)
{
 if (!head) return 0;
 cout << order <<":" << endl;
 bool check = head->declare_life();
 return search_for_life(head->next(),++order) +check;
}

//Recursive destructor implemented for a planet
sol_sys::~sol_sys()
{
 if (sun_name) delete[]sun_name; 
 if (head) delete head;
}
