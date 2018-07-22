//feature.java file by Tejas Menon, CS202 for Programs 4-5. Last edited 8/23.
//Purpose: This file contains the class implementation for feature that is the abstract base
//         hosting all common functions that can be called on all three of its children wheels, color and engine.
//         Most functions in this file are implemented recursively to allow for managing its specific LLL - both for
//         the user choice list and also for the options list that is generated upon program execution.

import java.io.*;

abstract class feature {
    protected String type; //type of feature - color, wheels or engine
    protected int option; //the option number that was read in
    protected int priority; //For Prog5, I will need to display results based on this priority
    protected int extra_cost; //cost for this feature
    protected feature next; //stores the next option or the next choice made (Upcasting)

    public abstract void display(); //display is implemented in the base classes
    public feature(String type) {
       this.type = type; //immutability of strings guarantees string integrity
    }

    public feature(feature from) {
        this.type = from.type;
        this.option = from.option;
        this.priority = from.priority;
        this.extra_cost = from.extra_cost;
        next = null;
    }

    //This function adds 'from' to the end of the LLL of features, using RTTI to add the appropriate node
    public boolean add(feature from) {
        if (from == null) return false;
        if (next == null) {
            if (from.getClass().getName().equals("color")) {
                next = new color((color) from); //DOWNCAST
            } else if (from.getClass().getName().equals("engine")) {
                next = new engine((engine) from);
            } else if (from.getClass().getName().equals("wheels")) {
                next = new wheels((wheels) from);
            }
            return true;
        }
        return next.add(from);
    }

    //This function searches in the option list for the option specified in the argument and returns
    //its feature reference to the calling routine.
    public feature search_for(int option) {
       if (option == this.option) return this;
       if (next != null) return next.search_for(option);
       return null; //option number out of bounds
    }

    //This function reads in strings in a specific manner and marks and resets the read in point.
    //Finally it passes in the modified buffer to the super class that then executes the overrided function
    public boolean read_in(BufferedReader br) throws java.io.IOException {
      if (!br.ready()) return false;
      type = br.readLine();
      String hold = br.readLine();
      option = Integer.parseInt(hold);
      hold = br.readLine();
      priority = Integer.parseInt(hold);
      hold = br.readLine();
      extra_cost = Integer.parseInt(hold);
      br.readLine(); br.readLine(); br.readLine(); br.readLine();
      if (type.equals("engine")) br.readLine();
      br.mark(100);
      hold = br.readLine();
      br.reset();
      if (hold == null || !hold.equals(type)) return true;
      if (type.equals("engine")) next = new engine();
      if (type.equals("color")) next = new color();
      if (type.equals("wheels")) next = new wheels();
      return next.read_in(br);
    }
}
