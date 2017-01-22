#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <stdint.h>
#include <pi_calc.h>

static void pi_calc_f_mod(mpq_t input) {
    mpf_t numerator;
    mpf_init(numerator);
    mpf_set_z(numerator, mpq_numref(input));
    mpf_t denominator;
    mpf_init(denominator);
    mpf_set_z(denominator, mpq_denref(input));
    mpf_t div;
    mpf_init(div);
    mpf_t integer_part;
    mpf_init(integer_part);

    // Integer component
    mpq_t floored;
    mpq_init(floored);

    mpf_div(div, numerator, denominator);
    mpf_floor(integer_part, div);
    mpq_set_f(floored, integer_part);

    // Get fractional part
    mpq_sub(input, input, floored);
}

pi_calc_handler* pi_calc_init() {
    pi_calc_handler* handler = calloc(sizeof(pi_calc_handler), 1);
    mpq_init( handler->x );
    mpq_set_ui( handler->x, 0, 1 );

    mpq_init( handler->p );

    mpq_init( handler->res );

    mpq_init( handler->sixteen );
    mpq_set_ui( handler->sixteen, 16, 1 );
    handler->n = 1;
    return handler;
}

static int16_t pi_calc_next_b16( pi_calc_handler* handler ) {
    mpq_set_ui( handler->p, (120* handler->n-89)*handler->n+16, (((512*handler->n-1024)*handler->n+712)*handler->n-206)*handler->n+21);

    mpq_mul(handler->res, handler->x, handler->sixteen);

    mpq_add(handler->res, handler->res, handler->p);

    pi_calc_f_mod(handler->res);

    mpq_set(handler->x, handler->res);

    mpq_mul(handler->res, handler->res, handler->sixteen);
    handler->n++;
    return (int16_t) mpq_get_d(handler->res);
}

char pi_calc_next_char( pi_calc_handler* handler ) {
    return (pi_calc_next_b16(handler) << 4) | pi_calc_next_b16( handler );
}

void pi_calc_free( pi_calc_handler* handler ) {
    free(handler);
}