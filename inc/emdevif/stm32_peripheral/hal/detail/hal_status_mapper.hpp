/**
 * @file hal_status_mapper.hpp
 * @brief 将 HAL_Status 映射到 emdevif::ErrorCode
 */

#pragma once
#ifndef EMDEVIF_STM32_PERIPHERAL_HAL_DETAIL_HAL_STATUS_MAPPER_HPP
    #define EMDEVIF_STM32_PERIPHERAL_HAL_DETAIL_HAL_STATUS_MAPPER_HPP

    #ifndef EMDEVIF_MODULE_INTERFACE_UNIT
        #include <cstdint>  // NOLINT

        #include "main.h"

        #include "emdevif/core/error_handler.hpp"
    #endif

namespace emdevif::stm32hal::detail {

constexpr ErrorCode halStatusToErrorCode(const HAL_StatusTypeDef hal_status)
{
    switch (hal_status) {
    case HAL_OK:
        return ErrorCode::Success;
    case HAL_ERROR:
        return ErrorCode::UnknownError;
    case HAL_BUSY:
        return ErrorCode::OperationFail;
    case HAL_TIMEOUT:
        return ErrorCode::Timeout;
    default:
        return ErrorCode::InternalError;
    }
}

}  // namespace emdevif::stm32hal::detail

#endif  // !EMDEVIF_STM32_PERIPHERAL_HAL_DETAIL_HAL_STATUS_MAPPER_HPP
