#pragma once
#include<stdio.h>
#include<string.h>
#include<stdio.h>
#include<math.h>
#include<stdlib.h>

//事件触发的判定：
//功率差值大于20W或20% 取小的

#define WINDOW_HALF_LENGTH 10	//半窗口长度 10个采样点 （10秒）
#define D_watt 5				//功率差阈值（绝对值）
//#define D_watt_percentage 0.2	//功率差阈值（相对值）
#define D_percentage 1		//首次判断的阈值 50%

#define DEBUG