//main.java file by Tejas Menon, CS202 for Programs 4-5. Last edited 8/23.
//Purpose: This file contains functions that test the implementation specifically for
//         program 4. It creates a car and displays their choices for the user.

import java.util.*;
import java.io.*;

public class main {
    public static void main(String[] args) throws IOException, no_opt_list_Exception {
        System.out.println("Hello user, this program will allow you to search all cars in our company with feature choices you select.");
        System.out.println("Enter 1 to proceed with choosing your desired features (there are three), or 0 to exit");
        Scanner sc = new Scanner(System.in);
        int temp = sc.nextInt();
        sc.nextLine();
        System.out.println();
        car.create_opt_list();
        company Racecars = new company(50); //creates a company of 50 dealerships.
        if (temp == 0) return;
        car hold = new car(5);
        Racecars.search(hold.get_choices());
        System.out.println("The most desirable choices will be at the top of this list. To view all cars");
        System.out.println("in this company, please press 1. Do note there will be over 1500 cars, so the display list may be very long");
        sc.nextInt(); sc.nextLine();
        Racecars.display(); //displays the company
    }
}
