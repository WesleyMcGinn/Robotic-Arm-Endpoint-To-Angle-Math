
// -------------- Wesley's Mathematical Endpoint to Angle Formulas: -------------- //

const double u = 5; // Distance from base rotation point to secondary rotation point
const double v = 5; // Distance from secondary rotation point to end of segment

const double radiansToDegrees = 57.29577951;
const double pi = 3.141592654;

bool possible(double c, double d) {
  if ((c * c + d * d <= u * u + 2 * u * v + v * v) && (c * c + d * d >= u * u - 2 * u * v + v * v)) { return true; } else { return false; }
}

double alpha(double c, double d) {
  if (possible(c, d)) {
    double angle = (pi * floor((c) / (u + v)) + atan(d / c) + acos(((c * c + d * d + u * u - v * v) * sqrt(c * c + d * d)) / (2 * u * c * c + 2 * u * d * d))) * radiansToDegrees;
    while (round(angle) >= 360) { angle -= 360; }
    while (round(angle) < 0)    { angle += 360; }
    return angle;
  }
}

double beta(double c, double d) {
  if (possible(c, d)) {
    double angle = (acos((u * u + v * v - c * c - d * d) / (2 * u * v)) - pi) * radiansToDegrees;
    while (round(angle) > 360) { angle -= 360; }
    while (round(angle) <= 0)  { angle += 360; }
    return (angle * -1 + 360);
  }
}

// ------------------------------------------------------------------------------- //


#include <Servo.h>

Servo rotation;
Servo base;
Servo joint1;
Servo joint2;
Servo claw;

void arm(double a, double b) {
  if (possible(a, b)) {
    base.write(alpha(a, b) + 7);
    joint1.write(beta(a, b) + 17);
  }
}

double X = 0;
double Y = 5;
int J = 50;

int R = 90;
int C = 100;

int zero_X = 0;
int zero_Y = 0;

#define joystick1_x (analogRead(2) - zero_X)
#define joystick1_y (analogRead(1) - zero_Y)
#define joystick1_b (digitalRead(8))

#define joystick2_x (analogRead(4) - zero_X)
#define joystick2_y (analogRead(3) - zero_Y)
#define joystick2_b (digitalRead(9))

void setup() {
  delay(3000);
  zero_X = analogRead(2);
  zero_Y = analogRead(1);
  rotation.attach(7, 500, 2500);
  base.attach(3, 500, 2500);
  joint1.attach(2, 500, 2500);
  joint2.attach(4, 500, 2500);
  claw.attach(5, 500, 2500);
  pinMode(8, INPUT);
  pinMode(9, INPUT);
}

void loop() {
  rotation.write(R);
  claw.write(C);
  joint2.write(J);
  arm(X, Y);
  delay(100);
    if (joystick1_x >= 10 || joystick1_x <= -10) {
      if (possible(X, Y)) { X += 0.5 * (joystick1_x / 500); } // Change X-Position of joint 2  Joystick 1 -
  } if (joystick1_y >= 10 || joystick1_y <= -10) {
      if (possible(X, Y)) { Y += 0.5 * (joystick1_y / 500); } // Change Y-Position of joint 2  Joystick 1 |
  } if (joystick2_x >= 10 || joystick2_x <= -10) {
      R += 2 * (joystick2_x / 500);                           // Rotate at base                Joystick 2 -
  } if (joystick2_y >= 10 || joystick2_y <= -10) {
      J += 2 * (joystick2_y / 500);                           // Rotate claw up / down         Joystick 2 |
  } if (joystick1_b == HIGH) {
      C -= 7;                                                 // Close Claw                    Joystick 1 Press
  } if (joystick2_b == HIGH) {
      C += 7;                                                 // Open Clawv                    Joystick 2 Press
  }
}
