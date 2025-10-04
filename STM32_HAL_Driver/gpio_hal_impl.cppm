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

inline void gpioWrite(void* port, const uint32_t pin, const uint_fast8_t pin_state) noexcept
{
    HAL_GPIO_WritePin(static_cast<GPIO_TypeDef*>(port), pin, (pin_state == 0U ? GPIO_PIN_RESET : GPIO_PIN_SET));
}

inline uint_fast8_t gpioRead(void* port, const uint32_t pin) noexcept
{
    return (HAL_GPIO_ReadPin(static_cast<GPIO_TypeDef*>(port), pin) == GPIO_PIN_RESET ? 0U : 1U);
}

inline void gpioToggle(void* port, uint32_t pin) noexcept
{
    HAL_GPIO_TogglePin(static_cast<GPIO_TypeDef*>(port), pin);
}

}  // namespace emdevif::stm32hal
