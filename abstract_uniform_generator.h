/*
This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

/*
 * File:    abstract_uniform_generator.h
 * Date:    12.12.2010
 * Authors: Pavel Novotny, fandisek@gmail.com
 *          Ota Pavelek, xpavel08@stud.fit.vutbr.cz
 * Project: Pseudorandom number generator library
 * About:   Interface for uniform pseudorandom number generator
 */

#ifndef ABSTRACTUNIFORMGENERATOR
#define ABSTRACTUNIFORMGENERATOR

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

#endif // ABSTRACTUNIFORMGENERATOR
