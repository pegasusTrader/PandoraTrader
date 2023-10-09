#include "cwMarKetDataReceiverToLocalKindle.h"
#include "cwTimeStamp.h"
#include "csvparser.h"
#include <fstream>


cwMarKetDataReceiverToLocalKindle::cwMarKetDataReceiverToLocalKindle()
	: m_bWorkingThreadRun(false)
{
}


cwMarKetDataReceiverToLocalKindle::~cwMarKetDataReceiverToLocalKindle()
{
}

std::string cwMarKetDataReceiverToLocalKindle::GetStrategyName()
{
	std::string strStrategyName("cwMarKetDataReceiverToLocalKindle");
	if (m_strStrategyName.size() > 0)
	{
		strStrategyName.append("_");
		strStrategyName.append(m_strStrategyName);
	}
	return strStrategyName;
}

void cwMarKetDataReceiverToLocalKindle::PriceUpdate(cwMarketDataPtr pPriceData)
{
	//cwMarketDataReceiver::PriceUpdate(pPriceData);


}

void cwMarKetDataReceiverToLocalKindle::OnBar(cwMarketDataPtr pPriceData, int iTimeScale, cwBasicKindleStrategy::cwKindleSeriesPtr pKindleSeries)
{
	cwAUTOMUTEX mt(m_DequeMutex, true);
	
	auto it = m_KindleFinishedIndex.find(pPriceData->InstrumentID);
	if (it == m_KindleFinishedIndex.end())
	{
		auto ret = m_KindleFinishedIndex.insert(
			std::pair<std::string, WriterControlFiled>(pPriceData->InstrumentID, WriterControlFiled()));
		it = ret.first;
	}

	it->second.TotalCount = pKindleSeries->GetKindleSize() > 0 ? pKindleSeries->GetKindleSize() - 1 : 0;


	if (pKindleSeries->m_bIsNewKindle)
	{
		it->second.Finished = (int)(pKindleSeries->GetKindleSize()) - 2;
	}
	else
	{
		if (pKindleSeries->m_bThisFinished)
		{
			it->second.Finished = (int)(pKindleSeries->GetKindleSize()) - 1;
		}
	}
}

void cwMarKetDataReceiverToLocalKindle::OnReady()
{
	SetWriteIndexInfoCacheToFile(true);

	//cwMarketDataReceiver::OnReady();
	
	int iInstrumentIndex = 1;

	for (auto itIns = m_InstrumentMap.begin();
		itIns != m_InstrumentMap.end(); itIns++)
	{
	}

	if (!m_bWorkingThreadRun)
	{
		m_bWorkingThreadRun = true;

		m_WorkingThread = std::thread(&cwMarKetDataReceiverToLocalKindle::WorkingThread, this);
	}

}

void cwMarKetDataReceiverToLocalKindle::InitialStrategy(const char * pConfigFilePath)
{
	cwMarketDataReceiver::InitialStrategy(pConfigFilePath);
	
	struct stat buf;
	if (stat(m_strWorkingPath.c_str(), &buf) != 0)
	{
#ifdef _MSC_VER
		_mkdir(m_strWorkingPath.c_str());
#else
		mkdir(m_strWorkingPath.c_str(), 0755);
#endif
	}
}

bool cwMarKetDataReceiverToLocalKindle::InitialHisKindleFromHisKindleFolder(const char* szHisFolder)
{
	cwBasicKindleStrategy::InitialHisKindleFromHisKindleFolder(szHisFolder);

	m_strWorkingPath = szHisFolder;
	if (m_strWorkingPath.size() > 0)
	{
		if (m_strWorkingPath.at(m_strWorkingPath.size() - 1) != '\\'
			&& m_strWorkingPath.at(m_strWorkingPath.size() - 1) != '/')
		{
#ifdef _MSC_VER
			m_strWorkingPath.append("\\");
#else
			m_strWorkingPath.append("/");
#endif
		}
	}
	return true;
}

#define KINDLEWRITEBUFFERSIZE 2048
void cwMarKetDataReceiverToLocalKindle::WorkingThread()
{
	{
		//创建文件夹
		struct stat buf;

		for (auto it = m_InstrumentMap.begin(); it != m_InstrumentMap.end(); it++)
		{
			if (CW_FTDC_PC_Futures != it->second->ProductClass)
			{
				continue;
			}

			std::string str = m_strWorkingPath;
			str.append(it->second->ProductID);

			if (stat(str.c_str(), &buf) != 0)
			{
#ifdef _MSC_VER
				_mkdir(str.c_str());
#else
				mkdir(str.c_str(), 0755);
#endif
			}

#ifdef _MSC_VER
			str.append("\\");
#else
			str.append("/");
#endif
			str.append(it->second->InstrumentID);
			str.append("_1m.csv");


			m_KindleFileMap.insert(std::pair<std::string, std::string>(it->second->InstrumentID, str));

			SubcribeKindle(it->second->InstrumentID, cwKINDLE_TIMESCALE_1MIN);

			//SubcribeIndexPriceKindle

			auto pKindle = SubcribeIndexKindle(it->second->ProductID, cwKINDLE_TIMESCALE_1MIN);
			str = m_strWorkingPath;
			str.append(it->second->ProductID);

#ifdef _MSC_VER
			str.append("\\");
#else
			str.append("/");
#endif

			str.append(pKindle->GetInstrumentID());
			str.append("_1m.csv");

			m_KindleFileMap.insert(std::pair<std::string, std::string>(pKindle->GetInstrumentID(), str));
		}
	}

	int iWriteCout = 0, iNothingToWrite = 0;
	while (m_bWorkingThreadRun)
	{
		cwSleep(1000);

		iWriteCout = 0;

		char KindleWriteBuffer[KINDLEWRITEBUFFERSIZE];

		cwAUTOMUTEX mt(m_DequeMutex, true);
		for (auto it = m_KindleFinishedIndex.begin();
			it != m_KindleFinishedIndex.end(); it++)
		{
			if (it->second.WriteCount >= it->second.Finished)
			{
				it->second.NothingToWriteCount++;
				continue;
			}

			it->second.NothingToWriteCount = 0;
			iWriteCout++;

			//设置mutex 防止一个程序开多个
			std::string strAppMutexName = it->first;
			strAppMutexName.append("_Kindle_1m");

#ifdef _MSC_VER
			HANDLE  m_hAppMutex(NULL);
#endif

#ifdef _MSC_VER
			int  unicodeLen = ::MultiByteToWideChar(CP_ACP, 0, strAppMutexName.c_str(), -1, NULL, 0);
			wchar_t* TAppMutexName = new wchar_t[unicodeLen + 1];
			memset(TAppMutexName, 0, (unicodeLen + 1) * sizeof(wchar_t));
			::MultiByteToWideChar(CP_ACP, 0, strAppMutexName.c_str(), -1, (LPWSTR)TAppMutexName, unicodeLen);

			//声明互斥体，同一个名称只能声明一次，如果声明两次，将返回ERROR_ALREADY_EXISTS错误。

			int nCnt = 0;
			while (nCnt < 3)
			{
				m_hAppMutex = ::CreateMutex(NULL, TRUE, TAppMutexName);
				if (m_hAppMutex == NULL || GetLastError() == ERROR_ALREADY_EXISTS)
				{
					cwSleep(1000);
					m_cwShow.AddLog("%d . ", nCnt);
					nCnt++;

					continue;
				}
				else
				{
					break;
				}
			}
			delete[] TAppMutexName;

#else
		
#endif

			auto FileIt = m_KindleFileMap.find(it->first);
			if (FileIt != m_KindleFileMap.end()
				&& FileIt->second.size() != 0)
			{
				bool bNew = false;
				{
					struct stat buf;
					if (stat(FileIt->second.c_str(), &buf) != 0)
					{
						bNew = true;
					}
				}

				std::fstream		m_Log;
				m_Log.open(FileIt->second.c_str(), std::fstream::out | std::fstream::app | std::ios::ate);

				if (m_Log.good())
				{
					if(bNew)
					{
						m_Log << "TimeStamp,time,Open,High,Low,Close,Volume,LastVolume,TurnOver,LastTurnOver,OpenInterest,HighTimeStamp,LowTimeStamp\n";
					}
					

					auto pKindleSeries = GetKindleSeries(it->first.c_str(), cwKINDLE_TIMESCALE_1MIN);
					if (pKindleSeries.get() != nullptr)
					{
						std::deque<cwKindleStickPtr> KindleStickDeque;
						pKindleSeries->GetKindleSerise(KindleStickDeque);

						for (int i = it->second.WriteCount + 1;
							i <= it->second.Finished; i++)
						{
							if (i < 0)
							{
								continue;
							}

							if (i >= (int)(KindleStickDeque.size()))
							{
								break;
							}

							cwKindleStickPtr pKindle = KindleStickDeque.at(i);
							if (pKindle.get() != nullptr)
							{
								memset(KindleWriteBuffer, 0, KINDLEWRITEBUFFERSIZE * sizeof(char));
#ifdef _MSC_VER
								sprintf_s(KindleWriteBuffer, "%lld,%s,%.3f,%.3f,%.3f,%.3f,%lld,%lld,%.0f,%.0f,%.0f,%lld,%lld",
									pKindle->StartTime, pKindle->szStartTime,
									pKindle->Open, pKindle->High, pKindle->Low, pKindle->Close,
									pKindle->TotalVolume, pKindle->LastVolume,
									pKindle->TotalTurnOver, pKindle->LastTurnOver,
									pKindle->OpenInterest,
									pKindle->HighTime, pKindle->LowTime);
#else
								sprintf(KindleWriteBuffer, "%lld,%s,%.3f,%.3f,%.3f,%.3f,%lld,%lld,%.0f,%.0f,%.0f,%lld,%lld",
									pKindle->StartTime, pKindle->szStartTime,
									pKindle->Open, pKindle->High, pKindle->Low, pKindle->Close,
									pKindle->TotalVolume, pKindle->LastVolume,
									pKindle->TotalTurnOver, pKindle->LastTurnOver,
									pKindle->OpenInterest,
									pKindle->HighTime, pKindle->LowTime);
#endif
								m_Log << KindleWriteBuffer << '\n';

								it->second.WriteCount = i;
							}
						}
					}

					m_Log.close();
				}

			}

#ifdef _MSC_VER
			ReleaseMutex(m_hAppMutex);
			CloseHandle(m_hAppMutex);
			m_hAppMutex = NULL;

#endif
		}


		for (auto it = m_KindleFinishedIndex.begin();
			it != m_KindleFinishedIndex.end(); it++)
		{
			if (it->second.NothingToWriteCount > 2 * cwKINDLE_TIMESCALE_1MIN)
			{
				it->second.Finished = it->second.TotalCount;
				it->second.NothingToWriteCount = 0;
			}
		}

		mt.unlock();
		if (iWriteCout == 0)
		{
			iNothingToWrite++;
		}
	}
}


