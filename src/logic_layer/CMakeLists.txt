file(GLOB LOGIC_LAYER ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
add_subdirectory(api)
add_library(LogicLayer ${LOGIC_LAYER})
target_include_directories(LogicLayer
  PUBLIC ${CMAKE_SOURCE_DIR}/include
)
target_link_libraries(LogicLayer
  PUBLIC Drogon::Drogon
  jsoncpp
  ShenShang::BasicLayer
  ShenShang::Api
)
add_library(ShenShang::LogicLayer ALIAS LogicLayer)