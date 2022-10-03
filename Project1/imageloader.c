/************************************************************************
**
** NAME:        imageloader.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**              Justin Yokota - Starter Code
**				Joe Liu
**
**
** DATE:        2020-08-15
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include "imageloader.h"

//Opens a .ppm P3 image file, and constructs an Image object. 
//You may find the function fscanf useful.
//Make sure that you close the file with fclose before returning.
Image *readData(char *filename) 
{
	//YOUR CODE HERE
	FILE *fp = fopen(filename, "r");
	Image *img = (Image*) malloc(sizeof(Image));
	char fmt[3];
	fscanf(fp, "%s", fmt);
	if(fmt[0] != 'P' || fmt[1] != '3') {
		printf("wrong format\n");
		return NULL;
	}
	fscanf(fp, "%u", &img->cols);
	fscanf(fp, "%u", &img->rows);
	int maxColor;
	fscanf(fp, "%d", &maxColor);
	if(maxColor != 255) {
		printf("wrong max value\n");
		return NULL;
	}
	int totalSize = img->cols * img->rows;
	img->image = (Color**) malloc(sizeof(Color*) * totalSize);
	for(int i = 0; i < totalSize; i++) {
		*(img->image + i) = (Color*) malloc(sizeof(Color));
		Color *temp = *(img->image + i);
		fscanf(fp, "%hhu %hhu %hhu", &temp->R, &temp->G, &temp->B);
	}
	fclose(fp);
	return img;
}

//Given an image, prints to stdout (e.g. with printf) a .ppm P3 file with the image's data.
void writeData(Image *image)
{
	//YOUR CODE HERE
	printf("P3\n");
	printf("%u %u\n", image->cols, image->rows);
	printf("255\n");
	Color** temp = image->image;
	for(int i = 0; i < image->rows; i++) {
		for(int j = 0; j < image->cols - 1; j++) {
			printf("%3u %3u %3u   ", (*temp)->R, (*temp)->G, (*temp)->B);
			temp++;
		}
		printf("%3u %3u %3u", (*temp)->R, (*temp)->G, (*temp)->B);
		printf("\n");
		temp++;
	}
}

//Frees an image
void freeImage(Image *image)
{
	//YOUR CODE HERE
	int totalSize = image->cols * image->rows;
	for(int i = 0; i < totalSize; i++) {
		free(*(image->image + i));
	}
	free(image->image);
	free(image);
}