//wheels.java file by Tejas Menon, CS202 for Programs 4-5. Last edited 8/23.
//Purpose: This file contains functions that implement wheels, and is a subclass of feature.
//         The file reads, outputs and copies itself, calling the super class when necessary.

import java.io.*;

class wheels extends feature{

   protected String type;
   protected String material;
   protected String size;

   public wheels() {
       super("wheels"); } //Sets the feature type of super to "wheels"

   //This function is used in car.java to copy an option from the opt_list to the choice_list. Accessed through the add() function
   public wheels(wheels from) {
       super(from);
       this.type = from.type;
       this.material = from.material;
       this.size = from.size;
   }

   //This function calls the base class's recursive add in function after reading in the appropriate values for itself.
    //It uses BufferedReader's marking and resetting functions for moving around in the buffer
   public boolean read_in(BufferedReader br) throws IOException {
       if (!br.ready()) return false;
       br.mark(100);
       br.readLine(); br.readLine(); br.readLine(); br.readLine();
       this.type = br.readLine();
       this.material = br.readLine();
       this.size = br.readLine();
       br.reset();
       return super.read_in(br);
   }

   //This function displays details for itself and its parent
   public void display() {

       System.out.println("Option number: " + super.option);
       System.out.println("Option type: " + super.type);
       System.out.println("Option Price: $" + super.extra_cost);
       System.out.println("Wheel type: " + this.type);
       System.out.println("Wheel Material: " + this.material);
       System.out.println("Wheel Size: " + this.size);
       System.out.println();
       if (next != null) next.display();
   }
}
