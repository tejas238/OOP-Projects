//car.java file by Tejas Menon, CS202 for Programs 4-5. Last edited 8/23.
//Purpose: This file contains functions that implement car, and this class performs all
//         client based user IO for availing details of their choices. The creation of a car
//         automatically acquires details regarding its contents. This automation will be useful
//         for program 5.

import java.util.*;
import java.io.*;

class no_opt_list_Exception extends java.lang.Exception{}

class car {
    static protected feature[] options; //An array of size 3 - the LLL of each element corresponding to its feature
    protected feature choices; //The choices that a user makes. In Prog5, this will be autofilled with 3 random features
    protected String car_name;
    protected int search_score;
    protected car right_n;
    protected car left_n;

    //This function creates a car and performs all operations to initialize one. MAXOPT corresponds to the largest
    //option number available to each feature in the external file. All features should contain the same number of options. (Not necessary but advised)
    public car(String car_name,int MAXOPT) throws java.io.IOException, no_opt_list_Exception {
        Random rand = new Random();
        this.car_name = car_name;
        this.search_score = 0;
        this.left_n = null;
        this.right_n = null;
        if (options == null) throw new no_opt_list_Exception(); //if no option list initialized statically, then throws
        int temp;
        for(int i=0;i<3;++i) {
            if (i==0) { //RTTI to find the correct feature to make
                color choice = (color) options[0].search_for(rand.nextInt(MAXOPT)+1);
                choices = new color(choice);
            }
            if (i==1) {
                engine choice = (engine) options[1].search_for(rand.nextInt(MAXOPT)+1);
                choices.add(choice); //add function can be called for all subsequent entries
            }
            if (i==2) {
                wheels choice = (wheels) options[2].search_for(rand.nextInt(MAXOPT)+1);
                choices.add(choice);
            }
        }
    }

    public car(int MAXOPT) throws no_opt_list_Exception {
        this.search_score = 0;
        this.left_n = null;
        this.right_n = null;
        if (options == null) throw new no_opt_list_Exception(); //if no option list initialized statically, then throws
        for(int i=0;i<3;++i) {
            options[i].display();
            System.out.println("Please enter an option from the list above:");
            Scanner sc = new Scanner(System.in);
            int temp = sc.nextInt(); sc.nextLine();
            while (temp<=0 || temp>MAXOPT) {
                System.out.println("Please re-enter a valid value:");
                temp = sc.nextInt(); sc.nextLine();
            }
            if (i==0) { //RTTI to find the correct feature to make
                color choice = (color) options[0].search_for(temp);
                choices = new color(choice);
            }
            if (i==1) {
                engine choice = (engine) options[1].search_for(temp);
                choices.add(choice); //add function can be called for all subsequent entries
            }
            if (i==2) {
                wheels choice = (wheels) options[2].search_for(temp);
                choices.add(choice);
            }
        }
    }

    public car(car from) {
        this.car_name = from.car_name;
        this.search_score = from.search_score;
        this.right_n = null;
        this.left_n = null;
        this.choices = new color((color)from.choices);
        this.choices.add(from.choices.next());
        this.choices.add(from.choices.next().next());
    }

    public boolean set_search_score(feature choices) {
        search_score = 0;
        if (choices == null) return false;
        int for_color = choices.get_option();
        int for_engine = choices.next().get_option();
        int for_wheels = choices.next().next().get_option();
        if (for_color == this.choices.get_option()) search_score += 2;
        if (for_engine == this.choices.next().get_option()) search_score += 3;
        if (for_wheels == this.choices.next().next().get_option()) search_score += 1;
        return true;
    }

    //This function creates the option list the is to be chosen from
    public static boolean create_opt_list() throws java.io.IOException{

        if (options != null) return false;
        BufferedReader br = new BufferedReader(new FileReader("all_options.txt"));
        options = new feature[3];
        options[0] = new color();
        options[0].read_in(br);
        options[1] = new engine();
        options[1].read_in(br);
        options[2] = new wheels();
        options[2].read_in(br);
        return true;
    }

    //Displays the choice list chosen by the user
    public void display_cho_list() {
        System.out.println("Car name: " + car_name);
        System.out.println();
        if (choices == null) return;
        choices.display();
    }

    public feature get_choices() { return choices; } //used to return user choices to begin search

    public car left() {
        return left_n;
    }

    public car right() {
        return right_n;
    }

    public void set_right(car right_n) { this.right_n = right_n;}

    public void set_left(car left_n) { this.left_n = left_n;}

    public int compareTo(String car_name) {
      return this.car_name.compareTo(car_name);
    }

    public int get_search_score() { return search_score;}
}
