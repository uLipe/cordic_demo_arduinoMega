

#include "cordic.h"

namespace ArduinoCordic {

static const int16_t cordic_max_range = (int16_t)((M_PI_2) * (float)(1 << 14));
static const int16_t cordic_gain = (int16_t)(0.607252935f * (float)(1 << 15));
static const int16_t atan_base = (int16_t)(0.785398f * (float)(1 << 14));
static const int16_t atan_lookup[16] = {
    (atan_base >> 0),
    (atan_base >> 1),
    (atan_base >> 2),
    (atan_base >> 3),
    (atan_base >> 4),
    (atan_base >> 5),
    (atan_base >> 6),
    (atan_base >> 7),
    (atan_base >> 8),
    (atan_base >> 9),
    (atan_base >> 10),
    (atan_base >> 11),
    (atan_base >> 12),
    (atan_base >> 13),
    (atan_base >> 14),
    (atan_base >> 15),
};

static inline void CordicKernelCompute(int16_t *x, int16_t *y, int16_t *z)
{
    int16_t xtmp = 0, xprev = 0, ytmp = 0, yprev = 0;
    int16_t ztmp = 0;
  
    xtmp = *x;
    ytmp = *y;
    ztmp = *z;

    for( int i = 0; i < 16; i+= 4) {
        /*
         * To compute cordic new operation we need
         * to execute for N iterations the following
         * equation sets:
         *
         * xnext = x - y*d*2 ^ -i
         * ynext = y + x*d*2 ^ -i
         * znext = z - d*atantab[i]
         */

        /* unroll the loop by 4 to speedup the calculations a bit */
        xprev = (xtmp >> i);
        yprev = (ytmp >> i);

        if(ztmp > 0) {
            xtmp = xtmp - yprev;
            ytmp = ytmp + xprev;
            ztmp = ztmp -  atan_lookup[i];
        } else {
            xtmp = xtmp + yprev;
            ytmp = ytmp - xprev;
            ztmp = ztmp +  atan_lookup[i];
        }

        xprev = (xtmp >> (i + 1));
        yprev = (ytmp >> (i + 1));

        if(ztmp > 0) {
            xtmp = xtmp - yprev;
            ytmp = ytmp + xprev;
            ztmp = ztmp -  atan_lookup[i + 1];
        } else {
            xtmp = xtmp + yprev;
            ytmp = ytmp - xprev;
            ztmp = ztmp +  atan_lookup[i + 1];
        }

        xprev = (xtmp >> (i + 2));
        yprev = (ytmp >> (i + 2));

        if(ztmp > 0) {
            xtmp = xtmp - yprev;
            ytmp = ytmp + xprev;
            ztmp = ztmp -  atan_lookup[i + 2];
        } else {
            xtmp = xtmp + yprev;
            ytmp = ytmp - xprev;
            ztmp = ztmp +  atan_lookup[i + 2];
        }

        xprev = (xtmp >> (i + 3));
        yprev = (ytmp >> (i + 3));

        if(ztmp > 0) {
            xtmp = xtmp - yprev;
            ytmp = ytmp + xprev;
            ztmp = ztmp -  atan_lookup[i + 3];
        } else {
            xtmp = xtmp + yprev;
            ytmp = ytmp - xprev;
            ztmp = ztmp +  atan_lookup[i + 3];
        }

    }

    *x = xtmp;
    *y = ytmp;
    *z = ztmp;
}

int16_t GetSine(int16_t angle) {

    if(angle > cordic_max_range || angle < -cordic_max_range) {
        return 0;
    }

    int16_t z = angle;
    int16_t x = cordic_gain;
    int16_t y = 0;

    CordicKernelCompute(&x, &y, &z);
    return (y);
}

int16_t GetCosine(int16_t angle) {

    if(angle > cordic_max_range || angle < -cordic_max_range) {
        return 0;
    }

    int16_t z = angle;
    int16_t x = cordic_gain;
    int16_t y = 0;

    CordicKernelCompute(&x, &y, &z);
    return (x);
}

int16_t GetMaxRange() {
    return cordic_max_range;
}

}
