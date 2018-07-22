//all_meetings.h file by Tejas Menon, CS202, last edited 7/14.
//Purpose: This file contains the class interface for the all_meetings class and also declarations of the 
//         several global functions for all the classes. The all_meetings class performs all the overlying
//         red-black tree insertion and also performs some IO for adding a response to a certain meeting. 

#include "g_of_contacts.h"


class all_meetings
{
 public:
 all_meetings(int start_num);
 ~all_meetings();
 all_meetings(const all_meetings&);
 all_meetings& operator=(const all_meetings&);
 keyword* operator[](const char*keyword);
 keyword* search(const char*,keyword*);
 friend ostream& operator<<(ostream &,const all_meetings&);
 void add_meeting();
 void add_response();
 
 protected:
 int start_file_num;
 int last_file_num;
 keyword * root;
 
 private:
 void copy(keyword*from,keyword*&to);
 void add_meeting(keyword*&root,int & reds,bool & direct,const keyword & to_add);
 void left_rotate(keyword*&);
 void right_rotate(keyword*&); 
 ostream& display_all(ostream&out,keyword*root) const;
};


 
//globals

istream& operator>>(istream &, contact&);
ostream& operator<<(ostream &,const contact&);

bool operator==(const contact&, const contact&);
bool operator!=(const contact&, const contact&);

istream& operator>>(istream&,keyword&);
ostream& operator<<(ostream&,const keyword&);
keyword operator+(const keyword&,const keyword&);
bool operator==(const keyword&,const keyword&);
bool operator!=(const keyword&,const keyword&);
bool operator>(const keyword&,const keyword&);
bool operator<(const keyword&,const keyword&);
bool operator>=(const keyword&,const keyword&);
bool operator<=(const keyword&,const keyword&);
 
bool operator==(const keyword&,const char*);
bool operator!=(const keyword&,const char*);
bool operator>(const keyword&,const char*);
bool operator<(const keyword&,const char*);
bool operator>=(const keyword&,const char*);
bool operator<=(const keyword&,const char*);
 
bool operator==(const char*, const keyword&);
bool operator!=(const char*, const keyword&);
bool operator>(const char*, const keyword&);
bool operator<(const char*, const keyword&);
bool operator>=(const char*, const keyword&);
bool operator<=(const char*, const keyword&);

ostream& operator<<(ostream&,const all_meetings&); 

int display_menu();
void display_by_keyword(all_meetings&);
