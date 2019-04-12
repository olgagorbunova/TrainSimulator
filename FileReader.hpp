//
//  FileReader.hpp
//  ProjectTrains
//
//  Created by Olga on 2018-06-07.
//  Copyright © 2018 Olga. All rights reserved.
//

#ifndef FileReader_hpp
#define FileReader_hpp

#include <string>
#include <memory>
#include <fstream>
#include <exception>
#include <stdexcept>
#include "Simulation.hpp"
#include "IronbendInc.hpp"
#include "Event.hpp"
#include "Time.hpp"
#include "SimConst.hpp"

/* class FILE READER:
 * -----------------
 * This class handles reading information files. Each of three files used in this sumulation is handled by a separate function. All files are structured in a specific way and class is using this fact to process the files.
 * File names are class members and are stored as constans, however other file names can be explicitly given as function arguments.
 * Other class members are pointers to Simulation and IronbendInc classes (provided as constructor arguments), as well as infile streams for the files.
 */

class FileReader {
private:
    Simulation *theSim;
    IronbendInc *theInc;
    
    std::string trainDataFileName;
    std::string stationDataFileName;
    std::string vehicleDataFileName;
    
    std::ifstream trainDataFile;
    std::ifstream stationDataFile;
    std::ifstream vehicleDataFile;
    
public:
    FileReader(Simulation *sim, IronbendInc *inc, std::string aTrainDataFile = TRAIN_DATA_FILE, std::string aStationDataFile = STATION_DATA_FILE, std::string aVehicleDataFile = VEHICLE_DATA_FILE): theSim(sim), theInc(inc), trainDataFileName(aTrainDataFile), stationDataFileName(aStationDataFile), vehicleDataFileName(aVehicleDataFile) {}
     
    ~FileReader();
    
    void readFiles();
    
    void openFiles();
    
    void readTrainDataFile(std::string trainDataFileName = TRAIN_DATA_FILE);
    void readStationDataFile(std::string stationDataFileName = STATION_DATA_FILE);
    void readVehicleDataFile(std::string vehicleDataFileName = VEHICLE_DATA_FILE);
};


#endif /* FileReader_hpp */
