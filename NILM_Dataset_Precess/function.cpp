#pragma once
#include"function.h"

extern int count;
extern int count_convert;

void read_data(FILE* fp, char* timestamp, float* watt)
{
	fscanf(fp, "%C%C%C%C%C%C%C%C%C%C %f\n", timestamp,
		timestamp + 1,
		timestamp + 2,
		timestamp + 3,
		timestamp + 4,
		timestamp + 5,
		timestamp + 6,
		timestamp + 7,
		timestamp + 8,
		timestamp + 9, watt);
}

void write_data(FILE* fp, char* timestamp, float watt)
{
	fprintf(fp, "%s %.2f\n", timestamp, watt);
}

//void convert(FILE* fp_from, FILE* fp_dest,
//	float window1[WINDOW_HALF_LENGTH],
//	float window2[WINDOW_HALF_LENGTH],
//	char window_1_time[WINDOW_HALF_LENGTH][11],
//	char window_2_time[WINDOW_HALF_LENGTH][11])
//{
//
//	char write_time[11];
//	strcpy(write_time, window_1_time[0]);
//	float write_watt = window1[0];
//
//	//int i = 0;
//
//	while (true)
//	{
//		//��ڶ������ڶ����һ������
//		read_data(fp_from, window_2_time[0], &window2[0]);
//		if (feof(fp_from) != 0)
//		{
//			//����������д�����
//			for (int i = 0; i < WINDOW_HALF_LENGTH; i++)
//			{
//				write_data(fp_dest, window_1_time[i], write_watt);
//			}
//			write_data(fp_dest, window_2_time[0], write_watt);
//
//			count = count + 11;
//			printf("final_count:%d,%d\n", count, count_convert);
//
//			return;
//		}
//
//		//��ֵ�趨
//		//int a = D_watt;
//		//int b = window1[9] * D_watt_percentage;
//		//int D = a < b ? a : b;
//		//int d = D * D_percentage;
//
//		int D = D_watt;
//		int d = D * D_percentage;
//
//		if (fabs(window2[0] - window1[9]) > d)
//		{
//			int time_now = -1;
//			int time_c = 0;
//
//			for (int i = 1; i < WINDOW_HALF_LENGTH; i++)
//			{
//				read_data(fp_from, window_2_time[i], &window2[i]);
//
//				if (feof(fp_from) != 0)
//				{
//					//����������д�����
//					for (int i = 0; i < WINDOW_HALF_LENGTH; i++)
//					{
//						write_data(fp_dest, window_1_time[i], write_watt);
//					}
//
//					for (int j = 0; j <= i; j++)
//					{
//						write_data(fp_dest, window_2_time[j], write_watt);
//					}
//
//					count = count + 11 + i;
//					printf("final_count:%d,%d\n", count, count_convert);
//
//					return;
//				}
//
//				if (fabs(window2[i] - window2[i - 1]) > d)
//				{
//					continue;
//				}
//				else
//				{
//					if (fabs(window2[i] - window1[9]) > D)
//					{
//						//�����¼�����������������¼
//						//��¼�ķ�ΧΪ�Ե�ǰʱ��Ϊ���ĵ�ǰ���������ڵ�����
//						time_now = i;
//						time_c = (int)((time_now - 1) / 2);
//						break;
//					}
//					else
//					{
//						count = count + i + 1;
//						for (int j = 0; j <= i; j++)
//						{
//#ifdef DEBUG
//							if (j >= 10)
//								printf("window_1_time!!!!");
//#endif // DEBUG
//							write_data(fp_dest, window_1_time[j], write_watt);
//						}
//						//�������ݺ���
//						for (int j = 0; j < WINDOW_HALF_LENGTH - i - 1; j++)
//						{
//#ifdef DEBUG
//							if (j + i + 1 >= 10)
//								printf("window_1_time!!!!");
//#endif // DEBUG
//							strcpy(window_1_time[j], window_1_time[j + i + 1]);
//							window1[j] = window1[j + i + 1];
//						}
//						for (int j = WINDOW_HALF_LENGTH - i - 1; j < WINDOW_HALF_LENGTH; j++)
//						{
//							strcpy(window_1_time[j], window_2_time[j - i - 1]);
//							window1[j] = window2[j - i - 1];
//						}
//						break;
//					}
//				}
//			}
//			if (time_now == -1)
//			{
//				continue;
//			}
//			//���ݼ�¼
//			count = count + time_c + 1;
//			for (int i = 0; i <= time_c; i++)
//			{
//#ifdef DEBUG
//				if (i >= 10)
//					printf("window_1_time!!!!");
//#endif // DEBUG
//				write_data(fp_dest, window_1_time[i], write_watt);
//			}
//			//�������ݺ���(window1)
//			for (int i = 0; i < WINDOW_HALF_LENGTH - time_c - 1; i++)
//			{
//#ifdef DEBUG
//				if (i + time_c + 1 >= 10)
//					printf("window_1_time!!!!");
//#endif // DEBUG
//				strcpy(window_1_time[i], window_1_time[i + time_c + 1]);
//				window1[i] = window1[i + time_c + 1];
//			}
//			for (int i = WINDOW_HALF_LENGTH - time_c - 1, j = 0; i < WINDOW_HALF_LENGTH; i++)
//			{
//				strcpy(window_1_time[i], window_2_time[j]);
//				window1[i] = window2[j];
//				j++;
//			}
//			//���ݼ�¼
//			count_convert = count_convert + WINDOW_HALF_LENGTH;
//			count = count + WINDOW_HALF_LENGTH;
//			for (int i = 0; i < WINDOW_HALF_LENGTH; i++)
//			{
//				write_data(fp_dest, window_1_time[i], window1[i]);
//			}
//			//�ٶ�ȡ���ݵ�����2�У����洢
//			for (int i = 0; i < time_now; i++)
//			{
//				strcpy(window_2_time[i], window_2_time[i + time_c + 1]);
//				window2[i] = window2[i + time_c + 1];
//			}
//			for (int i = time_now - (time_c); i < WINDOW_HALF_LENGTH; i++)
//			{
//				read_data(fp_from, window_2_time[i], &window2[i]);
//				if (feof(fp_from) != 0)
//				{
//					//����������д�����
//					for (int j = 0; j <= i; j++)
//					{
//						write_data(fp_dest, window_2_time[j], window2[i]);
//					}
//
//					count = count + i + 1;
//					printf("final_count:%d,%d\n", count, count_convert);
//
//					return;
//				}
//			}
//			count_convert = count_convert + WINDOW_HALF_LENGTH;
//			count = count + WINDOW_HALF_LENGTH;
//			for (int i = 0; i < WINDOW_HALF_LENGTH; i++)
//			{
//				write_data(fp_dest, window_2_time[i], window2[i]);
//			}
//			//�ٶ���10��������Ϊ�µ�window1
//			for (int i = 0; i < WINDOW_HALF_LENGTH; i++)
//			{
//				read_data(fp_from, window_1_time[i], &window1[i]);
//				if (feof(fp_from) != 0)
//				{
//					//����������д�����
//					for (int j = 0; j <= i; j++)
//					{
//#ifdef DEBUG
//						if (j >= 10)
//							printf("window_1_time!!!!");
//#endif // DEBUG
//						write_data(fp_dest, window_1_time[j], window1[0]);
//					}
//
//					count = count + i + 1;
//					printf("final_count:%d,%d\n", count, count_convert);
//
//					return;
//				}
//			}
//			//�����µĳ�ʼֵ
//
//#ifdef DEBUG
//			if (count % 100 == 0)
//			{
//				printf("timestamp:\t%s\tcount:\t%d\t%d\n", window_1_time[0],count, count_convert);
//			}
//#endif // DEBUG
//
//			strcpy(write_time, window_1_time[0]);
//			write_watt = window1[0];
//			//			i++;
//		}
//		else
//		{
//			write_data(fp_dest, window_1_time[0], write_watt);
//			count++;
//			//�������ݺ���
//			for (int i = 0; i < WINDOW_HALF_LENGTH - 1; i++)
//			{
//				strcpy(window_1_time[i], window_1_time[i + 1]);
//				window1[i] = window1[i + 1];
//			}
//			strcpy(window_1_time[9], window_2_time[0]);
//			window1[9] = window2[0];
//			continue;
//		}
//	}
//}

void convert(FILE* fp_from, FILE* fp_dest,
	float window1[WINDOW_HALF_LENGTH],
	float window2[WINDOW_HALF_LENGTH],
	char window_1_time[WINDOW_HALF_LENGTH][11],
	char window_2_time[WINDOW_HALF_LENGTH][11])
{

	char write_time[11];
	strcpy(write_time, window_1_time[0]);
	float write_watt = window1[0];

	//int i = 0;

	while (true)
	{
		//��ڶ������ڶ����һ������
		read_data(fp_from, window_2_time[0], &window2[0]);
		if (feof(fp_from) != 0)
		{
			//����������д�����
			for (int i = 0; i < WINDOW_HALF_LENGTH; i++)
			{
				write_data(fp_dest, window_1_time[i], write_watt);
			}
			write_data(fp_dest, window_2_time[0], write_watt);

			count = count + 11;

#ifdef DEBUG
			printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
			printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
			printf("                                                                      ");
			printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
			printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
			printf("final_count1\t%d\t\t%d\t", count, count_convert);
#endif // DEBUG

			return;
		}


		if (fabs(window2[0] - window1[9]) > D_watt)
		{
			//���ݼ�¼
			count = count +WINDOW_HALF_LENGTH;
			count_convert = count_convert + WINDOW_HALF_LENGTH;

			//��¼window1������
			for (int i = 0; i < WINDOW_HALF_LENGTH; i++)
			{
				write_data(fp_dest, window_1_time[i], window1[i]);
			}


			//�ٶ�9������
			//�ٶ�ȡ���ݵ�����2�У����洢
			for (int i = 1; i < WINDOW_HALF_LENGTH; i++)
			{
				read_data(fp_from, window_2_time[i], &window2[i]);
				if (feof(fp_from) != 0)
				{
					//����������д�����
					for (int j = 0; j <= i; j++)
					{
						write_data(fp_dest, window_2_time[j], window2[i]);
					}

					count = count + i + 1;
					count_convert= count_convert + i + 1;
#ifdef DEBUG
					printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
					printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
					printf("                                                                      ");
					printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
					printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");					
					printf("final_count2\t%d\t\t%d\t", count, count_convert);
#endif // DEBUG
					return;
				}
			}
			count_convert = count_convert + WINDOW_HALF_LENGTH;
			count = count + WINDOW_HALF_LENGTH;
			for (int i = 0; i < WINDOW_HALF_LENGTH; i++)
			{
				write_data(fp_dest, window_2_time[i], window2[i]);
			}

			//�ٶ���10��������Ϊ�µ�window1
			for (int i = 0; i < WINDOW_HALF_LENGTH; i++)
			{
				read_data(fp_from, window_1_time[i], &window1[i]);
				if (feof(fp_from) != 0)
				{
					//����������д�����
					for (int j = 0; j <= i; j++)
					{
						write_data(fp_dest, window_1_time[j], window1[0]);
					}

					count = count + i + 1;
#ifdef DEBUG
					printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
					printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
					printf("                                                                      ");
					printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
					printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
					printf("final_count3\t%d\t\t%d\t", count, count_convert);
#endif // DEBUG
					return;
				}
			}
			//�����µĳ�ʼֵ

#ifdef DEBUG
			if (count % 100 == 0)
			{
				printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
				printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
				printf("timestamp:\t%s\tcount:\t%d\t%d", window_1_time[0], count, count_convert);
			}
#endif // DEBUG

			strcpy(write_time, window_1_time[0]);
			write_watt = window1[0];
		}
		else
		{
			write_data(fp_dest, window_1_time[0], write_watt);
			count++;
			//�������ݺ���
			for (int i = 0; i < WINDOW_HALF_LENGTH - 1; i++)
			{
				strcpy(window_1_time[i], window_1_time[i + 1]);
				window1[i] = window1[i + 1];
			}
			strcpy(window_1_time[9], window_2_time[0]);
			window1[9] = window2[0];
			continue;
		}
	}
}