if(NOT TARGET LaserDriver)
    add_library(LaserDriver laser-driver.c)
endif()

target_include_directories(LaserDriver
          INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
          )

install(TARGETS LaserDriver DESTINATION lib)
install(FILES laser-driver.h DESTINATION include)
