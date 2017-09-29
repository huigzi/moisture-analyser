#include <algorithm.h>
/*
 *@file algorithm.c
 * @author ��ΰ
 * @version V1.0
 * @todo ��Ҫ����inBuf��cache��ˢ����ԭ����ȡ��Ҫʹ��bufCopy.
 */

/*
 * @brief ԭʼ���ε��㷨�������ؽ���ʱ�����ٶ�����Ҫ��
 * @note �㷨ʱ�临�ӶȲ��ã������иĽ��Ŀռ�
*/
int32_t SearchComponent(uint16_t *restrict x_leftTemp, uint16_t *restrict x_rightTemp, uint16_t *restrict y_topTemp, uint16_t *restrict y_bottomTemp, const uint8_t *restrict diffMap)
{
	int32_t i, flagLeft = 0, flagRight = 0, flagBottom = 0;
	if(* x_leftTemp - 1>=0)
	{
		for(i = *y_topTemp; i < *y_bottomTemp + 1; i++)
		{
			if (*(diffMap + i * 180 + *x_leftTemp - 1) == 0xff)
			{
				flagLeft= 1;
				break;
			}
		}
	}

	if(* x_rightTemp + 1 < 180)
	{
		for(i = *y_topTemp; i < *y_bottomTemp + 1; i++)
		{
			if (*(diffMap + i * 180 + *x_rightTemp + 1) == 0xff)
			{
				flagRight= 1;
				break;
			}
		}
	}

	if(* y_bottomTemp + 1 < 120)
	{
		for(i = *x_leftTemp; i < *x_rightTemp + 1; i++)
		{
			if (*(diffMap + (* y_bottomTemp + 1) * 180 + i) == 0xff)
			{
				flagBottom= 1;
				break;
			}
		}
	}

	*x_leftTemp = *x_leftTemp - 1*(flagLeft == 1);
	*x_rightTemp = *x_rightTemp + 1*(flagRight == 1);
	*y_bottomTemp = *y_bottomTemp + 1*(flagBottom == 1);

	return(flagLeft+flagRight+flagBottom);
}

/*@brief �Ľ���ð���㷨��ʱ�临�Ӷ�ΪO��n����O��n*n��*/

void BubbleSort(int32_t n, RainParameter *restrict rainBuf)
{
	int32_t flag = 1, i, j;
	RainParameter tempBuf = (struct RainParameter_){0};
	for(i = 0; i < n && flag; i++)
	{
		flag = 0;
		for(j = n-1; j >i; j--)
		{
			if((rainBuf + j)->area < (rainBuf + j - 1)->area)
			{
				memcpy(&tempBuf, (rainBuf + j - 1), sizeof(tempBuf));
				memcpy((rainBuf + j - 1), (rainBuf + j), sizeof(tempBuf));
				memcpy((rainBuf + j), &tempBuf, sizeof(tempBuf));
				flag = 1;
			}
		}
	}
	return;
}

/*
 *@brief ����������ֵ�ĵ㲢�����ֵͼ��
 *@note �����㷨�����ݿռ�����ʱЧ����ߣ�Ϊ��֤ʱ�䣬����ͼ�η�Χ�ݶ�Ϊ720*240 ��
 * Ŀǰ�˺���������ʱ��Ϊ9ms���ҡ�
 */

void CalDiffMap(uint8_t *restrict baseMap, const uint8_t *restrict inBuf, uint8_t *restrict diffMap, int32_t *restrict index)
{
	int32_t i, j;
	for(i = 0; i < 345600; i = i + 1440)
	{
		#pragma MUST_ITERATE(720);
		for(j = 0; j < 720; j++)
		{
			if((int16_t)*((uint8_t*)inBuf + i + j) < (int16_t)baseMap[i + j])
			{
				diffMap[((i + j) / 2880) * 180 + ((i + j) % 720) / 4] = 0xff;
			}
		}
	}
	return;
}

/*
 * @brief �����ͼ��ͬʱ������ֵ
 *@note Ŀǰ������ʱ��Ϊ31ms���иĽ���ء�
 */

void CalBaseMap(uint16_t *restrict baseSum,  uint8_t *restrict baseMap)
{
	int32_t i;
	#pragma MUST_ITERATE(345600)
	for(i = 0; i < 345600; i++)
	{
		baseMap[i] =baseSum[i] * 3 / 64;
	}
	return;
}

/*@brief Ŀǰ��16��ͼ��ƽ��  */

void CalSumMap(uint16_t *restrict baseSum, const uint8_t *restrict inBuf, int32_t k)
{
	int32_t i;
	#pragma MUST_ITERATE(21600)
	for(i = 0; i < 21600; i++)
	{
		baseSum[k*21600+i] += *(inBuf+k*21600+i);
	}
	return;
}
