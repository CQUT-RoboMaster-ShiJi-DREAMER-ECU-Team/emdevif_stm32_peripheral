/**
 * @file hal_status_mapper.cppm
 * @brief 将 HAL_Status 映射到 emdevif::ErrorCode
 */

module;

#include <cstdint>  // NOLINT

#include "main.h"

export module emdevif.stm32Peripheral.hal.statusMapper;

export import emdevif.errorHandler;

export namespace emdevif::stm32hal::internal {

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

}  // namespace emdevif::stm32hal::internal
