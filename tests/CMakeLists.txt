add_executable(main main.cpp)
target_link_libraries(main PRIVATE otx)
target_compile_features(main PUBLIC cxx_std_23)