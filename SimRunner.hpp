//
//  SimRunner.hpp
//  ProjectTrains
//
//  Created by Olga on 2018-06-06.
//  Copyright © 2018 Olga. All rights reserved.
//

#ifndef SimRunner_hpp
#define SimRunner_hpp

#include <string>
#include <memory>
#include "FileReader.hpp"
#include "Simulation.hpp"
#include "IronbendInc.hpp"
#include "Menu.hpp"
#include "Time.hpp"

/* class SIM RUNNER:
 * ----------------
 The class is handling running (starting and ending) simulation, as well as provides user interface for managing simulation and simulation parameters, getting simulation results and getting information about simulation components (trains, vehicles, stations).
 * Class public members are only run() function, as well as constructior and destructor. All other functions are class private members.
 */
class SimRunner {
private:
    IronbendInc *theInc;
    Simulation *theSim;
    FileReader *theMid;
    
    bool running = false;
    bool finished = false;
    
    Menu main;
    Menu simulation;
    Menu train;
    Menu station;
    Menu vehicle;
    
    void submenuSimulation();
    void submenuTrain();
    void submenuStation();
    void submenuVehicle();
    
    void changeStartTime();
    void changeEndTime();
    
    void changeInterval();
    void runNextInterval();
    void nextEvent();
    void completeSimulation();
    void printStatistics();
    
    void searchTrainByNumber();
    void searchTrainByVehId();
    void showAllTrains();
    
    void showStationName();
    void showStationByName();
    void showAllStations();
    
    void showVehById();
    void showAllVeh();
    
    void printResult();
    
public:
    SimRunner();
    ~SimRunner();
    
    int run();
};

int showMenu(Menu &m);
void hold();
int getInt(std::string prompt);

#endif /* SimRunner_hpp */
