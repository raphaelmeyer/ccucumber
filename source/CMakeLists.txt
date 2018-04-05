add_executable(wire-server
  main.cc
)

target_compile_features(wire-server PRIVATE cxx_std_14)

