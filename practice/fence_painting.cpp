#include <iostream>
#include <fstream>
#include <algorithm> 

using namespace std;

int main() {
    // 1. Use ifstream and ofstream instead of freopen
    ifstream fin("paint.in");
    ofstream fout("paint.out");

    int a, b, c, d;
    
    // 2. Read directly without the if-statement trap
    fin >> a >> b >> c >> d;

    // 3. Your exact, perfectly correct logic
    int overlap = max(0, min(b, d) - max(a, c));//max(0ll,min(b,d)-max(a,c))
    int answer = (b - a) + (d - c) - overlap;
  
    // 4. Output to the file stream
    fout << answer << endl;

    return 0;
}