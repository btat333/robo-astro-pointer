add_library(Utils models.c)

target_include_directories(Utils
          INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
          )

install(TARGETS Utils DESTINATION lib)
install(FILES models.h DESTINATION include)
install(FILES registry.h DESTINATION include)
install(FILES zhelpers.h DESTINATION include)