Simple example of neural network with bias neurons.
Inspired by this video:
[![by KofyBrek](https://img.youtube.com/vi/Zrrnqd0rCXg&t=3s/0.jpg)](https://www.youtube.com/watch?v=Zrrnqd0rCXg&t=3s)

It takes x and y coordinate of display as inputs and outputs color as 3 separate R,G,B values
It is drawn on the screen on the right side of network

As a learning database you add inputs as specific color in specific place

Input:
- x coordinate
- y coordinate

Output:
- Red value
- Green value
- Blue value

For example your learning database can look like this:
(x and values are divided by display Dimension, for example let's say display width is 500 and value x=0.5 would be x=250)

{{{x:0.34, y:0.20}{R:1.00, G:0.00, B:0.00}} {{x:0.83, y:0.18}{R:0.00, G:1.00, B:0.00}}}

Which means 
- Color red at x:0.34 y:0.20
- Color green at x:0.83 y:0.18

How to add inputs?
- Q+mouse_right - White input in x y coordinate
- W+mouse_right - Black input in x y coordinate
- R+mouse_right - Red input in x y coordinate
- G+mouse_right - Green input in x y coordinate
- B+mouse_right - Blue input in x y coordinate

Start and stop network with ENTER key