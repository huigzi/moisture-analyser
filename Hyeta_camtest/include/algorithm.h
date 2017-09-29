#pragma once

#include <inttypes.h>

typedef struct RainParameter_
{
	uint16_t left;
	uint16_t top;
	uint16_t right;
	uint16_t bottom;
	uint32_t area;
}RainParameter;

extern uint8_t temple_frame[20][350000];

int32_t  SearchComponent(uint16_t *restrict x_leftTemp, uint16_t *restrict x_rightTemp, uint16_t *restrict y_topTemp, uint16_t *restrict y_bottomTemp, const uint8_t *restrict diffMap);
void  BubbleSort(int32_t n, RainParameter *restrict rainBuf);
void  CalDiffMap(uint8_t *restrict baseMap, const uint8_t *restrict inBuf, uint8_t *restrict diffMap, int32_t *restrict index);
void  CalBaseMap(uint16_t *restrict baseSum, uint8_t *restrict baseMap);
void CalSumMap(uint16_t *restrict baseSum, const uint8_t *restrict inBuf, int32_t k);
