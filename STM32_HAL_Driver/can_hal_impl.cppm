/**
 * @file can_hal_impl.cppm
 * @brief STM32 HAL 库的 CAN 收发函数的封装，用以 emdevif::Can 类的回调函数
 */

module;

#include <cstdint>

#include <span>

#include "can.h"

#define EMDEVIF_MODULE_INTERFACE_UNIT

export module emdevif.stm32_peripheral.hal.can;

import emdevif.peripheral.model.can;
import emdevif.core.error_handler;

#ifdef __clang__
    #pragma clang diagnostic ignored "-Winclude-angled-in-module-purview"
#endif

#include "emdevif/stm32_peripheral/hal/can.hpp"
