// PandoraDemoStrategyTrader.cpp : Defines the entry point for the Pandora Trader console application.
//
//For more information, please visit https://github.com/pegasusTrader/PandoraTrader
//
//���������ۣ�����ṩ����ӭ�Ϲ�ʹ��
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

#include <string.h>
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
	// ����һ�� property_tree ����
	boost::property_tree::ptree pt;

	// �� XML �ļ��ж�ȡ����
	boost::property_tree::read_xml("PandoraTraderConfig.xml", pt);

	// ���� XML �е� MD ����
	std::string Front = pt.get<std::string>("Config.User.MarketDataServer.<xmlattr>.Front");
	std::string BrokerID = pt.get<std::string>("Config.User.MarketDataServer.<xmlattr>.BrokerID");
	std::string UserID = pt.get<std::string>("Config.User.MarketDataServer.<xmlattr>.UserID");
	std::string PassWord = pt.get<std::string>("Config.User.MarketDataServer.<xmlattr>.PassWord");

	strcpy(m_szMdFront, Front);
	strcpy(m_szMdBrokerID, BrokerID);
	strcpy(m_szMdUserID, UserID);
	strcpy(m_szMdPassWord, PassWord);

	// ���� XML �е� TD ����
	std::string Front_ = pt.get<std::string>("Config.User.TradeServer.<xmlattr>.Front");
	std::string BrokerID_ = pt.get<std::string>("Config.User.TradeServer.<xmlattr>.BrokerID");
	std::string UserID_ = pt.get<std::string>("Config.User.TradeServer.<xmlattr>.UserID");
	std::string PassWord_ = pt.get<std::string>("Config.User.TradeServer.<xmlattr>.PassWord");
	std::string ProductInfo_ = pt.get<std::string>("Config.User.TradeServer.<xmlattr>.ProductInfo");
	std::string AppID_ = pt.get<std::string>("Config.User.TradeServer.<xmlattr>.AppID");
	std::string AuthCode_ = pt.get<std::string>("Config.User.TradeServer.<xmlattr>.AuthCode");

	strcpy(m_szTdFront, Front_);
	strcpy(m_szTdBrokerID, BrokerID_);
	strcpy(m_szTdUserID, UserID_);
	strcpy(m_szTdPassWord, PassWord_);
	strcpy(m_szTdProductInfo, ProductInfo_);
	strcpy(m_szTdAppID, AppID_);
	strcpy(m_szTdAuthCode, AuthCode_);

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

	m_cwShow.AddLog("Welcome To Pandora Trader !!");
	m_cwShow.AddLog("Powered By PandoraTrader:");

	m_cwShow.AddLog("Current Version:%s", GetPandoraTraderVersion());
	m_cwShow.AddLog("Init Config From File!");

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