add_executable(wire-server
  step_definitions/steps.cc
)

target_link_libraries(wire-server
  PRIVATE
    ccucumber::settings
    ccucumber::main
)

target_include_directories(wire-server
  PRIVATE ../ccucumber
)

