add_library(settings INTERFACE)
add_library(ccucumber::settings ALIAS settings)

target_compile_features(settings INTERFACE cxx_std_14)

target_compile_options(settings
  INTERFACE
    "-Wall"
    "-Wextra"
    "-Werror"
)

