
# Include Eigen
find_package(Eigen3 3.3 REQUIRED NO_MODULE)

include_directories(include)

file(GLOB_RECURSE LIB_VOL_HEADERS include/volatility/*.hpp include/volatility/*.h)
file(GLOB_RECURSE LIB_VOL_SOURCES include/volatility/*.hpp src/*.cpp)

add_library(volatility STATIC ${LIB_VOL_HEADERS} ${LIB_VOL_SOURCES})
target_link_libraries(pca_library PUBLIC Eigen3::Eigen)
target_include_directories(pca_library PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)