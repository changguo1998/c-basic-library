#ifndef _CBL_FLOAT_MATRIX_H_
#define _CBL_FLOAT_MATRIX_H_

#include "CBL_Basic.h"

void _FLOAT_MATRIX_level0_get_row(Float* v, Float* X, Int m, Int n);

void _FLOAT_MATRIX_level0_get_column(Float* v, Float* X, Int m, Int n);

void _FLOAT_MATRIX_level0_transpose(Float* X, Int m, Int n);

void _FLOAT_MATRIX_level0_diag(Float* v, Float* X, Int m, Int n);

void _FLOAT_MATRIX_level0_diagm(Float* X, Float* v, Int m, Int n);

void _FLOAT_MATRIX_level0_product(Float Z, Float* X, Float* Y, Int p, Int q, Int r);

void _FLOAT_MATRIX_level0_inverse(Float* Y, Float* X, Int m, Int n);

/**
 * @brief FloatMatrix
 * @param nrow Int
 * @param ncol Int
 * @param data Float*
 */
struct FloatMatrix {
    Int    nrow; /**< number of row */
    Int    ncol;
    Float* data;
};

#endif // _CBL_FLOAT_MATRIX_H_
