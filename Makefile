CC       = g++
CPPFLAGS = -Wall -g
BIN_DIR  = bin
GTEST_LL = -I /usr/local/opt/gtest/include/ -l gtest -l gtest_main -pthread

all: $(BIN_DIR)/htest puzzle
	-@echo "--- All Built!---"

$(BIN_DIR)/htest: htest.cpp heap.h $(BIN_DIR)/.dirstamp
	$(CC) $(CPPFLAGS) htest.cpp $(GTEST_LL) -o $(BIN_DIR)/htest

$(BIN_DIR)/board.o: board.cpp board.h
	$(CC) $(CPPFLAGS) board.cpp -o $(BIN_DIR)/board.o -c

$(BIN_DIR)/puzzle_heur.o: puzzle_heur.h puzzle_heur.cpp
	$(CC) $(CPPFLAGS) puzzle_heur.cpp -o $(BIN_DIR)/puzzle_heur.o -c

$(BIN_DIR)/puzzle_solver.o: puzzle_solver.h puzzle_solver.cpp puzzle_move.h
	$(CC) $(CPPFLAGS) puzzle_solver.cpp -o $(BIN_DIR)/puzzle_solver.o -c

$(BIN_DIR)/puzzle_move.o: puzzle_move.h puzzle_move.cpp
	$(CC) $(CPPFLAGS) puzzle_move.cpp -o $(BIN_DIR)/puzzle_move.o -c

puzzle: puzzle.cpp $(BIN_DIR)/puzzle_solver.o $(BIN_DIR)/puzzle_heur.o $(BIN_DIR)/board.o $(BIN_DIR)/puzzle_move.o  
	$(CC) $(CPPFLAGS) puzzle.cpp puzzle_solver.cpp puzzle_heur.cpp board.cpp puzzle_move.cpp -o puzzle

$(BIN_DIR)/.dirstamp:
	mkdir -p $(BIN_DIR)
	touch $(BIN_DIR)/.dirstamp

.PHONY: clean tests

tests: $(BIN_DIR)/htest
	-@./$(BIN_DIR)/htest
	-@echo "--- All Tested!---"

clean:
	-@rm -rf puzzle
	-@rm -rf $(BIN_DIR)
	-@echo "--- All Clean!---"
