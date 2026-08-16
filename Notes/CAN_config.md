# STMF723ZET6 CAN配置手册

## 1. CubeMX配置

### 1.1 引脚配置

#### FDCAN1:

**PD0:**FDCAN1_RX

**PD1:**FDCAN1_TX

#### FDCAN2:

**PB12:**FDCAN2_RX

**PB13:**FDCAN2_TX

#### FDCAN3:

**PD12:**FDCAN3_RX

**PD13:**FDCAN3_TX

1.2时钟配置

时钟源选择外部高速晶振(HSE)，频率为8MHz

选择PLLCLK，将系统频率配置为550MHz

将FDCAN分频配置为110MHz

具体配置如图：

![时钟树](E:\Robot\Robot-Learning-Roadmap\Notes\PIC\时钟树.png)

1. 3 参数配置（参数具体含义后边会讲）

Auto Retransmission：Enable

Nominal Parameters: 5

Nominal Time Seg1: 16

Nominal Time Seg2: 5

Std Filters Nbr:1

Rx Fifo1 Elmts Nbr:8

Tx Fifo1 Elmts Nbr:8

未提及的保持默认即可

1.4 中断配置
进入NVIC Settings,打开FDCANx interrupt0