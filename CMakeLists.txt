set (CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++0x -Wall -Wextra -O3 -DNDEBUG")
set (CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-Wall -Wextra -O3 -DNDEBUG")
set (CMAKE_BUILD_TYPE "Release" CACHE STRING "Build type")
set (lib_sources src/AnisotropicEikonal.cpp src/GridHelpers.cpp src/GridUtilities.cpp src/grid.c)

set (BOOST_MIN_VERSION "1.49.0")
find_package(Boost ${BOOST_MIN_VERSION} REQUIRED COMPONENTS system filesystem REQUIRED)

add_library (eikonal ${lib_sources})
include_directories (${CMAKE_CURRENT_SOURCE_DIR})

add_executable (compute_eikonal_from_files src/compute_eikonal_from_files.cpp)
target_link_libraries (compute_eikonal_from_files eikonal ${Boost_LIBRARIES})
