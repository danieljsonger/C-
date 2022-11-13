#pragma once

#include <vector>
class DisjointSets{
    public:
        void addelements(int num);
        int find(int elem);
        void setunion(int b, int a);
        int size(int elem);
        
    private:
        std::vector<int> _elems;
};