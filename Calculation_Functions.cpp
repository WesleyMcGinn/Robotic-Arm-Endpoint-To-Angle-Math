// -------------- Wesley's Mathematical Endpoint to Angle Formulas: -------------- //

const double u = 5; // Distance from base rotation point to secondary rotation point
const double v = 5; // Distance from secondary rotation point to end of segment

const double radiansToDegrees = 57.29577951;
const double pi = 180 / radiansToDegrees;

bool possible(double c, double d) {
  if ((c * c + d * d <= u * u + 2 * u * v + v * v) && (c * c + d * d >= u * u - 2 * u * v + v * v)) { return true; } else { return false; }
}
double alpha(double c, double d) {
  if (possible(c, d)) {
    double angle = pi * floor((c) / (u + v)) + atan(d / c) + acos(((c * c + d * d + u * u - v * v) * sqrt(c * c + d * d)) / (2 * u * c * c + 2 * u * d * d));
    while (round(angle) >= 360.0) { angle -= 360.0; }
    while (round(angle) < 0.0) { angle += 360.0; }
    return (angle * radiansToDegrees);
  }
}
double beta(double c, double d) {
  if (possible(c, d)) {
    double angle = (acos((u * u + v * v - c * c - d * d) / (2 * u * v)) - pi) * radiansToDegrees;
    while (round(angle) > 360) { angle -= 360; }
    while (round(angle) <= 0) { angle += 360; }
    return (angle * -1 + 360);
  }
}

// ------------------------------------------------------------------------------- //
