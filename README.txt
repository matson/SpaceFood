Comments on Hunger and Fear force:

Predator: used the same draw mode as the "arrowhead" flock mode.  Changed the color and size of predator, should be yellow/purple and bigger than flockers.

Hunger Force: Used a function to compute the hunger force.  Passed the variables through the Predator constructor to use them.
Goal was to calculate the minimal distance from the predator to the flocker and set it to move in that direction. 
To do this I needed to loop through each of the flocker's distances and take the smallest 
one. Then that was set to the direction the predator must follow.  I used the same functionalities similar to the cohesion force for flockers.

Fear Force: The total opposite; first defined function and passed through the contructor.
Goal was to calculate the separation force, and check the position of the predator to do this calculation.  
Then set a boolean to compare values and if predator is "close" the fear force is present