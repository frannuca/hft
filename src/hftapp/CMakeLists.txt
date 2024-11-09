
set(APP_1_SOURCES src/main.cpp)

add_executable(hftapp ${APP_1_SOURCES})
target_link_libraries(hftapp pca_library)
