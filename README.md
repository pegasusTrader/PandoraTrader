# PandoraTrader
##### A Trade Platform

##### 起名由来：
据百度百科介绍，Pandora 是希腊神话中赫菲斯托斯用粘土做成的第一个女人。  
众神赠予使她拥有更诱人的魅力的礼物：火神赫菲斯托斯给她做了华丽的金长袍；爱神维纳斯赋予她妩媚与诱惑男人的力量；众神使者赫耳墨斯教会了她言语的技能。  
神灵们每人给她一件礼物，但唯独智慧女神雅典娜拒绝给她智慧。古希腊语中，潘是所有的意思，多拉则是礼物。“潘多拉”即为“拥有一切天赋的女人”。  
我们设计这样一个平台拥有设计者赋予各种技能，唯独不携带智慧，这个智慧是属于策略设计者的，期待策略设计者给予交易策略软件足够的智慧，能够在飘荡的市场上乘风破浪，挂云帆济沧海。

##### 架构介绍:
这是一个中国国内期货交易平台，采用 C++ 对 CTP 进行一层封装，提供友好的接口给策略交易模型。
您只需要关注策略模型进行策略开发即可，不用关心底层如何利用CTP进行下单撤单等控制。同时，我们也提供了回测平台，方便您对策略的测试。

            --------------------------
            |                        |
            |    User  Strategy      |
            |                        |
            --------------------------
                |                |
             Get Info        Call Back
                |                |
        ----------------------------------
        |                                |
        |       Basic Strategy           |
        |                                |
        ----------------------------------
             |                    |
        Trade API               MD API 
             |                    |

该平台对交易策略进行抽象，提供统一的中间层接口给策略，策略需要的信息都通过平台提供的中间层进行访问，不关注交易接口的细节，从而实现策略开发和交易接口开发的分离。
上图中的Trade API可以替换成飞马，QDP等柜台的api，交易api替换，策略可以不用调整。MD API同样可以替换成别的api，甚至是组播，广播数据。
方便交易策略在多种交易接口进行移植。该平台亦提供了 Linux 版本，需要别的api接入，如有需求请与作者联系更新（邮件地址：pandoratrader@163.com）！

##### 目录结构:

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
		│  ├─CTPTradeApi64-------------------------------------------X64 CTP API 6.3.15
		│  │
		│  └─CTPTradeApi32-------------------------------------------Win32 CTP API 6.3.15
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


##### 快速入门：
这是为了您能够快速使用该平台的介绍说明。

1. 本平台要求 VS2015 及以上版本的 IDE，可通过以下链接进行下载并安装:

       https://visualstudio.microsoft.com/zh-hans/vs/

2. 通过 PandoraTrader.sln 打开项目组，其中包含了交易平台 PandoraTrader 和回测平台 PandoraSimulator，详细如目录结构所示。
您可直接利用交易平台对策略进行模拟盘交易，也可利用我们的回测平台进行测试。


3. 交易平台中，PandoraDemoStrategyTrader.cpp 是 main 函数的入口，作为一个如何实例化该平台代码的 demo。
cwStrategyDemo 是一个策略demo，里面一些示例如何访问平台中间层提供的信息。直接编译就可以获得一个自动交易策略。
该策略主要演示了如何获取持仓，获取挂单等，如何根据行情下单，如何撤单等操作，有这些基础元操作后，您就可以组合搭建属于您自己的策略。
如果您想利用此平台来开发策略，您只需要和策略demo一样，以 cwBasicStrategy 为基类派生一个您的策略类，平台提供的报单撤单等功能函数都在该类中定义。
实现 PriceUpdate，OnRtnTrade，OnRtnOrder，OnOrderCanceled 这几个函数即可在相应的回调中做相应的处理。

       PriceUpdate：行情更新，当有最新行情更新时，该函数会被调用，可以在该函数内完成行情处理；

       OnRtnTrade：成交回报，当有成交时，该函数会被调用，如果需要在成交后相应处理，可以在该函数内完成；

       OnRtnOrder：报单回报，每次报单有更新时，该函数会被调用，可以在该函数内做相应的处理；

       OnOrderCanceled：当撤单成功后随即进入该函数并作出反应。
   
	完成策略开发后，将 PandoraDemoStrategyTrader 中的策略demo替换为您的策略即可。

4. Interface 文件夹下有该平台支持的交易接口和平台定义的头文件和封装库，例如：

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

##### 建议反馈：
如果有什么疑问和建议，您可以发送有邮件给pandoratrader@163.com于作者取得联系。

##### 特别提示：
请在法律和监管允许下使用该平台。

软件开放到公共域，您可以免费使用，但不可用于出售。

作者勤勉，尽可能提供可靠软件，但不保证没有疏忽遗漏，由此造成的损失，与作者无关。

如果上期技术暂停对CTP支持或者使用许可，请务必暂停使用该平台。


##### License:
Please use the platform with legal and regulatory permission.

This software is released into the public domain.  You are free to use it in any way you like, except that you may not sell this source code.

This software is provided "as is" with no expressed or implied warranty.
I accept no liability for any damage or loss of business that this software may cause.

If SFIT suspends CTP support or license, be sure to suspend the platform.