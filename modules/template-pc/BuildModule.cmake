include (${build_environment}/flags.cmake)

set (sources ${sources}
    src/main.cpp
)

set (cxxflags
    "-Os"
    "-ffunction-sections"
    "-fdata-sections"
    "-fno-exceptions"
    "-fno-rtti"
    "-fno-threadsafe-statics")

string (REGEX REPLACE ";" " " cxxflags "${cxxflags}")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${cxxflags}")
set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}")

add_executable (${PROJECT_NAME}.exe ${sources})
