#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

class Tree_generator
{
private:

    string createTree(int depth, char startChar);
    
public:
    void generateTree(int depth, int numTests);
};