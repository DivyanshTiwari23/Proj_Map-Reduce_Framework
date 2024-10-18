### `HOW TO RUN `
- Run the command 'make' to get an executable with name map_reduce
- It will take input from terminal and output back in terminal
- The input and output format are exactly same as hadoop map-reduce framework we used in assignment 2 of the course.

### `IMPLEMENTATION DETAILS`

- We have used threads in cpp to parallelise the entire process.
- Input will be read by main file
- It will be distributed among mappers number of threads to create a dictionary
- Once this step is completed shuffling is done to keep same keys grouped together
- After the shuffling multiple threads are run to combine the values of same keys by concatenating them. (Reducer step)
- Then the resultatn key value pairs are printed on the terminal.


## `THANK YOU`
