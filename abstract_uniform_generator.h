/*
 * Soubor:  abstract_uniform_generator.h
 * Datum:   12.12.2010
 * Autori:  Pavel Novotny, xnovot28@stud.fit.vutbr.cz
 *          Ota Pavelek, xpavel08@stud.fit.vutbr.cz
 * Projekt: Knihovna pro generovani pseudonahodnych cisel
 * Popis:   Rozhrani generatoru nahodnych cisel v rovnomernem rozdeleni
 */

/* Rozhrani pro tvorbu generatoru nahodnych cisel v rovnomernem rozdeleni */

/** Pure virtual class AbstractUniformGenerator **/
struct AbstractUniformGenerator
{
  /* Funkce pro generovani celych cisel v intervalu <0, 2^m - 1>, 
     kde m je pocet bitu generovaneho cisla                      */
  virtual unsigned long Random() = 0;

  /* Funkce pro generovani realnych cisel v intervalu <0, 1> */
  virtual double  Random_real1() = 0;

  /* Funkce pro generovani realnych cisel v intervalu <0, 1) */  
  virtual double  Random_real2() = 0;

  /* Funkce pro generovani realnych cisel v intervalu (0, 1) */  
  virtual double  Random_real3() = 0;
};
