#pragma once
#include "cwMarketDataReceiver.h"
#include "cwBasicCout.h"
#include <string>


class cwMarKetDataReceiverToLocalKindle :
	public cwMarketDataReceiver
{
public:
	cwMarKetDataReceiverToLocalKindle();
	~cwMarKetDataReceiverToLocalKindle();

	std::string  GetStrategyName();

	//MarketData SPI
	///行情更新
	virtual void PriceUpdate(cwMarketDataPtr pPriceData);

	//当生成一根新K线的时候，会调用该回调
	virtual void			OnBar(cwMarketDataPtr pPriceData, int iTimeScale, cwBasicKindleStrategy::cwKindleSeriesPtr pKindleSeries);
	virtual void			OnReady();

	void InitialStrategy(const char * pConfigFilePath);

	bool					InitialHisKindleFromHisKindleFolder(const char* szHisFolder);

	cwBasicCout				m_cwShow;

	struct WriterControlFiled
	{
		int TotalCount;				//总数
		int Finished;				//已完成（可写入）数

		int WriteCount;				//已写入数
		int NothingToWriteCount;	//经xx次，无内容可写入数


		WriterControlFiled()
		{
			TotalCount = 0;
			Finished = -1;

			WriteCount = -1;
			NothingToWriteCount = 0;
		}
	};


	std::string									m_strWorkingPath;
	std::string									m_strExeFolderPath;

	std::unordered_map<std::string, std::string> m_KindleFileMap;


	cwMUTEX													m_DequeMutex;
	std::unordered_map<std::string, WriterControlFiled>		m_KindleFinishedIndex;

	std::thread									m_WorkingThread;			//工作区工作线程
	volatile std::atomic<bool>					m_bWorkingThreadRun;		//工作区线程运行状态

	void										WorkingThread();



};

