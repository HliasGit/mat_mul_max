cmake_minimum_required(VERSION 3.10)
project(mat_mul)


find_package(MPI REQUIRED)
include_directories(${MPI_INCLUDE_PATH})

include_directories(include)

add_subdirectory(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# non aggiungo matrix_mult che non serve
set(SOURCES src/mat_mul.cpp)

add_executable(main ${SOURCES})
target_link_libraries(main ${MPI_LIBRARIES})

add_executable(test_multiplication test/test.cpp)
target_link_libraries(test_multiplication gtest gtest_main)

add_executable(mat_mul_ex src/mat_mul.cpp)


if (MPI_COMPILE_FLAGS)
  set_target_properties(main PROPERTIES COMPILE_FLAGS "${MPI_COMPILE_FLAGS}")
  set_target_properties(test_multiplication PROPERTIES COMPILE_FLAGS "${MPI_COMPILE_FLAGS}")
endif ()

if (MPI_LINK_FLAGS)
  set_target_properties(main PROPERTIES LINK_FLAGS "${MPI_LINK_FLAGS}")
  set_target_properties(test_multiplication PROPERTIES LINK_FLAGS "${MPI_LINK_FLAGS}")
endif ()

enable_testing()

include(GoogleTest)
gtest_discover_tests(test_multiplication)