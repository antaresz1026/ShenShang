file(GLOB LOGIC_LAYER ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
add_library(Logic_layer ${LOGIC_LAYER})
target_include_directories(Logic_layer
  PUBLIC ${CMAKE_SOURCE_DIR}/include
)
target_link_libraries(Logic_layer
  PUBLIC Drogon::Drogon
  jsoncpp
  Basic_layer
)
