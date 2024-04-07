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

void BarycentricCoordinates::simplify() {
  GiNaC::ex denum_a = a_poly.denom();
  GiNaC::ex denum_b = b_poly.denom();
  GiNaC::ex denum_c = c_poly.denom();
  GiNaC::ex denum_gcd =  gcd(denum_a , denum_b);
  denum_gcd = gcd(denum_gcd , denum_b);
  if(denum_gcd.normal() == 0) {
    denum_gcd = 1;
  }
  GiNaC::ex numer_a = a_poly.numer();
  GiNaC::ex numer_b = b_poly.numer();
  GiNaC::ex numer_c = c_poly.numer();
  GiNaC::ex numer_gcd = gcd(numer_a , numer_b);
  numer_gcd = gcd(numer_gcd , numer_b);
 if(numer_gcd.normal() == 0) {
   numer_gcd = 1;
 }
  BarycentricCoordinates::setCoordinates((a_poly * denum_gcd / numer_gcd).normal(), (b_poly * denum_gcd / numer_gcd).normal(), (c_poly * denum_gcd / numer_gcd).normal());
}

void BarycentricCoordinates::print() {
  std::cout << a_poly << " " << b_poly << " "  << c_poly << std::endl;
}
