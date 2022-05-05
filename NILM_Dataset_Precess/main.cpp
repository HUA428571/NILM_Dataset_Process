#include"head.h"
#include"function.h"

int count = 0;
int count_convert = 0;

//事件触发的判定：
//功率差值大于30W或30% 取小的

//REDD 数据格式：
// 1303132929 224.19
// 时间戳（10位）+空格+功率

int convert_house(int label_count, char *location,char *location_dest)
{
	count = 0;
	count_convert = 0;

	FILE* fp = NULL;
	FILE* fp_dest = NULL;

	char label[8]="\0";

	_itoa(label_count, label,10);

	strcat(location, label);
	strcat(location, ".dat");
	strcat(location_dest, label);
	strcat(location_dest, ".dat");

	fp = fopen(location, "r");
	if (fp == 0)
	{
		return -1;
	}
	fp_dest = fopen(location_dest, "w");
	if (fp_dest == 0)
	{
		return -1;
	}

	float window1[WINDOW_HALF_LENGTH];
	float window2[WINDOW_HALF_LENGTH];

	char window_1_time[WINDOW_HALF_LENGTH][11] = { "0000000000" };
	char window_2_time[WINDOW_HALF_LENGTH][11] = { "0000000000" };

	//先读10个数据
	for (int i = 0; i < WINDOW_HALF_LENGTH; i++)
	{
		read_data(fp, window_1_time[i], &window1[i]);
	}

	convert(fp, fp_dest, window1, window2, window_1_time, window_2_time);

#ifdef DEBUG
	printf("Finish:%s\n", location_dest);
#endif // DEBUG

	fclose(fp);
	fclose(fp_dest);
}

int main()
{
	char location[100];
	char location_dest[100];

	for (int i = 1; i <= 22; i++)
	{
		strcpy(location, "../low_freq/house_3/channel_");
		strcpy(location_dest, "../low_freq_convert/house_3/channel_");
		convert_house(i, location, location_dest);
	}

	return 0;
}

