
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

int main(){
    // unordered_map<int,string> map = new unordered_map<int,string>();
    // map.insert(9,"hehexd");
    unordered_map<int,string> map;
    map[1] = "hehexd";
    printf("%s\n", map.at(1).c_str());
    int l;
    char k[256];
    scanf("%d",&l);
    scanf("%s",k);
    map[l] = string(k);
    for(int i=0; i< l; i++){
        map[i] = k;
        printf("%s\n", map[l].c_str());
    }
    return 0;
}