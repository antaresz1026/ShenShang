file(GLOB Utils ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
add_library(Utils ${Utils})
target_include_directories(Utils
  PUBLIC ${CMAKE_SOURCE_DIR}/include
  ${SODIUM_INCLUDE_DIRS}
)
target_link_libraries(Utils
  PUBLIC ${SODIUM_LIBRARIES}
  Boost::log 
  Boost::log_setup 
  Boost::thread 
  Boost::filesystem 
  Boost::system
  fmt::fmt
)
add_library(ShenShang::Utils ALIAS Utils)