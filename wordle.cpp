#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here

void combinations(
    std::string& word,
    size_t idx,
    int fixedFound,
    const int& fixedCount,
    std::set<std::string>& matches,
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict);


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here

    std::set<std::string> matches;
    std::string word = in;
    
    int fixedCount = 0;
    for(size_t j=0; j<word.length(); j++) {
        if(word[j] != '-') {
            fixedCount++;
        }
    }
    
    combinations(word, 0, 0, fixedCount, matches, in, floating, dict);

    return matches;

}

// Define any helper functions here

void combinations(
    std::string& word,
    size_t idx,
    int fixedFound,
    const int& fixedCount,
    std::set<std::string>& matches,
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // -i--, "nd"

    // put recursive step(go to next location) in the for loop (pick a letter)

    // everytime I make a word, I should check if the word contains the floaters
    // then check if the word exists before adding it to the set

    if(idx == word.length()) {
        // if it contains the floaters and is a word, add to set
        // return

        /*
        string temp = word;
        for(size_t i=0; i<floating.length(); i++) {
            size_t found = temp.find(floating[i]);
            if(found == std::string::npos) {
                return;
            }
            temp[found] = '-';
        }
        */

        if(dict.find(word) != dict.end()) {
            matches.insert(word);
        }
        return;
    }

    if(word[idx] != '-' && word[idx] == in[idx]) {
        //go to next pos
        //return
        combinations(word, idx+1, fixedFound+1, fixedCount, matches, in, floating, dict);
        return;
    }


    for(char i=97; i<123; i++) {
        // set the char at curr location to i
        // when idx > (len(word) - len(floating))
        // there should always be idx - (len(word) - len(floating)) floating chars found
        // recurse to next location
        
        word[idx] = i;

        int fixedRemaining = fixedCount - fixedFound;

        if(idx >= word.length() - floating.length() - fixedRemaining) {
            int needed = idx - (word.length() - floating.length() - fixedRemaining) + 1;
            int numFound = 0;

            string temp = word;
            // use a map instead of the for loop?
            for(size_t j=0; j<floating.length(); j++) {
                size_t found = temp.find(floating[j]);
                if(found != std::string::npos) {
                    temp[found] = '-';
                    numFound++;
                    if(numFound == needed) {
                        break;
                    }
                }
            }

            if(numFound < needed) {
                /*
                for(size_t j=0; j<floating.length(); j++) {
                    size_t found = word.find(floating[j]);
                    if(found == std::string::npos) {
                        word[idx] = floating[j];
                        combinations(word, idx+1, fixedFound, fixedCount, matches, in, floating, dict);
                    }
                }
                */
                continue; // only check the floating chars to be faster?
            }
        }

        combinations(word, idx+1, fixedFound, fixedCount, matches, in, floating, dict);
        
    }

}
