# PandoraTrader
A Trade Platform

这是一个国内期货交易平台，采用C++对CTP进行一层封装，提供友好的接口给策略交易模型。只需要利用策略模型进行策略开发即可，不用关心底层如何利用CTP进行下单撤单等控制。

该平台对交易策略进行抽象，提供统一的中间层接口给策略，策略需要的信息都通过平台提供的中间层进行访问，不关注交易接口的细节，从而实现策略开发和交易接口开发的分离。
方便交易策略在多种交易接口进行移植。该平台亦提供了Linux版本，敬请期待！

PandoraDemoStrategyTrader.cpp
这是main函数的入口，作为一个如何实例化该平台代码的demo

cwStrategyDemo 这是一个策略的demo，里面一些示例如何访问平台中间层提供的信息。
如果您想利用此平台来开发您的策略，您只需要和策略demo一样，以cwBasicStrategy为基类派生一个您的策略类
实现PriceUpdate，OnRtnTrade，OnRtnOrder，OnOrderCanceled这几个函数即可，在相应的回调中做相应的处理
完成策略开发后，将PandoraDemoStrategyTrader中的策略demo替换为您的策略即可。

Interface 文件夹下有该平台支持的交易接口和平台定义的头文件和封装库


特别提示：
请在法律和监管允许下使用该平台。

软件开放到公共域，您可以免费使用，但不可用于出售。

作者勤勉，尽可能提供可靠软件，但不保证没有疏忽遗漏，由此造成的损失，与作者无关。

如果上期技术暂停对CTP支持或者使用许可，请务必暂停使用该平台。

License:
Please use the platform with legal and regulatory permission.

This software is released into the public domain.  You are free to use it in any way you like, except that you may not sell this source code.

This software is provided "as is" with no expressed or implied warranty.
I accept no liability for any damage or loss of business that this software may cause.

If SFIT suspends CTP support or license, be sure to suspend the platform.
