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

//#define EMPTYSTRATEGY
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <filesystem>

#include <thread>
#include <iostream>

#include <string.h>
#include "cwFtdMdSpi.h"
#include "cwFtdTradeSpi.h"
//#include "cwMarketDataReceiver.h"

#include "cwStrategyDemo.h"
#include "tinyxml.h"
#include "cwBasicCout.h"
#include "cwVersion.h"

#ifdef _MSC_VER
#pragma comment(lib, "cwPandoraDLL.lib")
#pragma comment(lib, "tinyxml.lib")
#pragma comment(lib, "PandoraStrategy.lib")
#endif // WIN32


//本程序互斥量，用于判断是否有该程序在运行
#ifdef WIN32
HANDLE  m_hAppMutex(NULL);
#endif

#ifndef MAX_PATH
#define MAX_PATH          260
#endif // !MAX_PATH

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

	strcpy(m_szMdFront, Front);
	strcpy(m_szMdBrokerID, BrokerID);
	strcpy(m_szMdUserID, UserID);
	strcpy(m_szMdPassWord, PassWord);

	// 访问 XML 中的 TD 数据
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

#ifdef WIN32
bool CtrlHandler(DWORD fdwCtrlType)
{
	switch (fdwCtrlType)
	{
		// Handle the CTRL-C signal.   
	case CTRL_C_EVENT:
		printf("Ctrl-C event\n\n");
		//Beep(750, 300);
		return(TRUE);

		// CTRL-CLOSE: confirm that the user wants to exit.   
	case CTRL_CLOSE_EVENT:
		//Beep(600, 200);
		//printf("Ctrl-Close event\n\n");
		m_mdCollector.DisConnect();
		m_TradeChannel.DisConnect();

#ifdef WIN32
		if (m_hAppMutex != NULL)
		{
			ReleaseMutex(m_hAppMutex);
			CloseHandle(m_hAppMutex);
			m_hAppMutex = NULL;
		}
#endif
		return(TRUE);

		// Pass other signals to the next handler.   
	case CTRL_BREAK_EVENT:
		//Beep(900, 200);
		printf("Ctrl-Break event\n\n");
		return FALSE;

	case CTRL_LOGOFF_EVENT:
		//Beep(1000, 200);
		printf("Ctrl-Logoff event\n\n");
		return FALSE;

	case CTRL_SHUTDOWN_EVENT:
		//Beep(750, 500);
		printf("Ctrl-Shutdown event\n\n");
		return FALSE;

	default:
		return FALSE;
	}
}
#endif // WIN32

int main()
{

#ifdef WIN32
	if (!SetConsoleCtrlHandler((PHANDLER_ROUTINE)CtrlHandler, TRUE))
	{
		printf("\nThe Control Handler is uninstalled.\n");
		return 0;
	}
#endif // WIN32
	std::string strStrategyName = m_cwStategy.GetStrategyName();

	m_cwShow.AddLog("Welcome To Pandora Trader !!");
	m_cwShow.AddLog("Powered By PandoraTrader:");

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


	//设置mutex 防止一个程序开多个
	std::string strAppMutexName;
	strAppMutexName = m_szTdUserID;
	strAppMutexName.append("_");
	strAppMutexName += m_cwStategy.GetStrategyName().c_str();

#ifdef WIN32
	int  unicodeLen = ::MultiByteToWideChar(CP_ACP,	0, strAppMutexName.c_str(),	-1,	NULL, 0);
	wchar_t  * TAppMutexName = new wchar_t[unicodeLen + 1];
	memset(TAppMutexName, 0, (unicodeLen + 1)*sizeof(wchar_t));
	::MultiByteToWideChar(CP_ACP, 0, strAppMutexName.c_str(), -1,(LPWSTR)TAppMutexName,	unicodeLen);

	//声明互斥体，同一个名称只能声明一次，如果声明两次，将返回ERROR_ALREADY_EXISTS错误。
	m_hAppMutex = ::CreateMutex(NULL, TRUE, TAppMutexName);
	if (m_hAppMutex == NULL || GetLastError() == ERROR_ALREADY_EXISTS)
	{
		m_cwShow.AddLog("已经检测到一样的策略程序在运行，请不要重复打开策略程序！");
		m_cwShow.AddLog("程序将在5秒后自动退出！！");
		CloseHandle(m_hAppMutex);
		m_hAppMutex = NULL;
		delete [] TAppMutexName;

		int nCnt = 0;
		while (nCnt < 6)
		{
			cwSleep(1000);
			m_cwShow.AddLog("%d . ", nCnt);
			nCnt++;
		}
		
		return -1;
	}

	delete [] TAppMutexName;
#endif

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