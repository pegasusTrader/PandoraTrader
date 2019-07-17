# PandoraTrader
##### A Trade Platform

这是一个国内期货交易平台，采用 C++ 对 CTP 进行一层封装，提供友好的接口给策略交易模型。只需要利用策略模型进行策略开发即可，不用关心底层如何利用CTP进行下单撤单等控制。同时，我们也提供了回测平台，方便您对策略的测试。

该平台对交易策略进行抽象，提供统一的中间层接口给策略，策略需要的信息都通过平台提供的中间层进行访问，不关注交易接口的细节，从而实现策略开发和交易接口开发的分离。
方便交易策略在多种交易接口进行移植。该平台亦提供了 Linux 版本，敬请期待！


##### 快速入门：

1. 本平台要求 VS2015 及以上版本的 IDE，可通过以下链接进行下载并安装:

       https://visualstudio.microsoft.com/zh-hans/vs/

2. 通过 PandoraTrader.sln 打开项目组，其中包含了交易平台 PandoraTrader 和回测平台 PandoraSimulator。您可直接利用交易平台进行模拟盘交易，也可利用我们的回测平台进行测试。


3. 交易平台中，PandoraDemoStrategyTrader.cpp 是 main 函数的入口，作为一个如何实例化该平台代码的 demo。而 cwStrategyDemo 是一个策略demo，里面一些示例如何访问平台中间层提供的信息。如果您想利用此平台来开发策略，您只需要和策略demo 一样，以 cwBasicStrategy 为基类派生一个您的策略类。实现 PriceUpdate，OnRtnTrade，OnRtnOrder，OnOrderCanceled 这几个函数即可在相应的回调中做相应的处理。

       PriceUpdate：进行行情更新，对每个最新的tick行情进行处理；

       OnRtnTrade：成交回报，在交易成功后随即进入该函数并作出反应；

       OnRtnOrder：报单回报，在报单成功后随即进入该函数并作出反应；

       OnOrderCanceled：当撤单成功后随即进入该函数并作出反应。
   
   完成策略开发后，将 PandoraDemoStrategyTrader 中的策略demo替换为您的策略即可。

4. Interface 文件夹下有该平台支持的交易接口和平台定义的头文件和封装库，例如：

       cwStrategyLog.h：可自由实现log日志，观察报单、撤单及成交等情况；

       cwBasicCout.h：输出类，可将所需变量输出显示，基础用法与printf类似。

5. 利用模拟盘测试您的策略时，您需要对 PandoraTraderConfig.xml 进行以下配置：
       
        将模拟盘交易的账号信息（系统后置、BrokerID、UserID及密码等）填写至<MarketDataServer Front="tcp://180.168.146.187:10011" BrokerID="9999" UserID="" PassWord=""/>和<TradeServer Front="tcp://180.168.146.187:10000" BrokerID="9999" UserID="" PassWord="" ProductInfo="Pandora" AppID="Pandora" AuthCode="Pandora"/>，并在<Instrument ID="j1909"/>中输入所需测试的期货名称即可。


    若您暂不知晓该信息，可联系模拟盘平台客服获取。

6. 利用回测平台测试您的策略时，您需要对以下文件进行配置：

       HisMarketDataIndex.xml：用于读取历史交易数据。将交易数据文件的全路径放置于<MDFile DateIndexId="201905160" FilePath="\\Mac\Home\Desktop\PandoraTrader-master\MarketData_20190529_084005.csv" />，DateIndexId为9位数字，最后一位0表示白盘，2则表示夜盘。如需同时回测多天数据，按照此格式在后面继续补充即可；

       PegasusSimulatorConfig.xml：将HisMarketDataIndex.xml和Instrument.xml的全路径填写至<SimulatorServer Front="F:\HisData\HisMarketDataIndex.xml" Interval="0" Instrument="F:\HisData\Instrument.xml"/>，并在<Instrument ID="j1909"/>中输入所需测试的期货名称。


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