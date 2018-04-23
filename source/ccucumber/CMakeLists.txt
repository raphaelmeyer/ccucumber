find_package(Threads REQUIRED)

# interface

add_library(ccucumber INTERFACE)
add_library(ccucumber::ccucumber ALIAS ccucumber)
target_include_directories(ccucumber INTERFACE interface)

# runner

add_library(runner SHARED
  Socket.cc
  Step.cc
  TcpServer.cc
  WireServer.cc
)
add_library(ccucumber::runner ALIAS runner)

target_link_libraries(runner
  PUBLIC
    ccucumber::ccucumber
  PRIVATE
    ccucumber::settings
    nlohmann::json
    ts::networking
    Threads::Threads
)

target_include_directories(runner PRIVATE interface/ccucumber)

# main

add_library(main SHARED
  main.cc
)
add_library(ccucumber::main ALIAS main)
target_link_libraries(main
  PUBLIC
    ccucumber::runner
  PRIVATE
    ccucumber::settings
)

