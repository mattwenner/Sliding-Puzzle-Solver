#include <iostream>
#include <iomanip>
#include <map>
#include <cmath>
#include <cstdlib>
#include <stdexcept>
#include "board.h"
using namespace std;
//default constructor
Board::Board(){}

Board::Board(int dim, int numInitMoves, int seed )
{
  _size = dim*dim;
  _tiles = new int[_size];
  srand(seed);
  for(int i=0; i < _size; i++){
    _tiles[i] = i;
  }
  int blankLoc = 0;
  while(numInitMoves > 0){
    int r = rand()%4;
    int randNeighbor = -1;
    if(r == 0){
      int n = blankLoc - dim;
      if(n >= 0){
	randNeighbor = n;
      }
    }
    else if(r == 1){
      int w = blankLoc - 1;
      if(blankLoc % dim != 0){
	randNeighbor = w;
      }
    }
    else if(r == 2){
      int s = blankLoc + dim;
      if(s  < _size){
	randNeighbor = s;
      }
    }
    else {
      int e = blankLoc + 1;
      if(blankLoc % dim != dim-1){
	randNeighbor = e;
      }
    }
    if(randNeighbor > -1){
      _tiles[blankLoc] = _tiles[randNeighbor];
      _tiles[randNeighbor] = 0;
      blankLoc = randNeighbor;
      numInitMoves--;
    }
  }
}

Board::~Board(){
  delete [] _tiles;
}

Board::Board(const Board& other){
  this->_size=other._size;
  this->_tiles=new int[_size];
  for(int i=0; i<this->size(); i++){
    _tiles[i]=(other)[i];
  }
}



void Board::move(int tile)
{
  int side_dim = dim();
  int tr, tc, br, bc;

  // find tile row and column
  int i=-1;
  while(_tiles[++i] != tile);

  tr = i / side_dim; 
  tc = i % side_dim;

  // find blank row and column
  int j=-1;
  while(_tiles[++j] != 0);

  br = j / side_dim;
  bc = j % side_dim;

  if( abs(static_cast<double>(tr-br)) + abs(static_cast<double>(tc-bc)) != 1){
    cout << "Invalid move of tile " << tile << " at ";
    cout << tr << "," << tc << " and blank spot at ";
    cout << br << "," << bc << endl;
    return;
  }
  // Swap tile and blank spot
  _tiles[j] = tile;
  _tiles[i] = 0;
}

// Generate new boards representing all the potential moves of tiles into 
// the current blank tile location. The returned map should have
// the key as the tile moved and the value as a new Board object with the
// configuration reflecting the move of that tile into the blank spot
map<int, Board*> Board::potentialMoves() const
{
  map<int, Board*>myMap;
  for(int i=0; i<this->size(); i++){
    if (_tiles[i]==0){
      //found tile continaing zero
      int zero_tile=i;
      //able to move up
      if(zero_tile/dim()>0){
        Board* UBoard=new Board(*this);
        UBoard->move(_tiles[zero_tile-dim()]);
        myMap.insert(make_pair(_tiles[zero_tile-dim()],UBoard));
        
      }
      //able to move down
      if(zero_tile/dim()<dim()-1){
        Board* DBoard=new Board(*this);
        DBoard->move(_tiles[zero_tile+dim()]);
        myMap.insert(make_pair(_tiles[zero_tile+dim()], DBoard));
        
      }
      //able to move left
      if(zero_tile%dim()>0){
        Board* LBoard=new Board(*this);
        LBoard->move(_tiles[zero_tile-1]);
        myMap.insert(make_pair(_tiles[zero_tile-1], LBoard));
        
      }
      //able to move right
      if(zero_tile%dim()<dim()-1){
        Board* RBoard=new Board(*this);
        RBoard->move(_tiles[zero_tile+1]);
        myMap.insert(make_pair(_tiles[zero_tile+1], RBoard));
        
      }
    }
  }
  
  return myMap;
  
}

const int& Board::operator[](int loc) const 
{ 
  return _tiles[loc]; 
}

int Board::size() const 
{ 
  return _size; 
}

int Board::dim() const
{
  return static_cast<int>(sqrt(_size));
}

void Board::printRowBanner(ostream& os) const
{
  int side_dim = dim();
  if(side_dim == 0) return;
  os << '+';
  for(int i=0; i < side_dim; i++){
    os << "--+";
  }
  os << endl;
}
//checks if we found solved state
bool Board::solved() const{
  bool solved=true;
  for(int i=0; i<size(); i++){
    if(i!=_tiles[i]){
      solved=false;
    }
  }
  return solved;
}
//compares heuristic values of board tiles
bool Board::operator<(const Board& rhs) const{

  for(int i=0; i<size(); i++){
    if(this->_tiles[i]<rhs[i]){
      return true;
    }
    else if(this->_tiles[i]>rhs[i]){
      return false;
    }
  }
  return false;
}
//prints format
ostream& operator<<(ostream &os, const Board &b){
  int i=0;
  int j=0;
  while(i<=2*b.dim()){
    //for odd values of i, we have tile number format
    //for even values of i, we have barrier format
    if(i%2==0){
      b.printRowBanner(os);
    }
    else{
      os<<"|";
      for(int k=0; k<b.dim(); k++){
        
        if(b[j]==0){
          os<<"  "<<"|";
        }
        else if(b[j]<10){
          os<<" "<<b[j]<<"|";
        }
        else{
          os<<b[j]<<"|";
        }
        j++;
      }
      os<<endl;
    }
    i++;
  }
  return os;
}
//assignment operator for board
Board& Board::operator=(const Board& other){
  //makes sure board isn't assigned to itself
  if(&other==this){
    return *this;

  }
  //if already contains tiles, delete them
  if(_tiles){
    delete [] _tiles;
  }
  //copy contents over
  this->_size=other._size;
  this->_tiles=new int[_size];
  for(int i=0; i<this->size(); i++){
    _tiles[i]=(other)[i];
  }

  return *this;
}