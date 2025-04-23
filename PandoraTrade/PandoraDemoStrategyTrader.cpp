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


//�����򻥳����������ж��Ƿ��иó���������
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


#ifdef WIN32
#define GetCharElement(Type, Name) const char * psz##Name = Element->Attribute(#Name);\
if (psz##Name != NULL)\
{\
	strcpy_s(m_sz##Type##Name, psz##Name);\
}
#else
#define GetCharElement(Type, Name) const char * psz##Name = Element->Attribute(#Name);\
if (psz##Name != NULL)\
{\
	strcpy(m_sz##Type##Name, psz##Name);\
}
#endif // WIN32

namespace fs = std::filesystem;


bool ReadXmlConfigFile()
{
	// ����һ�� property_tree ����
	boost::property_tree::ptree pt;

	// �� XML �ļ��ж�ȡ����
	boost::property_tree::read_xml("example.xml", pt);

	// ���� XML �е�����
	std::string name = pt.get<std::string>("root.person.name");
	int age = pt.get<int>("root.person.age");

	m_cwShow.AddLog("Get Account Config File : %s");

	TiXmlDocument doc(strFullPath.c_str());
	bool loadOkay = doc.LoadFile(TIXML_ENCODING_LEGACY);

	if (!loadOkay)
	{
		m_cwShow.AddLog("Load PandoraTraderConfig File Failed ! ");
		return false;
	}

	TiXmlNode* RootNode = doc.RootElement();
	if (RootNode != NULL)
	{
		//Read General
		TiXmlNode* ChildNode = RootNode->FirstChild("User");
		if (ChildNode != NULL)
		{
			TiXmlNode* SubChildNode = ChildNode->FirstChild("MarketDataServer");
			if (SubChildNode != NULL)
			{
				TiXmlElement * Element = SubChildNode->ToElement();
				GetCharElement(Md, Front);
				GetCharElement(Md, BrokerID);
				GetCharElement(Md, UserID);
				GetCharElement(Md, PassWord);
			}

			SubChildNode = ChildNode->FirstChild("TradeServer");
			if (SubChildNode != NULL)
			{
				TiXmlElement * Element = SubChildNode->ToElement();
				GetCharElement(Td, Front);
				GetCharElement(Td, BrokerID);
				GetCharElement(Td, UserID);
				GetCharElement(Td, PassWord);
				GetCharElement(Td, ProductInfo);
				GetCharElement(Td, AppID);
				GetCharElement(Td, AuthCode);
				GetCharElement(Td, DllPath);
			}
		}

		ChildNode = RootNode->FirstChild("Subscription");
		if (ChildNode != NULL)
		{
			TiXmlNode* SubChildNode = ChildNode->FirstChild("Instrument");
			while (SubChildNode != NULL)
			{
				TiXmlElement * Element = SubChildNode->ToElement();
				const char * pszTemp = Element->Attribute("ID");
				if (pszTemp != NULL)
				{
					m_SubscribeInstrument.push_back(pszTemp);
				}
				SubChildNode = SubChildNode->NextSibling("Instrument");
			}
		}

		m_strStrategyConfigFile.clear();
		ChildNode = RootNode->FirstChild("StrategyConfigFile");
		if (ChildNode != NULL)
		{
			TiXmlElement * Element = ChildNode->ToElement();
			const char * pszTemp = Element->GetText();
			if (pszTemp != NULL)
			{
				m_strStrategyConfigFile = pszTemp;
			}
		}

		m_strHisDataFolder.clear();
		ChildNode = RootNode->FirstChild("HisDataFolder");
		if (ChildNode != nullptr)
		{
			TiXmlElement * Element = ChildNode->ToElement();
			const char * pszTemp = Element->GetText();
			if (pszTemp != NULL)
			{
				m_strHisDataFolder = pszTemp;
			}
		}
	}

	return true;
}

void ResetParameter()
{
	memset(m_szMdFront, 0, sizeof(m_szMdFront));
	memset(m_szMdBrokerID, 0, sizeof(m_szMdBrokerID));
	memset(m_szMdUserID, 0, sizeof(m_szMdUserID));
	memset(m_szMdPassWord, 0, sizeof(m_szMdPassWord));

	memset(m_szTdFront, 0, sizeof(m_szTdFront));
	memset(m_szTdBrokerID, 0, sizeof(m_szTdBrokerID));
	memset(m_szTdUserID, 0, sizeof(m_szTdUserID));
	memset(m_szTdPassWord, 0, sizeof(m_szTdPassWord));
	memset(m_szTdProductInfo, 0, sizeof(m_szTdProductInfo));
	memset(m_szTdAppID, 0, sizeof(m_szTdAppID));
	memset(m_szTdAuthCode, 0, sizeof(m_szTdAuthCode));
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
		m_cwShow.AddLog("The Program will shut down in 5s��");

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


	//����mutex ��ֹһ�����򿪶��
	std::string strAppMutexName;
	strAppMutexName = m_szTdUserID;
	strAppMutexName.append("_");
	strAppMutexName += m_cwStategy.GetStrategyName().c_str();

#ifdef WIN32
	int  unicodeLen = ::MultiByteToWideChar(CP_ACP,	0, strAppMutexName.c_str(),	-1,	NULL, 0);
	wchar_t  * TAppMutexName = new wchar_t[unicodeLen + 1];
	memset(TAppMutexName, 0, (unicodeLen + 1)*sizeof(wchar_t));
	::MultiByteToWideChar(CP_ACP, 0, strAppMutexName.c_str(), -1,(LPWSTR)TAppMutexName,	unicodeLen);

	//���������壬ͬһ������ֻ������һ�Σ�����������Σ�������ERROR_ALREADY_EXISTS����
	m_hAppMutex = ::CreateMutex(NULL, TRUE, TAppMutexName);
	if (m_hAppMutex == NULL || GetLastError() == ERROR_ALREADY_EXISTS)
	{
		m_cwShow.AddLog("�Ѿ���⵽һ���Ĳ��Գ��������У��벻Ҫ�ظ��򿪲��Գ���");
		m_cwShow.AddLog("������5����Զ��˳�����");
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