# Compilation configuration
enable_testing()

set (CMAKE_CXX_STANDARD 23)
set (CMAKE_EXPORT_COMPILE_COMMANDS ON)
set (CMAKE_CXX_EXTENSIONS OFF)

set(SANITIZERS -fsanitize=address -fsanitize=leak -fsanitize=undefined)
set(WARNINGS -Wall -Wextra -Werror)

add_compile_options(${SANITIZERS} ${WARNINGS})
add_link_options(${SANITIZERS} ${WARNINGS})

# Tags and attributes generation
include(cmake/generate.cmake)
generate_tags_file()
generate_attributes_file()
