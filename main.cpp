#include<string>
#include<algorithm>
#include<iostream>
using namespace std;

int mini(int a, int b, int c){
    return(min(a, min(b,c)));
}

int levenshtein_dist(string word1, string word2){
    ///
    ///  Please use lower-case strings
    ///
    int size1 = word1.size(), size2 = word2.size();
    int suppr_dist, insert_dist, subs_dist;
    int* dist = new int[(size1+1)*(size2+1)];

    for(int i=0; i<size1+1; ++i){
        dist[(size2+1)*i] = 0;
    }
    for(int j=0; j<size2+1; ++j){
        dist[j] = 0;
    }
    for(int i=1; i<size1+1; ++i){
        for(int j=1; j<size2+1; ++j){
            suppr_dist = dist[(size2+1)*(i-1)+j] + 1;
            insert_dist = dist[(size2+1)*i+j-1] + 1;
            subs_dist = dist[(size2+1)*(i-1)+j-1];
            if(word1[i-1]!=word2[j-1]){
                subs_dist += 1;
            }
            dist[(size2+1)*i+j] = mini(suppr_dist, insert_dist, subs_dist);
        }
    }
    int res = dist[(size1+1)*(size2+1) - 1];
    delete dist;
    return(res);
}

int main(){
    string w1 = "ponts";
    string w2 = "hotes";
    cout<<levenshtein_dist(w1,w2)<<endl;
}

