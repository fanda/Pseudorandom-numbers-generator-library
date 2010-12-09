
#include <iostream>
#include <cmath>
#include <vector>

#include "mtwister.h"

class RandomGenerator : public MT32
{
public:
  RandomGenerator(int seed) : MT32(seed) {}
  ~RandomGenerator() {}

  double Uniform(double min, double max);
  double Exponential(double lambda);
  double Normal(double mi, double sigma);
  double Weibull(double shape, double scale);
  int    Poisson(double lambda);

private:

};


