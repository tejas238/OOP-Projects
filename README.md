# CS202 Projects – Object Oriented Programming in C++ and Java

**C++**
**Star Exploration Game**

* Procedurally generated star system allows user exploration to discover a planet with life.
* A planet with life depends on several factors- distance from the local sun, composition, number of moons, atmosphere & velocity. These factors affect each other and the passage of time causes these to change.
* ADT implements a DLL for all planets in a solar system and an array of DLLs for a solar systems in a galaxy
* Velocity and mass of spaceship affects its position in space and the chosen planet to investigate depends on which planet exerts highest gravitational force on the spaceship.
* Preset planet conditions are read from an external file which depend on planet object's variables.
* Inheritence is implemented for derived classes such as planet/spaceship to behave like fundamental classes such as mass/time. 

**Event Management Chat System**

* An event posting and chatting application allows users to sign-up and create event specific chat threads.
* Events are identified by a keyword and stored within a red-black tree organized by keyword. Events with the same keyword are stored in a linear linked list and are accessible in O(logn) time.
* Events can be displayed and its corresponding chat when queried by keyword. Operator overloading implements common functions for LLL insertion/display/replication and relational operators for comparison between users and events.
* Chat histories are stored within a dynamically created external data file per event.

**Java**
**Product Selection & Search Interface**

* For a choice of vehicular features - wheels, color and engine - a user is able to display search results for all cars ordered by a match score. Cars are randomly generated with feature configurations chosen from an external data file and placed into randomly assigned dealership objects.
* A BST within a BST stores all cars arranged by name with the outer BST storing all dealerships also arranged by name.
* A search invocation assigns a match score to every car in the database and then creates another search result BST storing cars by match score value.
