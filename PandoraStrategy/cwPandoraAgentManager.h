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


	typedef std::shared_ptr<cwPandoraPositionAgent>	cwPositionAgentPtr;

	enum cwPandoraAgentEnum : int
	{
		Enum_Agent_Postion = 0,
		Enum_Agent_Count
	};

	struct cwAgentData
	{
		int					AgentID;
		cwPandoraAgentEnum	AgentType;
		cwPositionAgentPtr	pPositionAgent;
	};
	typedef std::shared_ptr<cwAgentData> cwAgentDataPtr;

	cwAgentDataPtr			RegisterAgent(std::string instrumentid, cwPandoraAgentEnum agentEnum);

	inline virtual bool		HasAgent(std::string instrumentid);
protected:
	std::unordered_map<std::string, cwAgentDataPtr>		m_cwPandoraAgentDataMap;

};

