/*
 * Soubor:  mtwister.
 * Datum:   19.11.2010
 * Autori:  Pavel Novotny, xnovot28@stud.fit.vutbr.cz
            Ota Pavelek, xpavel08@stud.fit.vutbr.cz
 * Projekt: Knihovna pro generovani pseudonahodnych cisel
 * Popis:   Generator pseudonahodnych cisel Mersenne twister
 */

#include "abstract_uniform_generator.h"


/* Period parameters */
#define N 624
#define M 397

/* Constant vector A */
#define VECTOR 0x9908b0dfUL

/* Most significant w-r bits */
#define UPPER_MASK 0x80000000UL

/* Least significant r bits */
#define LOWER_MASK 0x7fffffffUL

/* Mask for all 32 bits */
#define BITS_32_MASK 0xFFFFFFFFUL

/* Tempering macro definition */
#define TEMPERING_U(x) (x >> 11)
#define TEMPERING_S(x) (x <<  7) & 0x9D2C5680UL;
#define TEMPERING_T(x) (x << 15) & 0xEFC60000UL;
#define TEMPERING_L(x) (x >> 18)

/* Unsigned long converted to double limits for dividing */
#define DOUB_ULONG_MAX    4294967295.
#define DOUB_ULONG_MAX_PP 4294967296.


/* Mersenne Twister generator of uniform deviates numbers */

/** Class uses interface of AbstractUniformGenerator **/
class MT32 : public AbstractUniformGenerator
{
public:
    MT32(unsigned long seed) { seed(s); }
    MT32(unsigned long * init_vector, int size) { seed(init_vector, size); }
    ~MT32() {}

    void seed(int seed);    
    void seed(unsigned long * init_vector, int size);

    /* Generates 32 bit random integer */
    inline unsigned long Random() 
    { 
      if (position >= n) {
        for (int i = 0; i < (n-m); i++)
          state[i] = state[i+m] ^ twiddle(state[i], state[i+1]);
        for (int i = n - m; i < (n-1); i++)
          state[i] = state[i+m-n] ^ twiddle(state[i], state[i+1]);
        state[n-1] = state[m-1] ^ twiddle(state[n-1], state[0]);
        position = 0; // reset position
      }
      // tempering
      unsigned long x  = state[position++];
                    x ^= TEMPERING_U(x);
                    x ^= TEMPERING_S(x);
                    x ^= TEMPERING_T(x);
             return x ^  TEMPERING_L(x);
    }

    /* Random number on [0,1]-real-interval */
    inline double Random_real1() 
    {
      return static_cast<double>(Random()) * (1. / DOUB_ULONG_MAX);
    }

    /* Random number on [0,1)-real-interval */
    inline double Random_real2() 
    {
      return static_cast<double>(Random()) * (1. / DOUB_ULONG_MAX_PP);
    }

    /* Random number on (0,1)-real-interval */
    inline double Random_real3() 
    {
      return static_cast<double>(Random() + 0.5) * (1. / DOUB_ULONG_MAX_PP);
    }

private:   
    static const int n = N, m = M;
    static unsigned long state[N];
    static int position;
    static bool init;

    /* Helps to have nicer code */
    inline unsigned long twiddle(unsigned long u, unsigned long v) 
    {
      return (((u & UPPER_MASK)|(v & LOWER_MASK)) >> 1)^((v & 1UL) * VECTOR);
      /* Look at  (v & 1UL) * VECTOR  which sped this up against
         (v & 1UL) ? VECTOR : 0UL     (by Adam Ierymenko)        */
    }
};

/* initialize static class members */
unsigned long MT32::state[N] = {0x0UL};
int MT32::position = 0;
bool MT32::init = false;


/* Seed method used when instance is being created or 
   when user wants to change it                        */
void MT32::seed(int s)
{
  state[0] = s & BITS_32_MASK;
  for (int i = 1; i < n; i++) {
    state[i] = 1812433253UL * (state[i - 1] ^ (state[i - 1] >> 30)) + i;
    state[i] &= BITS_32_MASK;
  }
  position = n;
}
   
/* Array seed method used when instance is being created or 
   when user wants to change it                             */ 
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
    state[i] &= BITS_32_MASK;
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
    state[i] &= BITS_32_MASK;
    i++;
    if (i >= n) {
      state[0] = state[n - 1];
      i = 1;
    }
  }
  state[0] = UPPER_MASK;
  position = n;      
}
