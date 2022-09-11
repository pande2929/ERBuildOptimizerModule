#include <vector>
#include <future>
#include <algorithm>
#include "./include/SubsetSum.h"

using namespace std;

// Async worker thread. Performs a subset of the nested loop target sum evaluation.
vector<unsigned long long>
SubsetSum::GetSubsetPartial(const int target, const int start, const int count, const int min_max[][2]) {
    vector<unsigned long long> solutions;
    unsigned long long result = 0;

    // How would constraints work?
    // s_min, s_max
    // d_min, d_max
    // i_min, i_max
    // f_min, f_max
    // a_min, a_max

    // Mins must be: greatest of the attr_req mainhand, attr_req offhand, and base attribute in class
    // Maxes can either go up to 99, OR min value + 1 if not a scaling (correction > 0) attribute.

    for (int s = start; s <= start + count; s++) {
        for (int d = min_max[1][0]; d <= min_max[1][1]; d++) {
            for (int i = min_max[2][0]; i <= min_max[2][1]; i++) {
                for (int f = min_max[3][0]; f <= min_max[3][1]; f++) {
                    for (int a = min_max[4][0]; a <= min_max[4][1]; a++) {
                        if (s + d + i + f + a == target) {
                            result &= 0;
                            result |= (unsigned long long) s << 32;
                            result |= (unsigned long long) d << 24;
                            result |= (unsigned long long) i << 16;
                            result |= (unsigned long long) f << 8;
                            result |= (unsigned long long) a;

                            solutions.push_back(result);
                        }
                    }
                }
            }
        }
    }

    return solutions;
}

// Concatenate the second vector into the first.
inline void SubsetSum::ConcatVector(vector<unsigned long long> &a, const vector<unsigned long long> &b) {
    a.reserve(a.size() + b.size());
    a.insert(a.end(), b.begin(), b.end());
}

// Performs a multi-threaded brute force. All five bytes of the tuple are stored in an unsigned long long.
vector<unsigned long long> SubsetSum::GetAllSubsets(const int target, const int min_max[][2]) {
    const int THREAD_COUNT = 3;
    int set_size = (min_max[0][1] - min_max[0][0]) / THREAD_COUNT;
    int remainder = (min_max[0][1] - min_max[0][0]) % THREAD_COUNT;

    int offset = min_max[0][0];

    vector<unsigned long long> solutions;

    // Async threads
    auto f0 = async(launch::async, &SubsetSum::GetSubsetPartial, target, 0 * set_size + offset, set_size, min_max);
    auto f1 = async(launch::async, &SubsetSum::GetSubsetPartial, target, 1 * set_size + offset, set_size, min_max);
    auto f2 = async(launch::async, &SubsetSum::GetSubsetPartial, target, 2 * set_size + offset, set_size, min_max);
    auto f3 = async(launch::async, &SubsetSum::GetSubsetPartial, target, 3 * set_size + offset, remainder - 1, min_max);

    // Combine async results into one vector
    ConcatVector(solutions, f0.get());
    ConcatVector(solutions, f1.get());
    ConcatVector(solutions, f2.get());
    ConcatVector(solutions, f3.get());

    sort(solutions.begin(), solutions.end());

    return solutions;
}