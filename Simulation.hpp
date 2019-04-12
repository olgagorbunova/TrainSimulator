//
//  Simulation.hpp
//  ProjectTrains
//
//  Created by Olga on 2018-06-01.
//  Copyright © 2018 Olga. All rights reserved.
//

#ifndef Simulation_hpp
#define Simulation_hpp
#include <memory>
#include <string>
#include <vector>
#include <queue>
#include "Time.hpp"
#include "SimConst.hpp"
#include "Event.hpp"

/* class SIMULATION:
 * ----------------
 * This class handles activities directly related to simulation: event scheduling, processing and simulation time management (time of events, start and end time of intervals that events are processed within, start and end time of simulation, etc.
 * Boolean member 'visible' is used for 'hiding' events that are processed before selected start time (if there are such events in the queue).
 * Boolean 'pastMidnight' is used for handling camparison of event times aafter 00:00 when usual comparison gives incorrect result.
 * Boolean 'silentComplete' is set to true when simulation is to be complete in a silent mode.
 */
class Simulation {
private:

    Time interval;
    Time currentTime;
    Time intervalStartTime;
    Time simStopTime;
    Time intervalStopTime;
    Time startShowingTime;
    
    Time eventTime;
    
    bool pastMidnigh = false;
    bool visible = true;
    bool silentComplete = false;
    
    std::priority_queue<Event*, std::vector<Event*>, EventComparison> eventQueue;
    
public:
    Simulation();
    ~Simulation();
    
    Time getTime() const {return currentTime;}
    Time getIntervalStart() const {return intervalStartTime;}
    Time getIntervalStop() const {return intervalStopTime;}
    Time getSimStopTime() const {return simStopTime;}
    Time getStartShowingTime() const {return startShowingTime;}
    Time nextEventTime();
    
    void setInterval(Time newInterval) {interval = newInterval;}
    void setIntervalStartTime(Time newIntStart) {intervalStartTime = newIntStart;}
    void setIntervalStopTime(Time newIntStop) {intervalStopTime = newIntStop;}
    void setSimStopTime(Time newSimStop) {simStopTime = newSimStop;}
    void setStartShowingTime(Time newStartShow) {startShowingTime = newStartShow;}
    
    void runInterval();
    bool continueRunInterval();
    bool continueRunSim();
    
    bool processEvent();
    
    void handleNewStartTime(Time newStartTime);
    
    void setInvisible() {visible = false;}
    bool isVisible() {return visible;}
    void setSilentComplete() {silentComplete = true;}
    bool isSilentComplete() {return silentComplete;}
    
    bool eventQueueEmpty() {return eventQueue.empty();}
    
    bool simIsFinished();
    
    void scheduleEvent(Event *newEvent);
};

#endif /* Simulation_hpp */
