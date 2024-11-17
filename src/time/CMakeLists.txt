include_directories(include)


file(GLOB_RECURSE LIB_TIME_HEADERS include/time/*.hpp include/time/*.h )
file(GLOB_RECURSE LIB_TIME_SOURCES src/*.hpp src/*.cpp)

add_library(time_library STATIC ${LIB_TIME_HEADERS} ${LIB_TIME_SOURCES})
target_include_directories(time_library PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)