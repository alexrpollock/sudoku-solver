/* CSCI261 Final Project: Sudoku Solver 
 *
 * Author: ALEX_POLLOCK
 *
 * Description: Implementation file for Puzzle Solving Functions 
 * 
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <string>
#include "Cell.h"
#include "boardFunctions.h"

using namespace std;

void solvePuzzle(vector < vector <Cell> > &theBoard){
    bool isSolved=false;
    int counter=0;
    while(isSolved!=true){
        vector < vector <Cell> > prevBoard=theBoard;
        stepOne(theBoard);
        stepTwo(theBoard);
        //stepThree(theBoard); Needs to be fixed: for intermediate puzzles
        counter++;
        isSolved=true;
        for(int rowSpot=0;rowSpot<theBoard.size();rowSpot++){
            for(int colSpot=0;colSpot<theBoard.at(rowSpot).size();colSpot++){
                if(theBoard.at(rowSpot).at(colSpot).getAnswer()==-1){
                    isSolved=false;
                }
            }
        }
        if(counter>100){//Avoids Infinite Loop if the puzzle is unsolvable
            isSolved=true;
        }
    }//end Solving
    return;
}

void stepOne(vector < vector <Cell> > &theBoard){//Eliminates possibles for a cell if the value is an answer in the same row, column, or 3x3 box
    //check rows
    for(int rowSpot=0;rowSpot<theBoard.size();rowSpot++){
        for(int colSpot=0;colSpot<theBoard.at(rowSpot).size();colSpot++){
            if(theBoard.at(rowSpot).at(colSpot).getAnswer()==-1){
                for(int i=0;i<9;i++){
                    if(theBoard.at(rowSpot).at(i).getAnswer()!=-1){
                        theBoard.at(rowSpot).at(colSpot).removePossible(theBoard.at(rowSpot).at(i).getAnswer());
                    }
                }
            }
        }
    }
    //check cols
    for(int colSpot=0;colSpot<9;colSpot++){
        for(int rowSpot=0;rowSpot<9;rowSpot++){
            if(theBoard.at(rowSpot).at(colSpot).getAnswer()==-1){
                for(int i=0;i<theBoard.size();i++){
                    if(theBoard.at(i).at(colSpot).getAnswer()!=-1){
                        theBoard.at(rowSpot).at(colSpot).removePossible(theBoard.at(i).at(colSpot).getAnswer());
                    }
                }
            }
        }
    }
    //check boxes
    for(int rowSpot=0;rowSpot<theBoard.size();rowSpot++){
        for(int colSpot=0;colSpot<theBoard.at(rowSpot).size();colSpot++){
            if(theBoard.at(rowSpot).at(colSpot).getAnswer()==-1){
                for(int i=rowBox(rowSpot);i<rowBox(rowSpot)+3;i++){
                   for(int j=colBox(colSpot);j<colBox(colSpot)+3;j++){
                       if(theBoard.at(i).at(j).getAnswer()!=-1){
                            theBoard.at(rowSpot).at(colSpot).removePossible(theBoard.at(i).at(j).getAnswer());
                        }
                    } 
                }
            }
        }
    }
    return;
}

void stepTwo(vector < vector <Cell> > &theBoard){//If a cell is the only one with a possible answer in a row, column, or box it becomes the answer for that cell
    //check rows
    for (int rowSpot=0;rowSpot<theBoard.size();rowSpot++){
        int val=0;
        vector <int> freq(9);
        for(int colSpot=0; colSpot<theBoard.at(rowSpot).size(); colSpot++){
            Cell workingCell=theBoard.at(rowSpot).at(colSpot);
            if(workingCell.getAnswer() == -1){
                for (int i=0; i<workingCell.getPossibles().size(); i++){
                    val = workingCell.getPossibles().at(i);
                    freq.at(val-1)+=1;
                }
            }
        }
        for(int i=0;i<freq.size();i++){
            if(freq.at(i)==1){
                for( int colSpot=0; colSpot<theBoard.at(rowSpot).size(); colSpot++){
                    if(theBoard.at(rowSpot).at(colSpot).getAnswer() == -1){
                        for(int j=0; j<theBoard.at(rowSpot).at(colSpot).getPossibles().size(); j++){
                            if(theBoard.at(rowSpot).at(colSpot).getPossibles().at(j)==(i+1)){
                                theBoard.at(rowSpot).at(colSpot).setAnswer(theBoard.at(rowSpot).at(colSpot).getPossibles().at(j));
                            }
                        }
                    }
                }
            }
        }
        freq.resize(0);
        stepOne(theBoard);
    }
    //check cols
    for (int colSpot=0;colSpot<theBoard.at(0).size();colSpot++){
        int val=0;
        vector <int> freq(9);
        for(int rowSpot=0; rowSpot<theBoard.size(); rowSpot++){
            Cell workingCell=theBoard.at(rowSpot).at(colSpot);
            if(workingCell.getAnswer() == -1){
                for (int i=0; i<workingCell.getPossibles().size(); i++){
                    val = workingCell.getPossibles().at(i);
                    freq.at(val-1)+=1;
                }
            }
        }
        for(int i=0;i<freq.size();i++){
            if(freq.at(i)==1){
                for( int rowSpot=0; rowSpot<theBoard.size(); rowSpot++){
                    if(theBoard.at(rowSpot).at(colSpot).getAnswer() == -1){
                        for(int j=0; j<theBoard.at(rowSpot).at(colSpot).getPossibles().size(); j++){
                            if(theBoard.at(rowSpot).at(colSpot).getPossibles().at(j)==(i+1)){
                                theBoard.at(rowSpot).at(colSpot).setAnswer(theBoard.at(rowSpot).at(colSpot).getPossibles().at(j));
                            }
                        }
                    }
                }
            }
        }
        freq.resize(0);
        stepOne(theBoard);
    }
    return;
}
//Step 3 needs to be fixed: only for intermediate puzzles
// Involves the logic behind preemptive sets
/*void stepThree(vector < vector <Cell> > &theBoard){
    for (int rowSpot=0;rowSpot<theBoard.size();rowSpot++){
        for(int colSpot=0;colSpot<theBoard.at(rowSpot).size();colSpot++){
            int val1=-1;
            int val2=-1;
            int colSpotCell1=-1;
            int colSpotCell2=-1;
            Cell workingCell=theBoard.at(rowSpot).at(colSpot);
            if(workingCell.getAnswer() == -1){
                if(workingCell.getPossibles().size()==2){
                    val1=workingCell.getPossibles().at(0);
                    val2=workingCell.getPossibles().at(1);
                    colSpotCell1=colSpot;
                    for(int i=0;i<theBoard.at(rowSpot).size();i++){
                        Cell workingCell2=theBoard.at(rowSpot).at(i);
                        if( ( isSame( workingCell.getPossibles(), workingCell2.getPossibles() ) ) == true){
                            colSpotCell2=i;
                            for(int j=0;j<theBoard.at(rowSpot).size();j++){
                                if(theBoard.at(rowSpot).at(j).getAnswer()==-1 && j!=colSpotCell1 && j!=colSpotCell2){
                                    theBoard.at(rowSpot).at(j).removePossible(val1);
                                    theBoard.at(rowSpot).at(j).removePossible(val2);
                                }
                            }
                        }
                    }
                }
            }
            stepOne(theBoard);
            stepTwo(theBoard);
        }
    }
    return;
}*/

int colBox(int colSpot){//Finds which 3x3 box to use, column
    if(colSpot>=0 && colSpot<3){
        return 0;
    }else if (colSpot>=3 && colSpot<6){
        return 3;
    }else if(colSpot>=6 && colSpot<9){
        return 6;
    }else{
        return 0;
    }
}

int rowBox(int rowSpot){//Finds which 3x3 box to use, row
    if(rowSpot>=0 && rowSpot<3){
        return 0;
    }else if (rowSpot>=3 && rowSpot<6){
        return 3;
    }else if(rowSpot>=6 && rowSpot<9){
        return 6;
    }else{
        return 0;
    }
}

bool isSame(vector <int> cell1, vector <int> cell2){//Determines if two possible sets are the same (for step 3)
    bool isSame=false;
    if(cell1.size()==cell2.size()){
        for(int i=0;i<cell1.size();i++){
            if(cell1.at(i)==cell2.at(i)){
                isSame=true;
            }else{
                isSame=false;
                return isSame;
            }
        }
    }else{
        return isSame;
    }
    return isSame;
}
bool validateAnswer( const vector < vector <Cell> > &theBoard){//Checks to make sure the board is solved according to the rules of sudoku
    bool isValid=true;
    for (int rowSpot=0;rowSpot<theBoard.size();rowSpot++){
        int val=0;
        vector <int> freq(9);
        for(int colSpot=0; colSpot<theBoard.at(rowSpot).size(); colSpot++){
            Cell workingCell=theBoard.at(rowSpot).at(colSpot);
            val = workingCell.getAnswer();
            if(val!=-1){
                freq.at(val-1)+=1;
            }else{
                isValid=false;
                return isValid;
            }
        }
        for(int i=0;i<freq.size();i++){
            if(freq.at(i)!=1){
                isValid=false;
                return isValid;
            }
        }
        freq.resize(0);
    }
    return isValid;
}