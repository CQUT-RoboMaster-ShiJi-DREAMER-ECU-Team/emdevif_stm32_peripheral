# emdevif_stm32_peripheral

属于 emdevif 的一个扩展，用于提供一部分 STM32 HAL/LL 外设库的封装

## 使用方法

参考 [emdevif](https://github.com/CQUT-RoboMaster-ShiJi-DREAMER-ECU-Team/emdevif.git) 中的示例项目文件结构的配置，
您可以使用 `git clone` 或 `git submodule add` 将本仓库添加到一个合适的目录中，例如：

```Shell
git submodule add https://github.com/CQUT-RoboMaster-ShiJi-DREAMER-ECU-Team/emdevif_stm32_peripheral.git emdevif_collection/emdevif_stm32_peripheral
```

这样，文件结构将会变成：

```
project_root
├── inc/
│   └── ...
├── src/
│   └── ...
├── CMakeLists.txt
├── emdevif_collection/
│   ├── emdevif/
│   │   └── ...
│   └── emdevif_stm32_peripheral/
│       └── ...
└── ...
```

### 配置

| CMake 变量                               | 类型     | 默认值  | 说明                                                                                                                                                                                                                                                                         |
|----------------------------------------|--------|------|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| EMDEVIF_DEVICE_ENABLED_PERIPHERAL_LIST | String | `""` | 要启用的外设列表。外设名称必须全部大写，并且用分号间隔开。<br>例如将此变量设置为 `"USART;CAN"` 后，将会启用 USART 和 CAN 外设                                                                                                                                                                                             |
| EMDEVIF_STM32_PERIPHERAL_DRIVER        | String | `""` | 要使用的库的种类列表，每个元素在 `HAL`、`LL`、`BOTH` 中取，每个元素的位置与 `EMDEVIF_DEVICE_ENABLED_PERIPHERAL_LIST` 的元素对应。<br>例如将 `EMDEVIF_DEVICE_ENABLED_PERIPHERAL_LIST` 设置为 `"USART;CAN;SPI"`，<br>将 `EMDEVIF_STM32_PERIPHERAL_DRIVER` 设置为 `"HAL;LL;BOTH"` 后，USART 将使用 HAL 库，CAN 使用 LL 库，SPI 两种库都使用。 |

例如：

```CMake
set(EMDEVIF_DEVICE_ENABLED_PERIPHERAL_LIST "USART;CAN" CACHE STRING "" FORCE)
set(EMDEVIF_STM32_PERIPHERAL_DRIVER "LL;HAL" CACHE STRING "" FORCE)
add_subdirectory(
    # path to emdevif_stm32_peripheral
)  # 需要确保这一句在设置变量之后
```
