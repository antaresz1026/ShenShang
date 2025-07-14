cmake_minimum_required(VERSION 3.10)
project(ShenShang LANGUAGES CXX)

# ----------- Options -----------
option(BUILD_TESTS "Build test targets" ON)
option(ENABLE_INSTALL "Enable install step" ON)

# ----------- Compiler Settings -----------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # compile_commands.json

# ----------- Build Types -----------
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

# Debug / Release flags
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
  if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(DEBUG)
  endif()
elseif(MSVC)
  add_compile_options(/W4)
endif()

# ----------- Project Structure -----------
set(PROJECT_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(PROJECT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

include_directories(${PROJECT_INCLUDE_DIR})

file(GLOB_RECURSE SRC_FILES ${PROJECT_SRC_DIR}/*.cpp)

# ----------- Main Target -----------
add_executable(${PROJECT_NAME} ${SRC_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_INCLUDE_DIR})

# ----------- Subdirectories / Modules -----------
# add_subdirectory(external/mylib)
# target_link_libraries(${PROJECT_NAME} mylib)

# ----------- Tests -----------
if(BUILD_TESTS)
  enable_testing()
  include(CTest)

  # GoogleTest or Catch2 example
  # Add a subdirectory containing tests
  add_subdirectory(tests)

  # Optionally: target_link_libraries(MyTests PRIVATE mylib)
endif()

# ----------- Install Rules -----------
if(ENABLE_INSTALL)
  install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
  install(DIRECTORY ${PROJECT_INCLUDE_DIR}/ DESTINATION include)
endif()
