//
// Created by hejiang on 2018/3/21.
//
//需要include SDL.h文件，否则libmain.so找不到入口函数
#include "SDL.h"
#include "entry.h"

int main(int argc, char* argv[])
{
	entry(argc, argv);

	return 0;
}
