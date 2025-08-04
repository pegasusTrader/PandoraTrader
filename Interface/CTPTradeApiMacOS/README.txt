1. 说明

本次更新内容:
交易API新增接口如下：
   1）新增接口：获取已连接的前置的信息，GetFrontInfo
   2）新增接口：投资者投资者新组保设置查询，ReqQryInvestorPortfSetting

2. 开发环境要求

开发者需要配置Xcode开发环境，否则采集模块可能无法正常使用。

3. 操作系统要求

要求操作系统为MacOS 10.15以上版本。

4. 应用权限配置

信息采集模块采集信息时，需要应用具备某些权限。若应用不具备某些权限，
可能会导致获取到对应的采集项为空。因此在使用信息采集模块前， 请使用者申请权限。
包括允许应用访问网络权限。


5. 支持架构

SDK支持x86_64和arm64。

6. 如何使用API和采集模块

将交易api和行情api以及信息采集模块导入项目中。


7. 替换动态库可能出现的问题

 7.1. 头文件找不到
修改引入头文件如下：
#import "thosttraderapi_se/ThostFtdcTraderApi.h"

 7.2. 程序运行失败
选择 TARGETAS > General > Frameworks,Libraries,and Embedded Content
设置 SDK Embed 为 Embed & Sign。





