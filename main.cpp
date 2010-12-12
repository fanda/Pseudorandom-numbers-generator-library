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

#define RANDAMOUNT 100000

using std::string;
using std::endl;

void printHelp() {
  std::cout << "napoveda:" << endl;
  std::cout << "seznam parametru:" << endl;
  std::cout << "  -h nebo --help tiskne tuto napovedu" << endl;
  std::cout << "  uniform, exponential, normal, weibull, poisson, gamma otestuji pruslusne rozlozeni" << endl;
  std::cout << "  all otestuje vsechna rozlozeni" << endl;
  std::cout << "priklad pouziti:" << endl;
  std::cout << "  ./test normal uniform exponential\t otestuje normalni, rovnomerne a exponencialni rozlozeni" << endl;
  std::cout << "kazde rozlozeni je testovano se tremi ruznymi parametry a 100000 vygenerovanymi hodnotami" << endl;
}

int main(int argc, char *argv[])
{
  //analyza parametru prikazoveho radku
  if (argc == 1) {
    printHelp();
    exit(0);
  }


  bool help = false;;
  bool uniform = false;
  bool exponential = false;
  bool normal = false;
  bool weibull = false;
  bool poisson = false;
  bool gamma = false;

  //priznak, jestli je zadano vykresleni aspon 1 rozlozeni
  bool atLeastOne = false;

  for (int i = 0; i < argc; i++) {
    string param(argv[i]);
    if (param.compare("-h") == 0 || param.compare("--help") == 0) {
      help = true;
    }
    if (param.compare("uniform") == 0) {
      uniform = true;
      atLeastOne = true;
    }
    if (param.compare("exponential") == 0) {
      exponential = true;
      atLeastOne = true;
    }
    if (param.compare("normal") == 0) {
      normal = true;
      atLeastOne = true;
    }
    if (param.compare("weibull") == 0) {
      weibull = true;
      atLeastOne = true;
    }
    if (param.compare("poisson") == 0) {
      poisson = true;
      atLeastOne = true;
    }
    if (param.compare("gamma") == 0) {
      gamma = true;
      atLeastOne = true;
    }
    if (param.compare("all") == 0) {
      atLeastOne = true;
      uniform = true;
      exponential = true;
      normal = true;
      weibull = true;
      poisson = true;
      gamma = true;
    }
  }

  if (help == true) {
    printHelp();
    exit(0);
  }

  if (atLeastOne == false) {
    std::cerr << "chybne zadane parametry, pouzijte -h nebo --help pro zobrazeni napovedy" << endl;
    exit(1);
  }

  RandomGenerator<MT32> rg((unsigned long)time(NULL));
  
  std::ofstream file;

  //zpracovani exponencialniho rozlozeni
  if (exponential == true) {
    file.open("tests/generated/exponential_3");
    if (file.good()) {
      for (int i = 0; i < RANDAMOUNT; i++) {
        file << rg.Exponential(3) << endl;
      }
    }
    else {
      std::cerr << "nepodarilo se otevrit soubor tests/generated/exponential_3" << endl;
    }
    file.close();

    file.open("tests/generated/exponential_1.5");
    if (file.good()) {
      for (int i = 0; i < RANDAMOUNT; i++) {
        file << rg.Exponential(1.5) << endl;
      }
    }
    else {
      std::cerr << "nepodarilo se otevrit soubor tests/generated/exponential_1.5" << endl;
    }
    file.close();

    file.open("tests/generated/exponential_1");
    if (file.good()) {
      for (int i = 0; i < RANDAMOUNT; i++) {
        file << rg.Exponential(1) << endl;
      }
    }
    else {
      std::cerr << "nepodarilo se otevrit soubor tests/generated/exponential_1" << endl;
    }
    file.close();

    system("gnuplot gnuplot_scripts/exponential");
  }


  //zpracovani normalniho rozlozeni
  if (normal == true) {
    file.open("tests/generated/normal_0_1");
    if (file.good()) {
      for (int i = 0; i < RANDAMOUNT; i++) {
        file << rg.Normal(0, 1) << endl;
      }
    }
    else {
      std::cerr << "nepodarilo se otevrit soubor tests/generated/normal_0_1" << endl;
    }
    file.close();

    file.open("tests/generated/normal_-2_0.5");
    if (file.good()) {
      for (int i = 0; i < RANDAMOUNT; i++) {
        file << rg.Normal(-2, std::sqrt(0.5)) << endl;
      }
    }
    else {
      std::cerr << "nepodarilo se otevrit soubor tests/generated/normal_-2_0.5" << endl;
    }
    file.close();

    file.open("tests/generated/normal_0_5");
    if (file.good()) {
      for (int i = 0; i < RANDAMOUNT; i++) {
        file << rg.Normal(0, std::sqrt(5)) << endl;
      }
    }
    else {
      std::cerr << "nepodarilo se otevrit soubor tests/generated/normal_0_5" << endl;
    }
    file.close();

    system("gnuplot gnuplot_scripts/normal");
  }


  //zpracovani Weibullova rozlozeni
  if (weibull == true) {
    file.open("tests/generated/weibull_5_1");
    if (file.good()) {
      for (int i = 0; i < RANDAMOUNT; i++) {
        file << rg.Weibull(5, 1) << endl;
      }
    }
    else {
      std::cerr << "nepodarilo se otevrit soubor tests/generated/weibull_5_1" << endl;
    }
    file.close();

    file.open("tests/generated/weibull_2_3");
    if (file.good()) {
      for (int i = 0; i < RANDAMOUNT; i++) {
        file << rg.Weibull(2, 3) << endl;
      }
    }
    else {
      std::cerr << "nepodarilo se otevrit soubor tests/generated/weibull_2_3" << endl;
    }
    file.close();

    file.open("tests/generated/weibull_1.5_0.2");
    if (file.good()) {
      for (int i = 0; i < RANDAMOUNT; i++) {
        file << rg.Weibull(1.5, 0.2) << endl;
      }
    }
    else {
      std::cerr << "nepodarilo se otevrit soubor tests/generated/weibull_1.5_0.2" << endl;
    }
    file.close();

    system("gnuplot gnuplot_scripts/weibull");
  }


  //zpracovani Poissonova rozlozeni
  if (poisson == true) {
    file.open("tests/generated/poisson_1");
    if (file.good()) {
      for (int i = 0; i < RANDAMOUNT; i++) {
        file << rg.Poisson(1) << endl;
      }
    }
    else {
      std::cerr << "nepodarilo se otevrit soubor tests/generated/poisson_1" << endl;
    }
    file.close();

    file.open("tests/generated/poisson_4");
    if (file.good()) {
      for (int i = 0; i < RANDAMOUNT; i++) {
        file << rg.Poisson(4) << endl;
      }
    }
    else {
      std::cerr << "nepodarilo se otevrit soubor tests/generated/poisson_4" << endl;
    }
    file.close();

    file.open("tests/generated/poisson_10");
    if (file.good()) {
      for (int i = 0; i < RANDAMOUNT; i++) {
        file << rg.Poisson(10) << endl;
      }
    }
    else {
      std::cerr << "nepodarilo se otevrit soubor tests/generated/poisson_10" << endl;
    }
    file.close();

    system("gnuplot gnuplot_scripts/poisson");
  }

  //zpracovani gama rozlozeni
  if (gamma == true) {
    file.open("tests/generated/gamma_0.5_1");
    if (file.good()) {
      for (int i = 0; i < RANDAMOUNT; i++) {
        file << rg.Gamma(0.5, 1) << endl;
      }
    }
    else {
      std::cerr << "nepodarilo se otevrit soubor tests/generated/gamma_0.5_1" << endl;
    }
    file.close();

    file.open("tests/generated/gamma_6_2");
    if (file.good()) {
      for (int i = 0; i < RANDAMOUNT; i++) {
        file << rg.Gamma(6, 2) << endl;
      }
    }
    else {
      std::cerr << "nepodarilo se otevrit soubor tests/generated/gamma_6_2" << endl;
    }
    file.close();

    file.open("tests/generated/gamma_2_0.8");
    if (file.good()) {
      for (int i = 0; i < RANDAMOUNT; i++) {
        file << rg.Gamma(2, 0.8) << endl;
      }
    }
    else {
      std::cerr << "nepodarilo se otevrit soubor tests/generated/gamma_2_0.8" << endl;
    }
    file.close();

    system("gnuplot gnuplot_scripts/gamma");
  }


  //zpracovani rovnomerneho rozlozeni
  if (uniform == true) {
    file.open("tests/generated/uniform_10_20");
    if (file.good()) {
      for (int i = 0; i < RANDAMOUNT; i++) {
        file << rg.Uniform(10, 20) << endl;
      }
    }
    else {
      std::cerr << "nepodarilo se otevrit soubor tests/generated/uniform_10_20" << endl;
    }
    file.close();

    file.open("tests/generated/uniform_-11.5_0");
    if (file.good()) {
      for (int i = 0; i < RANDAMOUNT; i++) {
        file << rg.Uniform(-11.5, 0) << endl;
      }
    }
    else {
      std::cerr << "nepodarilo se otevrit soubor tests/generated/uniform_-11.5_0" << endl;
    }
    file.close();

    file.open("tests/generated/uniform_-5_3.7");
    if (file.good()) {
      for (int i = 0; i < RANDAMOUNT; i++) {
        file << rg.Uniform(-5, 3.7) << endl;
      }
    }
    else {
      std::cerr << "nepodarilo se otevrit soubor tests/generated/uniform-5_3.7" << endl;
    }
    file.close();

    system("gnuplot gnuplot_scripts/uniform");
  }
  return 0;
}

/* konec souboru main.c */
