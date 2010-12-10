
#include "pseudorandom.h"
//#include "lgamma.h"

double RandomGenerator::Uniform(double min, double max)
{
  return (min + (max - min) * Random_real1());   
}

double RandomGenerator::Exponential(double lambda)
{   
  return (-1./ lambda) * std::log(Random_real1());
}

double RandomGenerator::Normal(double mu, double sigma)
{
  double u, v, x, y, q;
  do {
    u = Random_real1();
    v = 1.7156 * (Random_real1() - 0.5);
    x = u - 0.449871;
    y = std::abs(v) - 0.386595;
    q = (x*x) + y * (0.19600 * y - 0.25472 * x);
  } while (q > 0.27597 && (q > 0.27846 || v*v > -4 * std::log(u)*u*u));
  return mu + sigma * v / u;
}

double RandomGenerator::Weibull(double shape, double scale)
{   
  if (!shape || !scale) 
    return -1.;// NaN; TODO
  double random_number = Random_real3(); // interval (0,1)
  if (!random_number) {
    if (shape > 1)
      return 0;
    /*if (shape < 1) TODO
      return +Inf;*/
  }
  return scale * std::pow(-1.* std::log(1.- random_number), 1./ shape);
}

int RandomGenerator::Poisson(double lambda)
{
  double u, u2, v, v2, p, t, lfac;
  double sqr_lambda, log_lambda, exp_lambda, old_lambda = -1.;
  std::vector<double> log_fact(2, 1024);
  log_fact[1] = -1.;
  int k;
  if (lambda < 5.) { // use PRODUCT OF UNIFORMS method - Knuth
    if (lambda != old_lambda) 
      exp_lambda = Exponential(-lambda);
    k = -1;
    t = 1.;
    do {
      ++k;
      t *= Random_real1();
    } while (t > exp_lambda);
  }
  else { // use RATIO-OF-UNIFORMS method
    if (lambda != old_lambda) {
      sqr_lambda = std::sqrt(lambda);
      log_lambda = std::log(lambda);
    }
    while (true) {
      u = 0.64 * Random_real1();
      v = -0.68 + 1.28 * Random_real1();    
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
      // do we have precomputed log-factorial?
      // do we want to use them??? XXX
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

double RandomGenerator::Gamma(double alpha, double beta) {
  double oalpha, a1, a2;
  oalpha = alpha;
  //Doub a1,a2;
  //Gammadev(Doub aalph, Doub bbet, Ullong i)
  //: Normaldev(0.,1.,i), alph(aalph), oalph(aalph), bet(bbet) {
  //Constructor arguments are  ̨, ˇ , and a random sequence seed.
  if (alpha <= 0.) {
    throw("bad alpha in Gammadev");
  }
  if (alpha < 1.) {
    alpha += 1.;
  }
  a1 = alpha-1./3.;
  a2 = 1./sqrt(9.*a1);

  /*Return a gamma deviate by the method of Marsaglia and Tsang.*/
  double u,v,x;
  do {
    do {
      x = Normal(0, 1);
      v = 1. + a2*x;
    } while (v <= 0.);
    v = v*v*v;
    u = Random_real1();
  } while (u > (1. - 0.331 * x * x * x * x) &&
      log(u) > 0.5 * x * x + a1*(1.-v+log(v))); //Rarely evaluated.
  if (alpha == oalpha) {
    return a1*v/beta;
  }
  else {// Case where  ̨ < 1, per Ripley.
    do {
	    u = Random_real1();
    }while (u == 0.);
    return pow(u,1./oalpha)*a1*v/beta;
  }
}
