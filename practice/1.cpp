#include <bits/stdc++.h>
using namespace std;

void getResult(int D, int N, int soundTrack[][2]){
    long long X = 0;
    map<int, int> uniqueSongs;

    // Step 1: Add up all T to get sum X.
    // Step 3 (prep): Find the lowest T for each unique song.
    for(int i = 0; i < N; ++i){
        int S = soundTrack[i][0];
        int T = soundTrack[i][1];
        
        X += T; 
        
        if(uniqueSongs.find(S) == uniqueSongs.end()){
            uniqueSongs[S] = T;
        } else {
            uniqueSongs[S] = min(uniqueSongs[S], T);
        }
    }

    // Step 2: Multiply X with the number of unique songs to get Y.
    long long K = uniqueSongs.size();
    long long Y = X * K;

    // Extract the lowest T values for each unique song to sort them.
    vector<int> min_T;
    for(auto const& pair : uniqueSongs){
        min_T.push_back(pair.second);
    }

    // Step 3: Sort all the retained songs in descending order according to T.
    sort(min_T.begin(), min_T.end(), greater<int>());

    // Step 4 & 5: Multiply T of each unique song with sequence number, sum them up to subtract from Y.
    long long sum_P = 0;
    for(int i = 0; i < K; ++i){
        sum_P += (long long)min_T[i] * i; 
    }

    long long Z = Y - sum_P;
    
    // Calculate final result R
    long long R = Z - D;

    // Step 6: Print Z, followed by R, followed by the comparison symbol.
    cout << Z << "\n";
    cout << R << "\n";
    
    if (Z < D) {
        cout << "<" << "\n";
    } else if (Z == D) {
        cout << "=" << "\n";
    } else {
        cout << ">" << "\n";
    }
}

int main()
{
    int D,N;
    cin>>D;
    cin>>N;
    int soundTrack[N][2];
    for(int i=0; i<N; ++i){
        cin>>soundTrack[i][0];
        cin>>soundTrack[i][1];
    }
    getResult(D, N, soundTrack);
    return 0;
}