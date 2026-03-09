/**
 * @file gpio.hpp
 * @brief
 */

#pragma once
#ifndef EMDEVIF_STM32_PERIPHERAL_HAL_GPIO_HPP
    #define EMDEVIF_STM32_PERIPHERAL_HAL_GPIO_HPP

    #include "emdevif/core/detail/config.hpp"

    #ifndef EMDEVIF_MODULE_INTERFACE_UNIT
        #include <cstdint>

        #include "gpio.h"

        #include "emdevif/core/error_handler.hpp"
    #endif

EMDEVIF_MODULE_EXPORT
namespace emdevif::stm32hal {

struct GpioHandle {
    GPIO_TypeDef* port;
    uint32_t pin;
};

inline void gpioWrite(void* handle, const uint_fast8_t pin_state) noexcept
{
    const auto gpio_handle = static_cast<GpioHandle*>(handle);
    HAL_GPIO_WritePin(gpio_handle->port, gpio_handle->pin, (pin_state == 0U ? GPIO_PIN_RESET : GPIO_PIN_SET));
}

inline uint_fast8_t gpioRead(void* handle) noexcept
{
    const auto gpio_handle = static_cast<GpioHandle*>(handle);
    return (HAL_GPIO_ReadPin(gpio_handle->port, gpio_handle->pin) == GPIO_PIN_RESET ? 0U : 1U);
}

inline void gpioToggle(void* handle) noexcept
{
    const auto gpio_handle = static_cast<GpioHandle*>(handle);
    HAL_GPIO_TogglePin(gpio_handle->port, gpio_handle->pin);
}

}  // namespace emdevif::stm32hal

#endif  // !EMDEVIF_STM32_PERIPHERAL_HAL_GPIO_HPP
