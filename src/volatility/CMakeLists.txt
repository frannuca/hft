
# Include Eigen
find_package(Eigen3 3.3 REQUIRED NO_MODULE)

include_directories(include)

file(GLOB_RECURSE LIB_VOL_HEADERS include/volatility/*.hpp include/volatility/*.h)
file(GLOB_RECURSE LIB_VOL_SOURCES include/volatility/*.hpp src/*.cpp)

add_library(volatility STATIC ${LIB_VOL_HEADERS} ${LIB_VOL_SOURCES})
target_link_libraries(volatility PUBLIC Eigen3::Eigen opt_library)
target_include_directories(volatility PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)