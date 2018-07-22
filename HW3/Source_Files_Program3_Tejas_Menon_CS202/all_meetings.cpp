//all_meetings.cpp file by Tejas Menon, CS202, last edited 7/14.
//Purpose: This file contains the class implementation of the all_meetings red black tree ADT
//         and its globally overloaded operator function <<. This class manipulates a red black tree
//         to add keywords (meetings) with the same keyworded meetings falling in the same LLL.  

#include "all_meetings.h"

all_meetings::all_meetings(int start_num):start_file_num(start_num),last_file_num(start_num),root(NULL) {}

all_meetings::~all_meetings()
{
 if (root) delete root;
 for (int i=start_file_num;i<last_file_num;++i) {
  stringstream ss;
  ss << i;
  string temp = ss.str(); 
  remove(temp.c_str());
 }
}

all_meetings::all_meetings(const all_meetings&from)
{
 start_file_num = from.start_file_num;
 last_file_num = from.last_file_num;
 copy(from.root,root);
}

void all_meetings::copy(keyword*from,keyword*&to)
{
 if (!from) return;
 to = new keyword(*from);
 copy(from->left(),to->left());
 copy(from->right(),to->right());
}

all_meetings& all_meetings::operator=(const all_meetings&from)
{
 if (this != &from) {
  if (root) delete root; root = NULL;
  start_file_num = from.start_file_num;
  last_file_num = from.last_file_num;
  copy(from.root,root);
 }
 return *this;
}

keyword* all_meetings::operator[](const char * a_keyword)
{
 return search(a_keyword,root);
}

//Searches for a keyword in the tree
keyword* all_meetings::search(const char * a_keyword,keyword * root)
{
 if (!root) return NULL;
 if (*root == a_keyword) return root;
 if (*root > a_keyword) return search(a_keyword,root->left());
 else return search(a_keyword,root->right());
}

//gets input for adding a user inputted response 
void all_meetings::add_response()
{
 char keyword1[TEMP];
 char meeting_name[TEMP];
 char response[TEMP];
 contact temp;
 cout << "Hello user, to add a response to a certain meeting, please enter in these details:\n";
 cout << "The keyword that the meeting is associated with: ";
 cin.get(keyword1,TEMP,'\n'); cin.ignore(100,'\n');
 cout << "The meeting name you want to add to: ";
 cin.get(meeting_name,TEMP,'\n'); cin.ignore(100,'\n');
 cout << "Now please enter the name of the participant you want to respond as: ";
 cin >> temp; cin.ignore(100,'\n');
 cout << "Their response: ";
 cin.get(response,TEMP,'\n'); cin.ignore(100,'\n');
 keyword * add_in = this->operator[](keyword1);
 if (!add_in) cout << "Sorry, the keyword couldn't be found!\n\n";
 else { 
  bool check = add_in->add_response(meeting_name,temp,response); 
  if (check) cout << "Adding the response was successful!\n\n";
  else cout << "Either the meeting name or contact was invalid. Could not add!\n\n";
 }
}

ostream& operator<<(ostream&out,const all_meetings&show)
{
 return show.display_all(out,show.root);
}

//Displays all meetings in the tree
ostream& all_meetings::display_all(ostream&out,keyword*root) const
{
 if (!root) return out;
 display_all(out,root->left());
 out << *root << "\n\n";
 return display_all(out,root->right());
}

//Wrapper to add a meeting using the red black insertion algorithm
void all_meetings::add_meeting()
{
 cout << "To add a meeting, please enter in these details:\n";
 keyword to_add(last_file_num++);
 cin >> to_add;
 int reds = 0;
 bool direct = 0; //direction 1 for right, 0 for left
 add_meeting(root,reds,direct,to_add);
 root->color() = 0;
 cout << "Meeting added!" << endl;
}

//Adds a meeting, then checks for two reds in a row, and in case of a red sibling, recolors and checks again
//and otherwise performs the appropriate rotation
void all_meetings::add_meeting(keyword*&root,int & reds,bool & direct,const keyword & to_add)
{
 if (!root) {
  root = new keyword(to_add);
  root->left() = root->right() = NULL;
  root->color() = 1; ++reds;
  return;
 }
 bool go_to;
 if (to_add > *root) {
  go_to = 1;
  add_meeting(root->right(),reds,direct,to_add);
 }
 else if (to_add < *root) {
  go_to = 0;
  add_meeting(root->left(),reds,direct,to_add);
 }
 else if (to_add == *root) {
  *root += to_add;
  return;
 }
 if (reds<2 && !root->color()) {
  reds = 0;
  return;
 }
 if (reds == 1) {
  ++reds; 
  direct = go_to;
  return;
 }
 if (reds == 2) {
  if (root->right() && root->right()->color() == 1 && root->left() && root->left()->color()==1) {
   root->color() = 1;
   root->left()->color() = 0;
   root->right()->color() = 0; reds=1;
   return;
  }
  if (go_to==0 && direct==0) right_rotate(root);
  if (go_to==1 && direct==1) left_rotate(root);
  if (go_to==0 && direct==1) {
   left_rotate(root->left());
   right_rotate(root);
  }
  if (go_to==1 && direct==0) {
   right_rotate(root->right());
   left_rotate(root);
  }
  reds = 0;
  return;
 }
}

//left rotates for the above insertion
void all_meetings::left_rotate(keyword*&root)
{
 if (root->color() == 0) {
  root->color() = 1;
  root->right()->color() = 0;
 }
 keyword * hold = root;
 root = root->right();
 hold->right() = root->left();
 root->left() = hold;
} 

//right rotates for the above insertion
void all_meetings::right_rotate(keyword*&root)
{
 if (root->color() == 0) {
  root->color() = 1;
  root->left()->color() = 0;
 }
 keyword * hold = root;
 root = root->left();
 hold->left() = root->right();
 root->right() = hold;
} 
