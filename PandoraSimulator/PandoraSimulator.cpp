// RDPlatform.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"

#include "cwPegasusSimulator.h"
#include "cwSimMdSpi.h"
#include "cwSimTradeSpi.h"
#include "cwStrategyDemo.h"
#include "cwBasicCout.h"

#ifdef _MSC_VER
#pragma comment(lib, "cwCTPDLL.lib")
#pragma comment(lib, "cwStrategys.lib")
#pragma comment(lib, "PandoraStrategy.lib")
#pragma comment(lib, "tinyxml.lib")
#endif // WIN32

cwBasicCout				m_cwShow;

cwFtdcBrokerIDType		m_szMdBrokerID;
cwFtdcUserIDType		m_szMdUserID;
cwFtdcPasswordType		m_szMdPassWord;

cwPegasusSimulator		m_PegasusSimulator;
cwSimMdSpi				m_mdCollector;
cwSimTradeSpi			m_TradeChannel;
cwStrategyDemo			m_Strategy;

std::vector<std::string> m_SubscribeInstrument;

std::string				m_strStrategyConfigFile;

unsigned int PriceServerThread()
{

	m_TradeChannel.Connect(&m_PegasusSimulator);


	//m_SubscribeInstrument.push_back("zn1904");
	//m_SubscribeInstrument.push_back("SR909");

	m_mdCollector.SetUserLoginField(m_szMdBrokerID, m_szMdUserID, m_szMdPassWord);
	m_mdCollector.SubscribeMarketData(m_SubscribeInstrument);

	m_mdCollector.Connect(&m_PegasusSimulator);

	m_PegasusSimulator.SimulationStart();

	m_mdCollector.WaitForFinish();

	return 0;
}

int main()
{
	char exeFullPath[MAX_PATH];
	memset(exeFullPath, 0, MAX_PATH);
	std::string strFullPath;
#ifdef WIN32
	WCHAR TexeFullPath[MAX_PATH] = { 0 };

	GetModuleFileName(NULL, TexeFullPath, MAX_PATH);
	int iLength;
	//获取字节长度   
	iLength = WideCharToMultiByte(CP_ACP, 0, TexeFullPath, -1, NULL, 0, NULL, NULL);
	//将tchar值赋给_char    
	WideCharToMultiByte(CP_ACP, 0, TexeFullPath, -1, exeFullPath, iLength, NULL, NULL);
#else
	size_t cnt = readlink("/proc/self/exe", exeFullPath, MAX_PATH);
	if (cnt < 0 || cnt >= MAX_PATH)
	{
		printf("***Error***\n");
		exit(-1);
	}
#endif // WIN32

	strFullPath = exeFullPath;
	strFullPath = strFullPath.substr(0, strFullPath.find_last_of("/\\"));

#ifdef WIN32
	strFullPath.append("\\PandoraSimulatorConfig.xml");
#else
	strFullPath.append("/PandoraSimulatorConfig.xml");
#endif // WIN32


	m_Strategy.InitialStrategy(NULL);

	m_PegasusSimulator.InitialSimulator(strFullPath.c_str());
	m_PegasusSimulator.SetMdSpi((void*)(&m_mdCollector));
	m_PegasusSimulator.SetTradeSpi((void*)&m_TradeChannel);

	m_TradeChannel.RegisterBasicStrategy(dynamic_cast<cwBasicStrategy*>(&m_Strategy));

	m_mdCollector.RegisterTradeSPI(dynamic_cast<cwBasicTradeSpi*>(&m_TradeChannel));
	m_mdCollector.RegisterStrategy(dynamic_cast<cwBasicStrategy*>(&m_Strategy));

	std::thread m_PriceServerThread = std::thread(PriceServerThread);
	//std::thread m_TradeServerThread = std::thread(TradeServerThread);

	while (true)
	{
		cwSleep(3000);
		m_cwShow.AddLog("%s", m_Strategy.m_strCurrentUpdateTime.c_str());
		//std::cout << m_Strategy.m_strCurrentUpdateTime.c_str() << '\n';
	}
    return 0;
}

