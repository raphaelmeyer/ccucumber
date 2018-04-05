add_executable(wire-server
  main.cc
  Socket.cc
)

target_compile_features(wire-server PRIVATE cxx_std_14)

target_compile_options(wire-server
  PRIVATE
    "-Wall"
    "-Wextra"
    "-Werror"
)

