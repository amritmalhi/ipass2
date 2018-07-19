enable_language(ASM)
enable_language(C)

SET(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS)

set(compile_flags " -std=c++14")

set(CMAKE_CXX_FLAGS
        "${CMAKE_CXX_FLAGS} ${compile_flags}"
)

set(CMAKE_C_FLAGS
        "${CMAKE_C_FLAGS} ${compile_flags}"
)
