#include "Direction.hpp"
#include <string.h>
#include <iostream>
#include <unordered_map>
#include <stdbool.h>

#define EMPTY_ROW "____________________________________________________________________________________________________"
#define C_COLUMNS   "   0         1         2         3         4         5         6         7         8         9         "
#define EVEN_COLUMNS "   0 2 4 6 8 0 2 4 6 8 0 2 4 6 8 0 2 4 6 8 0 2 4 6 8 0 2 4 6 8 0 2 4 6 8 0 2 4 6 8 0 2 4 6 8 0 2 4 6 8 "
#define ODD_COLUMNS "     1 3 5 7 9 1 3 5 7 9 1 3 5 7 9 1 3 5 7 9 1 3 5 7 9 1 3 5 7 9 1 3 5 7 9 1 3 5 7 9 1 3 5 7 9 1 3 5 7 9"
using namespace std;
namespace ariel{
    class Notebook{
        private:
            unordered_map<int, unordered_map<int,string> > _pages;
            int _numPages;
            unordered_map<int, int> max_row;
            unordered_map<int, string> getPage(int numPage)  const ;
            string getRow(int pageNum, int numRow) const;
            void update_row(int pageNum, int row, string & _row);
            void checkValidString(string str);
            void printNextRow(int numPage, int row) const;
            void printPage(int numPage) const;
            bool validifyRowExistence(int numPage, int rowNum) const;
            void addPage(const int numPage);
            
        public:
            Notebook();
            void write(int page, int row, int column, Direction dir, string str);
            string read(int page, int row, int column, Direction dir, int len); 
            void erase(int page, int row, int column, Direction dir, int len);
            void show(int page);
    };
}










