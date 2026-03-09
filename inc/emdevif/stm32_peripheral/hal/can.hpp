/**
 * @file can.hpp
 * @brief
 */

#pragma once
#ifndef EMDEVIF_STM32_PERIPHERAL_HAL_CAN_HPP
    #define EMDEVIF_STM32_PERIPHERAL_HAL_CAN_HPP

    #include "emdevif/core/detail/config.hpp"
    #include "emdevif/stm32_peripheral/hal/detail/hal_status_mapper.hpp"

    #ifndef EMDEVIF_MODULE_INTERFACE_UNIT
        #include <cstdint>

        #include <span>

        #include "can.h"

        #include "emdevif/peripheral/model/can.hpp"
        #include "emdevif/core/error_handler.hpp"
    #endif

EMDEVIF_MODULE_EXPORT
namespace emdevif::stm32hal {

inline ErrorCode canAddTxMessage(bool,
                                 void* handle,
                                 const CanModel::DataHeader& header,
                                 std::span<const uint8_t> data) noexcept
{
    uint32_t tx_mailbox;

    CAN_TxHeaderTypeDef hal_tx_header{.IDE = static_cast<uint32_t>(header.ide),
                                      .RTR = static_cast<uint32_t>(header.rtr),
                                      .DLC = static_cast<uint32_t>(header.dlc)};
    if (header.ide == CanModel::DataIdentifier::StandardId) {
        hal_tx_header.StdId = header.id;
    }
    else if (header.ide == CanModel::DataIdentifier::ExtendedId) {
        hal_tx_header.ExtId = header.id;
    }

    const auto status = HAL_CAN_AddTxMessage(handle, &hal_tx_header, data.data(), &tx_mailbox);
    return detail::halStatusToErrorCode(status);
}

}  // namespace emdevif::stm32hal

#endif  // !EMDEVIF_STM32_PERIPHERAL_HAL_CAN_HPP
