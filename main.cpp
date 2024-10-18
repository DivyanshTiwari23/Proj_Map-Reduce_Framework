#include <bits/stdc++.h>
using namespace std;

#include "mapper.h"
#include "shuffle.h"
#include "reducer.h"

int mappers = 2;
int reducers = 2;

int main(int argc, char ** argv)
{
    if(argc > 2)
    {
        mappers = atoi(argv[1]);
        reducers = atoi(argv[2]);
    }
    else if(argc > 1)
    {
        mappers = atoi(argv[1]);
    }

    // This act likes a controller node. 
    // It will read the input given.
    // Then distribute it among other nodes to process it parallely.

    vector<string> inputs;
    string line;

    while(getline(cin, line))
    {
        inputs.push_back(line);
    }
    
    vector<thread> mapper_threads(mappers);
    int input_size = inputs.size();
    int chunk_size_ = input_size / mappers;

    // This is supposed to be sending chunk_size data to each mapper.
    // But since we dont have communication channels here, we are simulating it.
    // So here, we are sending the entire data.

    // Since data is local to thread and once the function is executed the data is lost, 
    // we are storing the data in a global variable.
    // It simulates the local storage of each thread and we are ensuring not to use this global variable,
    // like shared memory across threads but to send this data only through communication.

    // cout<<"yaha tak sab changa si"<<endl;

    VMSVS key_values(mappers);
    
    // Mapping part from each node.
    for(int i = 0; i < mappers; i++)
    {
        mapper_threads[i] = thread(mapping_func, ref(inputs), i, chunk_size_, ref(key_values));
    }

    for(int i = 0; i < mappers; i++)
    {
        mapper_threads[i].join();
    }

    // Shuffling part from each node starts.

    // cout<<"yaha tak bhi sab changa si"<<endl;

    vector<string> keys_distribution(mappers*mappers);
    for(int i = 0; i < mappers; i++)
    {
        mapper_threads[i] = thread(getIntervals, ref(keys_distribution), i, ref(key_values), mappers);
    }

    for(int i = 0; i < mappers; i++)
    {
        mapper_threads[i].join();  // all nodes reported to the controller node.
    }

    // This part is done by controller node.
    sort(keys_distribution.begin(), keys_distribution.end());
    int chunk_size = keys_distribution.size() / reducers;

    vector<string> partitions(reducers);  
    string last_key = keys_distribution[0];
    partitions[0] = last_key;
    int count = 0;

    for(int i = 1; i < keys_distribution.size(); i++)
    {
        if(i%chunk_size == 0)
        {   
            while(i < keys_distribution.size() && keys_distribution[i] == last_key)i++;
            if(i < keys_distribution.size())
            {
                last_key = keys_distribution[i];
                partitions[count] = last_key;
                count++;
            }
        }
    }
    if(last_key != keys_distribution.back())
    {
        partitions[reducers - 1] = keys_distribution.back();
    }

    VMSVS key_values_reduced(reducers);
    mutex data_lock;

    for(int i = 0; i < mappers; i++)
    {
        mapper_threads[i] = thread(reduce_func, ref(partitions), ref(key_values), i, ref(key_values_reduced), ref(data_lock));
    }
    for(int i = 0; i < mappers; i++)
    {
        mapper_threads[i].join();
    }

    // Printing the output.
    for(int i = 0; i < reducers; i++)
    {
        for(auto x : key_values_reduced[i])
        {
            cout << x.first << "\t";
            for(auto y : x.second)
            {
                cout << y << " ";
            }
            cout << endl;
        }
    }

    return 0;
}