
include_directories(inc)

set(LIB_2_HEADERS inc/lib2/fun2.h)
set(LIB_2_SOURCES src/fun2.cpp)

add_library(lib2 STATIC ${LIB_2_HEADERS} ${LIB_2_SOURCES})