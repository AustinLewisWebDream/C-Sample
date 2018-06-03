HEADERS=functions.h imdb.h
OBJECTS=$(HEADERS:.h=.o) main.o
PROGRAM=CS216PA2
COMPILE=g++ -g -std=c++11 -Wall

$(PROGRAM): $(OBJECTS)
	$(COMPILE) $^ -o $@
%.o: %.cpp $(HEADERS)
	$(COMPILE) -c $< -o $@
clean:
	rm $(PROGRAM) $(OBJECTS)
