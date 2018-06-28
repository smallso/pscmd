# Pscmd

### 简介
近期在写项目时遇到需要获取其他进程命令行字符串的需求，查阅 MSDN 后发现微软并未在 Windows SDK 中提供相关的 WINAPI。Google 后发现了一些文章，一小部分包含具体实现（通过分析 WINAPI GetCommandLine 的反汇编实现并计算偏移量地址后通过 WINAPI ReadProcessMemory 跨进程读内存），但都不符合我的预期，因此就自己实现了一个。

### 使用
详细的使用方式请访问 SMALLSO Blog https://www.xiaoyy.org/opensrc/19.html 获取，其文章中有对该项目的详细介绍。

### 联系
如您发现该项目存在 BUG 或缺陷，可以提交反馈。
* E-mail    xiaoyy@altca.cn
* WorkQQ   	20177621
* Website   https://www.xiaoyy.org/
