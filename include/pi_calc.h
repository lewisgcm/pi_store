#include <gmp.h>

#ifndef _PI_CALC_H_
#define _PI_CALC_H_

struct pi_calc_handler {
    mpq_t x;
    mpq_t p;
    mpq_t res;
    mpq_t sixteen;
    unsigned long n;
};
typedef struct pi_calc_handler pi_calc_handler;

pi_calc_handler* pi_calc_init();

char pi_calc_next_char( pi_calc_handler* handler );

void pi_calc_free( pi_calc_handler* handler );

#endif