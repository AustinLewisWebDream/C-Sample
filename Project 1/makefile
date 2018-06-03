HEADERS=card.h deck.h SortingList.h sortingOperations.h term.h
OBJECTS=$(HEADERS:.h=.o) lab12.o
PROGRAM=Lab12
COMPILE=g++ -g -std=c++11 -Wall

$(PROGRAM): $(OBJECTS)
	$(COMPILE) $^ -o $@
%.o: %.cpp $(HEADERS)
	$(COMPILE) -c $< -o $@
clean:
	rm $(PROGRAM) $(OBJECTS)
