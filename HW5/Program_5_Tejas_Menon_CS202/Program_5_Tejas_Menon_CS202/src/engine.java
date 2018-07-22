//engine.java file by Tejas Menon, CS202 for Programs 4-5. Last edited 8/23.
//Purpose: This file contains functions that implement engine, and is a subclass of feature.
//         The file reads, outputs and copies itself, calling the super class when necessary.

import java.io.*;

class engine extends feature{

   protected String type;
   protected String output;
   protected String volume;
   protected String efficiency;

   public engine() {
       super("engine"); } //Sets the feature type of super to "wheels"

    // This function is used in car.java to copy an option from the opt_list to the choice_list. Accessed through the add() function
   public engine(engine from) {
       super(from);
       this.type = from.type;
       this.output = from.type;
       this.volume = from.volume;
       this.efficiency = from.efficiency;
   }

   //This function calls the base class's recursive add in function after reading in the appropriate values for itself.
    //It uses BufferedReader's marking and resetting functions for moving around in the buffer
   public boolean read_in(BufferedReader br) throws IOException {
       if (!br.ready()) return false;
       br.mark(100);
       br.readLine(); br.readLine(); br.readLine(); br.readLine();
       this.type = br.readLine();
       this.output = br.readLine();
       this.volume = br.readLine();
       this.efficiency = br.readLine();
       br.reset();
       return super.read_in(br);
   }

   //This function displays details for itself and its parent
   public void display() {

       System.out.println("Option number: " + super.option);
       System.out.println("Option type: " + super.type);
       System.out.println("Option Price: $" + super.extra_cost);
       System.out.println("Engine type: " + this.type);
       System.out.println("Engine Output: " + this.output);
       System.out.println("Engine Volume: " + this.volume);
       System.out.println("Engine Efficiency: " + this.efficiency);
       System.out.println();
       if (next != null) next.display();
   }
}
