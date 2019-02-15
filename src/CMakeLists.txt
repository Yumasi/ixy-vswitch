set(SOURCES
  action.cc
  interface.cc
  main.cc
  tx_queue.cc
  )

set(HEADERS
  action.hh
  interface.hh
  spinlock.hh
  tx_queue.hh
  )

add_executable(ixy-vswitch
  ${SOURCES}
  ${HEADERS}
  )

target_link_libraries(ixy-vswitch ixy)

set_property(TARGET ixy-vswitch PROPERTY CXX_STANDARD 17)
