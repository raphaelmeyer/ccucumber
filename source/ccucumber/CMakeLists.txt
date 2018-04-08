add_library(ccucumber SHARED
  Socket.cc
  WireServer.cc
)
add_library(cc::cucumber ALIAS ccucumber)

target_link_libraries(ccucumber
  PRIVATE
    ccucumber::settings
    nlohmann::json
)

target_include_directories(ccucumber
  PUBLIC include)


