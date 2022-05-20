#include "TMCAgent.h"
#include "WordleAgent/Random.h"
#include <iostream>
#include <algorithm>

const std::map<char,int> TMCAgent::freqMap 
    = { { 'E', 6651 },
        { 'S', 6638 },
        { 'A', 5980 },
        { 'O', 4428 },
        { 'R', 4154 },
        { 'I', 3750 },
        { 'L', 3365 },
        { 'T', 3290 },
        { 'N', 2947 },
        { 'U', 2506 },
        { 'D', 2448 },
        { 'Y', 2066 },
        { 'C', 2016 },
        { 'P', 2013 },
        { 'M', 1975 },
        { 'H', 1752 },
        { 'G', 1638 },
        { 'B', 1624 },
        { 'K', 1492 },
        { 'F', 1110 },
        { 'W', 1037 },
        { 'V', 693 },
        { 'Z', 434 },
        { 'J', 291 },
        { 'X', 288 },
        { 'Q', 112 }, };


TMCAgent::TMCAgent(Game& game)
	: Agent(game)
{
    // start with our own copy of the full word set
	m_word_set = GetGame().GetWordSet();
    
    // copy of the set but sorted by frequency of letters.
    m_word_set_sorted.insert(m_word_set.begin(), m_word_set.end());

}



std::string TMCAgent::GetNextGuess()
{
	auto last = GetGame().GetLastGuessResult();
    if (last)
    {
        // update our knowledge based on the result of the last guess

        // first, remove the guess from the list as it obviously wasn't correct
        m_word_set_sorted.erase(last->guess);
        
//         std::cout << "Guess: " << last->guess << " (removed)" << std::endl;
        
        // for the result code associated with each letter of the guess
        for (size_t i = 0; i < last->result.size(); i++)
        {
            // if (this letter was in the correct position) then
            if (last->result[i] == Colour::GREEN)
            {
//                std::cout << last->guess[i] << " is GREEN" << std::endl;
//                std::cout << "Removing: ";
                // filter out any words which don't have this letter in that position
                for (WordSet::iterator iter = m_word_set_sorted.begin(); iter != m_word_set_sorted.end(); )
                {

                    // if (this letter of this word doesn't match this letter of the guess word) then
                    if ((*iter)[i] != last->guess[i])
                    {
//                        std::cout << *iter << ", ";
                        iter = m_word_set_sorted.erase(iter);
                    }
                    else
                    {
                        ++iter;
                    }
                }
            }
            else if (last->result[i] == Colour::YELLOW)
            {
//                std::cout << last->guess[i] << " is YELLOW" << std::endl;
//                std::cout << "Removing: ";
                //filter out any words which don't have this letter in any position or have this letter in this position
                for (WordSet::iterator iter = m_word_set_sorted.begin(); iter != m_word_set_sorted.end(); )
                {
                    
                    size_t found = (*iter).find(last->guess[i]);

                    if (found == std::string::npos)
                    {   //letter does not occur in this word at all
//                        std::cout << *iter << ", ";
                        iter = m_word_set_sorted.erase(iter);
                    }
                    else if ((*iter)[i] == last->guess[i])
                    {   //letter is in this position
//                        std::cout << *iter << ", ";
                        iter = m_word_set_sorted.erase(iter);
                    }
                    else
                    {
                        //letter exists in another position
                        ++iter;
                    }
                }
            }
            else if (last->result[i] == Colour::BLACK)
            {
//                std::cout << last->guess[i] << " is BLACK" << std::endl;
//                std::cout << "Removing: ";
                auto ch = last->guess[i];
                auto item = last->letters.find(ch);
                if (item != last->letters.end()) {
                    auto color = item->second;
                    if (color != Colour::GREEN) {
                        //filter out any words which DO have this letter, if it's not already marked as green
                        for (WordSet::iterator iter = m_word_set_sorted.begin(); iter != m_word_set_sorted.end(); )
                        {
                            size_t found = (*iter).find(last->guess[i]);
                            if (found == std::string::npos)
                            {
                                ++iter;
                            }
                            else
                            {
//                                std::cout << *iter << ", ";
                                iter = m_word_set_sorted.erase(iter);
                            }
                        }
                    }
                }
            }
//            std::cout << m_word_set.size() << " words remaining" << std::endl;
        }
        // debugging
        //std::cout << "m_word_set_sorted size = " << m_word_set_sorted.size() << std::endl;


        if (m_word_set_sorted.empty()) {
            std::cout << "Deleted all the words, OOPS!" << std::endl;
            return "";
        }
        else
        {   //return the next highest scoring word
            return *m_word_set_sorted.begin();
        }
    }
    else
    {
        //first guess

        return std::string("SOARE");
    }
}
