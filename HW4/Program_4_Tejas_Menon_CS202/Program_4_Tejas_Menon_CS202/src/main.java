//main.java file by Tejas Menon, CS202 for Programs 4-5. Last edited 8/23.
//Purpose: This file contains functions that test the implementation specifically for
//         program 4. It creates a car and displays their choices for the user.

import java.util.*;
import java.io.*;

public class main {
    public static void main(String []args) throws IOException {
        System.out.println("Hello user, this program will allow you to create a personalized car from three features.");
        System.out.println("Enter 1 to proceed with choosing your car, or 0 to exit");
        Scanner sc = new Scanner(System.in);
        int temp = sc.nextInt();
        System.out.println();
        if (temp != 0) {
            System.out.println("Please enter the amount of options you have for each feature in the external file. ONLY 5 ARE IN BY DEFAULT!!");
            temp = sc.nextInt();
            System.out.println();
            car test = new car(temp);
            System.out.println(); System.out.println();
            System.out.println("Here are your choices!");
            test.display_cho_list();
        }
    }
}
