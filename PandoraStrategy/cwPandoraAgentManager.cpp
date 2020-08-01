#include "cwPandoraAgentManager.h"



cwPandoraAgentManager::cwPandoraAgentManager()
{
}


cwPandoraAgentManager::~cwPandoraAgentManager()
{
}

cwPandoraAgentManager::cwAgentDataPtr cwPandoraAgentManager::RegisterAgent(std::string instrumentid, cwPandoraAgentEnum agentEnum)
{
	cwAgentDataPtr pPandoraAgentMrg;
	if (agentEnum >= Enum_Agent_Count)
	{
		return pPandoraAgentMrg;
	}

	cwAgentDataPtr pAgentData = std::make_shared<cwAgentData>();
	if (pAgentData.get() == NULL)
	{
		return pPandoraAgentMrg;
	}

	pAgentData->AgentType = agentEnum;

	switch (agentEnum)
	{
	case cwPandoraAgentManager::Enum_Agent_Postion:
	{
		pAgentData->pPositionAgent = std::make_shared<cwPandoraPositionAgent>();
		if (pAgentData->pPositionAgent.get() == NULL)
		{
			return pPandoraAgentMrg;
		}
		pAgentData->pPositionAgent->m_strInstrumentID = instrumentid;
		pAgentData->AgentID = cwAgentManager::RegisterAgent(instrumentid, dynamic_cast<cwBasicAgent*>(pAgentData->pPositionAgent.get()), true);
	}
		break;
	case cwPandoraAgentManager::Enum_Agent_Count:
	default:
		return pPandoraAgentMrg;
		break;
	}

	auto it = m_cwPandoraAgentDataMap.insert(std::pair<std::string, cwAgentDataPtr> (instrumentid, pAgentData));
	if (!it.second)
	{
		it.first->second = pAgentData;
	}

	return pAgentData;
}

inline bool cwPandoraAgentManager::HasAgent(std::string instrumentid)
{
	auto it = m_cwPandoraAgentDataMap.find(instrumentid);
	if (it != m_cwPandoraAgentDataMap.end())
	{
		switch (it->second->AgentType)
		{
		case cwPandoraAgentManager::Enum_Agent_Postion:
		{
			if (it->second->pPositionAgent.get() != NULL)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		break;
		case cwPandoraAgentManager::Enum_Agent_Count:
		default:
			break;
		}
		return false;
	}
	else
	{
		return false;
	}
}
