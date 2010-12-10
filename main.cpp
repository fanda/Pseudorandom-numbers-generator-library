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

  /*for (int i = 0; i < 1000; i++)
    std::cout<< rg.Uniform(1,20) <<std::endl;
  //std::cout<<std::endl;*/

  /*for (int i = 0; i < 1000; i++)
    std::cout<< rg.Exponential(5) <<std::endl;
  //std::cout<<std::endl;*/

  /*for (int i = 0; i < 1000; i++)
    std::cout<< rg.Normal(5, 5) <<std::endl;
  //std::cout<<std::endl;*/

  /*for (int i = 0; i < 10; i++)
    std::cout<< rg.Poisson(5) <<std::endl;

  for (int i = 0; i < 10; i++)
    std::cout<< rg.Poisson(15) <<std::endl;*/

  /*for (int i = 0; i < 10; i++)
    std::cout<< rg.Poisson(25) <<std::endl;*/

  //std::cout<<std::endl;*/
   
  for (int i = 0; i < 10; i++) {
    std::cout << rg.Gamma(1, 2.0) << std::endl;
  }
  return 0;
}

/* konec souboru main.c */
