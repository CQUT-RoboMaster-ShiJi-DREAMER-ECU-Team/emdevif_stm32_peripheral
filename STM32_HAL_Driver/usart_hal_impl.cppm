/**
 * @file usart_hal_impl.cppm
 * @brief STM32 HAL 库的 USART 收发函数的封装，用以 emdevif::Serial 类的回调函数
 */

module;

#include <span>

#include "usart.h"

export module emdevif.stm32Peripheral.hal.usart;

import emdevif.stm32Peripheral.hal.statusMapper;
export import emdevif.errorHandler;
import emdevif.peripheral.model.serial;

export namespace emdevif::stm32hal {

constexpr uint32_t uart_max_delay = HAL_MAX_DELAY;

constexpr uint32_t uart_none_blocking = 0U;

inline SerialModel::State uartGetState(bool, void* handle) noexcept
{
    if (HAL_UART_GetState(static_cast<UART_HandleTypeDef*>(handle)) == HAL_UART_STATE_READY) {
        return SerialModel::Ready;
    }

    return SerialModel::Busy;
}

inline ErrorCode uartReceiveBlocking(bool, void* handle, std::span<uint8_t> received_data, const uint32_t timeout_ms)
{
    const auto status = HAL_UART_Receive(static_cast<UART_HandleTypeDef*>(handle),
                                         received_data.data(),
                                         received_data.size_bytes(),
                                         timeout_ms);
    return internal::halStatusToErrorCode(status);
}

inline ErrorCode uartReceiveInterrupt(bool, void* handle, std::span<uint8_t> received_data, uint32_t)
{
    const auto status =
        HAL_UART_Receive_IT(static_cast<UART_HandleTypeDef*>(handle), received_data.data(), received_data.size_bytes());
    return internal::halStatusToErrorCode(status);
}

inline ErrorCode uartReceiveDma(bool, void* handle, std::span<uint8_t> received_data, uint32_t)
{
    const auto status = HAL_UART_Receive_DMA(static_cast<UART_HandleTypeDef*>(handle),
                                             received_data.data(),
                                             received_data.size_bytes());
    return internal::halStatusToErrorCode(status);
}

inline ErrorCode uartReceiveToIdleDma(bool, void* handle, std::span<uint8_t> received_data, uint32_t)
{
    const auto status = HAL_UARTEx_ReceiveToIdle_DMA(static_cast<UART_HandleTypeDef*>(handle),
                                                     received_data.data(),
                                                     received_data.size_bytes());
    return internal::halStatusToErrorCode(status);
}

inline ErrorCode uartTransmitBlocking(bool, void* handle, std::span<const uint8_t> data, const uint32_t timeout_ms)
{
    const auto status =
        HAL_UART_Transmit(static_cast<UART_HandleTypeDef*>(handle), data.data(), data.size_bytes(), timeout_ms);
    return internal::halStatusToErrorCode(status);
}

inline ErrorCode uartTransmitInterrupt(bool, void* handle, std::span<const uint8_t> data, uint32_t)
{
    if (HAL_UART_GetState(static_cast<UART_HandleTypeDef*>(handle)) != HAL_UART_STATE_READY) {
        return ErrorCode::PermissionDenied;
    }

    const auto status = HAL_UART_Transmit_IT(static_cast<UART_HandleTypeDef*>(handle), data.data(), data.size_bytes());
    return internal::halStatusToErrorCode(status);
}

inline ErrorCode uartTransmitDma(bool, void* handle, std::span<const uint8_t> data, uint32_t)
{
    if (HAL_UART_GetState(static_cast<UART_HandleTypeDef*>(handle)) != HAL_UART_STATE_READY) {
        return ErrorCode::PermissionDenied;
    }
    if (HAL_DMA_GetState(static_cast<UART_HandleTypeDef*>(handle)->hdmatx) != HAL_DMA_STATE_READY) {
        return ErrorCode::PermissionDenied;
    }

    const auto status = HAL_UART_Transmit_DMA(static_cast<UART_HandleTypeDef*>(handle), data.data(), data.size_bytes());
    return internal::halStatusToErrorCode(status);
}

}  // namespace emdevif::stm32hal
