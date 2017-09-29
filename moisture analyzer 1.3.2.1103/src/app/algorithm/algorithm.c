/**
 *纹理特征的描述是建立在对灰度共生矩阵分析基础上的。灰度共生矩阵的概念最早是1973年由Haralick提出的。1992年Ohanian通过大量理论计算，精确验证了灰度共生矩阵统计特征
 *和纹理结构之间的相关性。
 *2016-10-13增加二叉树算法，求K个最大和最小值
 *2016-12-1增加快速排序算法
 */

#include <algorithm.h>
#include <ti/mathlib/mathlib.h>
#include <string.h>
#include <stdlib.h>

double Lsqe(const double* restrict Moving_sequence , const int count)
{
	double sumx = 0, sumy = 0, sumx2 = 0, sumxy = 0, slope = 0;
	int i, n = 0;
	n = count;
	for(i = 0; i < n; i++)
	{
		sumx = sumx + i;
		sumy = sumy + *(Moving_sequence+i);
		sumx2 = sumx2 + powdp(i, 2);
		sumxy = sumxy + (i * *(Moving_sequence+i));
	}
	slope = (sumxy - ((sumx*sumy) / (double)n)) / (sumx2 - (powdp(sumx, (double)2) / n));
	return slope;
}

double NTC_Iteration(const double NTC_R)
{
	double correct_temperature = 0, NTC_R_Tempo = 0;
	const double C = -0.2426;
	const double D = 4.58;
	const double E = -53.17;
	const double F = 131.6;

	NTC_R_Tempo = logdp(NTC_R);
	correct_temperature = C*powdp(NTC_R_Tempo, 3)+D*powdp(NTC_R_Tempo, 2)+E*NTC_R_Tempo+F;
	return (correct_temperature);
}

double NTC_Black_Iteration(const double NTC_R)
{
	double correct_temperature = 0, NTC_R_Tempo = 0;
	const double A = -0.02251;
	const double B = 0.6218;
	const double C = -6.811;
	const double D = 37.92;
	const double E = -128.5;
	const double F = 224.4;

	NTC_R_Tempo = logdp(NTC_R);
	correct_temperature = A*powdp(NTC_R_Tempo, 5) + B*powdp(NTC_R_Tempo, 4) + C*powdp(NTC_R_Tempo, 3)+D*powdp(NTC_R_Tempo, 2)+E*NTC_R_Tempo+F;
	return (correct_temperature);
}

double Pt100_Iteration(const double PT100_R)
{
	int i;
	double temporary_temperature = 0, correct_temperature = 0;
	const double A_PT100 = 3.9083e-3;
	const double B_PT100 = -5.775e-7;
	const double C_PT100 = -4.183e-12;
	temporary_temperature = (PT100_R / 100 - 1) / A_PT100 ;
	if(PT100_R >= 18.52 && PT100_R < 100) //-200℃- 0℃
	{
	    for(i = 0 ; i < 50 ; i ++)
	    {
	    	correct_temperature = temporary_temperature + (PT100_R - 100*(1 + A_PT100*temporary_temperature + B_PT100*powdp(temporary_temperature,2) -
	    			100*C_PT100*powdp(temporary_temperature,3) + C_PT100*powdp(temporary_temperature,4))) /
	    					(100 * (A_PT100 + 2*B_PT100*temporary_temperature - 300*C_PT100*powdp(temporary_temperature,2) +
	    							4*C_PT100*powdp(temporary_temperature,3))) ;
	    	if(_fabs(correct_temperature - temporary_temperature) < 0.001)
	    		break ;
	        else
	        	temporary_temperature = correct_temperature ;
	    }
	}
	else if(PT100_R >= 100 && PT100_R <= 390.48)  //0℃- 850℃
	{
	    for(i = 0 ; i < 50 ; i ++)
	    {

	    	correct_temperature = temporary_temperature + (PT100_R - 100*(1 + A_PT100*temporary_temperature + B_PT100*powdp(temporary_temperature,2))) /
	    			(100*(A_PT100 + 2*B_PT100*temporary_temperature)) ;

	    	if(_fabs(correct_temperature - temporary_temperature) < 0.001)
	            break ;
	        else
	        	temporary_temperature = correct_temperature ;
	    }
	}
	else
	{
		correct_temperature = 1000;
	}
	return(correct_temperature);
}

double Laplace_GLCM(const double* Difference_Image, const short Threshold_Value)
{
	int i = 0, GLAM_Distance = 5;
	double entropy = 0, tempo_count3 = 0;
	double Laplace_Transform_Tempo[720*480];
	short  tempo_count1 = 0, tempo_count2 = 0, histImage[720*480];
	double GLCM_Tempo[64];

	memset((void*)Laplace_Transform_Tempo, 0, sizeof(Laplace_Transform_Tempo));
	memset((void*)GLCM_Tempo, 0, sizeof(GLCM_Tempo));
	memset((void*)histImage, 0, sizeof(histImage));

	for(i = 0; i < 720*480; i++)
	{
		if((i%720) > 1 || (i/720) > 1 || (i%720) < 718 || (i/720) < 478)
		{
			Laplace_Transform_Tempo[i] = *(Difference_Image+i)*8 - *(Difference_Image+i+1) - *(Difference_Image+i-1) -
					*(Difference_Image+i-720) - *(Difference_Image+i+720) - *(Difference_Image+i+721) - *(Difference_Image+i+719) -
						*(Difference_Image+i-719) - *(Difference_Image+i-721);
			if(Laplace_Transform_Tempo[i] < 0)
			{
				Laplace_Transform_Tempo[i] = -Laplace_Transform_Tempo[i];
			}
			histImage[i] = (short)(Laplace_Transform_Tempo[i] / 7);
			if(histImage[i] > 7)
			{
				histImage[i] = 7;
			}
		}
	}

	for(i = 0; i < 720*480; i++)
	{
		tempo_count1 = histImage[i];
		if(i%720+GLAM_Distance >= 0 && i%720+GLAM_Distance < 720)
		{
			tempo_count2 = histImage[i + GLAM_Distance];
			GLCM_Tempo[tempo_count1*8+tempo_count2]++;
		}
		if(i%720-GLAM_Distance >= 0 && i%720-GLAM_Distance < 720)
		{
			tempo_count2 = histImage[i - GLAM_Distance];
			GLCM_Tempo[tempo_count1*8+tempo_count2]++;
		}
	}

	for(i = 0; i < 720*480; i++)
	{
		tempo_count1 =histImage[i];
		if(i/720+GLAM_Distance >= 0 && i/720+GLAM_Distance < 480)
		{
			tempo_count2 = histImage[i + GLAM_Distance*720];
			GLCM_Tempo[tempo_count1*8+tempo_count2]++;
		}
		if(i/720-GLAM_Distance >= 0 && i/720-GLAM_Distance < 480)
		{
			tempo_count2 = histImage[i - GLAM_Distance*720];
			GLCM_Tempo[tempo_count1*8+tempo_count2]++;
		}
	}

	for(i = 0; i < 720*480; i++)
	{
		tempo_count1 = histImage[i];
		if(i/720+GLAM_Distance >= 0 && i/720+GLAM_Distance < 480 && i%720+GLAM_Distance >= 0 && i%720+GLAM_Distance < 720)
		{
			tempo_count2 = histImage[i + GLAM_Distance*720 + GLAM_Distance];
			GLCM_Tempo[tempo_count1*8+tempo_count2]++;
		}
		if(i/720-GLAM_Distance >= 0 && i/720-GLAM_Distance < 480 && i%720-GLAM_Distance >= 0 && i%720-GLAM_Distance < 720)
		{
			tempo_count2 = histImage[i - GLAM_Distance*720 - GLAM_Distance];
			GLCM_Tempo[tempo_count1*8+tempo_count2]++;
		}
	}

	for(i = 0; i <sizeof(GLCM_Tempo); i++)
	{
		tempo_count3 += GLCM_Tempo[i];
	}

	for(i = 0; i <sizeof(GLCM_Tempo); i++)
	{
		GLCM_Tempo[i] = GLCM_Tempo[i] / (double)tempo_count3;
	}

	for(i = 0; i <sizeof(GLCM_Tempo); i++)
	{
		entropy -= GLCM_Tempo[i] * log10dp(GLCM_Tempo[i]);
	}

	return entropy;
}

Base_Pic* new_Base_Pic(void)
{
	Base_Pic* Tempo_Obj = NULL;
	Tempo_Obj = (Base_Pic*)malloc(sizeof(Base_Pic));
	Tempo_Obj->pDerivedObj = Tempo_Obj;
	if(Tempo_Obj == NULL)
	{
		return NULL;
	}
	Tempo_Obj->Pic_CMOS = (unsigned char*)malloc(sizeof(unsigned char)*720*480);
	if(Tempo_Obj->Pic_CMOS == NULL)
	{
		return NULL;
	}
	return Tempo_Obj;
}

Base_Pic* new_Now_Pattern(void)
{
	Now_Pattern* Tempo_Obj = NULL;
	Tempo_Obj = (Now_Pattern*)malloc(sizeof(Tempo_Obj));
	Base_Pic* Tempo_Base_Obj = new_Base_Pic();
	if(Tempo_Obj == NULL)
	{
		Tempo_Base_Obj->Delete_Num(Tempo_Base_Obj);
		return NULL;
	}
	Tempo_Base_Obj->pDerivedObj = Tempo_Obj;
	Tempo_Obj->pBaseObj = NULL;
	Tempo_Obj->AverageGray = (double*)malloc(sizeof(double)*54);
	if(Tempo_Obj->AverageGray == NULL)
	{
		return NULL;
	}
	return Tempo_Base_Obj;
}

void Obj_Delete_Num(Base_Pic* const Pic_Obj)
{
	memset((void*)(Pic_Obj->Pic_CMOS), 0, sizeof(unsigned char)*720*480);
}

void HeapAdjust_MAX(int nStart, int nLen, Abandon_pixel_tag * restrict abandon_pix_buf)
{
	int nMinChild = 0;
	Abandon_pixel_tag fTemp;
	while((2*nStart + 1)<nLen)
	{
		nMinChild = 2*nStart +1;
		if((2*nStart + 2)<nLen)
		{
			if((abandon_pix_buf+2*nStart+2)->grey < (abandon_pix_buf+2*nStart+1)->grey)
			{
				nMinChild = 2*nStart+2;
			}
		}
		if ((abandon_pix_buf+nStart)->grey > (abandon_pix_buf+nMinChild)->grey)
		{
			fTemp.grey = (abandon_pix_buf+nStart)->grey;
			fTemp.position = (abandon_pix_buf+nStart)->position;

			(abandon_pix_buf+nStart)->grey = (abandon_pix_buf+nMinChild)->grey;
			(abandon_pix_buf+nStart)->position = (abandon_pix_buf+nMinChild)->position;

			(abandon_pix_buf+nMinChild)->grey = fTemp.grey;
			(abandon_pix_buf+nMinChild)->position = fTemp.position;
			nStart = nMinChild;
		}
		else
		{
			break;
		}
	}
	return;
}

void HeapAdjust_MIN(int nStart, int nLen, Abandon_pixel_tag * restrict abandon_pix_buf)
{
	int nMinChild = 0;
	Abandon_pixel_tag fTemp;
	while((2*nStart + 1)<nLen)
	{
		nMinChild = 2*nStart +1;
		if((2*nStart + 2)<nLen)
		{
			if((abandon_pix_buf+2*nStart+2)->grey > (abandon_pix_buf+2*nStart+1)->grey)
			{
				nMinChild = 2*nStart+2;
			}
		}
		if ((abandon_pix_buf+nStart)->grey < (abandon_pix_buf+nMinChild)->grey)
		{
			fTemp.grey = (abandon_pix_buf+nStart)->grey;
			fTemp.position = (abandon_pix_buf+nStart)->position;

			(abandon_pix_buf+nStart)->grey = (abandon_pix_buf+nMinChild)->grey;
			(abandon_pix_buf+nStart)->position = (abandon_pix_buf+nMinChild)->position;

			(abandon_pix_buf+nMinChild)->grey = fTemp.grey;
			(abandon_pix_buf+nMinChild)->position = fTemp.position;
			nStart = nMinChild;
		}
		else
		{
			break;
		}
	}
	return;
}

void BuildHeap_MAX(int nLen, Abandon_pixel_tag * restrict abandon_pix_buf)
{
	int i = 0;
	for(i = nLen/2-1; i>=0; i--)
	{
		HeapAdjust_MAX(i, nLen, abandon_pix_buf);
	}
	return;
}

void BuildHeap_MIN(int nLen, Abandon_pixel_tag * restrict abandon_pix_buf)
{
	int i = 0;
	for(i = nLen/2-1; i>=0; i--)
	{
		HeapAdjust_MIN(i, nLen, abandon_pix_buf);
	}
	return;
}

int compare_short(const short short1, const short short2)
{
	if(short1 > short2)
	{
		return 1;
	}
	else if(short1 < short2)
	{
		return -1;
	}
	else
		return 0;
}

int partition(short* data, int i, int k, int (*compare)(const short key1, const short key2))
{
	int r[3], temp = 0;
	short pvalue = 0;

	r[0] = (rand() % (k - i + 1)) + i;
	r[1] = (rand() % (k - i + 1)) + i;
	r[2] = (rand() % (k - i + 1)) + i;

	if(r[0] > r[1])
	{
		temp = r[1];
		r[1] = r[0];
		r[0] = temp;
	}
	if(r[1] > r[2])
	{
		temp = r[1];
		r[1] = r[0];
		r[0] = temp;
	}

	pvalue = *(data+r[1]);

	i--;
	k++;

	while(1)
	{
		do{
			k--;
		}while(compare_short(*(data+k), pvalue) > 0);

		do{
			i++;
		}while(compare_short(*(data+i), pvalue) < 0);

		if(i >= k)
		{
			break;
		}
		else
		{
			temp = data[k];
			data[k] = data[i];
			data[i] = temp;
		}
	}

	return k;
}

int qksort(short* data, int i, int k, int (*compare)(const short key1, const short key2))
{
	int j;
	while(i < k)
	{
		if((j = partition(data, i, k, compare)) < 0)
		{
			return -1;
		}
		if(qksort(data, i, j, compare) < 0)
		{
			return -1;
		}
		i = j + 1;
	}

	return 0;
}
