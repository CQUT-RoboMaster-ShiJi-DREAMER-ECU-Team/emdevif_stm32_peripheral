cmake_minimum_required(VERSION 3.28)

set(EMDEVIF_DEVICE_ENABLED_PERIPHERAL_LIST "" CACHE STRING "Add enabled peripheral in this list. \
For example, set it to \"USART;CAN\" in order to enable USART and CAN peripheral")

set(EMDEVIF_STM32_PERIPHERAL_DRIVER "" CACHE STRING "Set witch driver(HAL, LL or BOTH) to use in \
EMDEVIF_DEVICE_ENABLED_PERIPHERAL_LIST")

project(emdevif_stm32_peripheral C CXX ASM)

add_library(${PROJECT_NAME} STATIC)

target_link_libraries(${PROJECT_NAME}
    PUBLIC emdevif_core
    PRIVATE emdevif_compile_options emdevif_stm32cubemx_support emdevif_peripheral_model
)

function(chooseFilesToInclude peripheralList driverList out_chosenFiles)
    set(chosenFiles "")

    list(LENGTH peripheralList peripheralListLength)
    list(LENGTH driverList     driverListLength)
    if (NOT (peripheralListLength EQUAL driverListLength))
        message(FATAL_ERROR "The length of EMDEVIF_DEVICE_ENABLED_PERIPHERAL_LIST and EMDEVIF_STM32_PERIPHERAL_DRIVER \
are not equal. Please make them corresponding to each element one by one.")
    endif ()

    list(FIND driverList "HAL" firstHalDriverElementIndex)
    list(FIND driverList "BOTH" firstBothElementIndex)
    if ((NOT (firstHalDriverElementIndex EQUAL -1)) OR (NOT (firstBothElementIndex EQUAL -1)))
        list(APPEND chosenFiles "STM32_HAL_Driver/hal_status_mapper.cppm")
    endif ()

    math(EXPR maxIndex "${peripheralListLength} - 1")
    foreach (index RANGE ${maxIndex})
        list(GET driverList     ${index} driver)
        list(GET peripheralList ${index} peripheral)

        string(TOLOWER ${peripheral} realPeripheralName)

        if (driver STREQUAL "HAL")
            list(APPEND chosenFiles "STM32_HAL_Driver/${realPeripheralName}_hal_impl.cppm")
            set(messageDriverName "\"HAL\"")
        elseif (driver STREQUAL "LL")
            list(APPEND chosenFiles "STM32_LL_Driver/${realPeripheralName}_ll_impl.cppm")
            set(messageDriverName "\"LL\"")
        elseif (driver STREQUAL "BOTH")
            list(APPEND chosenFiles "STM32_HAL_Driver/${realPeripheralName}_hal_impl.cppm")
            list(APPEND chosenFiles "STM32_LL_Driver/${realPeripheralName}_ll_impl.cppm")
            set(messageDriverName "\"HAL\" and \"LL\"")
        else ()
            message(FATAL_ERROR "Unknown item in EMDEVIF_STM32_PERIPHERAL_DRIVER!")
        endif ()

        message(STATUS "[${PROJECT_NAME}]: Enabled peripheral \"${peripheral}\" with driver ${messageDriverName}")
    endforeach ()

    set(${out_chosenFiles} ${chosenFiles} PARENT_SCOPE)
endfunction()

chooseFilesToInclude(
    "${EMDEVIF_DEVICE_ENABLED_PERIPHERAL_LIST}"
    "${EMDEVIF_STM32_PERIPHERAL_DRIVER}"
    emdevifStm32HalDriverImplModules
)

target_sources(${PROJECT_NAME}
    PUBLIC FILE_SET emdevif_stm32_peripheral_modules TYPE CXX_MODULES
        FILES ${emdevifStm32HalDriverImplModules}
)
