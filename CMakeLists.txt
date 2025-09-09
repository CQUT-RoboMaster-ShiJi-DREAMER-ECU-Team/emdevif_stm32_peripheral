cmake_minimum_required(VERSION 3.28)

project(emdevif_stm32_peripheral C CXX ASM)

if (NOT (TARGET emdevif_core))
    message(FATAL_ERROR "${PROJECT_NAME} requires target \"emdevif_core\"!")
endif ()
if (NOT (TARGET emdevif_compile_options))
    message(FATAL_ERROR "${PROJECT_NAME} requires target \"emdevif_compile_options\"!")
endif ()
if (NOT (TARGET emdevif_stm32cubemx_support))
    message(FATAL_ERROR "${PROJECT_NAME} requires target \"emdevif_stm32cubemx_support\"!")
endif ()

add_library(${PROJECT_NAME} STATIC)

target_link_libraries(${PROJECT_NAME}
    PUBLIC emdevif_core
    PRIVATE emdevif_compile_options emdevif_stm32cubemx_support
)

file(GLOB emdevifStm32HalDriverImplModules "STM32_HAL_Driver/*.cppm")
target_sources(${PROJECT_NAME}
    PUBLIC FILE_SET emdevif_stm32_peripheral_modules TYPE CXX_MODULES
        FILES ${emdevifStm32HalDriverImplModules}
)
