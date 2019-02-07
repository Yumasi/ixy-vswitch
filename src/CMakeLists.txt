set(SOURCES
  interface.cc
  main.cc
  )

set(HEADERS
  interface.hh
  spinlock.hh
  )

add_executable(ixy-vswitch
  ${SOURCES}
  ${HEADERS}
  )

target_link_libraries(ixy-vswitch ixy)

set_property(TARGET ixy-vswitch PROPERTY CXX_STANDARD 17)
