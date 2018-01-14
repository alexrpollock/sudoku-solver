/* CSCI261 Final Project: Sudoku Solver 
 *
 * Author: ALEX_POLLOCK
 *
 * Description: Header file for File Functions
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

#pragma once

vector < vector <Cell> > setUpBoard(string puzzle);
void outBoard(string puzzleIn, vector < vector <Cell> > &theBoard);
bool validateBoard(vector < vector <Cell> > theBoard);