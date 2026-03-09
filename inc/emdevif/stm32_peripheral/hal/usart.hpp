/**
 * @file usart.hpp
 * @brief
 */

#pragma once
#ifndef EMDEVIF_STM32_PERIPHERAL_HAL_USART_HPP
    #define EMDEVIF_STM32_PERIPHERAL_HAL_USART_HPP

    #include "emdevif/core/detail/config.hpp"
    #include "emdevif/stm32_peripheral/hal/detail/hal_status_mapper.hpp"

    #ifndef EMDEVIF_MODULE_INTERFACE_UNIT
        #include <span>

        #include "usart.h"

        #include "emdevif/core/error_handler.hpp"
        #include "emdevif/peripheral/model/serial.hpp"
    #endif

EMDEVIF_MODULE_EXPORT
namespace emdevif::stm32hal {

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
    return detail::halStatusToErrorCode(status);
}

inline ErrorCode uartReceiveInterrupt(bool, void* handle, std::span<uint8_t> received_data, uint32_t)
{
    const auto status =
        HAL_UART_Receive_IT(static_cast<UART_HandleTypeDef*>(handle), received_data.data(), received_data.size_bytes());
    return detail::halStatusToErrorCode(status);
}

inline ErrorCode uartReceiveDma(bool, void* handle, std::span<uint8_t> received_data, uint32_t)
{
    const auto status = HAL_UART_Receive_DMA(static_cast<UART_HandleTypeDef*>(handle),
                                             received_data.data(),
                                             received_data.size_bytes());
    return detail::halStatusToErrorCode(status);
}

inline ErrorCode uartReceiveToIdleDma(bool, void* handle, std::span<uint8_t> received_data, uint32_t)
{
    const auto status = HAL_UARTEx_ReceiveToIdle_DMA(static_cast<UART_HandleTypeDef*>(handle),
                                                     received_data.data(),
                                                     received_data.size_bytes());
    return detail::halStatusToErrorCode(status);
}

inline ErrorCode uartTransmitBlocking(bool, void* handle, std::span<const uint8_t> data, const uint32_t timeout_ms)
{
    const auto status =
        HAL_UART_Transmit(static_cast<UART_HandleTypeDef*>(handle), data.data(), data.size_bytes(), timeout_ms);
    return detail::halStatusToErrorCode(status);
}

inline ErrorCode uartTransmitInterrupt(bool, void* handle, std::span<const uint8_t> data, uint32_t)
{
    if (HAL_UART_GetState(static_cast<UART_HandleTypeDef*>(handle)) != HAL_UART_STATE_READY) {
        return ErrorCode::PermissionDenied;
    }

    const auto status = HAL_UART_Transmit_IT(static_cast<UART_HandleTypeDef*>(handle), data.data(), data.size_bytes());
    return detail::halStatusToErrorCode(status);
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
    return detail::halStatusToErrorCode(status);
}

}  // namespace emdevif::stm32hal

#endif  // !EMDEVIF_STM32_PERIPHERAL_HAL_USART_HPP
