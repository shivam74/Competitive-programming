#include <iostream>
inline void read(long long &x) {
    x = 0;
    char c = getchar();
    bool neg = false; 
    while (c < '0' || c > '9') {
        if (c == '-') neg = true;
        c = getchar();
    }
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = getchar();
    }
    if (neg) x = -x;
} 

int main() {
    long long n;
    read(n);
    long long sum = -1e18; 
    long long ans = -1e18;   
    for (int i = 0; i < n; i++) {
        long long x;
        read(x);       
        sum = (sum + x > x) ? (sum + x) : x; 
        ans = (ans > sum) ? ans : sum;
    }
    std::cout<<ans;
    return 0;
}