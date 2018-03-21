#include "HanioTowerAlgo.h"
/*
#include <stdio.h>
void hannuota(int n, char a, char b, char c) {
if (n == 1) {
printf("%c->%c\n", a, c);
return ;
}
hannuota(n - 1, a, c, b);
printf("%c->%c\n", a, c);
hannuota(n - 1, b, a, c);
}
main() {
hannuota(4, 'A', 'B', 'C');
}
*/
HanioTowerAlgo::HanioTowerAlgo(int level) {
	this->level = level;
	CalculateSolution(level, 1, 2, 3);
}

vector<int> HanioTowerAlgo::GetSolution() {
	return solution;
}

void HanioTowerAlgo::CalculateSolution(int level, int a, int b, int c) {
	if (level == 1) {
		solution.push_back(a);
		solution.push_back(c);
		return;
	}
	CalculateSolution(level - 1, a, c, b);
	solution.push_back(a);
	solution.push_back(c);
	CalculateSolution(level - 1, b, a, c);
}
