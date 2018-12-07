# ns3-project
---




成员
张智源	1652782	
邱骏翔	1652707	
朱    宽     1751130	
周宇东	1751659

---

## 运行环境

Ubuntu16.04 

---

## 使用软件

Vmware虚拟机

ns3模拟器

Wireshark

---

## 项目简介
	在传统的大型数据中心，网络通常是三层结构。
	Cisco称之为：分级的互连网络模型（hierarchical inter-networking model）。
	这个模型包含了以下三层：
	Access Layer（接入层）：有时也称为Edge Layer。
	接入交换机通常位于机架顶部，所以它们也被称为ToR（Top of Rack）交换机，它们物理连接服务器。
	Aggregation Layer（汇聚层）：有时候也称为Distribution Layer。
	汇聚交换机连接Access交换机，同时提供其他的服务，例如防火墙，SSL offload，入侵检测，网络分析等。
	Core Layer（核心层）：核心交换机为进出数据中心的包提供高速的转发。
	为多个汇聚层提供连接性，核心交换机为通常为整个网络提供一个弹性的L3路由网络。
	我们所做的，便是模拟一个数据中心的网络结构.

---

## 网络拓扑结构图

![pic](https://github.com/acdzh/ns3-project/blob/master/img/dc.jpg)

---

## 实验步骤

	1.编写程序模拟网络拓扑及网络消息传输状态（多对多）
	2.利用Wireshark和NetAnim对输出的文件进行分析
	3.得出实验小结
## 实验小结

	本次实验学习了Ubuntu的基础用法，对于网络链接协议（ssh、NAT等用于连接虚拟机网络的）有了深入了解
	学习了ns3.29的环境配置，使用ns3模拟了一个数据中心的网络结构，对分级的互连网络模型有了具体的了解，熟悉了弹性的L3路由网络结构。



