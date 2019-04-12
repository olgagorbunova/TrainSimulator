//
//  SimConst.hpp
//  ProjectTrains
//
//  Created by Olga on 2018-05-29.
//  Copyright © 2018 Olga. All rights reserved.
//

#ifndef SimConst_hpp
#define SimConst_hpp
#include "Time.hpp"
#include <string>

/* ---- Vehicle types ---- */
const int COACH_PASS = 0;
const int SLEEPING_PASS = 1;
const int OPEN_FREIGHT = 2;
const int COVERED_FREIGHT = 3;
const int ELECTRICAL_ENGINE = 4;
const int DIESEL_ENGINE = 5;

/* ---- Train states ---- */
const int NOT_ASSEMBLED = 0;
const int INCOMPLETE = 1;
const int ASSEMBLED = 2;
const int READY = 3;
const int RUNNING = 4;
const int ARRIVED = 5;
const int FINISHED = 6;

enum States {notAssembled, incomplete, assembled, ready, running, arrived, finished};
const std::string statesStr[] = {"NOT ASSEMBLED", "INCOMPLETE", "ASSEMBLED", "READY", "RUNNING", "ARRIVED", "FINISHED"};

/* ---- Simulation time constants ---- */

const Time START_TIME(0, 0);
const Time STOP_TIME(23, 59);
const Time SIM_INTERVAL(0, 10);

const Time TIME_FOR_ASSEMBLING(0, 30);
const Time GET_READY_TO_DEPART(0, 10);
const Time TIME_TO_DIASSEMBLE(0, 20);

/* ---- Data files ---- */
const std::string TRAIN_DATA_FILE = "Trains.txt";
const std::string STATION_DATA_FILE = "TrainMap.txt";
const std::string VEHICLE_DATA_FILE = "TrainStations.txt";

const char DELIM_TRAIN_DATA_FILE = ' ';
const char DELIM1_VEH_DATA_FILE = '(';
const char DELIM2_VEH_DATA_FILE = ')';

#endif /* SimConst_hpp */
