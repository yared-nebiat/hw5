#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool combinations(
    int currDay,
    int numDays,
    int numWorkers,
    vector<size_t>& shifts,
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
);


// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below

    int numDays = avail.size();
    int numWorkers = avail[0].size();

    vector<size_t> shifts(numWorkers, 0);

    for(int i=0; i<numDays; i++) {
        sched.push_back(vector<Worker_T>());
    }    

    return combinations(0, numDays, numWorkers, shifts, avail, dailyNeed, maxShifts, sched);

}



bool combinations(
    int currDay,
    int numDays,
    int numWorkers,
    vector<size_t>& shifts,
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
) 
{

    // if I reached the end
    if(currDay == numDays) {
        return true;
    }


    for(int i=0; i<numWorkers; i++) {
        // if there are workers needed and the worker is available and they haven't maxed shifts
        if(dailyNeed > sched[currDay].size() && avail[currDay][i] && shifts[i] < maxShifts) {
            sched[currDay].push_back(i);
            shifts[i]++;
        }

        if(dailyNeed == sched[currDay].size()) {
            if(combinations(currDay+1, numDays, numWorkers, shifts, avail, dailyNeed, maxShifts, sched)) return true;
            shifts[i]--;
            sched[currDay].pop_back();
        }
    }

    return false;


}