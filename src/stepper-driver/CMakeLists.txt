if(NOT TARGET StepperDriver)
    add_library(StepperDriver stepper-driver.c)
endif()

target_include_directories(StepperDriver
          INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
          )

install(TARGETS StepperDriver DESTINATION lib)
install(FILES stepper-driver.h DESTINATION include)
