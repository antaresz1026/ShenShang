cmake_policy(SET CMP0167 OLD)
cmake_minimum_required(VERSION 3.10)
project(ShenShang LANGUAGES CXX)

# ----------- Options -----------
option(BUILD_TESTS "Build test targets" ON)
option(ENABLE_INSTALL "Enable install step" OFF)

# ----------- Compiler Settings -----------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ----------- Build Types -----------
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
  if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(DEBUG)
  endif()
elseif(MSVC)
  add_compile_options(/W4)
endif()

set(PROJECT_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(PROJECT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

find_package(Drogon REQUIRED)
find_package(Boost REQUIRED COMPONENTS log log_setup thread filesystem system date_time)
find_package(GTest REQUIRED)

include_directories(${PROJECT_INCLUDE_DIR})
file(GLOB_RECURSE SRC_FILES ${PROJECT_SRC_DIR}/*.cpp)

add_subdirectory(src/basic_layer)
add_subdirectory(src/logic_layer)

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE Basic_layer Logic_layer)

if(BUILD_TESTS)
  enable_testing()
  include(CTest)
  add_subdirectory(tests)
endif()

if(ENABLE_INSTALL)
  install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
  install(DIRECTORY ${PROJECT_INCLUDE_DIR}/ DESTINATION include)
endif()
