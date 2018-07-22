//g_of_contacts.h file by Tejas Menon, CS202, last edited 7/14.
//Purpose: This file contains the class interface for the g_of_contacts, its containing contact class and also its derivatives meeting and keyword
//         The g_of_contacts manages an array of contacts for each class out of which it can choose to
//         perform any correspondence to its meeting's unique external data file. The contacts class additionally
//         supports operators for ease in using the all_meetings class.


#include <iostream>
#include <fstream>
#include <cctype>
#include <cstring>
#include <ctime>
#include <cstdio>
#include <string> //USED ONLY FOR INTEGER TO STRING CONVERSION (Not available for cstring)
#include <sstream>

using namespace std;

const int TEMP = 1000;

class g_of_contacts 
{
 public:
 g_of_contacts(int file_number);
 ~g_of_contacts();
 g_of_contacts(const g_of_contacts&);
 g_of_contacts& operator=(const g_of_contacts&);
 void input();
 void display()const;
 
 protected:
 class contact * list;
 int size;
 int file_num;
 
 private:
 void copy(const g_of_contacts&);
}; 

class contact
{
 public:
 contact();
 ~contact();
 contact(const contact&);
 contact& operator=(const contact&);
 friend istream& operator>>(istream &,contact&);
 friend ostream& operator<<(ostream &,const contact&);
 friend bool operator==(const contact&, const contact&);
 friend bool operator!=(const contact&, const contact&);
 bool add_response(const contact& from,char * response,int file_num) const;
 void copy(const contact&);

 protected:
 char * name; 
};

class meeting: public g_of_contacts
{
 public:
 meeting(int file_number);
 ~meeting();
 meeting(const meeting&);
 meeting& operator=(const meeting&);
 void input();
 void display() const;

 protected:
 char * meeting_name;
 char * meeting_location;
 char * meeting_time;
 
 private:
 void copy(const meeting&);
};

class keyword: public meeting
{
 public:
 keyword(int file_number);
 ~keyword();
 keyword(const keyword&);
 keyword& operator=(const keyword&);
 keyword& operator+=(const keyword&);

 friend istream& operator>>(istream&,keyword&);
 friend ostream& operator<<(ostream&,const keyword&);
 friend keyword operator+(const keyword&,const keyword&);
 friend bool operator==(const keyword&,const keyword&);
 friend bool operator!=(const keyword&,const keyword&);
 friend bool operator>(const keyword&,const keyword&);
 friend bool operator<(const keyword&,const keyword&);
 friend bool operator>=(const keyword&,const keyword&);
 friend bool operator<=(const keyword&,const keyword&);
 
 friend bool operator==(const keyword&,const char*);
 friend bool operator!=(const keyword&,const char*);
 friend bool operator>(const keyword&,const char*);
 friend bool operator<(const keyword&,const char*);
 friend bool operator>=(const keyword&,const char*);
 friend bool operator<=(const keyword&,const char*);
 
 friend bool operator==(const char*, const keyword&);
 friend bool operator!=(const char*, const keyword&);
 friend bool operator>(const char*, const keyword&);
 friend bool operator<(const char*, const keyword&);
 friend bool operator>=(const char*, const keyword&);
 friend bool operator<=(const char*, const keyword&);
 
 bool add_response(char * meeting, const contact& from,char * response)const;
 keyword*& left();
 keyword*& right();
 bool& color();
  
 protected:
 char * word;
 bool color_rb; //1 is red and 0 is black
 keyword * next_k; 
 keyword * left_k;
 keyword * right_k;

 private:
 void copy(const keyword&,bool in_new);
};
