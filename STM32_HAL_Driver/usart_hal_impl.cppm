/**
 * @file usart_hal_impl.cppm
 * @brief STM32 HAL 库的 USART 收发函数的封装，用以 emdevif::Serial 类的回调函数
 */

module;

#include <span>

#include "usart.h"

#define EMDEVIF_MODULE_INTERFACE_UNIT

export module emdevif.stm32_peripheral.hal.usart;

import emdevif.core.error_handler;
import emdevif.peripheral.model.serial;

#ifdef __clang__
    #pragma clang diagnostic ignored "-Winclude-angled-in-module-purview"
#endif

#include "emdevif/stm32_peripheral/hal/usart.hpp"
