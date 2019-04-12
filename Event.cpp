//
//  Event.cpp
//  ProjectTrains
//
//  Created by Olga on 2018-06-04.
//  Copyright © 2018 Olga. All rights reserved.
//

#include "Event.hpp"
#include "Simulation.hpp"
#include "IronbendInc.hpp"
#include <iostream>
#include <iomanip>
using namespace std;

/* AssembleAttemptEvent::processEvent:
 * ----------------------------------
 * Attempt to assemble train is made. If successfull, train state is changed to ASSEMBLED and new ReadyToDepart event is scheduled (departure time - time specified as constant GET_READY_TO_DEPART). If not, train state is changed to INCOMPLETE.
 * Event information is printed unless Simulation is in the 'silent complete' or 'invisible' mode.
 */
void AssembleAttemptEvent::processEvent() {
    bool assembled = theInc->assembleTrain(trainNum);
    if(assembled) {
        theInc->setTrainState(trainNum, 2);
        Time departTime;
        theInc->getDeptTime(trainNum, departTime);
        
        Event *e = new ReadyToDepartEvent(departTime - GET_READY_TO_DEPART, theSim, theInc, trainNum);
        theSim->scheduleEvent(e);
    }
    else {
        theInc->setTrainState(trainNum, 1);
    }
    if(theSim->isVisible() && !theSim->isSilentComplete())
        showEvent();
}

/* AssembleAttemptEvent::showEvent:
 * -------------------------------
 Prints information about a train after AssembleAttempt event.
 */
void AssembleAttemptEvent::showEvent() {
    showTime(time);
    
    Time departTime;
    theInc->getDeptTime(trainNum, departTime);
    Time arrTime;
    theInc->getArrTime(trainNum, arrTime);
    
    int stateNr = theInc->getTrainState(trainNum);
    States state = static_cast<States>(stateNr);
    
    cout << " Train [" << trainNum << "] (" << statesStr[state] << ") from " << theInc->getDeptStation(trainNum) << " (";
    showTime(departTime);
    cout << ") to " << theInc->getArrStation(trainNum) << " (";
    showTime(arrTime);
    if(stateNr == 2) {
        cout << ") is now assembled." << endl << endl;
    }
    else {
        cout << ") has failed to assemble and is now cancelled." << endl << endl;
    }
}

/* ReadyToDepartEvent::processEvent:
 * --------------------------------
 * Train state is changed to READY and new Departure event is scheduled for departure time.
 * Event information is printed unless Simulation is in the 'silent complete' or 'invisible' mode.
 */
void ReadyToDepartEvent::processEvent() {
    theInc->setTrainState(trainNum, 3);
    
    Time departTime;
    theInc->getDeptTime(trainNum, departTime);
    
    Event *e = new DepartureEvent(departTime, theSim, theInc, trainNum);
    theSim->scheduleEvent(e);

    if(theSim->isVisible() && !theSim->isSilentComplete())
        showEvent();
}

/* ReadyToDepartEvent::showEvent:
 * -----------------------------
 Prints information about a train after ReadyToDepart event.
 */
void ReadyToDepartEvent::showEvent() {
    showTime(time);
    
    Time departTime;
    theInc->getDeptTime(trainNum, departTime);
    Time arrTime;
    theInc->getArrTime(trainNum, arrTime);
    
    int stateNr = theInc->getTrainState(trainNum);
    States state = static_cast<States>(stateNr);
    
    cout << " Train [" << trainNum << "] (" << statesStr[state] << ") from " << theInc->getDeptStation(trainNum) << " (";
    showTime(departTime);
    cout << ") to " << theInc->getArrStation(trainNum) << " (";
    showTime(arrTime);
    cout << ") is now approaching platform and is ready to depart." << endl << endl;
}


/* DepartureEvent::processEvent:
 * ----------------------------
 * Train state is changed to RUNNING and new Arrival event is scheduled for arrival time.
 * Event information is printed unless Simulation is in the 'silent complete' or 'invisible' mode.
 */
void DepartureEvent::processEvent() {
    theInc->setTrainState(trainNum, 4);
    
    Time arrTime;
    theInc->getArrTime(trainNum, arrTime);
    
    Event *e = new ArrivalEvent(arrTime, theSim, theInc, trainNum);
    theSim->scheduleEvent(e);
    
    if(theSim->isVisible() && !theSim->isSilentComplete())
        showEvent();
}

/* DepartureEvent::showEvent:
 * -----------------------------
 Prints information about a train after DepartureEvent event.
 */
void DepartureEvent::showEvent() {
    showTime(time);
    
    Time departTime;
    theInc->getDeptTime(trainNum, departTime);
    Time arrTime;
    theInc->getArrTime(trainNum, arrTime);
    
    int stateNr = theInc->getTrainState(trainNum);
    States state = static_cast<States>(stateNr);
    
    cout << " Train [" << trainNum << "] (" << statesStr[state] << ") from " << theInc->getDeptStation(trainNum) << " (";
    showTime(departTime);
    cout << ") to " << theInc->getArrStation(trainNum) << " (";
    showTime(arrTime);
    cout << setprecision(2) << fixed;
    cout << ") is now heading to it's destination. Average speed: " << theInc->getTrainAvgSpeed(trainNum) << endl << endl;
}

/* ArrivalEvent::processEvent:
 * ----------------------------
 * Train state is changed to ARRIVED and new Deassemble event is scheduled (arrival time + time specified as constant TIME_TO_DIASSEMBLE).
 * Event information is printed unless Simulation is in the 'silent complete' or 'invisible' mode.
 */
void ArrivalEvent::processEvent() {
    theInc->setTrainState(trainNum, 5);
    
    Time arrTime;
    theInc->getArrTime(trainNum, arrTime);
    
    Event *e = new DissembleEvent(arrTime + TIME_TO_DIASSEMBLE, theSim, theInc, trainNum);
    theSim->scheduleEvent(e);
    
    if(theSim->isVisible() && !theSim->isSilentComplete())
        showEvent();
}

/* ArrivalEvent::showEvent:
 * -----------------------------
 Prints information about a train after DepartureEvent event.
 */
void ArrivalEvent::showEvent() {
    showTime(time);
    
    Time departTime;
    theInc->getDeptTime(trainNum, departTime);
    Time arrTime;
    theInc->getArrTime(trainNum, arrTime);
    
    int stateNr = theInc->getTrainState(trainNum);
    States state = static_cast<States>(stateNr);
    
    cout << " Train [" << trainNum << "] (" << statesStr[state] << ") from " << theInc->getDeptStation(trainNum) << " (";
    showTime(departTime);
    cout << ") to " << theInc->getArrStation(trainNum) << " (";
    showTime(arrTime);
    cout << setprecision(2) << fixed;
    cout << ") has now arrived to it's destination." << endl << endl;
}

/* DissembleEvent::processEvent:
 * ----------------------------
 * Train is diassembled and it's state is changed to FINISHED.
 * Event information is printed unless Simulation is in the 'silent complete' or 'invisible' mode.
 */
void DissembleEvent::processEvent() {
    theInc->setTrainState(trainNum, 6);
    
    theInc->diassembleTrain(trainNum);
    
    if(theSim->isVisible() && !theSim->isSilentComplete())
        showEvent();
}

/* DissembleEvent::showEvent:
 * -----------------------------
 Prints information about a train after DepartureEvent event.
 */
void DissembleEvent::showEvent() {
    showTime(time);
    
    Time departTime;
    theInc->getDeptTime(trainNum, departTime);
    Time arrTime;
    theInc->getArrTime(trainNum, arrTime);
    
    int stateNr = theInc->getTrainState(trainNum);
    States state = static_cast<States>(stateNr);
    
    cout << " Train [" << trainNum << "] (" << statesStr[state] << ") from " << theInc->getDeptStation(trainNum) << " (";
    showTime(departTime);
    cout << ") to " << theInc->getArrStation(trainNum) << " (";
    showTime(arrTime);
    cout << setprecision(2) << fixed;
    cout << ") has been diassembled at destination station." << endl << endl;
}
