//
//  SimRunner.cpp
//  ProjectTrains
//
//  Created by Olga on 2018-06-06.
//  Copyright © 2018 Olga. All rights reserved.
//

#include "SimRunner.hpp"
#include <iostream>
#include <iomanip>
#include <exception>
#include <stdexcept>
using namespace std;

/*
 Class constructor initiates three pointer objects for classes IronbendInc, FileReader and Simulation. FileReader class reads simulation information from files. IronbendInc class provides information about simulation components and results. Simulation class manages and handles simulation.
 * Constructor assignes menu items for menu objects Main, Simulation, Train, Station and Vehicle. Note, this implementation does not use 'enabled' menu item status so it remains 'true' throughout runtime.
 */
SimRunner::SimRunner() {
    
    theInc = new IronbendInc;
    theSim = new Simulation;
    theMid = new FileReader(theSim, theInc);
    
    main.setMenuRubrik("MAIN MENU");
    main.addMenuItem("Change start time", true);
    main.addMenuItem("Change end time", true);
    main.addMenuItem("Simulation menu", true);
    main.addMenuItem("Train menu", true);
    main.addMenuItem("Station menu", true);
    main.addMenuItem("Vehicle menu", true);
    main.addMenuItem("Exit", true);
    
    simulation.setMenuRubrik("SIMULATION MENU");
    simulation.addMenuItem("Change interval", true);
    simulation.addMenuItem("Run next interval", true);
    simulation.addMenuItem("Next event", true);
    simulation.addMenuItem("Complete simulation", true);
    simulation.addMenuItem("Print statistics", true);
    simulation.addMenuItem("Back to main menu", true);
    
    train.setMenuRubrik("TRAIN MENU");
    train.addMenuItem("Search train by number", true);
    train.addMenuItem("Search train by vehicle id", true);
    train.addMenuItem("Show all trains", true);
    train.addMenuItem("Back to main menu", true);
    
    station.setMenuRubrik("STATION MENU");
    station.addMenuItem("Show station names", true);
    station.addMenuItem("Show station by name", true);
    station.addMenuItem("Show all stations", true);
    station.addMenuItem("Back to main menu", true);
    
    vehicle.setMenuRubrik("VEHICLE MENU");
    vehicle.addMenuItem("Show vehicle by id", true);
    vehicle.addMenuItem("Show all vehicles", true);
    vehicle.addMenuItem("Back to main menu", true);
}

/*
 Class destructor deletes IronbendInc, FileReader and Simulation objects.
 */
SimRunner::~SimRunner() {
    delete theInc;
    delete theSim;
    delete theMid;
}

/* run:
 * ---
 * Function orders FileReader to read files, and displays Main menu options by calling showMenu() finction.
 * Function has return data type int, because it contains a file reading block that returns a value while catching an exception.
 */
int SimRunner::run() {
    
    { //read files
        try {
            theMid->readFiles();
        }
        catch (exception &e) {
            cerr << e.what();
            cout << " Terminating." << endl;
            return 1;
        }
    }
    
    bool again = true; //display Main menu
    do
    {
        switch(showMenu(main))
        {
            case 1: changeStartTime(); hold();
                break;
            case 2: changeEndTime(); hold();
                break;
            case 3: submenuSimulation();
                break;
            case 4: submenuTrain();
                break;
            case 5: submenuStation();
                break;
            case 6: submenuVehicle();
                break;
            case 7: again = false; //exit program
                break;
        }
    } while(again);
    return 0;
}

/* submenuSimulation:
 * -----------------
 * Displays Simulation sub-menu options by calling showMenu() finction.
 */
void SimRunner::submenuSimulation()
{
    bool again = true;
    do
    {
        switch(showMenu(simulation))
        {
            case 1: changeInterval(); hold();
                break;
            case 2: runNextInterval(); hold();
                break;
            case 3: nextEvent(); hold();
                break;
            case 4: completeSimulation(); hold();
                break;
            case 5: printStatistics(); hold();
                break;
            case 6: again = false; //return to main menu
                break;
        }
    } while(again);
}

/* submenuTrain:
 * ------------
 * Displays Train sub-menu options by calling showMenu() finction.
 */
void SimRunner::submenuTrain()
{
    bool again = true;
    do
    {
        switch(showMenu(train))
        {
            case 1: searchTrainByNumber(); hold();
                break;
            case 2: searchTrainByVehId(); hold();
                break;
            case 3: showAllTrains(); hold();
                break;
            case 4: again = false; //return to main menu
                break;
        }
    } while(again);
}

/* submenuStation:
 * --------------
 * Displays Station sub-menu options by calling showMenu() finction.
 */
void SimRunner::submenuStation()
{
    bool again = true;
    do
    {
        switch(showMenu(station))
        {
            case 1: showStationName(); hold();
                break;
            case 2: showStationByName(); hold();
                break;
            case 3: showAllStations(); hold();
                break;
            case 4: again = false; //return to main menu
                break;
        }
    } while(again);
}

/* submenuVehicle:
 * ---------------
 * Displays Vehicle sub-menu options by calling showMenu() finction.
 */
void SimRunner::submenuVehicle()
{
    bool again = true;
    do
    {
        switch(showMenu(vehicle))
        {
            case 1: showVehById(); hold();
                break;
            case 2: showAllVeh(); hold();
                break;
            case 3: again = false; //return to main menu
                break;
        }
    } while(again);
}

/* changeStartTime:
 * ---------------
 * If simulation has started, informs user that start time no longer can be changed. Otherwise, prompts user for new simulation start time and sends a Time object to Simulation for handling.
 */
void SimRunner::changeStartTime() {
    if(running) {
        cout << "Start time can not be changed - simulation has been started" << endl;
    }
    else {
        int min, hr = 0;
        
        hr = getInt("Enter new start time [HOURS  ]: ");
        min = getInt("Enter new start time [MINUTES]: ");
        
        Time newStartTime(hr, min);
        theSim->handleNewStartTime(newStartTime);
    }
}

/* changeEndTime:
 * --------------
 * If simulation has started, informs user that end time no longer can be changed. Otherwise, prompts user for new simulation end time and sends a Time object to Simulation for handling.
 */
void SimRunner::changeEndTime() {
    if(running) {
        cout << "End time can not be changed - simulation has been started" << endl;
    }
    else {
        int min, hr = 0;
        
        hr = getInt("Enter new end time [HOURS  ]: ");
        min = getInt("Enter new end time [MINUTES]: ");
        
        Time newStopTime(hr, min);
        theSim->setSimStopTime(newStopTime);
    }
}

/* changeInterval:
 * --------------
 * If simulation has finished, informs user. Otherwise, prompts user for value for a new simulation interval which will be applicable from the next simulation interval run. User input in minutes is received as integer which is then converted into a Time object and sent to Simulation for handling.
 */
void SimRunner::changeInterval() {
    
    if(finished) {
        cout << "Simulation has finished" << endl;
    }
    else {
        int newInt, min, hr = 0;
        
        newInt = getInt("Enter new interval time (in minutes): ");
        
        min = newInt%60;
        hr = (newInt-min)/60;
        
        Time newInterval(hr, min);
        theSim->setInterval(newInterval);
        Time newIntStop = theSim->getIntervalStart() + newInterval;
        theSim->setIntervalStopTime(newIntStop);
    }
}

/* runNextInterval:
 * ---------------
 * If sim is not in running state, running is set to true.
 * If simulation is finished, user is informed and no interval is run. Otherwise, next time interval is run. Interval times are displayed. User can choose if program shall continue to running next interval.
 * In case simulation start time has been set to later than first event, events before start time are run in a "silent mode"- no information is dsplayed on screen.
 * Informs user if simulation is finished during execution of this function.
 */
void SimRunner::runNextInterval() {
    
    if(theSim->simIsFinished()) { //inform user if simulation finished
        cout << "Simulation has finished" << endl;
        finished = true;
    }
    
    if(!running) {
        running = true;
    }
    
    //Handling time interval before simulaion start time.
    while((!theSim->eventQueueEmpty()) && (theSim->getTime() < theSim->getSimStopTime())
          && (theSim->getTime() < theSim->getStartShowingTime()) && !finished) {
        theSim->runInterval();
        
        if(theSim->simIsFinished()) {
            cout << "Simulation has finished" << endl;
            finished = true;
        }
    }
    
    //Handling 'silent complete' of simulation
    while((!theSim->eventQueueEmpty()) && theSim->isSilentComplete()) {
        theSim->runInterval();
        
        if(theSim->simIsFinished()) {
            cout << "Simulation has finished" << endl;
            finished = true;
        }
    }
    
    char ch;
    bool again = true;
    
    while((!theSim->simIsFinished()) && again) {
        if(finished) {
            cout << "Simulation has finished" << endl;
            break;
        }
        //conditions that have to be met to run interval in a "non-scilent" mode (prompt and interval span are printed)
        //first condition: checking if there are events in the interval
        //second condition: upcomming even is not before simulation end time
        else if(theSim->getIntervalStop() > theSim->nextEventTime() || theSim->getSimStopTime() < theSim->nextEventTime()) {
            cout << "Run interval? ('y'/'n'): ";
            cin >> ch;
            cin.get();
            cout << endl;
            ch = toupper(ch);
            if(ch != 'N') {
                Time start = theSim->getIntervalStart();
                Time stop = theSim->getIntervalStop();
                
                cout << "EVENTS BETWEEN ["; showTime(start);
                cout << "] AND ["; showTime(stop);
                cout << "]:" << endl <<endl;
                theSim->runInterval();

                if(theSim->simIsFinished()) {
                    cout << "Simulation has finished" << endl;
                    finished = true;
                }
            }
            else
                again = false;
        }
        //the "scilent" interval running applies if there are no events in the interval
        else {
            theSim->runInterval();
            if(theSim->simIsFinished()) {
                cout << "Simulation has finished" << endl;
                finished = true;
            }
        }
    }
}

/* nextEvent:
 * ---------
 * If sim is not in running state, running is set to true.
 * If simulation is finished, user is informed and no event is processed. Otherwise, next event in event queue is processed.
 * In case simulation start time has been set to later than even time, all events before start time are run in a "silent mode"- no information is displayed on screen - and then event after the start time is displayed.
 * Informs user if simulation is finished during execution of this function.
 */
void SimRunner::nextEvent() {
    if(!running) {
        running = true;
    }
    
    // This loop handles time interval before simulaion start time, if applicable.
    while((!theSim->eventQueueEmpty()) && (theSim->getTime() < theSim->getSimStopTime())
          && (theSim->getTime() < theSim->getStartShowingTime()) && !finished) {
        theSim->processEvent();
        if(theSim->simIsFinished()) {
            cout << "Simulation has finished" << endl;
            finished = true;
        }
    }
    
    // After simulation start time(if applicable), or any other event:
    if(finished) {
        cout << "Simulation has finished" << endl;
    }
    else {
        if(!theSim->processEvent()) {
            finished = true;
            cout << "Simulation has finished" << endl;
            
        }
        if(theSim->simIsFinished()) {
            cout << "Simulation has finished" << endl;
            finished = true;
        }
    }
}

/* completeSimulation:
 * ------------------
 * If sim is not in running state, running is set to true.
 * Completes simulation by processing the remainnig simulation events in "silent mode". This is done by setting Simulation status silentComplete to true.
 * Informs user when smulation has finished.
 */
void SimRunner::completeSimulation() {
    if(!running) {
        running = true;
    }
    theSim->setSilentComplete();
    while(!(theSim->eventQueueEmpty())) {
        runNextInterval();
    }
}

/* printStatistics:
 * ---------------
 * Prints simulation results if sumulation has finished, otherwise informs that sim has to be finished first.
 */
void SimRunner::printStatistics() {
    if(finished) {
        printResult();
    }
    else {
        cout << "Simulation has to be finished in order to get results" << endl;
    }
}

/* searchTrainByNumber:
 * -------------------
 * Prompts user for train number, searches for train, if found - displays results, informs user if otherwise.
 */
void SimRunner::searchTrainByNumber() {
    int trainNum;
    trainNum = getInt("Enter train number: ");
    
    bool trainFound = theInc->showTrain(trainNum);
    if(!trainFound) {
        cout << "No train with such number found" << endl;
    }
}

/* searchTrainByVehId:
 * ------------------
 * Prompts user for vehicle number, searches for train that contains the vehicle, if found - displays results, informs user if otherwise.
 */
void SimRunner::searchTrainByVehId() {
    int vehId;
    vehId = getInt("Enter vehicle id: ");

    bool trainFound = theInc->showTrainByVeh(vehId);
    if(!trainFound) {
        cout << "No train with such vehicle id found" << endl;
    }
}

/* showAllTrains:
 * -------------
 * Displays info for all trains.
 */
void SimRunner::showAllTrains() {
    theInc->showAllTrains();
}

/* showStationName:
 * ---------------
 * Displays list of all station names.
 */
void SimRunner::showStationName() {
    theInc->showStationNames();
}

/* showStationByName:
 * -----------------
 * Prompts user for station name, searches for station with that name, if found - displays results, informs user if otherwise.
 */
void SimRunner::showStationByName() {
    string sName;
    cout << "Enter station name: ";
    getline(cin, sName);
    
    bool stationFound = theInc->showStation(sName);
    if(!stationFound) {
        cout << "No station with such name found" << endl;
    }
}

/* showAllStations:
 * ---------------
 * Displays info for all stations.
 */
void SimRunner::showAllStations() {
    theInc->showAllStations();
}

/* showVehById:
 * -----------
 * Prompts user for vehicle id, if found - displays results, informs user if otherwise.
 */
void SimRunner::showVehById() {
    int vehId;
    vehId = getInt("Enter vehicle id: ");

    bool vehFound = theInc->showVehicle(vehId);
    if(!vehFound) {
        cout << "No vehicle with such id found" << endl;
    }
}

/* showAllVeh:
 * ----------
 * Displays info for all vehicles.
 */
void SimRunner::showAllVeh() {
    theInc->showAllVehicles();
}

/* printResult:
 * -----------
 * Pre-condition: simulation has finished.
 * Prints simulation results: trains in state INCOMPLETE.
 */
void SimRunner::printResult() {
    cout << endl << "SIMULATION RESULTS" << endl;
    cout << "-------------------------------------" << endl;
    cout << "Following trains have not left their departure stations due to lack of vehicles:" << endl << endl;
    theInc->showTrainByState(1);
    cout << "All other trains have reached their destination according to schedule." << endl;
    cout << endl << "END OF REPORT" << endl;
}

/* showMenu:
 * --------
 * Prints info for Menu class: menu title, menu choises.
 * Returns user's choise as an integer.
 */
int showMenu(Menu &m)
{
    cout << m.getMenuRubrik() << endl;
    cout << "-------------------------------------" << endl;
    m.printMenuItems();
    int choise = m.getMenuChoise();
    
    return choise;
}
/* hold:
* -----
* Prompts user to press Enter key before proceeding further.
*/
void hold()
{
    cout << endl << "Press a key to return to menu...";
    cin.get();
    cout << endl;
}

/* getInt:
 * ------
 * Validating user input where integer is expected as an input.
 */
int getInt(std::string prompt) {
    bool valid = false;
    string input;
    
    while (valid == false) {
        cout << prompt;
        getline(cin, input);
        
        for (auto c : input) {
            if (isdigit(c))
                valid = true;
            else {
                valid = false;
                break;
            }
        }
    }
    return stoi(input);
}
