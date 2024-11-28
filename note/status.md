# Summary

## Content

* [Progress Overview](#Progress-Overview)
    - [Type](#Type)
    - [Module](#Module)
* [Progress functions](#Progress-functions)
    - [String](#string-methods)
    - [IntVector](#IntVector-methods)
    - [FloatVector](#floatvector-methods)
    - [ComplexVector](#complexvector-methods)
    - [IntMatrix](#intmatrix-methods)
    - [FloatMatrix](#floatmatrix-methods)
    - [ComplexMatrix](#complexmatrix-methods)

## Progress Overview

### Type

|                                         | file         |  header  | methods  |   test   |
|-----------------------------------------|--------------|:--------:|:--------:|:--------:|
| *non-numerical type*                    |              |          |          |          |
| [String](#String-methods)               | String       | &#x2713; | &#x2713; | &#x2713; |
| [Date](#Date-methods)                   | DateTime     |          |          |          |
| [Time](#Time-methods)                   | DateTime     |          |          |          |
| [DateTime](#DateTime-methods)           | DateTime     |          |          |          |
| StaticDict                              | Dict         |          |          |          |
| DynamicDict                             | Dict         |          |          |          |
| Sheet                                   | Dict         |          |          |          |
|                                         |              |          |          |          |
| *General Array Type*                    |              |          |          |          |
| Vector                                  | Vector       |          |          |          |
| Array                                   | Array        |          |          |          |
| TypeArray Template                      |              |          |          |          |
|                                         |              |          |          |          |
| *Int Arrays*                            |              |          |          |          |
| [IntVector](#IntVector-methods)         | IntVector    | &#x2713; | &#x2713; | &#x2713; |
| [IntMatrix](#IntMatrix-methods)         |              |          |          |          |
| IntTensor                               |              |          |          |          |
| IntArray                                |              |          |          |          |
|                                         |              |          |          |          |
| *Float Arrays*                          |              |          |          |          |
| [FloatVector](#FloatVector-methods)     | FloatVector  | &#x2713; | &#x2713; |  &cir;   |
| [FloatMatrix](#FloatMatrix-methods)     | FloatMatrix  |          |          |          |
| FloatTensor                             |              |          |          |          |
| FloatArray                              |              |          |          |          |
|                                         |              |          |          |          |
| *Complex Arrays*                        |              |          |          |          |
| [ComplexVector](#ComplexVector-methods) |              |          |          |          |
| [ComplexMatrix](#ComplexVector-methods) |              |          |          |          |
| ComplexTensor                           |              |          |          |          |
| ComplexArray                            |              |          |          |          |
|                                         |              |          |          |          |
| *Macro Template*                        |              |          |          |          |
| IntVector_n macro                       | IntVectorN   |          |          |          |
| IntMatrix_m_n macro                     | IntMatrixN   |          |          |          |
| IntTensor_p_q_r macro                   |              |          |          |          |
| FloatVector_n macro                     | FloatVectorN |          |          |          |

### Module

|              | file  |  header  | methods  |   test   |
|--------------|:-----:|:--------:|:--------:|:--------:|
| type defines | Basic | &#x2713; | &#x2713; |          |
| basic error  | Basic | &#x2713; | &#x2713; |          |
| Log          |  Log  | &#x2713; | &#x2713; | &#x2713; |

## Progress functions

### Date methods

| Function    | Status |
|-------------|:------:|
| read_       |        |
| write_      |        |
| today_      |        |
| set_        |        |
| set_julian_ |        |
| lessthan    |        |
| isequal     |        |
| day_of_year |        |
| diff        |        |
| julian      |        |
| add_        |        |
| regularize_ |        |
| string      |        |

### Time methods

| Function    | Status |
|-------------|:------:|
| read_       |        |
| write_      |        |
| now_        |        |
| set_        |        |
| zero_       |        |
| regularize_ |        |
| string      |        |
| diff        |        |
| diff_second |        |
| lessthan    |        |
| isequal     |        |
| add_        |        |
| add_second_ |        |

### DateTime methods

| Function    | Status |
|-------------|:------:|
| read_       |        |
| write_      |        |
| now_        |        |
| set_        |        |
| set_julian_ |        |
| regularize_ |        |
| diff        |        |
| diff_second |        |
| lessthan    |        |
| isequal     |        |
| add_        |        |
| add_second_ |        |
| julian      |        |
| string      |        |

### String methods

| Function   |  Status  |
|------------|:--------:|
| free       | &#x2713; |
| copy       | &#x2713; |
| cstr       | &#x2713; |
| read_      | &#x2713; |
| readuntil_ | &#x2713; |
| readline_  | &#x2713; |
| readfile_  | &#x2713; |
| write_     | &#x2713; |
| print_     | &#x2713; |
| println_   | &#x2713; |
| set        | &#x2713; |
| isequal    | &#x2713; |
| append     | &#x2713; |
| join       | &#x2713; |
| nextmatch  | &#x2713; |
| startswith | &#x2713; |
| endswith   | &#x2713; |
| contains   | &#x2713; |
| substring  | &#x2713; |
| split      | &#x2713; |
| strip      | &#x2713; |
| replace    | &#x2713; |
| replaceall | &#x2713; |
| reverse    | &#x2713; |

### IntVector methods

| Function        |  Status  |
|-----------------|:--------:|
| free            | &#x2713; |
| alloc           | &#x2713; |
| get             | &#x2713; |
| index           | &#x2713; |
| slice           | &#x2713; |
| count           | &#x2713; |
| index_flag      | &#x2713; |
| set             | &#x2713; |
| setas           | &#x2713; |
| vcat            | &#x2713; |
| rand            | &#x2713; |
| rand_from       | &#x2713; |
| fill            | &#x2713; |
| range           | &#x2713; |
| copy_           | &#x2713; |
| find_trues      | &#x2713; |
| filter          | &#x2713; |
| push            | &#x2713; |
| isequal         | &#x2713; |
| sum             | &#x2713; |
| prod            | &#x2713; |
| min             | &#x2713; |
| max             | &#x2713; |
| argmin          | &#x2713; |
| argmax          | &#x2713; |
| cumsum          | &#x2713; |
| cumprod         | &#x2713; |
| sort            | &#x2713; |
| sortperm        | &#x2713; |
| dot             | &#x2713; |
| coord_linear    | &#x2713; |
| coord_cartesian | &#x2713; |

### FloatVector methods

| Function    |  Status  |
|-------------|:--------:|
| free_       | &#x2713; |
| alloc_      | &#x2713; |
| get         | &#x2713; |
| index_      | &#x2713; |
| slice_      | &#x2713; |
| index_flag_ | &#x2713; |
| set_        | &#x2713; |
| setas_      | &#x2713; |
| vcat_       | &#x2713; |
| rand_       | &#x2713; |
| rand_from_  | &#x2713; |
| fill_       | &#x2713; |
| linrange_   | &#x2713; |
| range_      | &#x2713; |
| copy_       | &#x2713; |
| sum         | &#x2713; |
| mean        | &#x2713; |
| var         | &#x2713; |
| std         | &#x2713; |
| norm        | &#x2713; |
| prod        | &#x2713; |
| min         | &#x2713; |
| max         | &#x2713; |
| argmin      | &#x2713; |
| argmax      | &#x2713; |
| cumsum_     | &#x2713; |
| cumprod_    | &#x2713; |
| sort_       | &#x2713; |
| sortperm_   | &#x2713; |
| dot         | &#x2713; |
| cross_      | &#x2713; |
| map_f_f_    | &#x2713; |
| map_f_ff_   | &#x2713; |
| add_scalar_ | &#x2713; |
| sub_scalar_ | &#x2713; |
| mul_scalar_ | &#x2713; |
| div_scalar_ | &#x2713; |
| add_        | &#x2713; |
| sub_        | &#x2713; |
| mul_        | &#x2713; |
| div_        | &#x2713; |
| sqrt_       | &#x2713; |
| root_       | &#x2713; |
| pow_        | &#x2713; |
| normalize2_ | &#x2713; |
| normalize_  | &#x2713; |
| polyval     | &#x2713; |
| polyint_    | &#x2713; |
| polydiff_   | &#x2713; |
| get_row_    | &#x2713; |
| get_column_ | &#x2713; |
| ifft_       |  &cir;   |

### ComplexVector methods

### IntMatrix methods

### FloatMatrix methods

| Function        | Status |
|-----------------|:------:|
| free_           |        |
| alloc_          |        |
| get             |        |
| set_            |        |
| set_vector_     |        |
| setas_rowfirst_ |        |
| setas_colfirst_ |        |
| hcatv_          |        |
| hcat_           |        |
| vcat_           |        |
| rand_           |        |
| rand_from_      |        |
| fill_           |        |
| copy_           |        |
| diag_           |        |
| add_            |        |
| product_        |        |

### ComplexMatrix methods
