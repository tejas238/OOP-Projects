//contact.cpp file by Tejas Menon, CS202, last edited 7/14.
//Purpose: This file contains the class implementation of the g_of_contacts and contact classes and also their globally overloaded operator functions. These classes
//         manage the participants for each meeting and writes correspondence to a unique external data file for each meeting
//         that is deleted upon program exit.


#include "all_meetings.h"

g_of_contacts::g_of_contacts(int file_number):list(NULL),size(0),file_num(file_number) {}

g_of_contacts::~g_of_contacts()
{
 if (list) delete[]list;
} 

g_of_contacts::g_of_contacts(const g_of_contacts&from)
{
 copy(from); 
}

void g_of_contacts::copy(const g_of_contacts&from) 
{
 size = from.size;
 file_num = from.file_num;
 if (size) list = new contact[size];
 for(int i=0;i<size;++i) {
  list[i].copy((from.list)[i]);
 }
}

g_of_contacts& g_of_contacts::operator=(const g_of_contacts&from)
{
 if (this != &from) {
  if (list) delete[]list; 
  copy(from);
 }
 return *this;
}

void g_of_contacts::input()
{
 int num;
 if (list) return;
 cout << "Please enter the number of participants for this meeting" << endl;
 cin >> num; cin.ignore(100,'\n');
 while(num<=0) {
  cout << "Please re-enter this value" << endl;
  cin >> num; cin.ignore(100,'\n');
 }
 size = num;
 list = new contact[size];
 for(int i=0;i<size;++i) {
  cout << "Enter the name of participant "<<i+1 << endl;
  cin >> list[i]; cin.ignore(100,'\n');
 }
 cout << "*Participant input done*\n";
}

void g_of_contacts::display() const
{ 
 cout << "Here are all the participants for this meeting:" << endl;
 for (int i=0;i<size;++i) {
  cout << list[i] << ", ";
 }
 cout << "\n\nHere is the file containing all correspondence for this meeting:" << endl;
 ifstream file_in;
 char temp[TEMP];
 stringstream ss;
 ss << file_num;
 string temp1 = ss.str();
 file_in.open(temp1.c_str());
 while(file_in && !file_in.eof()) {
  file_in.getline(temp,TEMP,'\n');
  cout << temp << endl;
 }
 file_in.clear();
 file_in.close();
}

contact::contact():name(NULL) {}

contact::~contact() 
{
 if (name) delete[]name;
}

contact::contact(const contact&from)
{
 copy(from);
}

void contact::copy(const contact&from)
{
 name = new char[strlen(from.name)+1];
 strcpy(name,from.name);
}

contact& contact::operator=(const contact&from)
{
 if (this != &from) {
  if (name) delete[]name;
  copy(from);
 }
 return *this;
}

istream& operator>>(istream &in,contact&from)
{
 char temp[TEMP];
 in.get(temp,TEMP,'\n');
 from.name = new char[strlen(temp)+1]; strcpy(from.name,temp);
 return in;
} 

ostream& operator<<(ostream &out,const contact&from)
{
 out << from.name;
 return out;
}

bool operator==(const contact&check1, const contact&check2)
{
 return !strcmp(check1.name,check2.name);
}
 
bool operator!=(const contact&check1, const contact&check2)
{
 return (!(check1==check2));
}

bool contact::add_response(const contact& from,char * response,int file_num) const
{
 if (from==*this) {
  ofstream out_file;
  stringstream ss;
  ss << file_num;
  string temp1 = ss.str();
  out_file.open(temp1.c_str(),ios::app);
  out_file << "\"" << response << "\"" << endl;
  out_file << from.name << endl;
  time_t  a_time = time(NULL);
  out_file << ctime(&a_time) << "\n\n";
  out_file.close();
  out_file.clear();
  return 1;
 }
 return 0;
}
