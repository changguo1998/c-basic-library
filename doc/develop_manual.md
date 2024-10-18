# Develop manual

## Name style

- ***data type*** uppercase first character without underscore,
  example: `DataType`

- ***type methods declaration in struct*** data type followed "Methods",
  example: `DataTypeMethods`

- ***type methods defination*** data type joined with method name
  by underscore. Methods modifying values of object should end with underscore,
  and the ones not changing values should not end with underscore.
  example: `DataType_non_changable_method` and `DataType_changable_method_`

- ***macro for external usage*** CBL_ + macro name. example: `CBL_CALL`

## Externsion

Vector and VectorN type can be assigned with additional methods.
To define new methods, one need to add declaration to
`Type_external_methods_declaration` macro, defination to
`Type_external_methods_defination` macro, and function pointer to
method in `Type_external_methods_address` macro.
See `include/Type_IntVector3.h` for example
