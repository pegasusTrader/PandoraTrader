# PandoraTrader
## A Trade Platform

### 起名由来：
据百度百科介绍，Pandora 是希腊神话中赫菲斯托斯用粘土做成的第一个女人。  
众神赠予使她拥有更诱人的魅力的礼物：火神赫菲斯托斯给她做了华丽的金长袍；爱神维纳斯赋予她妩媚与诱惑男人的力量；众神使者赫耳墨斯教会了她言语的技能。神灵们每人给她一件礼物，但唯独智慧女神雅典娜拒绝给她智慧。  
古希腊语中，潘是所有的意思，多拉则是礼物。“潘多拉”即为“拥有一切天赋的女人”，在此，则寓意为“拥有一切技能的交易平台”。  
我们设计这样一个交易平台拥有设计者赋予各种技能，唯独不携带智慧；这个智慧是属于策略设计者的，期待策略设计者设计优秀的策略给予交易软件足够的智慧，能够在飘荡的市场上乘风破浪，挂云帆济沧海。

### 平台特色：
基于c++开发，支持多种交易API，跨平台的高频量化交易平台

 **高效**
   - c++ 
   - 低延时， 直连柜台，无需其他服务器支持

 **灵活**
  - 行情交易接口，作为系统组件，可任意组合
  - 行情或交易接口切换，策略无需调整
  - 支持多种交易接口，如CTP，QDP，Femas等

 **易用**
  - 跨平台支持Linux和Windows
  - 友好策略接口，只需关注策略逻辑
  - 仓位挂单等信息本地维护，策略可同步获取，简化逻辑
  - 支持自动开平模式
  - Tick级别回测

  **安全稳定**
   - 2017年初稳定运行至今
   - 内嵌风控，撤单次数和自成交不再成烦恼

   
### 为什么要用PandoraTrader：


### 组件架构:
PandoraTrader平台架构如下图所示，用户策略是程序的核心，各个组件相互配合，都是为用户策略服务。

用户策略（User Strategy)可以通过Pandora策略平台订阅行情，获取持仓，挂单，合约信息等；可以下单，撤单；策略平台会通过回调通知的方式，通知用户策略。

Pandora策略平台，通过实盘交易接口 Trade API 和MarketData API的组件可以连接到期货公司的柜台，通过这两个组件，实现行情订阅，下单和撤单等操作。

Pandora策略平台，通过回测交易接口，SimTrade API和SimMdAPI,可以连接到回测平台（PandoraSimulator）。

                  模块连接示意图     


                   用户策略                                   
        ┌────────────────────────────┐                           
        │	                         │                         
        │        User  Strategy      │
        │                            │
        └────────────────────────────┘
             |         |          |
         Get Info    Orders   Call Back
          获取信息    报撤单    回调通知
             |         |          |
                  策略平台(内嵌风控)                                        回测模拟系统
        ┌────────────────────────────────┐                       ┌───────────────────────┐   
        |                                |                       |                       |
        |                                |-----Sim Trade API-----|                       |
        |     Pandora Basic Strategy     |                       |    PandoraSimulator   |
        |                                |-----Sim Md API--------|                       |
        |                                |                       |                       |
        └────────────────────────────────┘                       └───────────────────────┘
             |                    |
         Trade API              MD API 
          交易接口             行情接口   
             |                    |
           期货公司 柜台（CTP, QDP etc.）
        ┌────────────────────────────────┐
        |                                |
        |              broker            |
        |        CTP QDP  Femas etc.     |
        |                                |
        └────────────────────────────────┘
             |      |       |        |
           CFFEX   SHFE    DCE      ZCE
           中金所  上期所  大商所    郑商所

该平台对交易策略进行抽象，提供统一的中间层接口给策略，策略需要的信息都通过平台提供的中间层进行访问，不关注交易接口的细节，从而实现策略开发和交易接口开发的分离。同一个策略通过调整交易接口组件，改变交易柜台，甚至是进行回测模拟。可以有效验证策略逻辑的正确性。
上图中的Trade API可以替换成飞马，QDP等柜台的api，交易api替换，策略可以不用调整。MD API同样可以替换成别的api，甚至是组播，广播数据。
平台支持 Linux 版本，develop分支支持Centos 7.3，如用Ubuntu系统请自行将Ubuntu文件夹中的库拷贝替换，如遇到不兼容，需要支持其他Linux版本或者别的API组件，可与作者联系（邮件地址：pandoratrader@163.com）！

### 程序展示
![image](data:image/png;base64,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)
![avatar](https://github.com/pegasusTrader/PandoraTrader/blob/master/pic/simnow_screenshot1.png)

### 仓库路径
- Github: https://github.com/pegasusTrader/PandoraTrader
- Gitee：https://gitee.com/wuchangsheng/PandoraTrader

### 分支说明
- Master: 目前实盘程序交易的版本
- develop_6_5_1: 新功能添加和测试的版本，会持续更新，可能部分功能处于开发中间状态。

### 目录结构:

		PANDORATRADER
		│  PandoraTrader.sln
		│  README.md
		│
		├─Interface
		│  ├─lib-----------------------------------------------------平台支持库文件
		│  │  ├─Debug
		│  │  │
		│  │  ├─Release
		│  │  │
		│  │  └─X64
		│  │      ├─Debug
		│  │      │
		│  │      └─Release
		│  │
		│  ├─include-------------------------------------------------平台公共头文件
		│  │
		│  ├─CTPTradeApi64-------------------------------------------X64 CTP API 6.5.1
		│  │
		│  └─CTPTradeApi32-------------------------------------------Win32 CTP API 6.5.1
		│
		├─PandoraTrade-----------------------------------------------实盘交易程序
		│      ReadMe.txt
		│      PandoraTrader.vcxproj
		│      stdafx.cpp
		│      stdafx.h
		│      targetver.h
		│      PandoraTrader.vcxproj.user
		│      PandoraTraderConfig.xml-------------------------------策略交易配置文件，负责配置行情（前置地址，用户，密码等），交易（前置地址，用户，密码，授权等），策略配置文件等
		│      PandoraDemoStrategyTrader.cpp-------------------------策略交易平台主程序，负责实例化策略，行情和交易，并初始化他们
		│
		├─PandoraSimulator-------------------------------------------回测验证程序
		│      PandoraSimulator.vcxproj
		│      PandoraSimulator.vcxproj.user
		│      PandoraSimulator.vcxproj.filters
		│      PandoraSimulator.cpp----------------------------------回测平台主程序，负责实例化回测系统，包括策略，模拟交易模块和模拟撮合等
		│      HisMarketDataIndex.xml--------------------------------回测历史数据文件表
		│      PandoraSimulatorConfig.xml----------------------------回测使用配置文件
		│
		├─PandoraStrategy--------------------------------------------用户策略库
		│  PandoraStrategy.vcxproj
		│  PandoraStrategy.vcxproj.user
		│  PandoraStrategy.vcxproj.filters
		│  cwEmptyStrategy.cpp---------------------------------------空策略cpp
		│  cwEmptyStrategy.h-----------------------------------------空策略(啥操作都不执行，用于检验连接登录等）的头文件
		│  cwStrategyDemo.h------------------------------------------演示策略头文件
		│  cwStrategyDemo.cpp----------------------------------------演示策略cpp
		│
		└─cwStrategys------------------------------------------------系统策略库，提供编写好的策略以及必要的支撑
		   │
		   ├─include
		   │      cwMarketDataBinaryReceiver.h-----------------------二进制形式数据接收存储策略
		   │      cwMarketDataReceiver.h-----------------------------csv形式数据接收存储策略
		   │
		   └─lib-----------------------------------------------------回测模拟器和策略的库文件
			   ├─X64
			   │  ├─Debug
			   │  │
			   │  └─Release
			   │
			   ├─Debug
			   │
			   └─Release


### 快速入门：
这是为了您能够快速使用该平台的介绍说明。

如果您在Linux下使用，请您从develop分支上获取最新内容，
使用CMAKE，G++来编译工程

        git clone -b develop_6_5_1 https://github.com/pegasusTrader/PandoraTrader.git    

进入工程目录后：

编译debug:

        mkdir builddebug    
        cd builddebug    
        cmake -DCMAKE_BUILD_TYPE=DEBUG ..    
        make    

编译Release:

        mkdir buildrelease     
        cd buildrelease    
        cmake -DCMAKE_BUILD_TYPE=RELEASE ..    
        make    

如果您在Windows下使用，建议您用visual studio来做工程管理和编译，按配置好的工程快速开始Pandora量化之旅。

1. 本平台要求 VS2015 及以上版本的 IDE，可通过以下链接进行下载并安装:

       https://visualstudio.microsoft.com/zh-hans/vs/

2. 通过 PandoraTrader.sln 打开项目组，其中包含了交易平台 PandoraTrader， 策略库工程PandoraStrategy 和回测平台 PandoraSimulator，详细如目录结构所示。
您可直接利用交易平台对策略进行实盘交易或者模拟环境交易，也可利用我们的回测平台进行测试。


3. 交易平台中，PandoraTrader 工程中有PandoraDemoStrategyTrader.cpp 是 main 函数的入口，作为一个如何实例化该平台代码的 demo。  
该实例化过程可以作为通用代码，只要替换其中包含的策略，就可以编译出一个新的交易程序。  
策略库工程PandoraStrateg中自带一个demo策略，即cwStrategyDemo，直接编译就可以获得一个自动交易策略，可以边运行边了解其中功能。  
这个demo提供了如何通过cwBasicStrategy访问平台中维护的持仓信息，挂单信息，根据行情下单，以及进行报单撤单等操作。有这些基础操作知识后，您就可以组合搭建属于您自己的策略。  
只需在PandoraStrateg工程中添加一个新的策略，以 cwBasicStrategy 为基类派生一个您的策略类，实现 PriceUpdate，OnRtnTrade，OnRtnOrder，OnOrderCanceled 这几个函数即可在相应的回调中做相应的处理。  
可以在回调函数中根据行情，持仓和挂单信息，进行报单，撤单等操作。如果有复杂耗时的数学计算，请起一个线程进行计算。秉持原则是让回调函数尽快返回处理后续的操作。  

       PriceUpdate：行情更新，当有最新行情更新时，该函数会被调用，可以在该函数内完成行情处理；
        
       OnRtnTrade：成交回报，当有成交时，该函数会被调用，如果需要在成交后相应处理，可以在该函数内完成；
        
       OnRtnOrder：报单回报，每次报单有更新时，该函数会被调用，可以在该函数内做相应的处理；
        
       OnOrderCanceled：当撤单成功后随即进入该函数并作出反应。
   
	完成策略开发后，记得将 PandoraDemoStrategyTrader 中的策略demo替换为您的新策略。
	在开发新策略的时候，强烈建议新建一个策略类。因为平台维护升级，可能会为了丰富这个Demo策略内容进行更新修改，以免您获取最新更新时，遇到不必要的麻烦。

4. Interface 文件夹下提供一些工具，可以更方便进行开发，排查问题。例如：

       cwStrategyLog.h：可自由实现log日志，观察报单、撤单及成交等情况；
        
       cwBasicCout.h：输出类，可将所需变量输出显示，基础用法与printf类似。

5. 利用Simnow模拟盘测试您的策略时，您需要对 PandoraTraderConfig.xml 进行以下配置：
       
        将模拟盘交易的账号信息（后置、BrokerID、UserID及密码）填写至
	    <MarketDataServer Front="tcp://180.168.146.187:10110" BrokerID="9999" UserID="" PassWord=""/>		//行情配置信息
	    和
	    <TradeServer Front="tcp://180.168.146.187:10100" BrokerID="9999" UserID="" PassWord="" ProductInfo="Pandora" AppID="Pandora" AuthCode="Pandora"/>		//交易配置信息
	    并在<Instrument ID="j1909"/>中输入所需测试的期货合约（可以配置多个）即可，也可以在策略中调用。


    若您暂不知晓该信息，可联系模拟盘平台客服获取。
    如果您要直接接入实盘交易，只要在配置文件中填入相应的实盘信息

6. 利用回测平台测试您的策略时，您需要对PegasusSimulatorConfig.xml文件进行配置：

		type="2" 用于配置回测时历史数据源和形式， 0表示单个csv文件，1表示二进制（bin）文件，2表示csv 序列文件，3表示二进制（bin)序列文件

		HisMarketDataIndex.xml：用于读取历史交易数据。将交易数据文件的全路径放置于<MDFile DateIndexId="201905160" FilePath="\\Mac\Home\Desktop\PandoraTrader-master\MarketData_20190529_084005.csv" />，DateIndexId为9位数字，最后一位0表示白盘，1则表示夜盘。如需同时回测多天数据，按照此格式在后面继续补充即可；
		
		PegasusSimulatorConfig.xml：将HisMarketDataIndex.xml和Instrument.xml的全路径填写至<SimulatorServer Front="F:\HisData\HisMarketDataIndex.xml" Interval="0" Instrument="F:\HisData\Instrument.xml"/>，并在<Instrument ID="j1909"/>中输入所需测试的期货名称。
如果需要历史数据，可以用cwMarketDataReceiver或cwMarketDataBinaryReceiver提供的类，作为策略类编译一个行情存储程序。用计划任务的方式定时启动，来收取历史数据。
cwMarketDataReceiver存下csv文件，cwMarketDataBinaryReceiver存下的是bin的二进制文件。
这两个策略要正确配置行情和交易配置信息，因为需要从交易柜台获取当前有交易合约，从而实现自动订阅合约。
也可以自行编写行情存储程序来自动收行情，程序启动之后，从交易spi中获取合约信息，订阅行情，然后将行情存储下来。Simulator定义的行情csv文件列如下

    Localtime,MD,InstrumentID,TradingDay,UpdateTime,UpdateMillisec,LastPrice,Volume,LastVolume,Turnover,LastTurnover,AskPrice5,AskPrice4,AskPrice3,AskPrice2,AskPrice1,BidPrice1,BidPrice2,BidPrice3,BidPrice4,BidPrice5,AskVolume5,AskVolume4,AskVolume3,AskVolume2,AskVolume1,BidVolume1,BidVolume2,BidVolume3,BidVolume4,BidVolume5,OpenInterest,UpperLimitPrice,LowerLimitPrice


### 策略开发

用户策略可以是一个空白策略，什么都不做处理；    
可以是一个工具性策略，比如自动止盈止损程序；    
可以是一个配对交易策略（Pairs Trading)；    
甚至可以是一个做市商策略。    
可以套利套保，可以做波段，甚至是高频做市商。

### 核心开放计划
核心库代码采用邀请授权机制开放，有C++开发功底的朋友，可以简要描述您自身情况以及参与项目意愿发送邮件到pandoratrader@163.com, 会尽快回复您的诉求。

### 致谢
   - tinyxml2 -- https://github.com/leethomason/tinyxml2

### 建议反馈：
如果有什么疑问和建议，您可以发送有邮件给pandoratrader@163.com与作者取得联系。    
欢迎加入QQ群（615093081）参与讨论。

### AI技术与量化
作者目前在尝试引入AI技术相关内容，如果您在这方面有什么想法，不论是策略还是平台，可以发送有邮件给pandoratrader@163.com与作者取得联系，进一步沟通交流。    

### 使用授权：
请在法律和监管允许下使用该平台。

软件开放到公共域，您可以免费使用，但不可用于出售。

作者勤勉，尽可能提供可靠软件，但因系统复杂，无法保证没有疏忽遗漏，由此造成的损失，与作者无关。

如果上期技术暂停对CTP支持或者使用许可，请务必暂停使用该平台。


#### License:
Please use the platform with legal and regulatory permission.

This software is released into the public domain.  You are free to use it in any way you like, except that you may not sell this source code.

This software is provided "as is" with no expressed or implied warranty.
I accept no liability for any damage or loss of business that this software may cause.

If SFIT suspends CTP support or license, be sure to suspend the platform.

