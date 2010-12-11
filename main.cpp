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
  
/*  for (int i = 0; i < 10; i++)
    std::cout<< rg.Uniform(1,100) <<std::endl;
  std::cout<<std::endl;*/

/*  for (int i = 0; i < 1000000; i++)
    std::cout<< rg.Random_real1() <<std::endl;*/
  //std::cout<<std::endl;*/

  for (int i = 0; i < 1000000; i++)
    std::cout<< rg.Weibull(1, 5) <<std::endl;
  //std::cout<<std::endl;*/

/*  for (int i = 0; i < 1000000; i++) {
    std::cout<< rg.Uniform(1, 20)  <<std::endl;
  }*/
  //std::cout<<std::endl;*/

/*  for (int i = 0; i < 1000000; i++) {
    std::cout<< rg.Exponential(0.5) <<std::endl;
  }*/

/*  for (int i = 0; i < 1000000; i++)
    std::cout<< rg.Normal(0, 5.0) <<std::endl;*/

/*  for (int i = 0; i < 1000000; i++)
    std::cout<< rg.Poisson(10) <<std::endl;*/

  //std::cout<<std::endl;*/
   
  /*for (int i = 0; i < 100000; i++) {
    int i = rg.Poisson(1.);
    if (i < 50)
    std::cout << i << std::endl;
  }*/
  return 0;
}

/* konec souboru main.c */
