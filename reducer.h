#ifndef REDUCER
#define REDUCER

#include <bits/stdc++.h>
using namespace std;
#define VMSVS vector<map<string, vector<string>>>

void reduce_func(vector<string>& partition, VMSVS &key_values, int id, VMSVS &key_values_reduced,  mutex &data_lock);

#endif

