function modulename(s::String)
    t = split(s, '_')
    return join(t[2:end], '_')
end

INC = "include"
SRC = "src"
TST = "test"

trials = [
    "Module_Basic",
    "Module_Log",
    "Type_DateTime",
    "Type_Dict",
    "Type_String",
    "Type_Part_math_basic",
    "Type_IntVector",
    "Type_IntVectorN",
    "Type_IntMatrix",
    "Type_FloatVector",
    "Type_FloatVectorN",
    "Type_FloatMatrix",
    "Type_Complex",
    "Type_ComplexVector",
    "Type_ComplexMatrix",
]

libs = map(trials) do m
    local tmp = String[]
    if isfile(joinpath(@__DIR__, "..", INC, m*".h"))
        push!(tmp, "$INC/$m.h")
    end
    if isfile(joinpath(@__DIR__, "..", SRC, m*".c"))
        push!(tmp, "$SRC/$m.c")
    end
#     if startswith(m, "Type_")
#         local tstr = modulename(m)
#         if isfile(joinpath(@__DIR__, "..", TST, tstr*".c"))
#             push!(tmp, "$TST/$tstr.c")
#         end
#     end
    return tmp
end

open("../sources.cmake", "w") do io
    for i = eachindex(libs)
        if isempty(libs[i])
            continue
        end
        print(io, "set($(modulename(trials[i]))_SET")
        for j = eachindex(libs[i])
            print(io, " $(libs[i][j])")
        end
        println(io, ")")
    end
end
