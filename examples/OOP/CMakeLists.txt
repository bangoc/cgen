add_executable(SllDemo SllDemo.c)
add_executable(SllG SllGDemo.c)
add_executable(SllStr SllStr.c)

foreach (p SllDemo SllG SllStr)
  target_link_libraries(${p} bkcgen)
endforeach()