/**
 * @file pwm_hal_impl.cppm
 * @brief STM32 HAL 库的 PWM 函数的封装，用以 emdevif::Pwm 类的回调函数
 */

module;

#include <cstdint>

#include "tim.h"
#include "emdevif/core/fatal_handler.h"

#define EMDEVIF_MODULE_INTERFACE_UNIT

export module emdevif.stm32_peripheral.hal.pwm;

import emdevif.core.error_handler;

#ifdef __clang__
    #pragma clang diagnostic ignored "-Winclude-angled-in-module-purview"
#endif

#include "emdevif/stm32_peripheral/hal/pwm.hpp"
