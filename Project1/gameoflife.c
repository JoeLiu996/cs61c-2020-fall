/************************************************************************
**
** NAME:        gameoflife.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Justin Yokota - Starter Code
**				YOUR NAME HERE
**
**
** DATE:        2020-08-23
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "imageloader.h"

int directionX[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
int directionY[8] = {1, 0, -1, 1, -1, 1, 0, -1};

int wrap(int i, int j) {
	return (i + j) % j;
}

//Determines what color the cell at the given row/col should be. This function allocates space for a new Color.
//Note that you will need to read the eight neighbors of the cell in question. The grid "wraps", so we treat the top row as adjacent to the bottom row
//and the left column as adjacent to the right column.
Color *evaluateOneCell(Image *image, int row, int col, uint32_t rule)
{
	//YOUR CODE HERE
	//count aliveNeighbors in 8 direction(WATCH OUT: R, G, B are seperate)
	//parse the rule
	//determine color
	int aliveNeighborsR = 0, aliveNeighborsG = 0, aliveNeighborsB = 0;
	Color* nextState = (Color*) malloc(sizeof(Color));
	int curStatusR, curStatusG, curStatusB;
	int indexR, indexG, indexB;
	Color** temp = image->image;

	temp += (col + row * (image->cols));
	curStatusB = ((*temp)->B) == 255;
	curStatusG = ((*temp)->G) == 255;
	curStatusR = ((*temp)->R) == 255;

	for(int i = 0; i < 8; i++) {
		int newRow = wrap(row + directionX[i], image->rows);
		int newCol = wrap(col + directionY[i], image->cols);
		if((*(image->image + newCol + newRow * (image->cols)))->R == 255) {
			aliveNeighborsR++;
		}
		if((*(image->image + newCol + newRow * (image->cols)))->G == 255) {
			aliveNeighborsG++;
		}
		if((*(image->image + newCol + newRow * (image->cols)))->B == 255) {
			aliveNeighborsB++;
		}
	}

	indexR = 9 * curStatusR + aliveNeighborsR;
	indexG = 9 * curStatusG + aliveNeighborsG;
	indexB = 9 * curStatusB + aliveNeighborsB;

	if(rule & (1 << indexR)) {
		nextState->R = 255;
	} else {
		nextState->R = 0;
	}
	if(rule & (1 << indexG)) {
		nextState->G = 255;
	} else {
		nextState->G = 0;
	}
	if(rule & (1 << indexB)) {
		nextState->B = 255;
	} else {
		nextState->B = 0;
	}

	return nextState;
}

//The main body of Life; given an image and a rule, computes one iteration of the Game of Life.
//You should be able to copy most of this from steganography.c
Image *life(Image *image, uint32_t rule)
{
	//YOUR CODE HERE
	Image *nextIter = (Image*) malloc(sizeof(Image));
	nextIter->cols = image->cols;
	nextIter->rows = image->rows;
	int totalSize = nextIter->cols * nextIter->rows;
	nextIter->image = (Color**) malloc(sizeof(Color*) * totalSize);
	Color** ptr = nextIter->image;
	for(int i = 0; i < nextIter->rows; i++) {
		for(int j = 0; j < nextIter->cols; j++) {
			*ptr = evaluateOneCell(image, i, j, rule);
			ptr++;
		}
	}
	return nextIter;
}

/*
Loads a .ppm from a file, computes the next iteration of the game of life, then prints to stdout the new image.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a .ppm.
argv[2] should contain a hexadecimal number (such as 0x1808). Note that this will be a string.
You may find the function strtol useful for this conversion.
If the input is not correct, a malloc fails, or any other error occurs, you should exit with code -1.
Otherwise, you should return from main with code 0.
Make sure to free all memory before returning!

You may find it useful to copy the code from steganography.c, to start.
*/
int main(int argc, char **argv)
{
	//YOUR CODE HERE
	if(argc != 3) {
		printf("usage: ./gameOfLife filename rule\n");
		printf("filename is an ASCII PPM file (type P3) with maximum value 255.\n");
		printf("rule is a hex number beginning with 0x; Life is 0x1808.\n");
		return -1;
	}
	Image *img = readData(argv[1]);
	uint32_t rule = strtol(argv[2], NULL, 16);
	Image *next = life(img, rule);
	writeData(next);
	freeImage(img);
	freeImage(next);
	return 0;
}
