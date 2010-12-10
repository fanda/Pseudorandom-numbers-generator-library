/*
 * Soubor:  mtwister.
 * Datum:   19.11.2010
 * Autori:  Pavel Novotny, xnovot28@stud.fit.vutbr.cz
            Ota Pavelek, xpavel08@stud.fit.vutbr.cz
 * Projekt: Knihovna pro generovani pseudonahodnych cisel
 * Popis:   Generator pseudonahodnych cisel Mersenne twister
 */

/* Period parameters */
#define N 624
#define M 397

/* Constant vector A */
#define VECTOR 0x9908b0dfUL

/* Most significant w-r bits */
#define UPPER_MASK 0x80000000UL

/* Least significant r bits */
#define LOWER_MASK 0x7fffffffUL

/* Tempering macro definition */
#define TEMPERING_U(x) (x >> 11)
#define TEMPERING_S(x) (x <<  7) & 0x9D2C5680UL;
#define TEMPERING_T(x) (x << 15) & 0xEFC60000UL;
#define TEMPERING_L(x) (x >> 18)

/* Unsigned long converted to double limits for dividing */
#define DOUB_ULONG_MAX    4294967295.
#define DOUB_ULONG_MAX_PP 4294967296.

class MT32 
{
public:
    MT32(unsigned long seed);
    MT32(unsigned long * init_vector, int size);
    ~MT32() {}

    void seed(int seed);    
    void seed(unsigned long * init_vector, int size);

inline unsigned long 
Random() 
{ // generate 32 bit random int
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

inline double 
Random_real1() /* random number on [0,1]-real-interval */
{
  return static_cast<double>(Random()) * (1. / DOUB_ULONG_MAX);
}

inline double 
Random_real2() /* random number on [0,1)-real-interval */
{
  return static_cast<double>(Random()) * (1. / DOUB_ULONG_MAX_PP);
}

inline double 
Random_real3() /* random number on (0,1)-real-interval */
{
  return static_cast<double>(Random() + 0.5) * (1. / DOUB_ULONG_MAX_PP);
}

private:   
    static const int n = N, m = M;
    static unsigned long state[N];
    static int position;
    static bool init;

inline unsigned long 
twiddle(unsigned long u, unsigned long v) 
{
   return (((u & UPPER_MASK) | (v & LOWER_MASK)) >> 1) ^ ((v & 1UL) * VECTOR);
   /* Look at  (v & 1UL) * VECTOR  which sped this up against
      (v & 1UL) ? VECTOR : 0UL     (by Adam Ierymenko)        */
}

};
