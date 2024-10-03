#include "CBL.h"

size_t CBL_typecode2size(UInt8 type) {
    switch(type) {
    case TYPECODE_INT8       : return sizeof(Int8);
    case TYPECODE_UINT8      : return sizeof(UInt8);
    case TYPECODE_INT32      : return sizeof(Int32);
    case TYPECODE_UINT32     : return sizeof(UInt32);
    case TYPECODE_INT64      : return sizeof(Int64);
    case TYPECODE_UINT64     : return sizeof(UInt64);
    case TYPECODE_INT128     : return sizeof(Int128);
    case TYPECODE_UINT128    : return sizeof(UInt128);
    case TYPECODE_FLOAT32    : return sizeof(Float32);
    case TYPECODE_FLOAT64    : return sizeof(Float64);
    case TYPECODE_FLOAT128   : return sizeof(Float128);
    case TYPECODE_COMPLEX32  : return sizeof(Complex32);
    case TYPECODE_COMPLEX64  : return sizeof(Complex64);
    case TYPECODE_COMPLEX128 : return sizeof(Complex128);
    case TYPECODE_STRING     : return sizeof(String);
    case TYPECODE_DATE       : return sizeof(Date);
    case TYPECODE_TIME       : return sizeof(Time);
    case TYPECODE_DATETIME   : return sizeof(DateTime);
    default                  : return 0;
    }
}
