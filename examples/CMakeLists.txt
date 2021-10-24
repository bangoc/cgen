add_executable(str_id str_id.c)
add_executable(s2i_pprint s2i_pprint.c)
add_executable(s2i_pprint_custom s2i_pprint_custom.c)
add_executable(songs_list dll_songs.c)

foreach (p songs_list)
  target_link_libraries(${p} bkc)
endforeach()

add_subdirectory(benchmarks)
add_subdirectory(ext)