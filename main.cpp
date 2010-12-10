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
  RandomGenerator rg((unsigned long)time(NULL));
  
/*  for (int i = 0; i < 10; i++)
    std::cout<< rg.Random() <<std::endl;
  std::cout<<std::endl;*/

  for (int i = 0; i < 1000000; i++)
    std::cout<< rg.Random_real1() <<std::endl;
  //std::cout<<std::endl;*/

  /*for (int i = 0; i < 1000000; i++)
    std::cout<< rg.Weibull(3,200) <<std::endl;
  //std::cout<<std::endl;*/

  /*for (int i = 0; i < 1000000; i++) {
    double n = rg.Normal(1, 5);
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
   
  /*for (int i = 0; i < 1000; i++) {
    std::cout << rg.Normal(0,1) << std::endl;
  }*/
  return 0;
}

/* konec souboru main.c */
