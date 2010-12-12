/*
 * Soubor:  main.cpp
 * Datum:   29.11.2010 14:21
 * Autor:   
 * Projekt: 
 * Popis:   
 */

#include "pseudorandom.h"

#include <ctime>
#include <fstream>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  RandomGenerator<MT32> rg((unsigned long)time(NULL));
  
  std::ofstream file1, file2, file3;
  //FIXME testovat jestli se povedlo
  file1.open("exponential_3");
  file2.open("exponential_1.5");
  file3.open("exponential_1");

  for (int i = 0; i < 100000; i++) {
    file1 << rg.Exponential(3) << std::endl;
    file2 << rg.Exponential(1.5) << std::endl;
    file3 << rg.Exponential(1) << std::endl;
  }

  file1.close();
  file2.close();
  file3.close();


  //FIXME testovat jestli se povedlo
  file1.open("normal_0_1");
  file2.open("normal_-2_0.5");
  file3.open("normal_0_5");

  for (int i = 0; i < 100000; i++) {
    file1 << rg.Normal(0, 1) << std::endl;
    file2 << rg.Normal(-2, std::sqrt(0.5)) << std::endl;
    file3 << rg.Normal(0, std::sqrt(5)) << std::endl;
  }

  file1.close();
  file2.close();
  file3.close();


  //FIXME testovat jestli se povedlo
  file1.open("weibull_5_1");
  file2.open("weibull_2_0.2");
  file3.open("weibull_1.5_1");

  for (int i = 0; i < 100000; i++) {
    file1 << rg.Weibull(5, 1) << std::endl;
    file2 << rg.Weibull(2, 0.2) << std::endl;
    file3 << rg.Weibull(1.5, 1) << std::endl;
  }

  file1.close();
  file2.close();
  file3.close();

/*  for (int i = 0; i < 10; i++)
    std::cout<< rg.Uniform(1,100) <<std::endl;
  std::cout<<std::endl;*/

/*  for (int i = 0; i < 1000000; i++)
    std::cout<< rg.Random_real1() <<std::endl;*/
  //std::cout<<std::endl;*/

/*  for (int i = 0; i < 100000; i++)
    std::cout<< rg.Weibull(1.5, 1) <<std::endl;*/
  //std::cout<<std::endl;*/

/*  for (int i = 0; i < 100000; i++) {
    std::cout<< rg.Gamma(2, 2)  <<std::endl;
  }*/
  //std::cout<<std::endl;*/

/*  for (int i = 0; i < 100000; i++)
    std::cout<< rg.Normal(-2, std::sqrt(0.5)) <<std::endl;*/

/*  for (int i = 0; i < 100000; i++)
    std::cout<< rg.Poisson(10) <<std::endl;*/

  //std::cout<<std::endl;*/
   
  /*for (int i = 0; i < 100000; i++) {
    int i = rg.Poisson(1.);
    if (i < 50)
    std::cout << i << std::endl;
  }*/

  system("gnuplot skript");
  return 0;
}

/* konec souboru main.c */
