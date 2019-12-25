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

	m_mdCollector.SetUserLoginField(" ", " ", " ");
	m_mdCollector.SubscribeMarketData(m_SubscribeInstrument);

	m_mdCollector.Connect(&m_PegasusSimulator);

	m_PegasusSimulator.SimulationStart();

	m_mdCollector.WaitForFinish();

	return 0;
}

int main()
{
	m_Strategy.InitialStrategy(NULL);

	m_PegasusSimulator.InitialStrategy(NULL);
	m_PegasusSimulator.SetMdSpi((void*)(&m_mdCollector));
	m_PegasusSimulator.SetTradeSpi((void*)&m_TradeChannel);

	m_TradeChannel.RegisterBasicStrategy(&m_Strategy);

	m_mdCollector.RegisterTradeSPI(&m_TradeChannel);
	m_mdCollector.RegisterStrategy(&m_Strategy);

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

