#include "CBL_Log.h"
#include "CBL_Vector.h"

int main() {
    Vector v1, v2;
    Int i, *p;
    char message[STR_MAX_STRING_LENGTH]="";
    LOG_file_output = false;
    v1 = VEC_new(sizeof(Int), TYPECODE_INT, 5);
    p = (Int*)v1.value;
    for(i = 0; i < 5; i++) p[i] = i;
    sprintf(message, "v1:");
    LOG_print_info(message);
    for(i = 0; i < 5; i++) {
        sprintf(message, " %d", p[i]);
        LOG_print_info(message);
    }

    v2 = VEC_copy(v1);
    for(i = 0; i < 5; i++) ((Int*)v2.value)[i] += 1;
    printf("v2:");
    for(i = 0; i < 5; i++) printf(" %d", ((Int*)v2.value)[i]);

    VEC_free(&v1);
    VEC_free(&v2);
}
