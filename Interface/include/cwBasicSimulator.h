//////////////////////////////////////////////////////////////////////////////////
//*******************************************************************************
//---
//---	author: Wu Chang Sheng
//---
//---	CreateTime:	2018/12/12
//---
//---	VerifyTime:	2018/12/12
//---
//*******************************************************************************
//////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>
#include <vector>
#include <map>

#include "cwTradeCommonDefine.h"

class cwBasicSimulator
{
public:
	cwBasicSimulator();
	~cwBasicSimulator();

	virtual void InitialSimulator(const char * pConfigFilePath);
	std::string			m_strConfigFileFullPath;


	virtual int ReqUserMdLogin() { return 0; }
	virtual int ReqQryInstrument() { return 0; }

	virtual int ReqOrderInsert(cwOrderPtr pOrder) { return 0; }
	virtual int CancelOrder(cwOrderPtr pOrder) { return 0; }

	/// MD
	//订阅合约
	void		SubScribePrice(std::vector<std::string>& SubscribeInstrument);
	//取消订阅合约
	void		UnSubScribePrice(std::vector<std::string>& UnSubscribeInstrument);

	bool		GetIsSubscribedInstrument(char * Ins);
	size_t		GetSubscribedInstrumentCount() { return m_SubscribeInstrumentMap.size(); };
	///Trade

	///系统自用接口信息，勿动
	void			   SetMdSpi(void * pSpi);
	void			   SetTradeSpi(void *pSpi);

protected:
	void *		m_pMdSpi;
	void *		m_pTradeSpi;

	std::map<std::string, bool>	m_SubscribeInstrumentMap;
};

