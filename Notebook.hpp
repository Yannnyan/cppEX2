#include "Direction.hpp"
#include <string.h>
#include <iostream>
#include <unordered_map>

#define EMPTY_ROW "____________________________________________________________________________________________________"
using namespace std;
namespace ariel{
    class Notebook{
        private:
            unordered_map<int, unordered_map<int,string> > _pages;
            int _numPages;
            int _maxRow;
            unordered_map<int, string> Notebook::getPage(int numPage)  const 
            {
                if (_pages.find(numPage) == _pages.end()){
                    throw invalid_argument("page not found");
                }
                return _pages.at(numPage);
            } 
            string getRow(int pageNum, int numRow) const
            {
                unordered_map<int, string> page = getPage(pageNum);
                if (page.find(numRow) == page.end()){
                    return EMPTY_ROW;
                }
                return _pages.at(pageNum).at(numRow);
            }
            void update_row(int pageNum, int row, string & _row)
            {
                getPage(pageNum).at(row) = _row;
            }
        public:
            void Notebook::write(int page, int row, int column, Direction dir, string str);
            string Notebook::read(int page, int row, int column, Direction dir, int len);
            void Notebook::erase(int page, int row, int column, Direction dir, int len);
            void Notebook::show(int page);
            

    };
}










