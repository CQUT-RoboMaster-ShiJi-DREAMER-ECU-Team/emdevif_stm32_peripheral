/**
 * @file spi_hal_impl.cppm
 * @brief STM32 HAL 库的 SPI 收发函数的封装，用以 emdevif::Spi 类的回调函数
 */

module;

#include <cstdint>

#include <span>

#include "spi.h"
#include "emdevif/core/attributes_and_useful_macros.h"
#include "emdevif/core/fatal_handler.h"

#define EMDEVIF_MODULE_INTERFACE_UNIT

export module emdevif.stm32_peripheral.hal.spi;

import emdevif.core.error_handler;

#ifdef __clang__
    #pragma clang diagnostic ignored "-Winclude-angled-in-module-purview"
#endif

#include "emdevif/stm32_peripheral/hal/spi.hpp"
