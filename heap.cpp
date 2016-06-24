#include <iostream>
#include <vector>

using namespace std;

template <class T>

class Heap{
    
private:
    vector<T> data;
    int (*comparator)(T, T);
    void swap(T& a, T& b)
    {
        T tmp = a;
        a = b;
        b = tmp;
    }
    
    void exchange(int parent)
    {
        // NO CHILD
        if(parent*2+1 >= data.size()){
            return;
        }
        
        // JUST LIGHT CHILD AND PARENT < LEFT CHILD
        else if(parent*2+2 >= data.size() && comparator(data[parent], data[parent*2+1]) < 0){
            return;
        }
        
        // COUPLE OF CHILDREN AND PARENT < BOTH OF CHILDREN
        else if (comparator(data[parent], data[parent*2+1]) < 0 &&
                 comparator(data[parent], data[parent*2+2]) < 0){
            return;
        }
        
        // COUPLE OF CHILDREN AND LEFT CHILD < RIGHT CHILD (SWAP LEFT CHILD)
        if (parent*2 + 2 < data.size() && comparator(data[parent*2+1], data[parent*2+2]) < 0){
            swap(data[parent], data[parent*2+1]);
            return exchange(parent*2+1);
        }
        
        // SWAP LEFT CHILDREN
        else{
            swap(data[parent], data[parent*2+2]);
            return exchange(parent*2+2);
        }
        
    }
public:
    Heap(int (*func)(T, T))
    {
        vector<T> data;
        comparator = func;
    }
    
    void append(T value)
    {
        int n = (int)data.size();
        data.push_back(value);
        
        int parent = (n - 1) / 2;
        
        while (comparator(data[n], data[parent]) < 0)
        {
            T tmp = data[parent];
            data[parent] = data[n];
            data[n] = tmp;
            
            n = parent;
            parent = (n - 1) / 2;
        }
    }
    
    T pop(){
        T rtn = data[0];
        data[0] = data[data.size() - 1];
        data.erase(data.end() - 1);
        exchange(0);
        return rtn;
    }
    
    int count(){
        return (int)data.size();
    }
    
};
