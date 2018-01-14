/* CSCI261 Final Project: Sudoku Solver 
 *
 * Author: ALEX_POLLOCK
 *
 * Description: Implementation file for Cell Class
 * 
 */
#include "Cell.h"
#include <vector>
#include <iostream>
using namespace std;

//constructors
Cell::Cell(){
    _answer=-1;
    for(int i=1;i<10;i++){
        _possibles.push_back(i);
    }
}
Cell::Cell(int answer){
    _answer=checkAnswer(answer);
}

//getters
int Cell::getAnswer() const{
    return _answer;
}
vector<int> Cell::getPossibles() const{
    return _possibles;
}

//setters
void Cell::setAnswer(int answer){
    _answer=checkAnswer(answer);
    if(_answer!=-1){
        while (!_possibles.empty()) {
            _possibles.pop_back();
        }
    }
    return;
}
void Cell::setPossibles(vector <int> &possibles){
    while(possibles.size()!=0){
        possibles.pop_back();
    }
    for(int i=0;i<possibles.size();i++){
        _possibles.push_back(possibles.at(i));
    }
    possibleToAnswer();
    return;
}

//helper functions
void Cell::removePossible(int toRemove){
    vector <int> withoutBad;
    for(int i=0;i<_possibles.size();i++){//Marks the possibles to remove
        if(_possibles.at(i)==toRemove){
            _possibles.at(i)=-1;
        }
    }
    for(int i=0;i<_possibles.size();i++){//Temp stores the correct possibles
        if(_possibles.at(i)!=-1){
            withoutBad.push_back(_possibles.at(i));
        }
    }
    while(_possibles.size()!=0){//Clears the possibles
        _possibles.pop_back();
    }
    for(int i=0;i<withoutBad.size();i++){//Re-adds the correct possibles
        _possibles.push_back(withoutBad.at(i));
    }
    possibleToAnswer();
    return;
}
int Cell::checkAnswer(int answer){
    if(answer>0 && answer<=9){
        return answer;
    }else{
        return -1;
    }
}
void Cell::possibleToAnswer(){//if there is one possible, it becomes the answer
    if(_possibles.size()==1){
        setAnswer(_possibles.at(0));
    }
}