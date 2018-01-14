/* CSCI261 Final Project: Sudoku Solver 
 *
 * Author: ALEX_POLLOCK
 *
 * Description: This program reads in a sudoku puzzle (as formatted in the template file),
 * determines the puzzle answer (if there is one), validates the answer according to the
 * rules of sudoku, and then outputs the solved board in a file appended Solution (or
 * NoSolution for an unsolvable puzzle.
 *
 * Currently, the program only solves easy level sudoku problems. The ranking for sudoku
 * problems is based off of the algorithms/logic required to solve the puzzle. Easy puzzles
 * demand the lowest level of logic. 
 *
 * Five puzzles were used as test cases. Test cases 1-3 are successful solutions of easy 
 * puzzles. Test cases 4 and 5 are intended to not work. Puzzle four is an unsolvable puzzle
 * and test 5 is an improperly formatted input file. 
 *
 * Custom puzzles can be made and tested using the file "UnsolvedPuzzleTemplate.txt", but
 * if the puzzle requires higher order logic than the program has, the program will output 
 * no solution. 
 * 
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <string>
#include "Cell.h" //Cell Class
#include "fileFunctions.h" //Functions for writing in/out to files
#include "boardFunctions.h" //Functions for solving puzzle

using namespace std;

int main() {
    cout<<"Welcome to the Sudoku Solver!"<<endl;
    cout<<"Create a file of your puzzle from the template to find the solution (file must be in the same folder as this program)."<<endl;
    cout<<"Enter the file name of the puzzle you would like to solve (without .txt): ";
    string fileName;
    cin>>fileName;//input file name
    vector < vector <Cell> > boardUser=setUpBoard(fileName);//create board from file
    if(!validateBoard(boardUser)){//check the board is 9x9
        cout<<"Input file error."<<endl;
        return -1;
    }
    //Solve the Puzzle
    solvePuzzle(boardUser);
    //Generate Output File
    outBoard(fileName, boardUser);
    //End User Input Puzzle
    
    //Puzzle 1: Test Solvable Easy Puzzle
    string fileName1="Puzzle1";//input file name
    vector < vector <Cell> > board1=setUpBoard(fileName1);//create board from file
    if(!validateBoard(board1)){//check the board is 9x9
        cout<<"Input file error."<<endl;
        return -1;
    }
    //Solve the Puzzle
    solvePuzzle(board1);
    //Generate Output File
    outBoard(fileName1, board1);
    //End Test Case 1
    
    //Puzzle 2: Test Solvable Easy Puzzle
    string fileName2="Puzzle2";//input file name
    vector < vector <Cell> > board2=setUpBoard(fileName2);//create board from file
    if(!validateBoard(board2)){//check the board is 9x9
        cout<<"Input file error."<<endl;
        return -1;
    }
    //Solve the Puzzle
    solvePuzzle(board2);
    //Generate Output File
    outBoard(fileName2, board2);
    //End Test Case 2
    
    //Puzzle 3: Test Solvable Easy Puzzle
    string fileName3="Puzzle3";//input file name
    vector < vector <Cell> > board3=setUpBoard(fileName3);//create board from file
    if(!validateBoard(board3)){//check the board is 9x9
        cout<<"Input file error."<<endl;
        return -1;
    }
    //Solve the Puzzle
    solvePuzzle(board3);
    //Generate Output File
    outBoard(fileName3, board3);
    //End Test Case 3
    
    //Puzzle 4: Test Unsolvable Puzzle
    string fileName4="Puzzle4";//input file name
    vector < vector <Cell> > board4=setUpBoard(fileName4);//create board from file
    if(!validateBoard(board4)){//check the board is 9x9
        cout<<"Input file error."<<endl;
        return -1;
    }
    //Solve the Puzzle
    solvePuzzle(board4);
    //Generate Output File
    outBoard(fileName4, board4);
    //End Test Case 4
    
    //Puzzle 5: Test Invalid Input File UNCOMMENT TO SEE ERROR MESSAGE
    /*string fileName5="Puzzle5";//input file name
    vector < vector <Cell> > board5=setUpBoard(fileName5);//create board from file
    if(!validateBoard(board5)){//check the board is 9x9
        cout<<"Input file error."<<endl;
        return -1;
    }
    //Solve the Puzzle
    solvePuzzle(board5);
    //Generate Output File
    outBoard(fileName5, board5);
    //End Test Case 5*/
    return 0;
}