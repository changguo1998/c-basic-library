#include <string.h>
#include "CBL.h"

int main() {
    DateTime dt;
    String   str1,    str2;
    Vector   vec_Int, vec_size;
    Int      shift;

    LOG_init();
    vec_size                 = VEC_allocate(TYPECODE_INT, sizeof(Int), 3);
    ((Int*)vec_size.data)[0] = 4;
    ((Int*)vec_size.data)[1] = 3;
    ((Int*)vec_size.data)[2] = 2;
    vec_Int                  = VEC_allocate(TYPECODE_INT, CBL_typecode2size(TYPECODE_INT), 3);
    ((Int*)vec_Int.data)[0]  = 2;
    ((Int*)vec_Int.data)[0]  = 1;
    ((Int*)vec_Int.data)[0]  = 0;
    shift                    = ARR_linear_index(vec_Int, vec_size);
    sprintf(str1.str, "shift: %d", shift);
    str1.len = strlen(str1.str);
    LOG_print_info(str1.str);
    dt = DT_now(1);
    DT_datetime_string(dt, str2.str);
    LOG_print_info(str2.str);

    LOG_final();
    return 0;
}
