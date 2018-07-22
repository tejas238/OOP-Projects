//color.java file by Tejas Menon, CS202 for Programs 4-5. Last edited 8/23.
//Purpose: This file contains functions that implement color, and is a subclass of feature.
//         The file reads, outputs and copies itself, calling the super class when necessary.

import java.io.*;

class color extends feature{

   protected String name;
   protected String finish;
   protected String scratch_resistance;

   public color() {
       super("color"); } //Sets the feature type of super to "wheels"

    //This function is used in car.java to copy an option from the opt_list to the choice_list. Accessed through the add() function
   public color(color from) {
       super(from);
       this.name = from.name;
       this.finish = from.finish;
       this.scratch_resistance = from.scratch_resistance;
   }

    //This function calls the base class's recursive add in function after reading in the appropriate values for itself.
    //It uses BufferedReader's marking and resetting functions for moving around in the buffer
   public boolean read_in(BufferedReader br) throws IOException {
       if (!br.ready()) return false;
       br.mark(100);
       br.readLine(); br.readLine(); br.readLine(); br.readLine();
       this.name = br.readLine();
       this.finish = br.readLine();
       this.scratch_resistance = br.readLine();
       br.reset();
       return super.read_in(br);
   }

   //This function displays details for itself and its parent
   public void display() {

       System.out.println("Option number: " + super.option);
       System.out.println("Option type: " + super.type);
       System.out.println("Option Price: $" + super.extra_cost);
       System.out.println("Color name: " + this.name);
       System.out.println("Color finish: " + this.finish);
       System.out.println("Scratch Resistance: " + this.scratch_resistance);
       System.out.println();
       if (next != null) next.display();
   }
}
