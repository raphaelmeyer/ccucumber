add_executable(wire-server
  wire-server.cc
)

target_link_libraries(wire-server
  PRIVATE
    ccucumber::settings
    cc::cucumber
)

