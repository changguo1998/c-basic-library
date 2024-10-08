#ifndef _CBL_TYPE_ARRAY_H_
#define _CBL_TYPE_ARRAY_H_

#include "CBL_Basic.h"

#define _DEFINE_INT_VECTOR_LEN_STRUCT(n) struct IntVector##n{\
    Int data[n];\
    Int (*get)(struct IntVector##n* this, Int i);\
    void (*set)(struct IntVector##n* this, Int i, Int v);\
    void (*fill)(struct IntVector##n* this, Int v);\
    Int (*sum)(struct IntVector##n* this);\
    void (*cumsum)(struct IntVector##n* this);\
    Int (*prod)(struct IntVector##n* this);\
    void (*cumprod)(struct IntVector##n* this);\
    Int (*dot)(struct IntVector##n this, struct IntVector##n v);\
};

#define _FUNCTION_INT_VECTOR_LEN_GET(n) Int _IntVector##n##_get(const struct IntVector##n* this, Int i){\
    if(i>=n) return 0;\
    return this->data[i];\
}

#define _FUNCTION_INT_VECTOR_LEN_SET(n) void _IntVector##n##_set(struct IntVector##n* this, Int i, Int v){\
    if(i>=n) return; this->data[i]=v;\
}

#define _FUNCTION_INT_VECTOR_LEN_FILL(n) void _IntVector##n##_fill(struct IntVector##n* this, Int v){\
    for(Int i=0; i<n; i++) this->data[i] = v;\
}

#define _FUNCTION_INT_VECTOR_LEN_SUM(n) Int _IntVector##n##_sum(const struct IntVector##n* this){\
    Int s=0, i=0;\
    for(; i<n; i++) s += this->data[i];\
    return s;\
}

#define _FUNCTION_INT_VECTOR_LEN_PROD(n) Int _IntVector##n##_prod(const struct IntVector##n* this){\
    Int p=1, i=0;\
    for(; i<n; i++) p *= this->data[i];\
    return p;\
}

#define _FUNCTION_INT_VECTOR_LEN_CUMSUM(n) void _IntVector##n##_cumsum(struct IntVector##n* this){\
    Int s=0, i=0;\
    for(; i<n; i++){\
        s += this->data[i];\
        this->data[i] = s;\
    }\
}

#define _FUNCTION_INT_VECTOR_LEN_CUMPROD(n) void _IntVector##n##_cumprod(struct IntVector##n* this){\
    Int s=1, i=0;\
    for(; i<n; i++){\
        s *= this->data[i];\
        this->data[i] = s;\
    }\
}

#define _FUNCTION_INT_VECTOR_LEN_DOT(n) Int _IntVector##n##_dot(const struct IntVector##n* this, const struct IntVector##n v){\
    Int s=0, i=0;\
    for(; i<n; i++) s += this->data[i]*v.data[i];\
    return s;\
}

#define _FUNCTION_INT_VECTOR_LEN_ASSIGN(n) void  _IntVector##n##_assign(struct IntVector##n* this){\
    this->get = &_IntVector##n##_get;\
    this->set = &_IntVector##n##_set;\
    this->fill = &_IntVector##n##_fill;\
    this->sum = &_IntVector##n##_sum;\
    this->cumsum = &_IntVector##n##_cumsum;\
    this->prod = &_IntVector##n##_prod;\
    this->cumprod = &_IntVector##n##_cumprod;\
    this->dot = &_IntVector##n##_dot;\
}

#define INT_VECTOR_LEN(n)\
    _DEFINE_INT_VECTOR_LEN_STRUCT(n)\
    _FUNCTION_INT_VECTOR_LEN_GET(n)\
    _FUNCTION_INT_VECTOR_LEN_SET(n)\
    _FUNCTION_INT_VECTOR_LEN_FILL(n)\
    _FUNCTION_INT_VECTOR_LEN_SUM(n)\
    _FUNCTION_INT_VECTOR_LEN_PROD(n)\
    _FUNCTION_INT_VECTOR_LEN_CUMSUM(n)\
    _FUNCTION_INT_VECTOR_LEN_CUMPROD(n)\
    _FUNCTION_INT_VECTOR_LEN_DOT(n)\
    _FUNCTION_INT_VECTOR_LEN_ASSIGN(n)

/* *************************************************************************************** */


#define _DEFINE_FLOAT_VECTOR_LEN_STRUCT(n) struct FloatVector##n{\
    Float data[n];\
    Float (*get)(struct FloatVector##n* this, Int i);\
    void (*set)(struct FloatVector##n* this, Int i, Float v);\
    void (*fill)(struct FloatVector##n* this, Float v);\
    Float (*sum)(struct FloatVector##n* this);\
    void (*cumsum)(struct FloatVector##n* this);\
    Float (*prod)(struct FloatVector##n* this);\
    void (*cumprod)(struct FloatVector##n* this);\
    Float (*dot)(struct FloatVector##n this, struct FloatVector##n v);\
    Float (*mean)(struct FloatVector##n* this);\
};

#define _FUNCTION_FLOAT_VECTOR_LEN_ASSIGN(n) void  _FloatVector##n##_assign(struct FloatVector##n* this){\
    this->get = &_FloatVector##n##_get;\
    this->set = &_FloatVector##n##_set;\
    this->fill = &_FloatVector##n##_fill;\
    this->sum = &_FloatVector##n##_sum;\
    this->cumsum = &_FloatVector##n##_cumsum;\
    this->prod = &_FloatVector##n##_prod;\
    this->cumprod = &_FloatVector##n##_cumprod;\
    this->dot = &_FloatVector##n##_dot;\
}

#define _FUNCTION_FLOAT_VECTOR_LEN_GET(n) Float _FloatVector##n##_get(const struct FloatVector##n* this, Int i){\
    if(i>=n) return 0;\
    return this->data[i];\
}

#define _FUNCTION_FLOAT_VECTOR_LEN_SET(n) void _FloatVector##n##_set(struct FloatVector##n* this, Int i, Int v){\
    if(i>=n) return; this->data[i]=v;\
}

#define _FUNCTION_FLOAT_VECTOR_LEN_FILL(n) void _FloatVector##n##_fill(struct FloatVector##n* this, Float v){\
    _TYPEARRAY_float_vec_fill(&(this->data), n, v);\
}

#define _FUNCTION_FLOAT_VECTOR_LEN_SUM(n) Float _FloatVector##n##_sum(const struct FloatVector##n* this){\
    return _TYPEARRAY_float_vec_sum(&(this->data), n);\
}

#define _FUNCTION_FLOAT_VECTOR_LEN_PROD(n) Float _FloatVector##n##_prod(const struct FloatVector##n* this){\
    Int i=0;\
    Float p = 1.0;\
    for(; i<n; i++) p *= this->data[i];\
    return p;\
}

#define _FUNCTION_FLOAT_VECTOR_LEN_CUMSUM(n) void _FloatVector##n##_cumsum(struct FloatVector##n* this){\
    Int i=0;\
    Float s=0.0;\
    for(; i < n; i++){\
        s += this->data[i];\
        this->data[i] = s;\
    }\
}

#define _FUNCTION_FLOAT_VECTOR_LEN_CUMPROD(n) void _FloatVector##n##_cumprod(struct FloatVector##n* this){\
    Int i = 0;\
    Float s = 1.0;\
    for(; i < n; i++){\
        s *= this->data[i];\
        this->data[i] = s;\
    }\
}

#define _FUNCTION_FLOAT_VECTOR_LEN_DOT(n) Int _FloatVector##n##_dot(const struct FloatVector##n* this, const struct FloatVector##n v){\
    Int i=0;\
    Float s=0.0;\
    for(; i<n; i++) s += this->data[i]*v.data[i];\
    return s;\
}

#define FLOAT_VECTOR_LEN(n)\
    _DEFINE_FLOAT_VECTOR_LEN_STRUCT(n)\
    _FUNCTION_FLOAT_VECTOR_LEN_GET(n)\
    _FUNCTION_FLOAT_VECTOR_LEN_SET(n)\
    _FUNCTION_FLOAT_VECTOR_LEN_FILL(n)\
    _FUNCTION_FLOAT_VECTOR_LEN_SUM(n)\
    _FUNCTION_FLOAT_VECTOR_LEN_PROD(n)\
    _FUNCTION_FLOAT_VECTOR_LEN_CUMSUM(n)\
    _FUNCTION_FLOAT_VECTOR_LEN_CUMPROD(n)\
    _FUNCTION_FLOAT_VECTOR_LEN_DOT(n)\
    _FUNCTION_FLOAT_VECTOR_LEN_ASSIGN(n)

#define _DEFINE_FLOAT_MATRIX_SIZE_STRUCT(m, n) struct FloatMatrix_##m##_##n{\
    Float data[m*n];\
    Float (*get)(struct FloatMatrix_##m##_##n *this, Int i, Int j);\
    void (*set)(struct FloatMatrix_##m##_##n *this, Int i, Int j, Float v);\
    void (*fill)(struct FloatMatrix_##m##_##n *this, Float v);\
    void (*rand)(struct FloatMatrix_##m##_##n *this);\
    void (*randn)(struct FloatMatrix_##m##_##n *this, Float mean, Float std);\
};

// INT_VECTOR_LEN(3)

// FLOAT_VECTOR_LEN(3)

// _DEFINE_FLOAT_MATRIX_SIZE_STRUCT(3, 3)

#endif // _CBL_TYPE_ARRAY_H_
