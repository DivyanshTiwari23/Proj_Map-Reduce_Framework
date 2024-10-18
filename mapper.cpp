#include "mapper.h"

void mapping_func(vector<string>& inputs, int id, int chunk_size, VMSVS &key_values)
{
    int start = id * chunk_size;
    for(int i = 0; i < chunk_size; i++)
    {
        stringstream ss(inputs[start + i]);
        string key, value;
        getline(ss, key, '\t');
        getline(ss, value);

        key_values[id][key].push_back(value);
    }
}