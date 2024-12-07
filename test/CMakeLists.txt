# In test/CMakeLists.txt or main CMakeLists.txt
include(CTest)
find_package(GTest REQUIRED)
# Include Eigen
find_package(Eigen3 3.3 REQUIRED NO_MODULE)
file(GLOB TEST_SOURCES "./*.cpp")

add_executable(runTests ${TEST_SOURCES})
target_link_libraries(runTests GTest::GTest GTest::Main pca_library  time_library  opt_library volatility Eigen3::Eigen)

# Register tests
add_test(NAME TestProject COMMAND runTests)