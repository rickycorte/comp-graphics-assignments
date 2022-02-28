/**************
 Function Triangle(float x1, float y1, float x2, float y2, float x3, float y3, float r, float g, float b)

 draws a triangle connecting points (x1,y1)  (x2, y2) and (x3, y3), colored with the (r,g,b) specified color.
 vertex are expressed in Normalized screen coordinates, (i.e. in range [-1,+1]), following the Vulkan convention.
 The red, green and blue (r,g,b) values are in the range [0,1].
 
 Using function Triangle(...) try to draw a children house, similar to the one below.
 
 First remove the two function below (given only as an example), and replace them with your own.
 Since it is a C program, you can use for loops if you think it can be helpful in your drawing.
 The for() command below that draws a sun like shape in exact center of the screen near the top,
 is an example on how you can use it: please remove it, and replace it with your own code.
 It is not necessery to use a for loop if you do not really need it: it has been put here only as
 an example to help students not familiar with C++.
***************/

// this file is just copy pasted inside a loop so macros are the only way to make magic things without becoming crazy by repetition
// Alternatively you can edit the main cpp file to create similar function that runs the macros code :3
//This approach is totally bad for many different reasons but the assignment asks to edit only this file so...

float lh, rh, top, bot;

#define QUAD(center_x, center_y, size_x, size_y, r, g, b) 	\
	lh = center_x - size_x /2;				 				\
	rh = center_x + size_x /2;				 				\
	top = center_y + size_y /2;			 					\
	bot = center_y - size_y /2;			 					\
	Triangle(lh, top, rh, top, lh, bot, r, g, b);	 		\
	Triangle(rh, top, rh, bot, lh, bot, r, g, b);

#define CIRCLE(x, y, radius, frames, r, g, b) 					\
	for(int i =0; i< frames; i++) {								\
		float step = 2.0 * 3.14159 / (float)frames;	  							\
		Triangle(x, y, 						 					\
			x + radius * cos(step * i), y - radius * sin(step * i),				\
			x + radius * cos(step * (i+1)), y - radius * sin( step * (i+1)),		\
			r, g, b);											\
	}

// house
QUAD(0.35, 0.5,0.5, 0.6, 0.0, 0.0, 1.0)
Triangle(0, 0.2, 0.35, -0.4, 0.7, 0.2, 1,0,0);
QUAD(0.45, 0.35, 0.1, 0.1, 1, 1, 0)
QUAD(0.25, 0.35, 0.1, 0.1, 1, 1, 0)
QUAD(0.35, 0.7, 0.1, 0.2, 1, 1, 0)

// draw a sample flower
QUAD(-0.5, 0.75, 0.01, 0.2, 0, 1, 0)
CIRCLE(-0.5, 0.7, 0.05, 50, 0.698, 0.160, 0.701)
CIRCLE(-0.5, 0.7, 0.02, 50, 1, 1, 0)

// ground
QUAD(0, 0.9, 2, 0.2, 0, 1, 0)


for(int i = 0; i < 32; i++) {
	Triangle( 0.00 + 0.05 * cos(6.28/32*(i-0.5)), -0.80 + 0.05 * sin(6.28/32*(i-0.5)),
			  0.00 + 0.10 * cos(6.28/32*i), -0.80 + 0.10 * sin(6.28/32*i),
			  0.00 + 0.05 * cos(6.28/32*(i+0.5)), -0.80 + 0.05 * sin(6.28/32*(i+0.5)),
			  1,1,0);
}
