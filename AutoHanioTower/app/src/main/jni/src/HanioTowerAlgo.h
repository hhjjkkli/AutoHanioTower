#pragma once
#include<vector>
using namespace std;

/*
求解汉诺塔解法
*/
class HanioTowerAlgo {
public:
	HanioTowerAlgo(int level);

	vector<int> GetSolution();

	void CalculateSolution(int level, int a, int b, int c);
private:
	int level = 1;//汉诺塔层数
	vector<int> solution;
};
