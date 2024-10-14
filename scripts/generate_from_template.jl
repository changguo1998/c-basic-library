function replace_all(str, pat, rep)
    tmp = str
    for i = eachindex(pat)
        while contains(tmp, pat[i])
            tmp = replace(tmp, pat[i]=>rep[i])
        end
    end
    return tmp
end

macro addvarh(name)
    str = string(name)
    return quote
        push!(h_pat_list, "{{"*$str*"}}")
        push!(h_rep_list, $(name))
    end
end

macro addvarc(name)
    str = string(name)
    return quote
        push!(c_pat_list, "{{"*$str*"}}")
        push!(c_rep_list, $(name))
    end
end

h_pat_list = String[]
h_rep_list = String[]
c_pat_list = String[]
c_rep_list = String[]


element_type = ARGS[1]
@addvarh element_type

dimension_number = parse(Int, ARGS[2])

if dimension_number == 1
    dimension_symbol = "Vector"
elseif dimension_number == 2
    dimension_symbol = "Matrix"
elseif dimension_number == 3
    dimension_symbol = "Tensor"
else
    dimension_symbol = "Array"*string(dimension_number)
end

INCLUDE_GUARD = uppercase("_$(element_type)_$(dimension_symbol)_H_")

@addvarh INCLUDE_GUARD

array_type = element_type * dimension_symbol

@addvarh array_type
@addvarc array_type

INCLUDE_FILE_NAME = "CBL_"*array_type*"_auto.h"
@addvarc INCLUDE_FILE_NAME
C_FILE_NAME = "CBL_"*array_type*"_auto.c"

dim_vars = String[]
dim_w = String[]

if dimension_number == 1
    push!(dim_vars, "len")
elseif dimension_number == 2
    append!(dim_vars, ["nrow", "ncol"])
    push!(dim_w, "w1")
else
    for i = 1:dimension_number
        push!(dim_vars, "n"*string(i-1))
        if i > 1
            push!(dim_w, "w"*string(i-1))
        end
    end
end

dimension_variables_list = join(dim_vars, ", ")
@addvarh dimension_variables_list
if isempty(dim_w)
    dimension_weight = ""
else
    dimension_weight = "Int "*join(dim_w, ", ")*";"
end
@addvarh dimension_weight



dimension_variables_initialization = join(map(v->"this->$v = 0;", dim_vars), "\n")

@addvarh dimension_variables_initialization

global_method_struct = uppercase("_CBL_$(element_type)_$(dimension_symbol)_METHODS")
@addvarh global_method_struct
@addvarc global_method_struct


methods_list = []

# get
push!(methods_list, (
    element_type,
    "get",
    join(map(v->"Int $v", dim_vars), ", ")
))

# get linear
if dimension_number > 1
    push!(methods_list, (
        element_type,
        "get_linear",
        "Int index"
    ))
end

# set_
push!(methods_list, (
    "void",
    "set_",
    join(map(v->"Int $v", dim_vars), ", ")
))

# set linear
if dimension_number > 1
    push!(methods_list, (
        "void",
        "set_linear_",
        "Int index, $(element_type) value"
    ))
end

# rand_
push!(methods_list, (
    "void",
    "rand_",
    "$(element_type) min, $(element_type) max"
))

if element_type == "Float"
    push!(methods_list, (
        "void",
        "rand_gauss_",
        "$(element_type) mean, $(element_type) std"
    ))
end

# fill_
push!(methods_list, (
    "void",
    "fill_",
    "$(element_type) value"
))


# copy_from_
push!(methods_list, (
    "void",
    "copy_from_",
    "struct $(array_type) src"
))

# sum
push!(methods_list, (
    element_type,
    "sum",
    ""
))

# prod
push!(methods_list, (
    element_type,
    "prod",
    ""
))

# min
push!(methods_list, (
    element_type,
    "min",
    ""
))

# max
push!(methods_list, (
    element_type,
    "max",
    ""
))

# argmin_linear
push!(methods_list, (
    "Int",
    "argmin_linear",
    ""
))

# argmax_linear
push!(methods_list, (
    "Int",
    "argmax_linear",
    ""
))

#=
#
push!(methods_list, (
    ,
    "",
    ""
))

=#

methods_function_pointer_list_buffer = String[]
methods_function_declaration_list_buffer = String[]
global_method_struct_initialization_buffer = String[]
methods_function_defination_list_buffer = String[]

for (m_return, m_name, m_args) = methods_list
    if endswith(m_name, "_")
        self_pointer = "struct $(array_type)* this"
    else
        self_pointer = "const struct $(array_type)* this"
    end
    if isempty(m_args)
        arglist = self_pointer
    else
        arglist = join([self_pointer, m_args], ", ")
    end
    push!(methods_function_pointer_list_buffer, "$(m_return) (*$(m_name))($(arglist));")
    push!(methods_function_declaration_list_buffer, "$(m_return) $(array_type)_$(m_name)($(arglist));")
    push!(global_method_struct_initialization_buffer, "$(array_type)_$(m_name)")
    push!(methods_function_defination_list_buffer, "$(m_return) $(array_type)_$(m_name)($(arglist)){}")
end

methods_function_pointer_list = join(methods_function_pointer_list_buffer, "\n")
@addvarh methods_function_pointer_list

methods_function_declaration_list = join(methods_function_declaration_list_buffer, "\n")
@addvarh methods_function_declaration_list

global_method_struct_initialization = join("&".*global_method_struct_initialization_buffer, ",\n")
@addvarc global_method_struct_initialization

methods_function_defination_list = join(methods_function_defination_list_buffer, "\n")
@addvarc methods_function_defination_list

hfile = read("../template/Type_Dimsymbol.h", String)
newhfile = replace_all(hfile, h_pat_list, h_rep_list)
open(INCLUDE_FILE_NAME, "w") do io
    println(io, newhfile)
end

cfile = read("../template/Type_Dimsymbol.c", String)
newcfile = replace_all(cfile, c_pat_list, c_rep_list)
open(C_FILE_NAME, "w") do io
    println(io, newcfile)
end
