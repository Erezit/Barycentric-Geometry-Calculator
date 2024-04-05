#include <ginac/ginac.h>
#include <iostream>

class BarycentricCoordinates {
  public:
  BarycentricCoordinates() = default;
  void setCoordinates(GiNaC::ex, GiNaC::ex, GiNaC::ex);
  GiNaC::ex getACoordinate();
  GiNaC::ex getBCoordinate();
  GiNaC::ex getCCoordinate();
  void simplify();
  private:
  GiNaC::ex a_poly = 0;
  GiNaC::ex b_poly = 0;
  GiNaC::ex c_poly = 0;
};
