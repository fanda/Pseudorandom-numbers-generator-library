/*
 * Soubor:  main.cpp
 * Datum:   29.11.2010 14:21
 * Autor:   
 * Projekt: 
 * Popis:   
 */

#include "pseudorandom.h"

#include <ctime>

int main(int argc, char *argv[])
{
  RandomGenerator<MT32> rg((unsigned long)time(NULL));
  
  for (int i = 0; i < 10; i++)
    std::cout<< rg.Uniform(1,100) <<std::endl;
  std::cout<<std::endl;

  /*for (int i = 0; i < 1000000; i++)
    std::cout<< rg.Random_real1() <<std::endl;
  //std::cout<<std::endl;*/

  for (int i = 0; i < 10; i++)
    std::cout<< rg.Gamma(2,2) <<std::endl;
  //std::cout<<std::endl;*/

  /*for (int i = 0; i < 1000000; i++) {
    double n = rg.Weibull(5, 1);
    if (n < 25. && n > -25.)
      std::cout<< n <<std::endl;
  }*/
  //std::cout<<std::endl;*/

  /*for (int i = 0; i < 10; i++)
    std::cout<< rg.Poisson(5) <<std::endl;

  for (int i = 0; i < 10; i++)
    std::cout<< rg.Poisson(15) <<std::endl;*/

  /*for (int i = 0; i < 10; i++)
    std::cout<< rg.Poisson(25) <<std::endl;*/

  //std::cout<<std::endl;*/
   
  /*for (int i = 0; i < 100000; i++) {
    int i = rg.Poisson(1.);
    if (i < 50)
    std::cout << i << std::endl;
  }*/
  return 0;
}

/* konec souboru main.c */
