/**
 * @file gpio_hal_impl.cppm
 * @module emdevif.stm32Peripheral.hal.gpio
 * @author DuYicheng
 * @date 2025-10-04
 * @brief STM32 HAL 库的 GPIO 函数的封装，用以 emdevif::Gpio 类的回调函数
 */

module;

#include <cstdint>

#include "gpio.h"

export module emdevif.stm32Peripheral.hal.gpio;

export import emdevif.errorHandler;
import emdevif.stm32Peripheral.hal.statusMapper;

export namespace emdevif::stm32hal {

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
