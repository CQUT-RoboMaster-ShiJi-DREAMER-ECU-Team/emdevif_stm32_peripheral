# AGENTS.md

## 模块定位
`emdevif` 的 STM32 外设扩展，实现 HAL/LL 封装适配。

## 开发约束
- `EMDEVIF_DEVICE_ENABLED_PERIPHERAL_LIST` 与 `EMDEVIF_STM32_PERIPHERAL_DRIVER` 必须逐项对应。
- 外设名保持大写输入约定，内部转换逻辑不得破坏既有路径。
- 仅做抽象适配，不修改 CubeMX 生成代码策略。

## 验证
- 检查 HAL/LL/BOTH 三种选择路径均可正确选源并编译。
