#pragma once
#include"head.h"

extern int count;
extern int count_convert;

void read_data(FILE* fp, char* timestamp, float* watt);

void write_data(FILE* fp, char* timestamp, float watt);

void convert(FILE* fp_from, FILE* fp_dest, float window1[WINDOW_HALF_LENGTH], float window2[WINDOW_HALF_LENGTH], char window_1_time[WINDOW_HALF_LENGTH][11], char window_2_time[WINDOW_HALF_LENGTH][11]);
