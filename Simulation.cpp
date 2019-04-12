//
//  Simulation.cpp
//  ProjectTrains
//
//  Created by Olga on 2018-06-01.
//  Copyright © 2018 Olga. All rights reserved.
//

#include <algorithm>
#include <iostream>
#include "Simulation.hpp"
using namespace std;

/* The class constructor provides values for the class members stored as constants. Values may change under program execution. */

Simulation::Simulation() {
    interval = SIM_INTERVAL;
    currentTime = START_TIME;
    
    intervalStartTime = START_TIME;
    intervalStopTime = intervalStartTime + interval;
    
    simStopTime = STOP_TIME;
    
    startShowingTime = START_TIME;
}

/* The class destructor deletes remaining events in queue. This functionality is necessary to deal with events that are left in the event queue in case simulation StopTime is scheduled before the last event time. */

Simulation::~Simulation() {
    while(!eventQueue.empty()) {
        Event *nextEvent = eventQueue.top();
        eventQueue.pop();
        
        delete nextEvent;
    }
}

/* runInterval:
 * -----------
 * This function sends events within a specific interval for processing. Interval start and stop times are decided by the class members. The finction updates start and stop times of the next interval, as well as current simulation time and next event time.
 * The function also keeps track of previous values for interval stop time, current simulation time and next event time. This is done with purpose to set simulation status to "over midnight" when one of the values goes past 00:00. Changing simulation status to "over midnight" allows avoiding erroneous time comparison after 00:00.
 * The function is handling "visible" status depending on whether next event time is before or after the StartShowingTime. */

void Simulation::runInterval() {
    
    Time currentTimeOld = currentTime;
    Time intervalStopTimeOld = intervalStopTime;
    Time eventTimeOld = eventTime;
    
    while(!eventQueue.empty() && continueRunInterval()) {
        
        Event *nextEvent = eventQueue.top();
        
        eventTimeOld = eventTime;
        eventTime = nextEvent->getTime(); //get next event time
        
        if(eventTime < eventTimeOld) { //checking for 'past midninght' condition
            pastMidnigh = true;
        }
        
        if(continueRunSim()) {
            if(eventTime > startShowingTime || pastMidnigh) { //checking for 'invisible' condition
                visible = true;
            }
            eventQueue.pop();
            
            currentTimeOld = currentTime;
            currentTime = eventTime;
            
            nextEvent->processEvent(); //process event
            delete nextEvent;
        }
        else {
            currentTimeOld = currentTime;
            currentTime = intervalStopTime;
        }
        
        if(currentTime < currentTimeOld) { //checking for 'past midninght' condition
            pastMidnigh = true;
        }
    }
    intervalStartTime = intervalStartTime + interval;
    
    intervalStopTimeOld = intervalStopTime;
    intervalStopTime = intervalStartTime + interval;
    
    if(intervalStopTime <intervalStopTimeOld) { //checking for 'past midninght' condition
        pastMidnigh = true;
    }
}

/* continueRunInterval
 * -------------------
 * Helper function for interval processing. Returns true (= continue run interval) if current simulations time is lower than event processing time, otherwise returns false. Always returns false if current simulaition time is past midninght. */

bool Simulation::continueRunInterval() {
    if(!pastMidnigh) {
        if(currentTime < intervalStopTime) {
            return true;
        }
        else {
            return false;
        }
    }
    else
        return true;
}

/* continueRunSim:
 * --------------
 * Helper function for interval processing. Returns true (= continue run interval) if current simulations time is lower than event processing time, otherwise returns false. Always returns false if current simulaition time is past midninght. */

bool Simulation::continueRunSim() {
    if(!pastMidnigh) {
        if(eventTime < intervalStopTime && eventTime < simStopTime) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return true;
    }
}

/* processEvent:
 * ------------
 * Functon processes one event at a time. The function updates interval start and end times if time for event that is being handled goes past current interval stop time.
 * The function also keeps track of previous values for interval stop time, current simulation time and next event time. This is done with purpose to set simulation status to "over midnight" when one of the values goes past 00:00. Changing simulation status to "over midnight" allows avoiding erroneous time comparison after 00:00.
 * The function is handling "visible" status depending on whether next event time is before or after the StartShowingTime.
 * Returns false if next event to be processed has time after simulation end time. */

bool Simulation::processEvent() {
    Time currentTimeOld = currentTime;
    Time intervalStopTimeOld = intervalStopTime;
    Time eventTimeOld = eventTime;
    
    bool eventProcessed = false;
    
    while(!eventProcessed && !eventQueueEmpty()) {
        
        Event *nextEvent = eventQueue.top();
        
        eventTimeOld = eventTime;
        eventTime = nextEvent->getTime();
        
        if(eventTime > simStopTime && !pastMidnigh) { //exclude past midnight events from comparison to avoid wrong results
            return false;
        }
        
        if(eventTime < eventTimeOld) {
            pastMidnigh = true;
        }
        if(eventTime > startShowingTime || pastMidnigh) {
            visible = true;
        }
        
        eventQueue.pop();
        
        currentTimeOld = currentTime;
        currentTime = eventTime;
        
        nextEvent->processEvent(); //process event
        delete nextEvent;
        eventProcessed = true;
        
        if(currentTime < currentTimeOld) {
            pastMidnigh = true;
        }
        
        while(eventTime > intervalStopTime) { //updates interval start and stop times if necessary
            intervalStartTime = intervalStartTime + interval;
            
            intervalStopTimeOld = intervalStopTime;
            intervalStopTime = intervalStartTime + interval;
            
            if(intervalStopTime <intervalStopTimeOld) {
                pastMidnigh = true;
            }
        }
    }
    return true;
}

/* nextEventTime:
 * --------------
 * Returns next event time as Time object. */

Time Simulation::nextEventTime() {
    Event *nextEvent = eventQueue.top();
    return nextEvent->getTime();
}

/* handleNewStartTime:
 --------------------
 * Updates startShowingTime with new value from in-parameter and sets simulation status to invisible. Status changed back to visible by processEvent() or processInterval() finctions. */

void Simulation::handleNewStartTime(Time newStartTime) {
    setStartShowingTime(newStartTime);
    setInvisible();
}

/* simIsFinished:
 * -------------
 * Returns true if event queue is empty, or if intervalStartTime > simStopTime and simulation current time is not past midnight. Otherwise returns false. */

bool Simulation::simIsFinished() {
    if(!pastMidnigh) {
        if(intervalStartTime > simStopTime || eventQueue.empty())
            return true;
        else
            return false;
    }
    else {
        if(eventQueue.empty())
            return true;
        else
            return false;
    }
}

/* scheduleEvent:
 * -------------
 * Adds event to event queue. Function is used by other classes (Event and File reader) to schedule simulation events. */

void Simulation::scheduleEvent(Event *newEvent) {
    eventQueue.push(newEvent);
}

