CXX = g++
CXXFLAGS = -g -Wall
driver: location.o driver.cpp
	$(CXX) $(CXXFLAGS) location.o driver.cpp -o driver
mytest: location.o mytest.cpp
	$(CXX) $(CXXFLAGS) location.o mytest.cpp -o mytest
location.o: location.cpp location.h
	$(CXX) $(CXXFLAGS) -c location.cpp
remake:
	make mytest
	make run

clean:
	rm *.o*
	rm *~ 

run:
	./mytest