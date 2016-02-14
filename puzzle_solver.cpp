#include "puzzle_solver.h"
#include "heap.h"
#include "puzzle_move.h"
#include <functional>
#include <vector>

using namespace std;

PuzzleSolver::PuzzleSolver(const Board &b, PuzzleHeuristic* ph) : _b(b) {
	_ph=ph;
	_expansions=0;
}

PuzzleSolver::~PuzzleSolver(){}

void PuzzleSolver::run(){
	PuzzleMoveScoreComp scomp;	
	PuzzleMoveBoardComp bcomp;
	PuzzleMoveSet closed(bcomp);
	Heap <PuzzleMove*,  PuzzleMoveScoreComp>  open(2, scomp);
	Board* copy=new Board(_b);
	PuzzleMove* initialMove=new PuzzleMove(copy);
	initialMove->h=_ph->compute(_b);
	open.push(initialMove);
	closed.insert(initialMove);
	
	while(!open.empty()){

		PuzzleMove* curr=open.top();
		open.pop();

		if(curr->b->solved()){
			while(curr->prev!=NULL){

				_solution.push_front(curr->tileMove);
				curr=curr->prev;
			}
			break;
		}
		else{
			map<int, Board*> pNextMoves=(curr->b)->potentialMoves();

			for(map<int, Board*>::iterator it=pNextMoves.begin(); it!=pNextMoves.end(); ++it){
				PuzzleMove* newPMove=new PuzzleMove(it->first ,it->second, curr );				
				newPMove->h=_ph->compute(*(newPMove->b));
				if(closed.find(newPMove)==closed.end()){					
					open.push(newPMove);
					closed.insert(newPMove);					
					_expansions++;				
				}
				else{
		
					delete newPMove->b;
					delete newPMove;
				}	
			}
		}
	}
	for(set<PuzzleMove*>::iterator it=closed.begin(); it!=closed.end(); ++it){
		if ((*it)->b){
			PuzzleMove *temp = *it;
			delete temp->b;
		}
		delete *it;
	}

}

deque<int>PuzzleSolver::getSolution(){
	return _solution;
}

int PuzzleSolver::getNumExpansions(){
	return _expansions;
}