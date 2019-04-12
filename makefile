CXX = g++
CXXFLAGS = -std=c++11

output: main.o SimRunner.o Menu.o MenuItem.o Simulation.o FileReader.o Event.o IronbendInc.o Train.o Station.o Vehicle.o Time.o
	$(CXX) main.o SimRunner.o Menu.o MenuItem.o Simulation.o FileReader.o Event.o IronbendInc.o Train.o Station.o Vehicle.o Time.o -o output

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

SimRunner.o: SimRunner.hpp SimRunner.cpp
	$(CXX) $(CXXFLAGS) -c SimRunner.cpp

Menu.o: Menu.hpp Menu.cpp
	$(CXX) $(CXXFLAGS) -c Menu.cpp

MenuItem.o: MenuItem.hpp MenuItem.cpp
	$(CXX) $(CXXFLAGS) -c MenuItem.cpp

Simulation.o: Simulation.hpp Simulation.cpp SimConst.hpp
	$(CXX) $(CXXFLAGS) -c Simulation.cpp

FileReader.o: FileReader.hpp FileReader.cpp SimConst.hpp
	$(CXX) $(CXXFLAGS) -c FileReader.cpp

Event.o: Event.hpp Event.cpp SimConst.hpp
	$(CXX) $(CXXFLAGS) -c Event.cpp

IronbendInc.o: IronbendInc.hpp IronbendInc.cpp
	$(CXX) $(CXXFLAGS) -c IronbendInc.cpp

Train.o: Train.hpp Train.cpp SimConst.hpp
	$(CXX) $(CXXFLAGS) -c Train.cpp

Station.o: Station.hpp Station.cpp
		$(CXX) $(CXXFLAGS) -c Station.cpp

Vehicle.o: Vehicle.hpp Vehicle.cpp SimConst.hpp
	$(CXX) $(CXXFLAGS) -c Vehicle.cpp

Time.o: Time.hpp Time.cpp
	$(CXX) $(CXXFLAGS) -c Time.cpp

clean:
	rm *.o output
