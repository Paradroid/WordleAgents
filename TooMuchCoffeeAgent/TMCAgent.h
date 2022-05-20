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
    
    struct score_compare {

        int score(const std::string& s) const {
            int sum = 0;
            for (char const& c : s) {
                sum += freqMap.at(c);
            }
            return sum;
        }

        bool operator()(const std::string& a, const std::string& b) const {
            int score1 = score(a);
            int score2 = score(b);
 
            return (score1 > score2) || ((score1 == score2) && (a > b));
        }
    } compare;

    //map of the frequency of each character in the wordlist
    static const std::map<char, int> freqMap;
 
    std::set<std::string, score_compare> m_word_set_sorted;
};

