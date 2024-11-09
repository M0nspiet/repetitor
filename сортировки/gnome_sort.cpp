#include<stdlib.h>
#include<vector>
#include<iostream>
#include <algorithm>

using namespace std;
const int n = 30;

int recursive_binsearch(const vector<int>& vec, int left, int right, int chislo) {
    if (left > right) {
        return -1;
    }
    int mid = left + (right - left) / 2;

    if (vec[mid] == chislo) {
        return mid;
    }
    else if (chislo < vec[mid]) {
        return recursive_binsearch(vec, left, mid - 1, chislo);
    }
    else {
        return recursive_binsearch(vec, mid + 1, right, chislo);
    }
}

void gnome_sort(vector<int> &vec){
    int n = vec.size();
    for(int i = 0; i < n; i++){
        int j = 0;
        while(j < vec.size() -1 ){
            if(vec[j] <= vec[j+1]){
                j++;
                continue;
            }
            swap(vec[j], vec[j+1]);
            j--;
            if(j<0){
                break;
            }
        }
    }
}

int main(){
    vector<int> vec(n);

    for(int i = 0; i < n; i++){
        vec[i] = rand()%100-50;
    }

    gnome_sort(vec);
    
    
    for(int i = 0; i < n; i++){
        cout << vec[i] <<"\n";
    }

    int indx = recursive_binsearch(vec, 0, vec.size() - 1, 8);

    cout <<"indx = " << indx;
}