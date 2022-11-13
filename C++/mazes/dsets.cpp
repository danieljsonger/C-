#include "dsets.h"

void DisjointSets::addelements(int num){

    int i = 0;
    while(i != num){
        i++;
        _elems.push_back(-1);
    }
}

int DisjointSets::find(int elem){
    if(_elems[elem] < 0){
        return elem;
    }
    return find(_elems[elem]);
}

void DisjointSets::setunion(int a, int b){
        int ind1 = find(a);
        int ind2 = find(b);
        int new_size = _elems[ind1] + _elems[ind2];
        if(_elems[ind1] < _elems[ind2]){
            _elems[ind2] = ind1;
            _elems[ind1] = new_size;
        }
        else if(_elems[ind1] > _elems[ind2]){
            _elems[ind1] = ind2;
            _elems[ind2] = new_size;
        }
        else{
                _elems[ind2] = ind1;
                _elems[ind1] = new_size;

        }
    }
    
int DisjointSets::size(int elem){
    return -1*_elems[find(elem)];
}

