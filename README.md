Sliding Puzzle Solver

Enter "make tests" to compile and run the tests for the heap. The .o object files should be in the bin folder. The heap test executable should also be in the bin folder, which you can run from there if desired.

Enter "make" to compile all files. The .o object files should be in the bin folder.

To run the puzzle executable, which is in the hw6 folder, enter "./puzzle", size of board, initial number of moves to scramble to board, the seed, and type of heuristic, all of which should be integers.

For example:
./puzzle 4 20 1771 2

will generate a 4x4 sliding puzzle which is scrambled by 20 moves, seeded by 1771, and has uses Manhattan Distance as a heuristic.

Entering 0 for the heuristic will use Breadth First Search heuristic.

Entering 1 for the heuristic will use an "out of place" heuristic that checks the number of tiles that are out of place.

Entering 2 for the heuristic will use the Manhattan Distance of each tile from its intended location as a heuristic.


