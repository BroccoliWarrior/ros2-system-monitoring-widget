# ROS 2 System Monitoring Widget

一个基于 **ROS 2** 的跨语言系统监控组件，结合 Python 编写的系统信息发布节点和 C++ + Qt 编写的可视化显示界面，用于实时展示主机资源状态。

## 🌟 功能简介

- 每秒发布一次主机状态信息，包括：
  - CPU 占用率
  - 内存使用情况（总量 / 可用量 / 百分比）
  - 网络流量（发送 / 接收）
  - 主机名与时间戳
- C++ + Qt 订阅消息并在窗口中实时可视化展示
- 利用 ROS 2 实现 Python → C++ 的跨语言通信

## 🧱 项目结构

- `sys_status_pub.py`：Python 发布节点，使用 `psutil` 获取系统状态，并发布 `SystemStatus` 消息至 `/sys_status` 话题
- `SysStatusDisplay.cpp`：C++ 订阅节点，使用 Qt 显示系统状态
- `SystemStatus.msg`（自定义消息）：
  ```text
  builtin_interfaces/Time stamp
  string host_name
  float32 cpu_percent
  float32 memory_percent
  float32 memory_total
  float32 memory_available
  float64 net_sent
  float64 net_recv
