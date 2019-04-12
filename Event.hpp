//
//  Event.hpp
//  ProjectTrains
//
//  Created by Olga on 2018-06-04.
//  Copyright © 2018 Olga. All rights reserved.
//

#ifndef Event_hpp
#define Event_hpp

#include <memory>
#include <string>
#include "Time.hpp"
#include "SimConst.hpp"

/* class EVENT:
 * -----------
 * Event is an abstract base class that represents a generic event concept.
 */
class Simulation;
class IronbendInc;

class Event {
protected:
    Time time; //event time
    
public:
    Event (Time t): time(t) {}
    virtual ~Event() {}
    
    virtual void processEvent() = 0; // pure virtual function
    Time getTime() const {return time;}
};

/* class EVENT COMPARISON:
 * ----------------------
 * Derived from Event. Compares two Event objectes by event time.
 */
class EventComparison {
public:
    bool operator() (Event *left, Event *right) {
        return left->getTime() > right->getTime();
    }
};

/* class ASSEMBLE ATTEMPT EVENT:
 * ----------------------------
 * Derived from Event. Handles train assemble attempt.
 * Contains pointers to Simulation and IronbendInc as class members (provided as constructor arguments).
 */
class AssembleAttemptEvent : public Event {
protected:
    Simulation *theSim;
    IronbendInc *theInc;
    int trainNum;
    
public:
    AssembleAttemptEvent(Time time, Simulation *sim, IronbendInc *inc, int tNum)
    : Event(time), theSim(sim), theInc(inc), trainNum(tNum) {}
    virtual ~AssembleAttemptEvent() {}
    
    virtual void processEvent();
    virtual void showEvent();
};

/* class READY TO DEPART EVENT:
 * ----------------------------
 * Derived from Event. Handles train ready to depart.
 * Contains pointers to Simulation and IronbendInc as class members (provided as constructor arguments).
 */
class ReadyToDepartEvent : public Event {
protected:
    Simulation *theSim;
    IronbendInc *theInc;
    int trainNum;
    
public:
    ReadyToDepartEvent(Time time, Simulation *sim, IronbendInc *inc, int tNum)
    : Event(time), theSim(sim), theInc(inc), trainNum(tNum) {}
    virtual ~ReadyToDepartEvent() {}
    
    virtual void processEvent();
    virtual void showEvent();
};

/* class READY TO DEPART EVENT:
 * ----------------------------
 * Derived from Event. Handles train departure event.
 * Contains pointers to Simulation and IronbendInc as class members (provided as constructor arguments).
 */
class DepartureEvent : public Event {
protected:
    Simulation *theSim;
    IronbendInc *theInc;
    int trainNum;
    
public:
    DepartureEvent(Time time, Simulation *sim, IronbendInc *inc, int tNum)
    : Event(time), theSim(sim), theInc(inc), trainNum(tNum) {}
    virtual ~DepartureEvent() {}
    
    virtual void processEvent();
    virtual void showEvent();
};

/* class READY TO DEPART EVENT:
 * ----------------------------
 * Derived from Event. Handles train arrival event.
 * Contains pointers to Simulation and IronbendInc as class members (provided as constructor arguments).
 */
class ArrivalEvent : public Event {
protected:
    Simulation *theSim;
    IronbendInc *theInc;
    int trainNum;
    
public:
    ArrivalEvent(Time time, Simulation *sim, IronbendInc *inc, int tNum)
    : Event(time), theSim(sim), theInc(inc), trainNum(tNum) {}
    virtual ~ArrivalEvent() {}
    
    virtual void processEvent();
    virtual void showEvent();
};

/* class READY TO DEPART EVENT:
 * ----------------------------
 * Derived from Event. Handles train dissemble event.
 * Contains pointers to Simulation and IronbendInc as class members (provided as constructor arguments).
 */
class DissembleEvent : public Event {
protected:
    Simulation *theSim;
    IronbendInc *theInc;
    int trainNum;
    
public:
    DissembleEvent(Time time, Simulation *sim, IronbendInc *inc, int tNum)
    : Event(time), theSim(sim), theInc(inc), trainNum(tNum) {}
    virtual ~DissembleEvent() {}
    
    virtual void processEvent();
    virtual void showEvent();
};

#endif /* Event_hpp */
