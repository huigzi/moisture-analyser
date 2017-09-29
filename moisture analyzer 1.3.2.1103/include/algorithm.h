/**
 * @brief  This file contains all the algorithm.
 * @author SUWEI
 * 2016.9.18 Add PT100 iterated algorithm
 *
 */
//#ifndef _ALGORITHM_
//#define _ALGORITHM_
#pragma once

#ifdef _cplusplus
extern "C" {
#endif

extern unsigned char average_10_pic[720*480];

double Pt100_Iteration(const double PT100_R);
double NTC_Iteration(const double NTC_R);
double NTC_Black_Iteration(const double NTC_R);
double Laplace_GLCM(const double* Difference_Image, const short Threshold_Value);
double Lsqe(const double* restrict Moving_sequence, const int count);

typedef struct Base_Pic_tag
{
	void* pDerivedObj;
	unsigned char* Pic_CMOS;
	void  (*Delete_Num)(void*);

}Base_Pic;

typedef struct Now_Pattern_tag
{
	Base_Pic* pBaseObj;
	double *AverageGray;

}Now_Pattern;

typedef struct Abandon_pixel_tag_
{
	unsigned char grey;
	int position;

}Abandon_pixel_tag;

typedef struct Run_
{
	int start;
	int end;
	int row;
	int label;
}Run;

typedef struct Graph_
{
	int ecount;
	int vcount;
}Graph;

void HeapAdjust_MAX(int nStart, int nLen, Abandon_pixel_tag * restrict abandon_pix_buf);
void BuildHeap_MAX(int nLen, Abandon_pixel_tag * restrict abandon_pix_buf);
void HeapAdjust_MIN(int nStart, int nLen, Abandon_pixel_tag * restrict abandon_pix_buf);
void BuildHeap_MIN(int nLen, Abandon_pixel_tag * restrict abandon_pix_buf);
void Obj_Delete_Num(Base_Pic* const Pic_Obj);
Base_Pic* new_Base_Pic(void);
Base_Pic* new_Now_Pattern(void);

int compare_short(const short short1, const short short2);
int partition(short* data, int i, int k, int (*compare)(const short key1, const short key2));
int qksort(short* data, int i, int k, int (*compare)(const short key1, const short key2));

#ifdef _cplusplus
}
#endif

//#endif
