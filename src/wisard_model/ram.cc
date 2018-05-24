#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <tuple>
#include <cmath>
#include <cstdlib>

using namespace std;

class RAM{
public:
  RAM(){}
  RAM(const int addressSize, const int entrySize, const bool ignoreZero=false): ignoreZero(ignoreZero){
    addresses = vector<int>(addressSize);
    generateRandomAddresses(entrySize);
  }
  RAM(const vector<int>& indexes, const bool ignoreZero=false): addresses(indexes), ignoreZero(ignoreZero){}

  int getVote(const vector<int>& image){
    int index = getIndex(image);
    if(ignoreZero && index == 0)
      return 0;
    if(positions.find(index) == positions.end()){
      return 0;
    }
    else{
      return positions[index];
    }
  }

  void train(const vector<int>& image){
    int index = getIndex(image);
    if(positions.find(index) == positions.end())
      positions[index] = 0;
    positions[index]++;
  }

  vector<vector<int>>& getMentalImage() {
    vector<vector<int>>* mentalPiece = new vector<vector<int>>(addresses.size());
    for(unsigned int i=0; i<mentalPiece->size(); i++){
      (*mentalPiece)[i].resize(2);
      (*mentalPiece)[i][0] = addresses[i];
      (*mentalPiece)[i][1] = 0;
    }

    for(map<int,int>::iterator j=positions.begin(); j!=positions.end(); ++j){
      if(j->first == 0) continue;
      for(unsigned int i=0; i<mentalPiece->size(); i++){
        if((*mentalPiece)[i].size() == 0){
          (*mentalPiece)[i].resize(2);
          (*mentalPiece)[i][0] = addresses[i];
          (*mentalPiece)[i][1] = 0;
        }
        if((j->first & (int)pow(2,i)) > 0){
          (*mentalPiece)[i][1] += j->second;
        }
      }
    }
    return *mentalPiece;
  }

protected:
  int getIndex(const vector<int>& image) const{
    int index = 0;
    for(unsigned int i=0; i<addresses.size(); i++){
      int pos = addresses[i];
      if(image[pos] > 0){
        index += (int)pow(2,i);
      }
    }
    return index;
  }

private:
  vector<int> addresses;
  map<int,int> positions;
  bool ignoreZero;

  void generateRandomAddresses(int entrySize){
    for(unsigned int i=0; i<addresses.size(); i++){
      addresses[i] = randint(0, entrySize-1);
    }
  }
};
