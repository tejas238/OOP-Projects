//meeting.cpp file by Tejas Menon, CS202, last edited 7/14.
//Purpose: This file contains the class implementation of the meeting (parent g_of_contacts) and its derived keyword class
//         and also all its global function declarations. The keyword class provides functionality for the LLL and also
//         manages input, output and several other operators. 


#include "all_meetings.h"

meeting::meeting(int file_number):g_of_contacts(file_number),meeting_name(NULL),meeting_location(NULL),meeting_time(NULL) {}

meeting::~meeting()
{
 if (meeting_name) delete[]meeting_name;
 if (meeting_location) delete[]meeting_location;
 if (meeting_time) delete[]meeting_time;
}

meeting::meeting(const meeting&from):g_of_contacts(from)
{
 copy(from);  
} 

void meeting::copy(const meeting&from)
{
 meeting_name = new char[strlen(from.meeting_name)+1]; strcpy(meeting_name,from.meeting_name);
 meeting_location = new char[strlen(from.meeting_location)+1]; strcpy(meeting_location,from.meeting_location);
 meeting_time = new char[strlen(from.meeting_time)+1]; strcpy(meeting_time,from.meeting_time);
}

meeting& meeting::operator=(const meeting&from)
{
 if (this != &from) {
  if (meeting_name) delete[]meeting_name;
  if (meeting_location) delete[]meeting_location;
  if (meeting_time) delete[]meeting_time;
  g_of_contacts::operator=(from);
  copy(from);
 }
 return *this;
}

void meeting::input()
{
 char temp[TEMP];
 if (meeting_name || meeting_time || meeting_location) return;
 g_of_contacts::input();
 cout << "Please enter the name of the meeting" << endl; 
 cin.get(temp,TEMP,'\n'); cin.ignore(100,'\n');
 meeting_name = new char[strlen(temp)+1]; strcpy(meeting_name,temp);
 cout << "Please enter the date and time of the meeting" << endl;
 cin.get(temp,TEMP,'\n'); cin.ignore(100,'\n');
 meeting_time = new char[strlen(temp)+1]; strcpy(meeting_time,temp);
 cout << "Now please enter the location of the meeting" << endl;
 cin.get(temp,TEMP,'\n'); cin.ignore(100,'\n');
 meeting_location = new char[strlen(temp)+1]; strcpy(meeting_location,temp);
 cout << "*Meeting information recorded*\n";
}

void meeting::display() const
{
 cout << "Meeting name: " << meeting_name << endl;
 cout << "Meeting location: " << meeting_location << endl;
 cout << "Meeting time: " << meeting_time << endl;
 g_of_contacts::display(); 
}

keyword::keyword(int file_num):meeting(file_num),word(NULL),next_k(NULL),left_k(NULL),right_k(NULL),color_rb(0) {}

keyword::~keyword() 
{
 if (word) delete[]word;
 if (next_k) delete next_k;
 if (right_k) delete right_k;
 if (left_k) delete left_k;
} 

keyword::keyword(const keyword&from):meeting(from),right_k(NULL),left_k(NULL),next_k(NULL)
{
 copy(from,false);
}

void keyword::copy(const keyword&from,bool in_new)
{
 if (!next_k && !in_new) {
  color_rb = from.color_rb;
  if (from.word) {
   word = new char[strlen(from.word)+1]; strcpy(word,from.word);
  }
  if (from.next_k) next_k = new keyword(*(from.next_k));
 }
 else if(in_new && !next_k) next_k = new keyword(from);
 else next_k->copy(from,in_new);
}

keyword& keyword::operator=(const keyword&from) 
{
 if (this != &from) {
  if (next_k) delete next_k; next_k = NULL;
  if (word) delete[] word;
  meeting::operator=(from);
  copy(from,false);
 }
 return *this;
}

keyword operator+(const keyword&one,const keyword&two)
{
 keyword temp = one;
 temp.copy(two,true);
 return temp;
}

keyword& keyword::operator+=(const keyword&from)
{
 return *this = *this + from; 
}

istream& operator>>(istream&in,keyword&from)
{
 char temp[TEMP];
 if (from.word) delete[]from.word;
 from.meeting::input();
 cout << "Now please enter a keyword that identifies the meeting" << endl;
 in.get(temp,TEMP,'\n'); in.ignore(100,'\n');
 from.word = new char[strlen(temp)+1]; strcpy(from.word,temp);
 cout << "*Keyword added*\n\n" << endl;
 return in;
}  
 
ostream& operator<<(ostream&out,const keyword&from)
{
 out << "Keyword identifying this meeting: " << from.word << "\n\n";
 from.meeting::display();
 if (from.next_k) out << *(from.next_k);
 return out;
}

bool operator==(const keyword&one,const keyword&two)
{
 return !strcmp(one.word,two.word);
}

bool operator!=(const keyword&one,const keyword&two)
{
 return !(one==two);
}

bool operator>(const keyword&one,const keyword&two)
{
 return (strcmp(one.word,two.word)>0);
}

bool operator<(const keyword&one,const keyword&two)
{
 return two>one;
}

bool operator>=(const keyword&one,const keyword&two)
{
 return ((one>two)||(one==two));
}

bool operator<=(const keyword&one,const keyword&two)
{
 return two>=one;
}
 
bool operator==(const keyword&one,const char*two)
{
 return !strcmp(one.word,two);
} 
 
bool operator!=(const keyword&one,const char*two)
{
 return !(one==two);
}

bool operator>(const keyword&one,const char*two)
{
 return (strcmp(one.word,two)>0);
}

bool operator<(const keyword&one,const char*two)
{
 return two>one;
}

bool operator>=(const keyword&one,const char*two)
{
 return ((one>two)||(one==two));
}
 
bool operator<=(const keyword&one,const char*two)
{
 return two>=one;
}
 
bool operator==(const char*one, const keyword&two)
{
 return !strcmp(one,two.word);
}

bool operator!=(const char*one, const keyword&two)
{
 return !(one==two);
}

bool operator>(const char*one, const keyword&two)
{
 return (strcmp(one,two.word)>0);
}

bool operator<(const char*one, const keyword&two)
{
 return two>one;
} 

bool operator>=(const char*one, const keyword&two)
{
 return ((one>two)||(one==two));
} 

bool operator<=(const char*one, const keyword&two)
{
 return two>=one; 
} 

bool keyword::add_response(char * meeting, const contact& from,char * response) const
{
 if (!strcmp(meeting,meeting_name)) {
  bool check = 0;
  for(int i=0;i<size;++i) {
   if (list[i].add_response(from,response,file_num)) check = 1;;
  }
  return check;
 }
 if (next_k) return next_k->add_response(meeting,from,response);
 return 0;
}

keyword*& keyword::left()
{
 return left_k;
}

keyword*& keyword::right()
{
 return right_k;
}

bool& keyword::color()
{
 return color_rb;
}
