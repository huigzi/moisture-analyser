#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm.h>
#include <inttypes.h>

extern uint8_t Pattern_ConDomain[360*240];
extern int16_t ConnectDomain_Flag, mutex;
extern double connect_domain_value;

Run run[1000] ;
Graph graph[1000] ;

int16_t Equivalence_Tab[1000][1000] = {0};
int16_t equaList[1000][1000] = {0}, tempList[1000] = {0}, labelFlag[1000] = {0}, labelCount[1000] = {0};
intmax_t equaList_count = 0, tempList_count = 0;
uint64_t Grahp_pair_count = 0, thread = 120, Run_Number = 0, label = 1, curRowIdx = 1, max_count = 0;
double connect_domain_tempo = 0, connect_domain_noise = 0;

typedef enum{
	RUN_HAS_START,
	RUN_NOT_START
}Run_status;

typedef enum{
	NOISE_ACQUISTION_READY,
	NEED_NOISE_ACQUISTION
}Noise_Acquistion_Status;


void ImageConnectDomain(void)
{
	Run_status run_status = RUN_NOT_START;
	int i, j, k;
	intmax_t firstRunOnCur = 0;
    intmax_t firstRunOnPre = 0;
    intmax_t lastRunOnPre = -1;

 //   uintmax_t  arrayLength = strtoumax(argv[1], NULL,10);
 //   void *array[arrayLength];
//    Noise_Acquistion_Status noise_status = NEED_NOISE_ACQUISTION;

    while(1)
    {
    	if(ConnectDomain_Flag == 1)
    	{
    		Run_Number = 0;

    		for(i = 0; i <1000; i++)
    		{
    			run[i] = (struct Run_){0};
    			graph[i] = (struct Graph_){0};
    		}

    		for(i = 0; i < 360*240; i++)
    		{
    			if((Pattern_ConDomain[i] >= thread) && (i%360 != 0) && (i%360 != 359) && (i / 360 != 0) && (i / 360 != 239))
    			{
    				Pattern_ConDomain[i] = 255;
    				if(Run_Number > 999)
    				{
    					Run_Number = 999;
    				}
    				if(run_status == RUN_NOT_START)
    				{
    					run[Run_Number].start = i;
    					run[Run_Number].row = i / 360;

    					if(Pattern_ConDomain[i+1] < thread)
    					{
    						run[Run_Number].end = i;
    					    Run_Number++;
    					}
    					else
    					{
    						run_status = RUN_HAS_START;
    						continue;
    					}
    				}
    				else if(run_status == RUN_HAS_START)
    				{
    					if(Pattern_ConDomain[i+1] < thread)
    					{
    						run[Run_Number].end = i;
    						Run_Number++;
    						run_status = RUN_NOT_START;
    					}
    				}
    			}
    			else
    			{
    				Pattern_ConDomain[i] = 0;
    			}
    		}

    		Grahp_pair_count = 0;
    		firstRunOnCur = 0;
    		firstRunOnPre = 0;
    		lastRunOnPre = -1;
    		label = 1;
    		curRowIdx = 1;

    		for(i = 0; i < Run_Number; i++)
    		{
    			if(run[i].row != curRowIdx)
    			{
    				curRowIdx = run[i].row;
    				firstRunOnPre = firstRunOnCur;
    				lastRunOnPre = i - 1;
    				firstRunOnCur = i;
    			}

    			for (j = firstRunOnPre; j <= lastRunOnPre; j++)
    			{
    				if ((run[i].start % 360) <= (run[j].end % 360) && (run[i].end % 360) >= (run[j].start % 360))
    				{
    					if (run[i].label == 0)// 没有被标号过
    					{
    						run[i].label = run[j].label;
    					}
    					else // 已经被标号
    					{
    						if (run[i].label != run[j].label)
    						{
    							graph[Grahp_pair_count].ecount = run[i].label;// 保存等价
    							graph[Grahp_pair_count].vcount = run[j].label;
    							Grahp_pair_count++;
    						}
    					}
    				}
    			}

    			if (run[i].label == 0) // 没有与前一列的任何run重合
    			{
    				run[i].label = label++;
    			}
    		}

    		memset(Equivalence_Tab, 0, sizeof(Equivalence_Tab));
    		memset(equaList, 0, sizeof(equaList));
    		equaList_count = 0;
    		memset(tempList, 0, sizeof(tempList));
    	    tempList_count = 0;

	//行列为邻接2点的有效数据对，通过某一行或者某一列可以找到与之邻接的团标记
    		for(i = 0; i < Grahp_pair_count; i++)
    		{
    			Equivalence_Tab[graph[i].ecount][graph[i].vcount] = 1;
    			Equivalence_Tab[graph[i].vcount][graph[i].ecount] = 1;
    		}

    		for(i = 1; i < 1000; i++)
    		{
    			if(labelFlag[i - 1] != 0)
    			{
    				continue;
    			}
    			//若为空，则自己和自己至少应该是等价的
    			labelFlag[i - 1] = equaList_count + 1;
    			tempList[tempList_count] = i;
    			tempList_count++;
    			//查看有没有邻接点
    			for(j = 0; j < tempList_count; j++)
    			{
    				for(k = 0; k < 1000; k++)
    				{
    					if(Equivalence_Tab[tempList[j] - 1][k] == 1 && labelFlag[k] == 0)
    					{
    						tempList[tempList_count] = k + 1;
    						tempList_count++;
    						labelFlag[k] = equaList_count + 1;
    					}
    				}
    			}

    			memcpy(equaList[equaList_count], tempList, 1000);
    			equaList_count++;
    			memset(tempList, 0, sizeof(tempList));
    			tempList_count = 0;
    		}

    		for(i = 0; i < 1000; i++)
    		{
    			run[i].label = labelFlag[run[i].label - 1];
    			labelCount[run[i].label - 1] = labelCount[run[i].label - 1] + run[i].end - run[i].start +1;
    		}

    		qksort(labelCount, 0, 999, compare_short);
    		for(i = 989; i < 1000; i++)
    		{
    			connect_domain_tempo += labelCount[i];
    		}

//    		if(noise_status == NEED_NOISE_ACQUISTION)
//    		{
//    			connect_domain_noise = connect_domain_tempo ;
//    		    noise_status = NOISE_ACQUISTION_READY;
//    		}
//
//    		connect_domain_tempo = connect_domain_tempo - connect_domain_noise;
//
//    		if(connect_domain_tempo < 0)
//    		{
//    			connect_domain_tempo = 0;
//    		}

    		printf("Connect domain = %f \n", connect_domain_tempo);

    		if(mutex == 0)
    		{
    			connect_domain_value =connect_domain_tempo;
    		}

    		connect_domain_tempo = 0;
    		memset(labelFlag, 0, sizeof(labelFlag));
    		memset(labelCount, 0, sizeof(labelCount));
    		ConnectDomain_Flag = 0;
    	}
    	else
    	{
    		TaskSleep(50);
    	}
    }
}
