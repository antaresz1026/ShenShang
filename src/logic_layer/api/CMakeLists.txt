file(GLOB LOGIC_LAYER ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
add_library(Api ${LOGIC_LAYER})
target_include_directories(Api
  PUBLIC ${CMAKE_SOURCE_DIR}/include
)
target_link_libraries(Api
  PUBLIC Drogon::Drogon
  jsoncpp
  ShenShang::BasicLayer
  ShenShang::Utils
)
add_library(ShenShang::Api ALIAS Api)