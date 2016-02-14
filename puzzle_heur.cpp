#include "puzzle_heur.h"
#include <cmath>

using namespace std;

int PuzzleManhattanHeuristic::compute(const Board &b){
	int h=0;
	for(int i=0; i<b.size(); i++){
		//dont count manhattan value of blank tile
		if(b[i]!=0){
			//add up manhattan values of individual tiles
			h+=abs(i/b.dim()-b[i]/b.dim());
			h+=abs(i%b.dim()-b[i]%b.dim());
		}
	}
	return h;
}

int PuzzleOutOfPlaceHeuristic::compute(const Board &b){
	int oop=0;
	for(int i=0; i<b.size(); i++){
		if(b[i]!=i){
			if(b[i]!=0){
				//everytime we find a tile out of place add to our heuristic
				oop++;
			}
		}
	}
	return oop;
}

int PuzzleBFSHeuristic::compute(const Board &b){
	return 0;
}