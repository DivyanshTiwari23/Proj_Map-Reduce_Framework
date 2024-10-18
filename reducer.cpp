#include "reducer.h"
#include <bits/stdc++.h>
using namespace std;

void reduce_func(vector<string>& partition, VMSVS &key_values, int id, VMSVS &key_values_reduced,  mutex &data_lock)
{
    string current = partition[0];
    int idx = 0;

    for(auto x : key_values[id])
    {   
        while(current < x.first)
        {
            idx++;
            current = partition[idx];
        }
        if(x.first <= current)
        {
            data_lock.lock();
            for(auto y : x.second)
            {
                key_values_reduced[idx][x.first].push_back(y);
            }
            data_lock.unlock();
        }
    }
}
