/* CSCI261 Final Project: Sudoku Solver 
 *
 * Author: ALEX_POLLOCK
 *
 * Description: Header file for Puzzle Solving Functions 
 * 
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <string>
#include "Cell.h"
using namespace std;

#pragma once

void solvePuzzle(vector < vector <Cell> > &theBoard);
void stepOne(vector < vector <Cell> > &theBoard);
void stepTwo(vector < vector <Cell> > &theBoard);
void stepThree(vector < vector <Cell> > &theBoard);
int colBox(int colSpot);
int rowBox(int rowSpot);
bool isSame(vector <int> cell1, vector <int> cell2);
bool validateAnswer( const vector < vector <Cell> > &theBoard);