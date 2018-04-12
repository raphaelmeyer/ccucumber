
add_custom_target(format
  COMMAND
    find source/ccucumber -name "*.h" -or -name "*.cc" | xargs clang-format -i -style=file
  WORKING_DIRECTORY
    ${PROJECT_SOURCE_DIR}
)

