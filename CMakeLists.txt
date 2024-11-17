cmake_minimum_required(VERSION 3.16)
project(HFT)

set(CMAKE_CXX_STANDARD 20)

set(GLOBAL_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_INSTALL_PREFIX ${PROJECT_BINARY_DIR}/install)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${GLOBAL_OUTPUT_PATH})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${GLOBAL_OUTPUT_PATH})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${GLOBAL_OUTPUT_PATH})

foreach(OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${GLOBAL_OUTPUT_PATH})
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${GLOBAL_OUTPUT_PATH})
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${GLOBAL_OUTPUT_PATH})
endforeach(OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES)


link_directories(${GLOBAL_OUTPUT_PATH})

add_subdirectory(src/pca_library)
add_subdirectory(src/volatility)
add_subdirectory(src/time)
add_subdirectory(src/optimizer)
add_subdirectory(src/hftapp)
add_subdirectory(test)

include_directories(src/pca_library/include)
include_directories(src/volatility/include)
include_directories(src/time/include)
include_directories(src/optimizer/include)


# Enable testing
enable_testing()

file(GLOB executables      "${GLOBAL_OUTPUT_PATH}/*.exe")
file(GLOB shared_libraries "${GLOBAL_OUTPUT_PATH}/*.dll")
file(GLOB static_libraries "${GLOBAL_OUTPUT_PATH}/*.lib")

install(FILES ${executables}      DESTINATION "bin")
install(FILES ${shared_libraries} DESTINATION "bin")
install(FILES ${static_libraries} DESTINATION "bin")


# SDK Installation
install(DIRECTORY "src/pca_library/include/" DESTINATION ${GLOBAL_OUTPUT_PATH} FILES_MATCHING PATTERN "*.h")
install(DIRECTORY "src/pca_library/include/" DESTINATION ${GLOBAL_OUTPUT_PATH} FILES_MATCHING PATTERN "*.hpp")

install(DIRECTORY "src/volatility/include/" DESTINATION ${GLOBAL_OUTPUT_PATH} FILES_MATCHING PATTERN "*.h")
install(DIRECTORY "src/volatility/include/" DESTINATION ${GLOBAL_OUTPUT_PATH} FILES_MATCHING PATTERN "*.hpp")

install(DIRECTORY "src/time/include/" DESTINATION ${GLOBAL_OUTPUT_PATH} FILES_MATCHING PATTERN "*.h")
install(DIRECTORY "src/time/include/" DESTINATION ${GLOBAL_OUTPUT_PATH} FILES_MATCHING PATTERN "*.hpp")

install(DIRECTORY "src/optimizer/include/" DESTINATION ${GLOBAL_OUTPUT_PATH} FILES_MATCHING PATTERN "*.h")
install(DIRECTORY "src/optimizer/include/" DESTINATION ${GLOBAL_OUTPUT_PATH} FILES_MATCHING PATTERN "*.hpp")
