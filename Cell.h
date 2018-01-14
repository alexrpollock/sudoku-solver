/* CSCI261 Final Project: Sudoku Solver 
 *
 * Author: ALEX_POLLOCK
 *
 * Description: Header file for Cell Class
 * 
 */
#include <vector>
using namespace std;
#pragma once

class Cell{
    public:
        Cell();
        Cell(int answer);
        int getAnswer() const;
        vector <int> getPossibles() const;
        void setAnswer(int answer);
        void setPossibles(vector <int> &possibles);
        void removePossible(int toRemove);
        
    private:
        int _answer;
        vector <int> _possibles;
        int checkAnswer(int answer);
        void possibleToAnswer();
};