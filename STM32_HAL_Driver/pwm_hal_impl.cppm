/**
 * @file pwm_hal_impl.cppm
 * @module emdevif.stm32Peripheral.hal.pwm
 * @author DuYicheng
 * @date 2025-10-05
 * @brief STM32 HAL 库的 PWM 函数的封装，用以 emdevif::Pwm 类的回调函数
 */

module;

#include <cstdint>

#include "tim.h"

#include "emdevif/fatal_handler.hpp"

export module emdevif.stm32Peripheral.hal.pwm;

import emdevif.errorHandler;

namespace emdevif::stm32hal {

export struct PwmHandle {
    TIM_HandleTypeDef* htim;
    uint32_t channel;
};

namespace internal {

uint32_t pwmGetCounterMode(const PwmHandle* pwm_handle) noexcept
{
    return (READ_BIT(pwm_handle->htim->Instance->CR1, TIM_CR1_DIR) == 0 ? TIM_COUNTERMODE_UP : TIM_COUNTERMODE_DOWN);
}

uint32_t pwmGetPwmMode(const PwmHandle* pwm_handle) noexcept
{
    const auto [htim, channel] = *pwm_handle;

    uint32_t mode;

    switch (channel) {
    case TIM_CHANNEL_1:
        mode = READ_BIT(htim->Instance->CCMR1, TIM_CCMR1_OC1M);
        break;
    case TIM_CHANNEL_2:
        mode = READ_BIT(htim->Instance->CCMR1, TIM_CCMR1_OC2M);
        break;
    case TIM_CHANNEL_3:
        mode = READ_BIT(htim->Instance->CCMR2, TIM_CCMR2_OC3M);
        break;
    case TIM_CHANNEL_4:
        mode = READ_BIT(htim->Instance->CCMR2, TIM_CCMR2_OC4M);
        break;
    default:
        EMDEVIF_FATAL_HANDLER("Invalid arguments!");
    }

    return mode;
}

}  // namespace internal

export inline void pwmEnable(void* handle) noexcept
{
    const auto pwm_handle = static_cast<PwmHandle*>(handle);

    HAL_TIM_PWM_Start(pwm_handle->htim, pwm_handle->channel);
}

export inline void pwmDisable(void* handle) noexcept
{
    const auto pwm_handle = static_cast<PwmHandle*>(handle);

    HAL_TIM_PWM_Stop(pwm_handle->htim, pwm_handle->channel);
}

export void pwmSetRatio(void* handle, const uint8_t ratio) noexcept
{
    const uint32_t real_ratio = ratio * 100;
    auto* const pwm_handle = static_cast<PwmHandle*>(handle);
    const auto [htim, channel] = *pwm_handle;
    const uint32_t autoreload_value = __HAL_TIM_GET_AUTORELOAD(pwm_handle->htim);

    uint32_t real_compare_value = real_ratio * autoreload_value / 10000U;

    const auto pwm_mode = internal::pwmGetPwmMode(pwm_handle);
    const auto pwm_counter_mode = internal::pwmGetCounterMode(pwm_handle);
    if (pwm_mode == TIM_OCMODE_PWM1) {
        if (pwm_counter_mode == TIM_COUNTERMODE_UP) {
            // do nothing
        }
        else {
            real_compare_value = autoreload_value - real_compare_value;
        }
    }
    else if (pwm_mode == TIM_OCMODE_PWM2) {
        if (pwm_counter_mode == TIM_COUNTERMODE_UP) {
            real_compare_value = autoreload_value - real_compare_value;
        }
        else {
            // do nothing
        }
    }

    if (real_compare_value > autoreload_value) {
        real_compare_value = autoreload_value;
    }

    __HAL_TIM_SET_COMPARE(htim, channel, real_compare_value);
}

}  // namespace emdevif::stm32hal
