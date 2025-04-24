// PandoraDemoStrategyTrader.cpp : Defines the entry point for the Pandora Trader console application.
//
//For more information, please visit https://github.com/pegasusTrader/PandoraTrader
//
//除对外销售，免费提供，欢迎合规使用
//
//Please use the platform with legal and regulatory permission.
//This software is released into the public domain.You are free to use it in any way you like, except that you may not sell this source code.
//This software is provided "as is" with no expressed or implied warranty.I accept no liability for any damage or loss of business that this software may cause.
//

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <filesystem>

#include <thread>
#include <iostream>

#include <cstring>
#include <string>
#include <string.h>
#include <stdio.h>
#include "cwFtdMdSpi.h"
#include "cwFtdTradeSpi.h"

#include "cwStrategyDemo.h"
#include "tinyxml.h"
#include "cwBasicCout.h"
#include "cwVersion.h"

#ifdef _MSC_VER
#pragma comment(lib, "cwPandoraDLL.lib")
#pragma comment(lib, "tinyxml.lib")
#pragma comment(lib, "PandoraStrategy.lib")
#endif // WIN32


#define MAX_PATH 260


//price Server
cwFtdMdSpi				m_mdCollector;
cwFtdTradeSpi			m_TradeChannel;
cwStrategyDemo			m_cwStategy;
cwBasicCout				m_cwShow;

//XML Config Parameter
char					m_szMdFront[64];
cwFtdcBrokerIDType		m_szMdBrokerID;
cwFtdcUserIDType		m_szMdUserID;
cwFtdcPasswordType		m_szMdPassWord;

char					m_szTdFront[64];
cwFtdcBrokerIDType		m_szTdBrokerID;
cwFtdcUserIDType		m_szTdUserID;
cwFtdcPasswordType		m_szTdPassWord;
cwFtdcProductInfoType	m_szTdProductInfo;
cwFtdcAppIDType			m_szTdAppID;
cwFtdcPasswordType		m_szTdAuthCode;
char					m_szTdDllPath[MAX_PATH];

std::vector<std::string> m_SubscribeInstrument;

std::string				m_strStrategyConfigFile;
std::string				m_strHisDataFolder;


namespace fs = std::filesystem;


bool ReadXmlConfigFile()
{
	// 创建一个 property_tree 对象
	boost::property_tree::ptree pt;

	// 从 XML 文件中读取数据
	boost::property_tree::read_xml("PandoraTraderConfig.xml", pt);

	// 访问 XML 中的 MD 数据
	std::string Front = pt.get<std::string>("Config.User.MarketDataServer.<xmlattr>.Front");
	std::string BrokerID = pt.get<std::string>("Config.User.MarketDataServer.<xmlattr>.BrokerID");
	std::string UserID = pt.get<std::string>("Config.User.MarketDataServer.<xmlattr>.UserID");
	std::string PassWord = pt.get<std::string>("Config.User.MarketDataServer.<xmlattr>.PassWord");

	snprintf(m_szMdFront, sizeof(m_szMdFront), "%s", Front.c_str());
	snprintf(m_szMdBrokerID, sizeof(m_szMdBrokerID), "%s", BrokerID.c_str());
	snprintf(m_szMdUserID, sizeof(m_szMdUserID), "%s", UserID.c_str());
	snprintf(m_szMdPassWord, sizeof(m_szMdPassWord), "%s", PassWord.c_str());

	//// 访问 XML 中的 TD 数据
	std::string Front_ = pt.get<std::string>("Config.User.TradeServer.<xmlattr>.Front");
	std::string BrokerID_ = pt.get<std::string>("Config.User.TradeServer.<xmlattr>.BrokerID");
	std::string UserID_ = pt.get<std::string>("Config.User.TradeServer.<xmlattr>.UserID");
	std::string PassWord_ = pt.get<std::string>("Config.User.TradeServer.<xmlattr>.PassWord");
	std::string ProductInfo_ = pt.get<std::string>("Config.User.TradeServer.<xmlattr>.ProductInfo");
	std::string AppID_ = pt.get<std::string>("Config.User.TradeServer.<xmlattr>.AppID");
	std::string AuthCode_ = pt.get<std::string>("Config.User.TradeServer.<xmlattr>.AuthCode");

	snprintf(m_szTdFront, sizeof(m_szTdFront), "%s", Front_.c_str());
	snprintf(m_szTdBrokerID, sizeof(m_szTdBrokerID), "%s", BrokerID_.c_str());
	snprintf(m_szTdUserID, sizeof(m_szTdUserID), "%s", UserID_.c_str());
	snprintf(m_szTdPassWord, sizeof(m_szTdPassWord), "%s", PassWord_.c_str());
	snprintf(m_szTdProductInfo, sizeof(m_szTdProductInfo), "%s", ProductInfo_.c_str());
	snprintf(m_szTdAppID, sizeof(m_szTdAppID), "%s", AppID_.c_str());
	snprintf(m_szTdAuthCode, sizeof(m_szTdAuthCode), "%s", AuthCode_.c_str());

	return true;
}

unsigned int PriceServerThread()
{

	m_mdCollector.SetUserLoginField(m_szMdBrokerID, m_szMdUserID, m_szMdPassWord);
	m_mdCollector.SubscribeMarketData(m_SubscribeInstrument);

	m_mdCollector.Connect(m_szMdFront);
	m_mdCollector.WaitForFinish();
	return 0;
}

unsigned int TradeServerThread()
{
	m_TradeChannel.SetDisConnectExit(false);
	m_TradeChannel.SetSaveInstrumentDataToFile(true);
	m_TradeChannel.SetUserLoginField(m_szTdBrokerID, m_szTdUserID, m_szTdPassWord, m_szTdProductInfo);
	m_TradeChannel.SetAuthenticateInfo(m_szTdAppID, m_szTdAuthCode);

	m_TradeChannel.Connect(m_szTdFront);
	m_TradeChannel.WaitForFinish();
	return 0;
}

int main()
{
	std::string strStrategyName = m_cwStategy.GetStrategyName();

	m_cwShow.AddLog("start:______");
	m_cwShow.AddLog("Powered By shibusama:");

	m_cwShow.AddLog("Current Version:%s", GetPandoraTraderVersion());
	m_cwShow.AddLog("Init Config From File!");

	if (!ReadXmlConfigFile())
	{
		m_cwShow.AddLog("Init Config Failed!!");
		m_cwShow.AddLog("The Program will shut down in 5s！");

		int nCnt = 0;
		while (nCnt < 6)
		{
			cwSleep(1000);
			m_cwShow.AddLog("%d . ", nCnt);
			nCnt++;
		}
		return -1;
	}

	m_cwShow.AddLog("User: %s ProductInfo:%s", m_szTdUserID, m_szTdProductInfo);


	if (m_strHisDataFolder.size() > 0)
	{
		m_cwStategy.InitialHisKindleFromHisKindleFolder(m_strHisDataFolder.c_str());
	}

	if (m_strStrategyConfigFile.size() == 0)
	{
		m_cwStategy.InitialStrategy(NULL);
	}
	else
	{
		m_cwStategy.InitialStrategy(m_strStrategyConfigFile.c_str());
	}


	m_TradeChannel.RegisterBasicStrategy(dynamic_cast<cwBasicStrategy*>(&m_cwStategy));

	m_mdCollector.RegisterTradeSPI(dynamic_cast<cwBasicTradeSpi*>(&m_TradeChannel));
	m_mdCollector.RegisterStrategy(dynamic_cast<cwBasicStrategy*>(&m_cwStategy));

	std::thread m_PriceServerThread = std::thread(PriceServerThread);

	std::thread m_TradeServerThread = std::thread(TradeServerThread);


	int iCnt = 0;
	while (1)
	{

		iCnt++;
		if (iCnt % 20 == 0)
		{
			if (iCnt % 80 == 0)
			{
				m_cwShow.AddLog("%s %s Md:%s Trade:%s",
					m_szTdUserID, strStrategyName.c_str(),
					m_mdCollector.GetCurrentStatusString(),
					m_TradeChannel.GetCurrentStatusString());
			}
			cwAccountPtr pAccount = m_TradeChannel.GetAccount();
			if (pAccount.get() != NULL)
			{
				m_cwShow.AddLog("%s Total:%.2f Available:%.2f PL:%.2f Fee:%.2f",
					m_cwStategy.m_strCurrentUpdateTime.c_str(),
					pAccount->Balance, pAccount->Available,
					pAccount->CloseProfit + pAccount->PositionProfit - pAccount->Commission,
					pAccount->Commission);
			}
		}
		cwSleep(1000);
	}
	return 0;
}