add_library(networking INTERFACE)
add_library(ts::networking ALIAS networking)

target_include_directories(networking
  INTERFACE networking-ts-impl/include
)

