set(SOURCES
  main.cc
  )

add_executable(ixy-vswitch
  ${SOURCES}
  )

target_link_libraries(ixy-vswitch ixy)
