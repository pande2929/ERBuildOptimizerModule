#ifndef SUBSET_SUM_H
#define SUBSET_SUM_H

#include <vector>

using namespace std;

class SubsetSum {
public:
	static vector<unsigned long long> GetAllSubsets(const int target, const int min_max[][2]);

private:
	static vector<unsigned long long> GetSubsetPartial(const int target, const int start, const int count, const int min_max[][2]);
	static void ConcatVector(vector<unsigned long long>& a, vector<unsigned long long> const& b);
};

#endif // SUBSET_SUM_H