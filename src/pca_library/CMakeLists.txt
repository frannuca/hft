
include_directories(inc)

# Include Eigen
find_package(Eigen3 3.3 REQUIRED NO_MODULE)

set(LIB_1_HEADERS inc/pca_library/pca.h)
set(LIB_1_SOURCES src/pca.cpp)


add_library(pca_library STATIC ${LIB_1_HEADERS} ${LIB_1_SOURCES})
target_link_libraries(pca_library PUBLIC Eigen3::Eigen)