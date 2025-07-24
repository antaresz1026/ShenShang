file(GLOB BASIC_LAYER ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
add_library(Basic_layer ${BASIC_LAYER})
target_include_directories(Basic_layer
  PUBLIC ${CMAKE_SOURCE_DIR}/include
)
target_link_libraries(Basic_layer
  PUBLIC Drogon::Drogon
)
