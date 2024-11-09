
set(APP_1_SOURCES src/main.cpp)

add_executable(app1 ${APP_1_SOURCES})
target_link_libraries(app1 pca_library)
target_link_libraries(app1 lib2)
