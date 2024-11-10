file(GLOB_RECURSE APP_HFT_SOURCES src/*.hpp src/*.cpp)

add_executable(hftapp ${APP_HFT_SOURCES})
target_link_libraries(hftapp pca_library)
