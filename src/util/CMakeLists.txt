if(NOT TARGET Utils)
    add_library(Utils attitude.c frame.c matrix.c models.c network.c time_util.c)
endif()

target_include_directories(Utils
          INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
          )

install(TARGETS Utils DESTINATION lib)
install(FILES attitude.h DESTINATION include)
install(FILES frame.h DESTINATION include)
install(FILES matrix.h DESTINATION include)
install(FILES models.h DESTINATION include)
install(FILES network.h DESTINATION include)
install(FILES registry.h DESTINATION include)
install(FILES time_util.h DESTINATION include)
install(FILES zhelpers.h DESTINATION include)
