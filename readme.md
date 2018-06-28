# pscmd

### 简介
近期在写项目时遇到需要获取其他进程命令行字符串的需求，查阅 MSDN 后发现微软并未在 Windows SDK 中提供相关的 WINAPI。Google 后发现了一些文章，一小部分包含具体实现（通过分析 WINAPI GetCommandLine 的反汇编实现并计算偏移量地址后通过 WINAPI ReadProcessMemory 跨进程读内存），但都不符合我的预期，因此就自己实现了一个。

### 使用
详细的使用方式请访问 **SMALLSO Blog** https://www.xiaoyy.org/opensrc/19.html 获取，文章中有详细对该项目的具体实现和使用方式进行介绍。另外，源代码中的许可证您可以忽略。

### 文件
* **demo.cpp** 演示如何使用 pscmd 提供的相关 API 获取指定进程的命令行字符串
* **pscmd.cpp** 实现 pscmd 相关的 API，包含宽窄字符两个版本（该文件中所 include 的 "stdafx.h" 预编译头文件，您可以根据应用的项目不同而移除，预编译头文件不包含在该项目中。）
* **pscmd.h** 声明 pscmd 相关的 API 与数据类型

### 依赖
该项目依赖 Windows SDK 所提供的两个头文件，分别是：
* **windows.h**
* **winternl.h**

### 联系
如您发现该项目存在 BUG 或缺陷，可以提交反馈。
* **E-mail**    xiaoyy@altca.cn
* **WorkQQ**   	20177621
* **Website**   https://www.xiaoyy.org/
