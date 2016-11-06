CXXFLAGS = -g -Wall

SOURCES = colaPrioridadTest.cpp
HEADERS = colaPrioridadMin.hpp
OBJS = $(SOURCES:.cpp=.o)

LIBS =

TARGET = colaPrioridadTest

$(TARGET): $(OBJS) $(HEADERS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all: $(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

valgrind: all
	valgrind --leak-check=full ./$(TARGET)
