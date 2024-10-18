#include "shuffle.h"
#include "mapper.h"

void getIntervals(vector<string>& intervals, int id, VMSVS &key_values, int mappers)
{
    int num_keys = key_values[id].size();
    int interval_size;
    if(mappers > 1)interval_size = num_keys / (mappers - 1);
    else interval_size = num_keys;
    
    int count = 0;
    int map_index = 0;
    string last_key = "";

    for(auto x : key_values[id])
    {   
        last_key = x.first;

        if(map_index%interval_size == 0)
        {
            intervals[id*mappers + count] = x.first;
            count++;
        }
        map_index++;
    }   
    // This is to ensure that the last key is always included in the interval.
    intervals[(id+1)*mappers - 1] = last_key; 
}