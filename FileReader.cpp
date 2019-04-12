//
//  FileReader.cpp
//  ProjectTrains
//
//  Created by Olga on 2018-06-07.
//  Copyright © 2018 Olga. All rights reserved.
//

#include "FileReader.hpp"
using namespace std;

/* Class destructor closes the files that have been opened.
 */
FileReader::~FileReader() {
    stationDataFile.close();
    trainDataFile.close();
    vehicleDataFile.close();
}

/* openFiles:
 * ---------
 * Input stream from the files are opened. If operation fails for either of files, a runtime_error exception is thrown.
 */
void FileReader::openFiles() {
    trainDataFile.open(trainDataFileName);
    if (!trainDataFile.is_open())
        throw runtime_error ("Could not open Train data file.");
    
    stationDataFile.open(stationDataFileName);
    if(!stationDataFile.is_open())
        throw runtime_error("Could not open Station data file.");
    
    vehicleDataFile.open(vehicleDataFileName);
    if (!vehicleDataFile.is_open())
        throw runtime_error ("Could not open Vehicle data file.");
}

/* readFiles:
 * ---------
 * Function combines several class functions for easier access of class functionality.
 * Note: station file has to be read before vehicle file.
 */
void FileReader::readFiles() {
    openFiles();
    
    readTrainDataFile();
    readStationDataFile();
    readVehicleDataFile();
}

/* readTrainDataFile:
 * -----------------
 * Function reads train data file in accordance with file format.
 * Each train is logged by calling a corresponding function from IronbendInc class; trains are logged in status "incomplete". Vehicles are added to train as 'conceptual' (with vehicle id = -1, and all parameters set to 0) by calling a corresponding function from IronbendInc class.
 * Each train initiates a new AssembleAttempt event which is logged by calling a corresponding function from Simulation class.
 */
void FileReader::readTrainDataFile(string trainDataFileName) {
    int trainNum, vehType, maxSpeed;
    Time depTime, arrTime;
    string deptStation, destStation;
    
    while(trainDataFile)
    {
        trainDataFile >> trainNum;
        trainDataFile.get();
        getline(trainDataFile, deptStation, DELIM_TRAIN_DATA_FILE);
        getline(trainDataFile, destStation, DELIM_TRAIN_DATA_FILE);
        trainDataFile >> depTime;
        trainDataFile >> arrTime;
        trainDataFile >> maxSpeed;
        trainDataFile.get();
        
        theInc->addTrain(trainNum, deptStation, destStation, depTime, arrTime, maxSpeed); //log train
        
        Event *e = new AssembleAttemptEvent(depTime - TIME_FOR_ASSEMBLING, theSim, theInc, trainNum);
        theSim->scheduleEvent(e); //log event
        
        while (trainDataFile >> vehType) {
            theInc->addVehicleToTrain(trainNum, vehType, -1, 0); //add conceptual vehicle to train
            if(trainDataFile.peek() == '\n')
                break;
        }
    }
    
}

/* readStationDataFile:
 * -------------------
 * Function reads station data file in accordance with file format.
 * Each station, as well destinations that are assiciated with station and distances to them, are logged by calling corresponding functions from IronbendInc class.
 */
void FileReader::readStationDataFile(string stationDataFileName) {
    int km;
    string stationName, destStation;
    
    while(getline(stationDataFile, stationName, ' ')) {
        getline(stationDataFile, destStation, ' ');
        stationDataFile >> km;
        stationDataFile.get();
        if(!theInc->stationFound(stationName)) {
            theInc->addStation(stationName); //log station, if station is not logged yet; verified for stations that have been read as distances and are already logged
        }
        
        theInc->addDistance(stationName, destStation, km); //log destination and distance
        
        if(!theInc->stationFound(destStation)) {
            theInc->addStation(destStation); //log station, if station is not logged yet; verified for stations that have been read as distances and are already logged
        }
        
        theInc->addDistance(destStation, stationName, km); //log destination and distance
    }
}

/* readVehicleDataFile:
 * -------------------
 * Pre-condition: station file is read.
 * Function reads vehicle data file in accordance with file format.
 * Each vehicle is logged (added to existing station vehicle pool) by calling corresponding functions from IronbendInc class.
 */
void FileReader::readVehicleDataFile(string vehicleDataFileName) {
    int vehId, vehType, param1;
    int param2 = 0;
    string stationName;
    char tmpCh = '|';
    
    while(vehicleDataFile.peek() != EOF) {
        getline(vehicleDataFile, stationName, DELIM1_VEH_DATA_FILE);
        
        while(vehicleDataFile.peek() != '\n' && vehicleDataFile.peek() != EOF) {
            vehicleDataFile >> vehId;
            vehicleDataFile >> vehType;
            vehicleDataFile >> param1;
            
            if(vehicleDataFile.peek() != DELIM2_VEH_DATA_FILE) {
                vehicleDataFile >> param2;
                
                while(tmpCh != DELIM1_VEH_DATA_FILE && vehicleDataFile.peek() != '\n' && vehicleDataFile.peek() != EOF) {
                    vehicleDataFile.get(tmpCh);
                }
                tmpCh = '|';
            }
            else {
                while(tmpCh != DELIM1_VEH_DATA_FILE && vehicleDataFile.peek() != '\n' && vehicleDataFile.peek() != EOF) {
                    vehicleDataFile.get(tmpCh);
                }
                tmpCh = '|';
            }
            //strip station name from unnecessary characters (caused by file format)
            stationName.erase(remove(stationName.begin(), stationName.end(), ' '), stationName.end());
            stationName.erase(remove(stationName.begin(), stationName.end(), '\n'), stationName.end());
            //vehicle added to station vehicle pool
            theInc->addVehicleToPool(stationName, vehType, vehId, param1, param2);
        }
    }
}
