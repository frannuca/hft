
# Include Eigen
find_package(Eigen3 3.3 REQUIRED NO_MODULE)
# Find and include NLopt
find_package(NLopt REQUIRED)


if(NOT NLopt_FOUND)
    message(FATAL_ERROR "NLopt library not found. Please install NLopt and set NLopt_DIR if necessary.")
endif()

include_directories("/opt/homebrew/opt/nlopt/include")
link_directories("/opt/homebrew/opt/nlopt/lib")

file(GLOB_RECURSE LIB_OPT_HEADERS include/optimization/*.hpp include/optimization/*.h)
file(GLOB_RECURSE LIB_OPT_SOURCES src/*.cpp)

add_library(opt_library STATIC ${LIB_OPT_HEADERS} ${LIB_OPT_SOURCES})
target_link_libraries(opt_library PUBLIC Eigen3::Eigen  NLopt::nlopt)
target_include_directories(opt_library PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)