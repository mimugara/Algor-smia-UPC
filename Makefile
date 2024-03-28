TARGET: localSearchLT localSearchIC metaheuristicLT metaheuristicIC difusioLT difusioIC greedyIC greedyLT

COMPILER: g++

FLAGS: -std=c++11 -Wall -Wextra

SRCS: localSearchLT.cc localSearchLT.hh localSearchIC.cc localSearchIC.hh metaheuristicLT.cc metaheuristicLT.hh metaheuristicIC.cc metaheuristicIC.hh difusioLT.cc difusioLT.hh difusioIC.cc difusioIC.hh
OBJS: $(SRCS:.cc=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(COMPILER) $(FLAGS) -o $(TARGET) $(OBJS)

clean:
	-rm localSearchLT localSearchIC metaheuristicLT metaheuristicIC difusioLT difusioIC output*
