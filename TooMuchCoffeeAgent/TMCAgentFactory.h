#pragma once
#include "WordleAgent/AgentFactory.h"
#include "TMCAgent.h"


// factory to create my custom agent
class TMCAgentFactory : public AgentFactory
{
public:

    // create my custom agent instance
    virtual std::unique_ptr<Agent> CreateAgent(Game& game) const
    {
        return std::make_unique<TMCAgent>(game);
    }
};