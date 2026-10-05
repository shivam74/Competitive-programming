#include <iostream>
#include <cstring>
#include <cstdlib>

typedef long long llint;

llint alignProcess(int M, int N, int *rtime, int *complex)
{
    // 1. Calculate prefix sums of robot times
    llint *pref = new llint[N + 1];
    pref[0] = 0;
    for (int i = 0; i < N; ++i) {
        pref[i + 1] = pref[i] + rtime[i];
    }

    // 2. Arrays to store the upper convex hull of lines (y = m*x + c)
    llint *hull_m = new llint[N + 1];
    llint *hull_c = new llint[N + 1];
    int hull_sz = 0;

    // 3. Build the upper envelope in O(N)
    for (int i = 1; i <= N; ++i) {
        llint m = -pref[i - 1];
        llint c = pref[i];

        while (hull_sz >= 2) {
            llint m1 = hull_m[hull_sz - 2], c1 = hull_c[hull_sz - 2];
            llint m2 = hull_m[hull_sz - 1], c2 = hull_c[hull_sz - 1];
            llint m3 = m, c3 = c;
            
            // Check if the middle line (m2, c2) is redundant.
            // Cross-multiplying the intersection condition to prevent double precision loss
            if ((c3 - c2) * (m1 - m2) >= (c2 - c1) * (m2 - m3)) {
                hull_sz--;
            } else {
                break;
            }
        }
        hull_m[hull_sz] = m;
        hull_c[hull_sz] = c;
        hull_sz++;
    }

    llint current_start = 0;
    
    // 4. Calculate the minimum start time for each subsequent chip in O(M log N)
    for (int j = 1; j < M; ++j) {
        llint fj_1 = complex[j - 1];
        llint fj = complex[j];

        int l = 0, r = hull_sz - 2;
        int best_idx = hull_sz - 1;

        // Binary search to find the optimal line for the ratio fj / fj_1
        while (l <= r) {
            int mid = l + (r - l) / 2;
            llint mA = hull_m[mid], cA = hull_c[mid];
            llint mB = hull_m[mid + 1], cB = hull_c[mid + 1];

            // If x is to the right of the intersection, line A is better
            if (fj * (mA - mB) >= fj_1 * (cB - cA)) {
                best_idx = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        current_start += fj_1 * hull_c[best_idx] + fj * hull_m[best_idx];
    }

    // 5. Total time is the accumulated start time plus the processing phase for the very last chip
    llint ans = current_start + (llint)complex[M - 1] * pref[N];

    // Cleanup dynamic memory
    delete[] pref;
    delete[] hull_m;
    delete[] hull_c;

    return ans;
}

int main( void )
{
    int M, N;
    int *rtime;
    int *complex;
    
    std::cin >> N >> M;
    
    rtime = new int[N];
    complex = new int[M];
    
    for( int i = 0; i < N; ++i )
        std::cin >> *(rtime + i);
        
    for( int i = 0; i < M; ++i )
        std::cin >> *(complex + i);
        
    std::cout << alignProcess(M, N, rtime, complex) << "\n";
    
    delete[] rtime;
    delete[] complex;
    
    return 0;
}