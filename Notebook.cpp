#include "Notebook.hpp"
#include "Direction.hpp"
#include <string.h>
#include <iostream>

using namespace ariel;
using namespace std;

class ariel::Notebook{
    // Notebook()
    // {
    //     // insert constructor details here
    // }
    void Notebook::write(int page, int row, int column, Direction dir, string str)
    {
        if (dir == Direction::Horizontal){
            int len = str.length();
            if (len + column >= 100 || column < 0 )
                throw(invalid_argument("invalid args"));
            string _row = ariel::Notebook::getRow(page, row);
            for(int i= column; i < column + len; i++){
                _row.at(i) = str.at(i - column);
            }
            ariel::Notebook::update_row(page, row, _row);
        }
        else if (dir == Direction::Vertical){
            int len = str.length();
            string _row;
            for(int i= 0; i < len; i++){
                _row = ariel::Notebook::getRow(page, row);
                _row.at(column) = str.at(i);
                ariel::Notebook::update_row(page,i+row, _row);
            }
        }
        else{
            throw invalid_argument("Direction is not horizontal nor vertical");
        }
    }
    string Notebook::read(int page, int row, int column, Direction dir, int len) const
    {
        if (dir == Direction::Horizontal){
            if (column + len >= 100)
                throw invalid_argument("can't read more than column 100");
            string _row = ariel::Notebook::getRow(page,row);
            return _row.substr(column, len);
        }
        else if (dir == Direction::Vertical){
            string ret = "";
            for (int i= row; i < row + len; i++){
                ret.push_back(ariel::Notebook::getRow(page,row).at(column));
            }
            return ret;
        }
        else{
            throw invalid_argument("no such direction");
        }
    }
    // simply writes len ~ characters into a specific spot
    void Notebook::erase(int page, int row, int column, Direction dir, int len)
    {
        if (dir == Direction::Horizontal){
            if (column < 0 || column + len >= 100){
                throw(invalid_argument("invalid args"));
            }
            string _row = "";
            for(int i=0; i < len ; i++)
            {
                _row.push_back('~');
            }
            ariel::Notebook::write(page,row,column,dir,_row);
        }
        else if(dir == Direction::Vertical){
            string _column = "";
            for (int i=0; i < len; i++){
                _column.push_back('~');
            }
            ariel::Notebook::write(page,row,column,dir,_column);
        }
        else{
            throw(invalid_argument("no such direction"));
        }
    }

    void const printPage(int numPage);
    void const printNextRow(int numPage, int row);
    void Notebook::show(int page)
    {
        for(int i=0; i< ariel::Notebook::_numPages; i++){
            printPage(ariel::Notebook::getPage(i));
        }
    }

    void const printPage(int numPage)
    {
        for(int i=0 ;i< ariel::Notebook::_maxRow; i++){
            printNextRow(numPage, i);
        }
    }
    void const printNextRow(int numPage, int row)
    {
        cout << ariel::Notebook::getRow(numPage, row) << endl;
    }

};






