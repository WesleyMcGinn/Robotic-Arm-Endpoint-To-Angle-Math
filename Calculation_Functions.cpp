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
  }
}
double beta(double c, double d) {
  if (possible(c, d)) {
    double v1 = (acos((u * u + v * v - c * c - d * d) / (2 * u * v)) - pi) * radiansToDegrees;
    while (round(v1) > 360) { v1 -= 360; }
    while (round(v1) <= 0) { v1 += 360; }
    return (v1 * -1 + 360) + 17;
  }
}

// ---------------------------------------------------------------------------------- //
