//dealership.java by Tejas Menon, CS202, last edit edited 08/30
//Purpose: This file contains all functions to manage a BST of cars for each dealership.
//         It also contains functions to add into the BST depending on their search score
//         which is utilized by the company class to display results sorted by score

import java.io.*;
import java.util.*;

class dealership {
   private car root; //all cars in the BST
   protected String dealership_name;
   protected int num_of_cars;
   protected dealership left_n;
   protected dealership right_n;

   public dealership() {} //used for initializing a dealership for searching (with no cars at declaration).

    //Initializes a dealership with the number of cars and a dealership location/name
   public dealership(int num_of_cars, String dealership_name) throws IOException,no_opt_list_Exception {
       this.dealership_name = dealership_name;
       this.num_of_cars = num_of_cars;
       for(int i=0;i<num_of_cars;++i) {
           root = add_car(root,get_car_name());
       }
   }

   //For the name of each car, the cars&dealership file is accessed and a random line number from the cars section read in
   protected String get_car_name() throws IOException {
       Random rand = new Random();
       int rand_opt;
       String car_name = null;
       rand_opt = rand.nextInt(47) + 3;
       BufferedReader br = new BufferedReader(new FileReader("cars&dealerships.txt"));
       while (rand_opt-- != 0) car_name = br.readLine();
       return car_name;
   }

   //Adds a car to the BST with the name passed in. Reconnects on rewinding the stack
   private car add_car(car root,String car_name) throws IOException,no_opt_list_Exception  {
       if (root == null) {
           root = new car(car_name,5); //there are 5 options in the all_options file for each feature (this can be changed, but the color, engine and wheels order must be maintained
           return root;
       }
       if (root.compareTo(car_name)<=0) root.set_right(this.add_car(root.right(),car_name));
       else root.set_left(this.add_car(root.left(),car_name));
       return root;
   }

   //Wrapper function to set a search score for each car in the dealership depending on the choice list
   public void set_search_score(feature choices,dealership add_to) {
      if (choices == null) return;
      set_search_score(choices,add_to,root);
   }

   //Recursive function that touches every car and passes in the choices list to its function for setting a search score
    //Once a car has its score, its passed into the add_to BST (where its added depending on score)
   private void set_search_score(feature choices,dealership add_to,car root) {
       if (root == null) return;
       root.set_search_score(choices);
       add_to.add_by_score(root);
       set_search_score(choices,add_to,root.left());
       set_search_score(choices,add_to,root.right());
   }

   //wrapper function that calls the recursive add by score function
   public void add_by_score(car root) {
       this.root = add_by_score(this.root,root);
   }

   //Adds a car to the current 'search BST' based on its score
   public car add_by_score(car root,car to_add) {
       if (root == null) {
           root = new car(to_add);
           return root;
       }
       if (root.get_search_score()<=to_add.get_search_score()) root.set_right(add_by_score(root.right(),to_add));
       else root.set_left(add_by_score(root.left(),to_add));
       return root;
   }

   //Wrapper display that calls the inorder display recursive function
   public void display() {
       System.out.println("Dealership location: " + dealership_name);
       System.out.println("Number of cars in the dealership: " + num_of_cars);
       System.out.println("Cars for this dealership are as follows:");
       System.out.println();
       display(root);
       System.out.println();
       System.out.println("--------xxxxx--------");
       System.out.println();
   }

   //Displays all cars in the BST inorder
   private void display(car root) {
       if (root == null) return;
       display(root.left());
       root.display_cho_list();
       display(root.right());
   }

   //Calls the postorder display with cars receiving the highest score displaying first. Displays upto 'upto' searches
   public void display_by_score(int upto) {
      display_by_score(root,upto);
   }

    //Displays all cars in order upto 'upto' cars based on its search score
   public int display_by_score(car root,int upto) {
       if (root == null || upto == 0) return upto;
       upto = display_by_score(root.right(),upto);
       if (upto>0) {
           System.out.println();
           root.display_cho_list();
           --upto;
       }
       upto = display_by_score(root.left(),upto);
       return upto;
   }

   public dealership left() {
        return left_n;
    }

    public dealership right() {
        return right_n;
    }

    public void set_right(dealership right_n) { this.right_n = right_n;}

    public void set_left(dealership left_n) { this.left_n = left_n;}

    public int compareTo(String dealership_name) {
      return this.dealership_name.compareTo(dealership_name);
    }
}
