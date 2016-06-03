
/*
 * @brief cordic class implementation
 */
 
#include <math.h>
#include "cordic.h"


/** static variables */
const frac16 cordic_gain = TO_FRAC_16(0.607252935f);

/*
 * cordic private core routine
 */
static inline void CordicCompute(frac16 *x, frac16 *y, frac12 *z, int iter, const frac12 *tab)
{
    frac16 xtmp = 0, xprev = 0, ytmp = 0, yprev = 0;
    frac12 ztmp = 0;
  
    /*
     *initialize cordic variables:
     */
    xtmp = *x;
    ytmp = *y;
    ztmp = *z;


    signed int  d = ( ztmp < 0? -1 : 1);


    for( int i = 0; i < iter; i++) {
        /*
         * To compute cordic new operation we need
         * to execute for N iterations the following
         * equation sets:
         *
         * xnext = x - y*d*2 ^ -i
         * ynext = y + x*d*2 ^ -i
         * znext = z - d*atantab[i]
         */

        xprev = (xtmp >> i);
        yprev = (ytmp >> i);
        d =( ztmp < 0? -1 : 1);

        if(d > 0) {
            xtmp = xtmp - yprev;
            ytmp = ytmp + xprev;
            ztmp = ztmp -  tab[i];
        }
        else {
            xtmp = xtmp + yprev;
            ytmp = ytmp - xprev;
            ztmp = ztmp +  tab[i];
        }

    }

    /*
     * after end of computation deposit the result:
     */
    *x = xtmp;
    *y = ytmp;
    *z = ztmp;

}



/** Cordic public methods */

/*
 * cordic_engine()
 */
cordic_engine::cordic_engine(int res)
{

    resolution = res;
    m_atanTab = new frac12[resolution];

    /*
     * based on resolution computes the atantab
     */
     frac16 base = TO_FRAC_12(0.785398f);

     for(int i = 0 ; i < res; i++) {
         m_atanTab[i] = base >> i;
     }

}

/*
 * ~cordic_engine
 */
cordic_engine::~cordic_engine()
{
    /* only needs to destroy atan tab memory area */
    delete []m_atanTab;
}

/*
 * set resulotion()
 */
void cordic_engine::set_resolution(int res)
{
    /*
     * WARNING, this function is not thread safe,
     * make sure the cordic is not running in other
     * context before to invoke this method
     */
     resolution = res;
     frac16 base = TO_FRAC_12(0.785398f);

     delete []m_atanTab;
     m_atanTab = new frac12[res];

     /*
      * re-computes the new length lookup
      */
     for(int i = 0 ; i < res; i++) {
         m_atanTab[i] = base >> i;
     }


}


/*
 * get_resolution()
 */
int cordic_engine::get_resolution(void)
{
    return(resolution);
}

/*
 * sine()
 */
frac16 cordic_engine::sine(frac12 angle)
{
    frac16 x, y;
    frac12 z;

    /*
     * intialize cordic for Sine
     */
    z = angle;
    x = cordic_gain;
    y = 0;

 
    /* compute it */
    CordicCompute(&x, &y, &z, resolution, m_atanTab);

    return(y);
}

/*
 * cosine()
 */
frac16 cordic_engine::cosine(frac12 angle)
{
    frac16 x, y;
    frac12 z;

    /*
     * intialize cordic for Sine
     */
    z = angle;
    x = cordic_gain;
    y = 0;

    /* compute it */
    CordicCompute(&x, &y, &z, resolution, m_atanTab);

    return(x);
}
