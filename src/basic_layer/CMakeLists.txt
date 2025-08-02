file(GLOB BASIC_LAYER ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_library(BasicLayer ${BASIC_LAYER})

target_include_directories(BasicLayer
  PUBLIC ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(BasicLayer
  PUBLIC Drogon::Drogon
)

add_library(ShenShang::BasicLayer ALIAS BasicLayer)