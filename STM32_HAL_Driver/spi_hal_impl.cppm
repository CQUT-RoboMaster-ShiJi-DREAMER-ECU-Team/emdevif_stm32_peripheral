/**
 * @file spi_hal_impl.cppm
 * @module emdevif.stm32Peripheral.hal.spi
 * @author DuYicheng
 * @date 2025-10-04
 * @brief STM32 HAL 库的 SPI 收发函数的封装，用以 emdevif::Spi 类的回调函数
 */

module;

#include <cstdint>

#include <span>

#include "spi.h"
#include "emdevif/attributes_and_useful_macros.h"

#include "emdevif/fatal_handler.h"

export module emdevif.stm32Peripheral.hal.spi;

export import emdevif.errorHandler;
import emdevif.stm32Peripheral.hal.statusMapper;

export namespace emdevif::stm32hal {

inline ErrorCode spiTransmitReceiveBlock(const bool in_isr,
                                         void* handle,
                                         const std::span<const uint8_t> tx_data,
                                         const std::span<uint8_t> rx_data,
                                         const uint32_t timeout_ms) noexcept
{
    EMDEVIF_ASSERT(tx_data.size() == rx_data.size());

    EMDEVIF_UNUSED(in_isr);

    const auto status = HAL_SPI_TransmitReceive(static_cast<SPI_HandleTypeDef*>(handle),
                                                tx_data.data(),
                                                rx_data.data(),
                                                tx_data.size(),
                                                timeout_ms);
    return internal::halStatusToErrorCode(status);
}

inline ErrorCode spiTransmitReceiveInterrupt(const bool in_isr,
                                             void* handle,
                                             const std::span<const uint8_t> tx_data,
                                             const std::span<uint8_t> rx_data,
                                             const uint32_t timeout_ms) noexcept
{
    EMDEVIF_ASSERT(tx_data.size() == rx_data.size());

    EMDEVIF_UNUSED(in_isr);
    EMDEVIF_UNUSED(timeout_ms);

    const auto status = HAL_SPI_TransmitReceive_IT(static_cast<SPI_HandleTypeDef*>(handle),
                                                   tx_data.data(),
                                                   rx_data.data(),
                                                   tx_data.size());
    return internal::halStatusToErrorCode(status);
}

inline ErrorCode spiTransmitReceiveDma(const bool in_isr,
                                       void* handle,
                                       const std::span<const uint8_t> tx_data,
                                       const std::span<uint8_t> rx_data,
                                       const uint32_t timeout_ms) noexcept
{
    EMDEVIF_ASSERT(tx_data.size() == rx_data.size());

    EMDEVIF_UNUSED(in_isr);
    EMDEVIF_UNUSED(timeout_ms);

    const auto status = HAL_SPI_TransmitReceive_DMA(static_cast<SPI_HandleTypeDef*>(handle),
                                                    tx_data.data(),
                                                    rx_data.data(),
                                                    tx_data.size());
    return internal::halStatusToErrorCode(status);
}

}  // namespace emdevif::stm32hal
