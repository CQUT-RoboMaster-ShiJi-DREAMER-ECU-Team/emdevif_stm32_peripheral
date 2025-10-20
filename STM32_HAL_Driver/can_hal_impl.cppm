/**
 * @file can_hal_impl.cppm
 * @author DuYicheng
 * @date 2025-09-12
 * @brief STM32 HAL 库的 CAN 收发函数的封装，用以 emdevif::Can 类的回调函数
 */

module;

#include <cstdint>

#include <span>

#include "can.h"

export module emdevif.stm32Peripheral.hal.can;

import emdevif.stm32Peripheral.hal.statusMapper;
import emdevif.connectivity.can;
export import emdevif.errorHandler;

export namespace emdevif::stm32hal {

inline ErrorCode canAddTxMessage(bool, void* handle, const Can::DataHeader& header, std::span<const uint8_t> data)
{
    uint32_t tx_mailbox;

    CAN_TxHeaderTypeDef hal_tx_header{.IDE = static_cast<uint32_t>(header.ide),
                                      .RTR = static_cast<uint32_t>(header.rtr),
                                      .DLC = static_cast<uint32_t>(header.dlc)};
    if (header.ide == Can::DataIdentifier::StandardId) {
        hal_tx_header.StdId = header.id;
    }
    else if (header.ide == Can::DataIdentifier::ExtendedId) {
        hal_tx_header.ExtId = header.id;
    }

    const auto status = HAL_CAN_AddTxMessage(handle, &hal_tx_header, data.data(), &tx_mailbox);
    return internal::halStatusToErrorCode(status);
}

}  // namespace emdevif::stm32hal
