#include "BarycentricCoordinates.h"

void BarycentricCoordinates::setCoordinates(GiNaC::ex poly1, GiNaC::ex poly2, GiNaC::ex poly3) {
  a_poly = poly1;
  b_poly = poly2;
  c_poly = poly3;
}

GiNaC::ex BarycentricCoordinates::getACoordinate() {
  return a_poly;
}

GiNaC::ex BarycentricCoordinates::getBCoordinate() {
  return b_poly;
}

GiNaC::ex BarycentricCoordinates::getCCoordinate() {
  return c_poly;
}
