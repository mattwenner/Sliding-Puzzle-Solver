#include <iostream>
#include <cstdlib>
#include <deque>
#include <fstream>
#include <string>
#include "board.h"
#include "puzzle_heur.h"
#include "puzzle_solver.h"
#include "puzzle_move.h"
#include <cstring>
#include <vector>
#include <cctype>

int main(int argc, char *argv[])
{
  if(argc < 5){
    cerr << "Usage: ./puzzle side initMoves seed heur" << endl;
    return 1;
  }
  vector<char*> checker;
  checker.push_back(argv[1]);
  checker.push_back(argv[2]);
  checker.push_back(argv[3]);
  checker.push_back(argv[4]);
  for(unsigned int h=0; h<checker.size(); h++){
  	for(unsigned int g=0; g<strlen(checker[h]); g++){
  		if(!isdigit(checker[h][g])){
  			cout<<"Error, inputs can only be ints"<<endl;
  			return -1;
  		}
  	}
  }

  int side=atoi(argv[1]);
  int initMoves=atoi(argv[2]);
  int seed=atoi(argv[3]);
  int heur=atoi(argv[4]);
  if(heur<0||heur>2){
  	cerr<<"Enter valid heuristic"<<endl;
  	return -1;
  }
  //our board
  Board* myBoard=new Board(side, initMoves, seed);
  //heuristic base class that allows for polymorphism
  PuzzleHeuristic *pHeuristic;
  //BFS
  if(heur==0){
  	pHeuristic=new PuzzleBFSHeuristic();
  }
  //Out of Place
  else if(heur==1){
  	pHeuristic=new PuzzleOutOfPlaceHeuristic();
  }
  //Manhattan
  else{
  	pHeuristic=new PuzzleManhattanHeuristic();
  }

  
  cout<<*myBoard<<endl;
  cout<<"Enter tile number to move or -1 for a cheat: -1. Enter 0 to quit."<<endl;
  
  string input_val;
  //keep on accepting inputs until user enters 0 or puzzle is solved
  while(cin>>input_val&& input_val!="0"){
  	
  	for(unsigned int k=0; k<input_val.size(); k++){
  		if(!isdigit(input_val[k])){
  			continue;
  		}
  	}
  	int i=atoi(input_val.c_str());


  	//make a move
  	if(i>=1&&i<side*side){
  		myBoard->move(i);

  	}
  	//A* search
  	else if(i==-1){
  		
  		PuzzleSolver ps(*myBoard, pHeuristic);
  		ps.run();
  		cout<<"Try this sequence:"<<endl;
  		for(unsigned int i=0; i<ps.getSolution().size(); i++){
  			cout<<ps.getSolution()[i]<<" ";
  		}
  		cout<<endl<<"(Expansions = "<<ps.getNumExpansions()<<")"<<endl;
  		
  	}
  	if(myBoard->solved()){
  		cout<<"SOLVED!"<<endl;
  		cout<<*myBoard<<endl;
  		break;
  	}
  	//loop again
  	else{
  		cout<<*myBoard<<endl;
  		cout<<"Enter tile number to move or -1 for a cheat: -1. Enter 0 to quit."<<endl;
  	}
  }

  delete pHeuristic;
  delete myBoard;

  return 0;
}
