#include "Direction.hpp"
#include <string.h>
#include <iostream>
#include <unordered_map>
using namespace std;
namespace ariel{
    class Notebook{
        public:
            void write(int page, int row, int column, Direction dir, std::string str){}
            std::string read(int page, int row, int column, Direction dir, int len){return "";}
            void erase(int page, int row, int column, Direction dir, int len){}
            void show(int page){}
    };
}










