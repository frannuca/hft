

# In test/CMakeLists.txt or main CMakeLists.txt
find_package(GTest REQUIRED)
# Include Eigen
find_package(Eigen3 3.3 REQUIRED NO_MODULE)

add_executable(runTests test_pca.cpp)
target_link_libraries(runTests GTest::GTest GTest::Main pca_library Eigen3::Eigen)

# Enable testing
enable_testing()

# Register tests
add_test(NAME PCA_Tests COMMAND runTests)