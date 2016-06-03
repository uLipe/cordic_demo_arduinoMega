/*
 *  @brief cordic trignometric class
 */

#ifndef __CORDIC_H
#define __CORDIC_H

#include "frac_math_helper.h"


class cordic_engine {

public:
    /* Constructor / Desctructor */
    cordic_engine(int res);
    ~cordic_engine();

    /* helper functions */
    void set_resolution(int res);
    int get_resolution(void);

    /* math functions */
    frac16 sine(frac12 angle);
    frac16 cosine(frac12 angle);

    /* rotate functions */
    /** TODO: Implement rotation functions */

private:
    frac12 *m_atanTab;
    int resolution;
};


#endif /* __CORDIC_H */

