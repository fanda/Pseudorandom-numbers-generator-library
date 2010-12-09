/*
 * Soubor:  mtwister.cpp
 * Datum:   19.11.2010
 * Autori:  Pavel Novotny, xnovot28@stud.fit.vutbr.cz
            Ota Pavelek, xpavel08@stud.fit.vutbr.cz
 * Projekt: Knihovna pro generovani pseudonahodnych cisel
 * Popis:   Generator pseudonahodnych cisel Mersenne twister
 */

#include "mtwister.h"

unsigned long MT32::state[N] = {0x0UL};
int MT32::position = 0;
bool MT32::init = false;


MT32::MT32(unsigned long s) 
{
  seed(s); 
}
MT32::MT32(unsigned long * init_vector, int size)
{
  seed(init_vector, size); 
}

void MT32::seed(int s)
{
  state[0] = s & 0xFFFFFFFFUL;
  for (int i = 1; i < n; i++) {
    state[i] = 1812433253UL * (state[i - 1] ^ (state[i - 1] >> 30)) + i;
    state[i] &= 0xFFFFFFFFUL;
  }
  position = n;
}
    
    void MT32::seed(unsigned long * init_vector, int size) 
    {
      int i = 1, 
          j = 0, 
          k = n > size ? n : size;
      seed(19650218UL);
      for (; k != 0; k--) {
        state[i] = init_vector[j] + j + (
            state[i] ^ ( ( state[i - 1] ^ (state[i - 1] >> 30) ) * 1664525UL) 
        );
        state[i] &= 0xFFFFFFFFUL;
        i++; 
        if (i >= n) {
          state[0] = state[n - 1];
          i = 1;
        }
        j++;
        if (j >= size) 
          j = 0;
      }
      for (k = n - 1; k != 0; k--) {
        state[i] = (
            state[i] ^ ((state[i - 1] ^ (state[i - 1] >> 30)) * 1566083941UL)
        ) - i;
        state[i] &= 0xFFFFFFFFUL;
        i++;
        if (i >= n) {
          state[0] = state[n - 1];
          i = 1;
        }
      }
      state[0] = UPPER_MASK;
      position = n;      
    }

