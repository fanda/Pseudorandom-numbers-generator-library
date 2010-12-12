/*
 * Soubor:  pseudorandom.h
 * Datum:   12.12.2010
 * Autori:  Pavel Novotny, xnovot28@stud.fit.vutbr.cz
 *          Ota Pavelek, xpavel08@stud.fit.vutbr.cz
 * Projekt: Knihovna pro generovani pseudonahodnych cisel
 * Popis:   Sablona tridy RandomGenerator prijmajici jako parametr generator
 *          nahodnych cisel v rovnomernem rozdeleni
 */

#include <iostream>
#include <cmath>
#include <vector>

#include "mtwister.h"


/** 
    Template class Random Generator 
    with parameter inherited from AbstractUniformGenerator (default MT32)     
**/
template <class UniformGenerator = MT32>
class RandomGenerator : public UniformGenerator
{
public:
  /* Constructors & destructors */
  RandomGenerator()         : UniformGenerator(),     old_lambda(-1.) {}  
  RandomGenerator(int seed) : UniformGenerator(seed), old_lambda(-1.) {}
  ~RandomGenerator() {}

  /* Derivation supported by library */
  double Uniform(double min, double max);
  double Exponential(double lambda);
  double Normal(double mi, double sigma);
  double Weibull(double shape, double scale);
  int    Poisson(double lambda);
  double Gamma(double alpha, double beta);

private:
  /* Memory for sped up Poisson distribution */
  double sqr_lambda, log_lambda, exp_lambda, old_lambda;
  std::vector<double> log_fact;

};


/** 
    Uniform derivation  <->  Uniform(a,b)
**/
/* Parameters: Minimal and maximal boundary od random number */
template <class UniformGenerator>
double 
RandomGenerator<UniformGenerator>::Uniform(double min, double max)
{
  if (min >= max) {
    std::cerr<< "Bad parameter in Uniform distribution" <<std::endl;
    throw;
  }
  return (min + (max - min) * this->Random_real1());   
}


/** 
    Exponential derivation  <->  Exp(lambda)
**/
/* Parameter: Rate lambda */
template <class UniformGenerator>
double 
RandomGenerator<UniformGenerator>::Exponential(double lambda)
{   
  if (lambda <= 0) {
    std::cerr<< "Bad parameter in Exponential distribution" <<std::endl;
    throw;
  }
  return (-1./ lambda) * std::log(this->Random_real3());
}


/** 
    Normal derivation  <->  Normal(mu, sigma^2)
**/
/* Parameters: Mean mu & squared scale sigma */
template <class UniformGenerator>
double 
RandomGenerator<UniformGenerator>::Normal(double mu, double sigma)
{
  if (sigma <= 0) {
    std::cerr<< "Bad parameter in Normal distribution" <<std::endl;
    throw;
  }
  double u, v, x, y, q;
  do {
    u = this->Random_real3();
    v = 1.7156 * (this->Random_real3() - 0.5); // scale v to (-r,r), r=(2/e)^0.5
    x = u - 0.449871;
    y = std::abs(v) + 0.386595;
    q = (x*x) + y * (0.19600 * y - 0.25472 * x);
  } while (q > 0.27597 && (q > 0.27846 || v*v > -4. * std::log(u)*u*u));
  return mu + sigma * v / u;
}


/** 
    Weibull derivation  <->  Weibull(k, lambda)
**/
/* Parameters: Shape k and scale lambda */
template <class UniformGenerator>
double 
RandomGenerator<UniformGenerator>::Weibull(double shape, double scale)
{   
  if (shape <= 0 || scale <= 0) {
    std::cerr<< "Bad parameter in Weibull distribution" <<std::endl;    
    throw;
  }
  return 1./scale * std::pow(-std::log(this->Random_real3()), 1./ shape);
}


/** 
    Poisson derivation  <->  Poisson(lambda)
**/
/* Parameter: Expected number of occurrences lambda */
template <class UniformGenerator>
int 
RandomGenerator<UniformGenerator>::Poisson(double lambda)
{
  if (lambda <= 0) {
    std::cerr<< "Bad parameter in Poisson distribution" <<std::endl;
    throw;
  }
  double u, u2, v, v2, p, t, lfac;
  if (old_lambda < 0)
    log_fact.assign(1024, -1.); // precomputed log-factorial
  int k;
  if (lambda < .5) { // use PRODUCT OF UNIFORMS method - Knuth
    if (lambda != old_lambda) 
      exp_lambda = std::exp(-lambda);
    k = -1;
    t = 1.;
    do {
      ++k;
      t *= this->Random_real1();
    } while (t > exp_lambda);
  }
  else { // use RATIO-OF-UNIFORMS method
    if (lambda != old_lambda) {
      sqr_lambda = std::sqrt(lambda);
      log_lambda = std::log(lambda);
    }
    while (true) {
      u = 0.64 * this->Random_real1();
      v = -0.68 + 1.28 * this->Random_real1();    
      if (lambda > 13.5) { // outer squeeze for fast rejection
        v2 = v * v;
        if (v >= 0.) {
          if (v2 > 6.5 * u * (0.64 - u) * (u + 0.2))
            continue;
        }
        else {
          if (v2 > 9.6 * u * (0.66 - u) * (u + 0.07))
            continue;
        }
      }
      k = int(std::floor(sqr_lambda * (v / u) + lambda + 0.5));
      if (k < 0) 
        continue;
      u2 = u * u;
      if (lambda > 13.5) {
        if (v >= 0.) {
          if (v2 < 15.2 * u2 * (0.61 - u) * (0.8 - u))
            break;
        }
        else {
          if (v2 < 6.76 * u2 * (0.62 - u) * (1.4 - u))
            break;          
        }
      }
      // using precomputed log-factorials or computing them
      if (k < 1024) {
        if (log_fact[k] < 0.)
          log_fact[k] = lgamma(k + 1.);
        lfac = log_fact[k];
      }
      else 
        lfac = lgamma(k + 1.);
      p = sqr_lambda * std::exp(-lambda + k * log_lambda - lfac);
      if (u2 < p)
        break;
    } // end of while
  }
  old_lambda = lambda;
  return k;
}


/** 
    Gamma derivation  <->  Gamma(a, b)
**/
/* Parameters: Shape alpha and scale beta */
template <class UniformGenerator>
double 
RandomGenerator<UniformGenerator>::Gamma(double alpha, double beta) 
{
  double oalpha, a1, a2;
  oalpha = alpha;
  if (alpha <= 0 || beta <= 0) {
    std::cerr<< "Bad parameter in Gamma distribution" <<std::endl;
    throw;
  }
  if (alpha < 1.) {
    alpha += 1.;
  }
  a1 = alpha-1./3.;
  a2 = 1./sqrt(9.*a1);
  /* Return a gamma deviate by the method of Marsaglia and Tsang. */
  double u,v,x;
  do {
    do {
      x = Normal(0, 1);
      v = 1. + a2*x;
    } while (v <= 0.);
    v = v*v*v;
    u = this->Random_real1();
  } while (u > (1. - 0.331 * x * x * x * x) &&
           log(u) > 0.5 * x * x + a1*(1.-v+log(v))); // Rarely evaluated.
  if (alpha == oalpha) {
    return a1*v/beta;
  }
  else {// Case where alpha < 1, per Ripley.
    return pow(this->Random_real3(), 1./ oalpha) * a1 * v / beta;    
  }
}
