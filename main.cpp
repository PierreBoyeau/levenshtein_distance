#include<string>
#include<algorithm>
#include<iostream>
using namespace std;

int mini(int a, int b, int c){
    return(min(a, min(b,c)));
}

int find_path(int& i, int& j, int* dist, int size2, string word1, string word2){
    if(i>0 && j>0){
        int value_mini = mini(dist[(size2+1)*(i-1)+j-1], dist[(size2+1)*(i)+j-1],
                dist[(size2+1)*(i-1)+j]);
        if(dist[(size2+1)*(i-1)+j-1]==value_mini){ //substitution of 2 characters
            cout<<word1[i-1]<<" exchanged with "<<word2[j-1]<<endl;
            i--; j--;
        }
        else if(dist[(size2+1)*(i)+j-1]==value_mini){ // addition of a characters
            cout<<"add "<<word2[j-1]<<endl;
            j--;
        }
        else{  // suppression of a character
            cout<<"suppress "<<word1[i-1]<<endl;
            i--;
        }
    }
    else if(i==0 && j>0){
        cout<<"add "<<word2[j-1]<<endl; j--;
    }
    else if(j==0 && i>0){
        cout<<"suppress "<<word1[i]<<endl; i--;}

}

int levenshtein_dist(string word1, string word2, bool getPath){
    ///
    ///  Please use lower-case strings
    ///
    int size1 = word1.size(), size2 = word2.size();
    int suppr_dist, insert_dist, subs_dist;
    int* dist = new int[(size1+1)*(size2+1)];

    for(int i=0; i<size1+1; ++i)
        dist[(size2+1)*i] = i;
    for(int j=0; j<size2+1; ++j)
        dist[j] = j;
    for(int i=1; i<size1+1; ++i){
        for(int j=1; j<size2+1; ++j){
            suppr_dist = dist[(size2+1)*(i-1)+j] + 1;
            insert_dist = dist[(size2+1)*i+j-1] + 1;
            subs_dist = dist[(size2+1)*(i-1)+j-1];
            if(word1[i-1]!=word2[j-1]){  // word indexes are implemented differently.
                subs_dist += 1;
            }
            dist[(size2+1)*i+j] = mini(suppr_dist, insert_dist, subs_dist);
        }
    }
    // Print list of modifications to make if asked by the user
    // --------------------------------------------------------
    if(getPath){
        int i = size1, j = size2;
        while(i!=0 && j!=0){
            find_path(i, j, dist, size2, word1, word2);
        }
    }
    // --------------------------------------------------------
    int res = dist[(size1+1)*(size2+1) - 1];
    delete dist;
    return(res);
}

int dl_dist(string word1, string word2){
    int size1 = word1.size(), size2 = word2.size();
    int suppr_dist, insert_dist, subs_dist, val;
    int* dist = new int[(size1+1)*(size2+1)];

    for(int i=0; i<size1+1; ++i)
        dist[(size2+1)*i] = i;
    for(int j=0; j<size2+1; ++j)
        dist[j] = j;
    for(int i=1; i<size1+1; ++i){
        for(int j=1; j<size2+1; ++j){
            suppr_dist = dist[(size2+1)*(i-1)+j] + 1;
            insert_dist = dist[(size2+1)*i+j-1] + 1;
            subs_dist = dist[(size2+1)*(i-1)+j-1];
            if(word1[i-1]!=word2[j-1])  // word indexes are implemented differently.
                subs_dist += 1;
            val = mini(suppr_dist, insert_dist, subs_dist);
            if(((i>=2) && (j>=2)) && ((word1[i-1]==word2[j-2]) && (word1[i-2]==word2[j-1])))
                val = min(dist[(size2+1)*(i-2)+j-2]+1, val);
            dist[(size2+1)*i+j] = val;
        }
    }

    int res = dist[(size1+1)*(size2+1) - 1];
    delete dist;
    return(res);
}


int main(){
    string w1 = "ponts";
    string w2 = "hotes";
    cout<<"Word 1 :"<<w1<<endl;
    cout<<"Word 2 :"<<w2<<endl;
    cout<<"Levenshtein distance : "<<endl;
    cout<<levenshtein_dist(w1, w2, true)<<endl;
    cout<<"\n"<<endl;

    w1 = "ecoles";
    w2 = "eclose";
    cout<<"Word 1 :"<<w1<<endl;
    cout<<"Word 2 :"<<w2<<endl;
    cout<<"Damerau-Levenshtein distance : "<<endl;
    cout<<dl_dist(w1, w2)<<endl;
}

