# Include Eigen
find_package(Eigen3 3.3 REQUIRED NO_MODULE)

include_directories(include)

file(GLOB_RECURSE LIB_PCA_HEADERS include/pca/*.hpp include/pca/*.h)
file(GLOB_RECURSE LIB_PCA_SOURCES src/*.hpp src/*.cpp)

add_library(pca_library STATIC ${LIB_PCA_HEADERS} ${LIB_PCA_SOURCES})
target_link_libraries(pca_library PUBLIC Eigen3::Eigen)
target_include_directories(pca_library PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)