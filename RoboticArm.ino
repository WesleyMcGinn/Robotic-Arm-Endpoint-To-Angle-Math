// -------- Wesley's Mathematical Double-Segment Endpoint to Angle Formulas: -------- //

const double radiansToDegrees = 57.29577951;
const double pi = 180 / radiansToDegrees;
const double u = 5; // Distance from base rotation point to secondary rotation point (cm)
const double v = 5; // Distance from secondary rotation point to end of segment (cm)
bool possible(double c, double d) {
  if ((c * c + d * d <= u * u + 2 * u * v + v * v) && (c * c + d * d >= u * u - 2 * u * v + v * v)) { return true; } else { return false; }
}
double alpha(double c, double d) {
  if (possible(c, d)) {
    double v1 = pi * floor((c) / (u + v));
    double v2 = atan(d / c);
    double v4 = ((c * c + d * d + u * u - v * v) * sqrt(c * c + d * d)) / (2 * u * c * c + 2 * u * d * d);
    double v3 = acos(v4);
    double v5 = v1 + v2 + v3;
    while (v5 >= 360) { v5 -= 360; }
    while (v5 < 0) { v5 += 360; }
    return (v5 * radiansToDegrees) + 7;
  } else {
    return;
  }
}
double beta(double c, double d) {
  if (possible(c, d)) {
    double v1 = (acos((u * u + v * v - c * c - d * d) / (2 * u * v)) - pi) * radiansToDegrees;
    while (round(v1) > 360) { v1 -= 360; }
    while (round(v1) <= 0) { v1 += 360; }
    return (v1 * -1 + 360) + 17;
  } else {
    return;
  }
}

// ---------------------------------------------------------------------------------- //


#include <Servo.h>

Servo rotation;
Servo base;
Servo joint1;
Servo joint2;
Servo claw;

void arm(double a, double b) {
  if (possible(a, b)) {
    base.write(alpha(a, b));
    joint1.write(beta(a, b));
    int thirdAngle = -1 * (alpha(a, b) - 7 + beta(a, b) - 17);
    while (thirdAngle < 0) { thirdAngle += 360; }
    while (thirdAngle >= 360) { thirdAngle -= 360; }
    if (thirdAngle <= 180) {
      joint2.write(thirdAngle);
    } else {
      joint2.write(180);
    }
  }
}

double potX() {
  return (20 * analogRead(0) / 1080) - 10;
}

double potY() {
  return (10 * analogRead(1) / 1080);
}

double potC() {
  return (180 * analogRead(2) / 1080);
}

double potR() {
  return (180 * analogRead(3) / 1080);
}

void setup() {
  Serial.begin(9600);
  
  rotation.attach(7, 500, 2500);
  base.attach(3, 500, 2500);
  joint1.attach(2, 500, 2500);
  joint2.attach(4, 500, 2500);
  claw.attach(5, 500, 2500);
}

void loop() {
  delay(50);
  rotation.write(potR());
  claw.write(potC());
  arm(potX(), potY());
}
