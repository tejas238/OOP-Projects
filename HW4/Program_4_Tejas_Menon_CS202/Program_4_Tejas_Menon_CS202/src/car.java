//car.java file by Tejas Menon, CS202 for Programs 4-5. Last edited 8/23.
//Purpose: This file contains functions that implement car, and this class performs all
//         client based user IO for availing details of their choices. The creation of a car
//         automatically acquires details regarding its contents. This automation will be useful
//         for program 5.

import java.util.*;
import java.io.*;

class car {
    protected feature[] options; //An array of size 3 - the LLL of each element corresponding to its feature
    protected feature choices; //The choices that a user makes. In Prog5, this will be autofilled with 3 random features

    //This function creates a car and performs all operations to initialize one. MAXOPT corresponds to the largest
    //option number available to each feature in the external file. All features should contain the same number of options. (Not necessary but advised)
    public car(int MAXOPT) throws java.io.IOException {
        this.create_opt_list(); //creates the option list prior to IO
        Scanner in = new Scanner(System.in);
        int temp;
        System.out.println("Choose one option for your car from each of the three categories Wheel, engine and color below");
        for(int i=0;i<3;++i) {
            options[i].display(); //displays the LLL corresponding to each feature
            System.out.println();
            System.out.print("Please enter the option number you want: ");
            temp = in.nextInt();
            in.nextLine();
            while (temp<1 || temp>MAXOPT) {
                System.out.println("Please re-enter your option!");
                temp = in.nextInt();
                in.nextLine();
            }
            System.out.println("Adding your choice to the car's specification!");
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

    //This function creates the option list the is to be chosen from
    public boolean create_opt_list() throws java.io.IOException{

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
        choices.display();
    }
}
