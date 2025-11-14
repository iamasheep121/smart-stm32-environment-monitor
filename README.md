```markdown
# 🚀 STM32 Environment Monitor - 智能环境监测系统

<div align="center">

![STM32](https://img.shields.io/badge/STM32-ARM_Cortex--M3-blue?logo=stmicroelectronics)
![C++](https://img.shields.io/badge/C++-Embedded-%2300599C?logo=c%2B%2B)
![PlatformIO](https://img.shields.io/badge/PlatformIO-Professional-%23FFBF00?logo=platformio)
![License](https://img.shields.io/badge/License-MIT-green)

**✨ 实时环境数据监测 · 🎯 高精度传感器 · 📊 智能数据分析**

</div>

## 🌟 项目亮点

### 🛠️ 核心技术栈
```c
📟 主控芯片：STM32F103C8T6 (Cortex-M3)
🌡️ 传感器：DHT11温湿度 + MQ系列气体检测  
📡 通信：ESP8266 WiFi模块 + UART协议
🎨 显示：0.96寸OLED屏幕 (SSD1306)
💾 存储：SD卡数据记录
```

### 🎯 功能特性
| 模块 | 功能 | 状态 |
|------|------|------|
| 🔥 **环境监测** | 温湿度、空气质量实时采集 | ✅ |
| 📶 **无线传输** | WiFi数据上传云端 | ✅ |
| 🖥️ **可视化** | OLED实时显示 | ✅ |
| ⚡ **低功耗** | 智能休眠模式 | 🔄 |
📊

## 🚀 快速开始

### 硬件连接
```bash
STM32 ─┬─ SHT30    (温湿度)
       ├─ MQ-7     (CO)
       ├─ LED      (灯)
       ├─ KEY      (按键)
       ├─ Buzzer   (蜂鸣器)
       ├─ MQ-2     (烟雾)  
       ├─ OLED     (显示)
       ├─ ESP8266  (WiFi)
       ├─ Tb6612+电机      (动力)
       └─ SD Card  (存储)（开发中）
```

### 软件部署
```bash
# 克隆项目
git clone https://github.com/iamasheep121/smart-stm32-environment-monitor.git

# keil打开code文件

# 编译上传
点开uvprojx工程
```

## 📁 项目结构
```
smart-stm32-environment-monitor/
├── code/                # 源代码
│   ├── APP              # 应用层实现逻辑
│   ├── Hardware/        # 硬件底层驱动
│   ├── NET/             # 通信实现
│   ├── User/            # 核心文件
│   └── library/         # 第三方库
├── docs/                # 说明文档                
├── hardware/            # 硬件设计及资料
│   ├── BOM              # 元器件清单
│   └── pcb/             # PCB设计
└── image/               # 功能图片
```

## 🔧 配置说明
```cpp
// config.h - 系统配置
#ESP8266_WIFI_INFO      "AT+CWJAP=\"www\",\"www123456\"\r\n"    "wifi名和密码" 

#define PROID			      "o5H719J5gg"     "onenet云平台产品ID"
#define ACCESS_KEY		  "******"         "onenet设备密钥"
#define DEVICE_NAME		  "Test1"          "设备名称"
```

## 🤝 贡献指南
我们欢迎所有形式的贡献！请参阅：
- [贡献指南](CONTRIBUTING.md)  
- [问题反馈](https://github.com/iamasheep121/smart-stm32-environment-monitor/issues)
- [功能请求](https://github.com/iamasheep121/smart-stm32-environment-monitor/issues/new?template=feature_request.md)


</div>

## 📜 开源协议
本项目基于 **MIT License** 开源 - 详见 [LICENSE](LICENSE) 文件。

---

<div align="center">

**💡 灵感源于生活 · 🔬 技术改变世界**

*如果这个项目对你有帮助，请给个 ⭐ 支持一下！*

[📚 文档](docs/) | [🐛 报告问题](issues) | [💡 建议功能](issues/new) | [👥 参与贡献](CONTRIBUTING.md)

</div>
```
## 演示视频

[点击查看功能演示](https://b23.tv/gXPj1FW)
