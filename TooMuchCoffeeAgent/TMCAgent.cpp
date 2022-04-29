#include "TMCAgent.h"
#include "WordleAgent/Random.h"
#include <iostream>

TMCAgent::TMCAgent(Game& game)
	: Agent(game)
{
	// start with our own copy of the full word set
	m_word_set = GetGame().GetWordSet();
}



std::string TMCAgent::GetNextGuess()
{
	auto last = GetGame().GetLastGuessResult();
    if (last)
    {
        // update our knowledge based on the result of the last guess

        // first, remove the guess from the list as it obviously wasn't correct
        m_word_set.erase(last->guess);

        // for the result code associated with each letter of the guess
        for (size_t i = 0; i < last->result.size(); i++)
        {

            // if (this letter was in the correct position) then
            if (last->result[i] == Colour::GREEN)
            {
                // filter out any words which don't have this letter in that position
                for (WordSet::iterator iter = m_word_set.begin(); iter != m_word_set.end(); )
                {
                    // if (this letter of this word doesn't match this letter of the guess word) then
                    if ((*iter)[i] != last->guess[i])
                    {
                        iter = m_word_set.erase(iter);
                    }
                    else
                    {
                        ++iter;
                    }
                }
            }
            else if (last->result[i] == Colour::YELLOW)
            {
                //filter out any words which don't have this letter at all
                for (WordSet::iterator iter = m_word_set.begin(); iter != m_word_set.end(); )
                {
                    
                    size_t found = (*iter).find(last->guess[i]);

                    if (found == std::string::npos)
                    {
                        iter = m_word_set.erase(iter);
                    }
                    else
                    {
                        ++iter;
                    }
                }
            }
            else if (last->result[i] == Colour::BLACK)
            {
                //filter out any words which DO have this letter
                for (WordSet::iterator iter = m_word_set.begin(); iter != m_word_set.end(); )
                {
                    size_t found = (*iter).find(last->guess[i]);

                    if (found == std::string::npos)
                    {
                        ++iter;
                    }
                    else
                    {
                        iter = m_word_set.erase(iter);
                    }
                }
            }
        }


        //TODO choose best word from remaining
        // return a random item from our remaining word set
        int index = Random::GetRandomInt(0, static_cast<int>(m_word_set.size() - 1));
        return *std::next(m_word_set.begin(), index);
    }
    else
    {
        //first guess
        return std::string("SEARS");
    }
}
