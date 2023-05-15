CXX = g++
CXXFLAGS = -std=c++14

SRC = main.cpp func.cpp mh.cpp rbt.cpp
OBJ = $(SRC:.cpp=.o)
DEPS = func.h mh.h rbt.h Ride.h

EXEC = gatorTaxi

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)