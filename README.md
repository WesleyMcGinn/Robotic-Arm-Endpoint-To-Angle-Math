# Robotic Arm Endpoint to Angle Math
This repository includes equations that calculate angles in a robotic arm based on the desired location of the endpoint.  This is helpful for any two-segment robotic part as it can move it easily directly vertical or horizontal.  The math used to get the equations is mainly based on the law of cosines and the pythagorean theorem, but it also involves other small pieces of geometry, algebra, and trigonometry.

# See It Work!
You can see the equations work by going to [this link](https://tinyurl.com/wes-fido-math-2).  Please note that in both the desmos simulator and all of the files in this repository, each letter represents something:
 - c - The x-position of the endpoint
 - d - The y-position of the endpoint
 - ⍺ - (Also known as "alpha") The angle (in degrees) from the horizontal base to the end of segment 1.
 - β - (Also known as "beta") The angle difference (in degrees) between the direction of segment 1 and the direction of segment 2, or the angle that segment 2 makes with the continuation of segment 1.
 - u - The length of segment 1
 - v - The length of segment 2
 - q - The amount of inaccuracy after calculating alpha and beta from the values of u, v, c, and d.
 
 Please also note that all trigonometric calculations are in degrees, not radians or gradians.  This means that half of one rotation is 180, not 3.141592654.
