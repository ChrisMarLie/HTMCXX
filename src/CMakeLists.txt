target_sources(htmcxx
  PUBLIC
    FILE_SET CXX_MODULES FILES
    htmcxx.cc
)

add_subdirectory(tags)
add_subdirectory(attributes)
add_subdirectory(utils)
