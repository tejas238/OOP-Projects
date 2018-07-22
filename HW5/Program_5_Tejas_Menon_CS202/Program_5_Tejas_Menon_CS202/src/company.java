//company.java by Tejas Menon, CS202, last edited 08/30.
//Purpose: This file contains all BST operations to manage a BST of dealerships.
//         Upon program execution, it creates a BST of num_of_dealership dealerships
//         automatically using a random number generator for the number of cars for each
//         dealership.

import java.io.*;
import java.util.*;

class company {
   private dealership root; //all dealerships in the BST
   private dealership sort_root; //A temporary search BST containing all the cars (in the company) ordered convieniently by the search score
   protected int num_of_dealerships;

   //creates a company having 'num of dealership' dealerships.
   public company(int num_of_dealerships) throws IOException,no_opt_list_Exception {
       this.num_of_dealerships = num_of_dealerships;
       sort_root = null;
       for(int i=0;i<num_of_dealerships;++i) {
           root = add_dealership(root,get_dealership_name());
       }
   }

   //Gets a location for a dealership from the 'cars&dealerships' file using a random num generator to pick the line
   protected String get_dealership_name() throws IOException {
       Random rand = new Random();
       int rand_opt;
       String dealership_name = null;
       rand_opt = rand.nextInt(14) + 53;
       BufferedReader br = new BufferedReader(new FileReader("cars&dealerships.txt"));
       while (rand_opt-- != 0) dealership_name = br.readLine();
       return dealership_name;
   }

   //Wrapper search to get from the user details about the search, calling several functions and setting up the
    //sort_root using the user's choice list
   public void search(feature choices) {
       this.sort_root = new dealership();
       search(choices,this.sort_root,this.root); //populates sort_root in the most desirable order
       Scanner sc = new Scanner(System.in);
       System.out.println("Upto how many search results would you like displayed?");
       int upto = sc.nextInt();
       sc.nextLine();
       while(upto<=0) {
           System.out.println("Please enter a valid value");
           upto = sc.nextInt();
       }
       System.out.println("Here are your results:");
       sort_root.display_by_score(upto); //displays from largest to smallest (highest score first)
   }

   //Recursive search that kickstarts the search function for each dealership to manage its car list
   private void search(feature choices,dealership add_to,dealership root) {
       if (root == null) return;
       root.set_search_score(choices,add_to);
       search(choices,add_to,root.left());
       search(choices,add_to,root.right());
   }

   //Adds a dealership to the company depending on the dealership name (happens at company declaration)
   private dealership add_dealership(dealership root,String dealership_name) throws IOException,no_opt_list_Exception  {
       if (root == null) {
           Random rand = new Random();
           root = new dealership(10+rand.nextInt(60),dealership_name);
           return root;
       }
       if (root.compareTo(dealership_name)<=0) root.set_right(this.add_dealership(root.right(),dealership_name));
       else root.set_left(this.add_dealership(root.left(),dealership_name));
       return root;
   }

   //displays the entire company (All cars in each dealership location) by calling the recursive display
   public void display() {
       System.out.println("Number of dealerships in the company: "+ num_of_dealerships);
       System.out.println("Cars across all dealerships: ");
       System.out.println("----------------------------------\n");
       display(root);
       System.out.println();
   }

   //Touches every dealership and calls its display function
   private void display(dealership root) {
       if (root == null) return;
       display(root.left());
       root.display();
       display(root.right());
   }
}
