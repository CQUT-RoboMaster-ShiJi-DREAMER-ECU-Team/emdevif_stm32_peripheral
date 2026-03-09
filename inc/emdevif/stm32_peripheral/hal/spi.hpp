/**
 * @file spi.hpp
 * @brief
 */

#pragma once
#ifndef EMDEVIF_STM32_PERIPHERAL_HAL_SPI_HPP
    #define EMDEVIF_STM32_PERIPHERAL_HAL_SPI_HPP

    #include "emdevif/core/detail/config.hpp"
    #include "emdevif/stm32_peripheral/hal/detail/hal_status_mapper.hpp"

    #ifndef EMDEVIF_MODULE_INTERFACE_UNIT
        #include <cstdint>

        #include <span>

        #include "spi.h"
        #include "emdevif/core/attributes_and_useful_macros.h"
        #include "emdevif/core/fatal_handler.h"

        #include "emdevif/core/error_handler.hpp"
    #endif

EMDEVIF_MODULE_EXPORT
namespace emdevif::stm32hal {

inline ErrorCode spiTransmitReceiveBlock(const bool in_isr,
                                         void* handle,
                                         const std::span<const uint8_t> tx_data,
                                         const std::span<uint8_t> rx_data,
                                         const uint32_t timeout_ms) noexcept
{
    EMDEVIF_ASSERT(tx_data.size_bytes() == rx_data.size_bytes());

    EMDEVIF_UNUSED(in_isr);

    const auto status = HAL_SPI_TransmitReceive(static_cast<SPI_HandleTypeDef*>(handle),
                                                tx_data.data(),
                                                rx_data.data(),
                                                tx_data.size_bytes(),
                                                timeout_ms);
    return detail::halStatusToErrorCode(status);
}

inline ErrorCode spiTransmitReceiveInterrupt(const bool in_isr,
                                             void* handle,
                                             const std::span<const uint8_t> tx_data,
                                             const std::span<uint8_t> rx_data,
                                             const uint32_t timeout_ms) noexcept
{
    EMDEVIF_ASSERT(tx_data.size_bytes() == rx_data.size_bytes());

    EMDEVIF_UNUSED(in_isr);
    EMDEVIF_UNUSED(timeout_ms);

    const auto status = HAL_SPI_TransmitReceive_IT(static_cast<SPI_HandleTypeDef*>(handle),
                                                   tx_data.data(),
                                                   rx_data.data(),
                                                   tx_data.size_bytes());
    return detail::halStatusToErrorCode(status);
}

inline ErrorCode spiTransmitReceiveDma(const bool in_isr,
                                       void* handle,
                                       const std::span<const uint8_t> tx_data,
                                       const std::span<uint8_t> rx_data,
                                       const uint32_t timeout_ms) noexcept
{
    EMDEVIF_ASSERT(tx_data.size_bytes() == rx_data.size_bytes());

    EMDEVIF_UNUSED(in_isr);
    EMDEVIF_UNUSED(timeout_ms);

    const auto status = HAL_SPI_TransmitReceive_DMA(static_cast<SPI_HandleTypeDef*>(handle),
                                                    tx_data.data(),
                                                    rx_data.data(),
                                                    tx_data.size_bytes());
    return detail::halStatusToErrorCode(status);
}

}  // namespace emdevif::stm32hal

#endif  // !EMDEVIF_STM32_PERIPHERAL_HAL_SPI_HPP
