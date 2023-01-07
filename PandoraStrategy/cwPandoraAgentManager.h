//////////////////////////////////////////////////////////////////////////////////
//*******************************************************************************
//---
//---	Create by Wu Chang Sheng on June.26th 2020
//---
//--	Copyright (c) by Wu Chang Sheng. All rights reserved.
//--    Consult your license regarding permissions and restrictions.
//--
//*******************************************************************************
//////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "cwAgentManager.h"
#include "cwPandoraPositionAgent.h"

class cwPandoraAgentManager :
	public cwAgentManager
{
public:
	cwPandoraAgentManager();
	~cwPandoraAgentManager();

#ifdef _MSC_VER
#pragma region CommenDefine
#endif // _MSC_VER
	typedef std::shared_ptr<cwPandoraPositionAgent>		cwPositionAgentPtr;

	enum cwPandoraAgentEnum : int
	{
		Enum_Agent_Postion = 0,					//cwPandoraPositionAgent		用算法来管理持仓
		Enum_Agent_TakeOver,					//cwPandoraTakeOverAgent		用算法来接管持仓，自动止盈止损,未完成
		Enum_Agent_Prerequisite,				//cwPandoraPrerequisiteAgent	用算法来管理报单，如果不满足要求条件则撤单，未完成
		Enum_Agent_ProfitLost,					//cwPandoraProfitLostAgent		用算法来管理报单，成交后，自动报出止盈单;如遇到止损，则报止损单，未完成
		Enum_Agent_TWAP,
		Enum_Agent_VWAP,
		Enum_Agent_Count
	};

	struct cwAgentData
	{
		int							AgentID;			//代理人编号
		cwPandoraAgentEnum			AgentType;			//代理人类型
		cwPositionAgentPtr			pPositionAgent;		//持仓管理代理人
	};
	typedef std::shared_ptr<cwAgentData> cwAgentDataPtr;
#ifdef _MSC_VER
#pragma endregion
#endif

	cwAgentDataPtr			RegisterAgent(std::string instrumentid, cwPandoraAgentEnum agentEnum);

public:
	//key InstrumentID, key :AgentID value:agentData
	std::unordered_map<std::string, std::unordered_map<int, cwAgentDataPtr>>		m_cwPandoraAgentDataMap;

};

