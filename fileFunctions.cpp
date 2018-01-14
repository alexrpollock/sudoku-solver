/* CSCI261 Final Project: Sudoku Solver 
 *
 * Author: ALEX_POLLOCK
 *
 * Description: Implementation file for File Functions
 * 
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <string>
#include "Cell.h"
#include "fileFunctions.h"
#include "boardFunctions.h"

using namespace std;

vector < vector <Cell> > setUpBoard(string puzzleIn){//Uses inputted string to read file name, creates 2D vector of cell objects
    puzzleIn.append(".txt");
    vector< vector <Cell> > theBoard( 9, vector <Cell> (9) );
    
    ifstream inPuzzle(puzzleIn);
    //check that files opened OK
    if( inPuzzle.fail() ) {
        cerr << "ERROR! Input file could not be opened" << endl;
        theBoard.resize(0);
        return theBoard;
    }
    char c;
    int rowSpot=0;
    int colSpot=0;
    int convert;
    while(!inPuzzle.eof()){
        while(inPuzzle.get(c)){
            if(isdigit(c)){
                convert=int(c)-48;
                theBoard.at(rowSpot).at(colSpot).setAnswer(convert);
                colSpot++;
            }else if(c=='.'){//Leaves as default constructor
                colSpot++;
            }
            
            if((isdigit(c) || c=='.')&& colSpot>8){//move to next row when reach last cell of column
                colSpot=0;
                rowSpot++;
            }
        }
    }
    theBoard.resize(rowSpot);//for validation, if board was too big/small
    inPuzzle.close();
    return theBoard;
}

void outBoard(string puzzleIn, vector < vector <Cell> > &theBoard){//creates the output file
    string puzzleOut=puzzleIn;
    if(validateAnswer(theBoard)==true){//checks to see if a valid solution was reached for file name
        puzzleOut.append("Solved.txt");
    }else{
        puzzleOut.append("NoSolution.txt");
    }
    ofstream outPuzzle(puzzleOut);
    if( outPuzzle.fail() ) {
        cerr << "ERROR! Output file could not be opened" << endl;
        return;
    }
    if(validateAnswer(theBoard)==true){//checks to see if a valid solution was reached before output
        string intermed;
        for(int rowSpot=0;rowSpot<theBoard.size();rowSpot++){
            for (int colSpot=0;colSpot<theBoard.at(rowSpot).size();colSpot++){
                intermed=to_string(theBoard.at(rowSpot).at(colSpot).getAnswer())[0];
                outPuzzle<<intermed;
                outPuzzle<<" ";
                if(colSpot%3==2 && colSpot!=8){
                    outPuzzle<<"|";
                }else if(colSpot%9==8 && rowSpot!=8){
                    outPuzzle<<endl;
                    if(rowSpot%3==2){
                        outPuzzle<<"------+------+------";
                        outPuzzle<<endl;
                    }
                }
            }
        }//end for
        
    }else{
        outPuzzle<<"Puzzle could not be solved.";
    }
    outPuzzle.close();
    return;
}

bool validateBoard(vector < vector <Cell> > theBoard){//checks that the created board size is 9x9
    bool isSize=false;
    if(theBoard.size()==9){
        if(theBoard.at(0).size()==9){
            isSize=true;
        }
    }
    return isSize;
}