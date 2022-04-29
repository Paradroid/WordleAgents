#pragma once
#include "framework.h"
#include "WordleAgent/Agent.h"

class TMCAgent : public Agent
{
public:

    // constructor.
    TMCAgent(Game& game);

    // return the agent's next guess at the solution.
    virtual std::string GetNextGuess();

private:

    WordSet m_word_set;
};

