#include "CBL_Log.h"
#include "CBL_Array.h"

int main() {
    Vector index;
    Array  array;
    Int *  ivec, n,      i,      ivar1, ivar2, ivar3;
    Float *fv, * fvar1, *fvar2, *fvar3;
    Char   msg[STR_MAX_STRING_LENGTH] = "";

    LOG_file_output = false;
    LOG_init();

    index   = VEC_allocate(TYPECODE_INT, sizeof(Int), 2);
    ivec    = (Int*)index.data;
    ivec[0] = 4;
    ivec[1] = 3;
    array   = ARR_allocate(sizeof(Float), TYPECODE_FLOAT, index);
    n       = ARR_prod_Int_vector(array.size);
    fv      = (Float*)array.data;
    for(i = 0; i < n; i++) fv[i] = (Float)rand() / (Float)RAND_MAX;

    LOG_print_info("float matrix in linear range:");
    for(i = 0; i < n; i++) printf("  %.3f", fv[i]);
    printf("\n");

    for(i = 0; i < 4; i++) {
        ivec[0] = i;
        ivec[1] = 0;
        ivar1   = ARR_linear_index(index, array.size);
        fvar1   = (Float*)ARR_address(array, index);
        ivec[1] = 1;
        ivar2   = ARR_linear_index(index, array.size);
        fvar2   = (Float*)ARR_address(array, index);
        ivec[1] = 2;
        ivar3   = ARR_linear_index(index, array.size);
        fvar3   = (Float*)ARR_address(array, index);
        sprintf(msg, "  %02d %02d %02d %.3f %.3f %.3f", ivar1, ivar2, ivar3, *fvar1, *fvar2, *fvar3);
        LOG_print_info(msg);
    }
    LOG_final();
    return 0;
}
