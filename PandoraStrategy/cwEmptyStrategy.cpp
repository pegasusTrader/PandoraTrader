
#include "cwEmptyStrategy.h"

#ifndef cwDouble_EQ
#include <limits>
#define cwDouble_EQ (std::numeric_limits<double>::epsilon())
#endif // !cwDouble_EQ

#ifndef MAX_PATH
#define MAX_PATH          260
#endif // !MAX_PATH


cwEmptyStrategy::cwEmptyStrategy()
	: m_bShowPosition(true)
{
}


cwEmptyStrategy::~cwEmptyStrategy()
{
}

std::string cwEmptyStrategy::GetStrategyName()
{
	std::string strStrategyName("EmptyStrategy");
	if (m_strStrategyName.size() > 0)
	{
		strStrategyName.append("_");
		strStrategyName.append(m_strStrategyName);
	}
	return strStrategyName;
}

void cwEmptyStrategy::PriceUpdate(cwMarketDataPtr pPriceData)
{
	if (pPriceData.get() == NULL)
	{
		return;
	}
	m_strCurrentUpdateTime = pPriceData->UpdateTime;
	if ((!m_bStrategyReady))
	{
		return;
	}
}

void cwEmptyStrategy::InitialStrategy(const char * pConfigFilePath)
{
	if (pConfigFilePath == NULL
		|| strlen(pConfigFilePath) == 0)
	{
		char exeFullPath[MAX_PATH];
		memset(exeFullPath, 0, MAX_PATH);
#ifdef _MSC_VER
		TCHAR TexeFullPath[MAX_PATH];
		::GetModuleFileName(NULL, TexeFullPath, MAX_PATH);

		int iLength;
		//获取字节长度   
		iLength = WideCharToMultiByte(CP_ACP, 0, TexeFullPath, -1, NULL, 0, NULL, NULL);
		//将tchar值赋给_char    
		WideCharToMultiByte(CP_ACP, 0, TexeFullPath, -1, exeFullPath, iLength, NULL, NULL);

		m_strConfigFileFullPath = exeFullPath;
		std::size_t found = m_strConfigFileFullPath.find_last_of("/\\");
		m_strConfigFileFullPath = m_strConfigFileFullPath.substr(0, found);
		m_strConfigFileFullPath.append("\\EmptyStrategy.xml");
#else
		size_t cnt = readlink("/proc/self/exe", exeFullPath, MAX_PATH);
		if (cnt < 0 || cnt >= MAX_PATH)
		{
			printf("***Error***\n");
			exit(-1);
		}

		m_strConfigFileFullPath = exeFullPath;
		std::size_t found = m_strConfigFileFullPath.find_last_of("/\\");
		m_strConfigFileFullPath = m_strConfigFileFullPath.substr(0, found);
		m_strConfigFileFullPath.append("/EmptyStrategy.xml");
#endif		
	}
	else
	{
		m_strConfigFileFullPath = pConfigFilePath;
	}

}

void cwEmptyStrategy::SetStrategyReady()
{

	std::vector<std::string> SubscribeInstrument;

	for (auto it = m_InstrumentMap.begin(); it != m_InstrumentMap.end(); it++)
	{
		SubscribeInstrument.push_back(it->first);

		if (SubscribeInstrument.size() >= 10)
		{
			SubScribePrice(SubscribeInstrument);

			SubscribeInstrument.clear();
		}
	}
	
	SubScribePrice(SubscribeInstrument);

	//Call Basic Strategy;
	cwBasicStrategy::SetStrategyReady();
}
