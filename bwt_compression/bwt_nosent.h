#pragma once

#include <string>
#include <utility>
#include <vector>
#include <algorithm>

std::pair<std::string, int> encode(const std::string &s) {
    if(s.empty()) return {"",0};
    std::vector<std::string> rotations;
    for(size_t i=0;i<s.size();i++){
        std::string rotation=s;
        std::rotate(rotation.begin(),rotation.begin()+i,rotation.end());
        rotations.push_back(rotation);
    }
    std::sort(rotations.begin(),rotations.end());
    std::string last_column;
    int original_pos=-1;
    for(size_t i=0;i<rotations.size();i++){
        last_column+=rotations[i].back();
        if(rotations[i]==s){
            original_pos=i;
        }
    }
    return {last_column,original_pos};
}

std::string decode(const std::string &s, int n) {
    if(s.empty()) return "";
    std::vector<std::string> table(s.size(),"");
    for(size_t i=0;i<s.size();i++){
        for(size_t j=0;j<s.size();j++){
            table[j]=s[j]+table[j];
        }
        std::sort(table.begin(),table.end());
    }
    return table[n];
}