#include "Notebook.hpp"
#include "Direction.hpp"
#include <string.h>
#include <iostream>
#include <stdbool.h>
#include <unordered_map>

using namespace ariel;
using namespace std;


ariel::Notebook::Notebook()
{
    // insert constructor details here
    this-> _numPages = 0;
    this-> addPage(1);
    this-> max_row[1] = 10;

}
void ariel::Notebook::write(const int page, const int row, const int column, Direction dir, string str)
{
    if (column < 0 || row < 0 || page <= 0)
        throw(invalid_argument("invalid args"));
    if(!this -> validifyRowExistence(page, row))
        this -> addPage(page);
    if (dir == Direction::Horizontal){
        unsigned int len = str.length();
        if (len + (unsigned int)column >= 100 || column < 0 )
            throw(invalid_argument("invalid args"));
        string _row = this -> getRow(page, row);
        for(unsigned int i= (unsigned int)column; i < (unsigned int)column + len; i++){
            _row.at(i) = str.at(i - (unsigned int)column);
        }
        this -> update_row(page, row, _row);
    }
    else if (dir == Direction::Vertical){
        int len = str.length();
        string _row;
        for(unsigned int i= 0; i < len; i++){ // iterate through the rows and change one by one the char specified
            _row = this -> getRow(page, row);
            _row.at((unsigned int)column) = str.at(i);
            this -> update_row(page,(int)i+row, _row);
        }
    }
    else{
        throw invalid_argument("Direction is not horizontal nor vertical");
    }
}
string ariel::Notebook::read(int page, int row, int column, Direction dir, int len) const
{
    if (page <= 0 || row < 0 || column < 0){
        throw(invalid_argument("read lt eq"));
    }
    if (!this -> validifyRowExistence(page, row)){
        return EMPTY_ROW;
    }
    if (dir == Direction::Horizontal){
        if (column + len >= 100)
            throw invalid_argument("can't read more than column 100");
        string _row = this -> getRow(page,row);
        return _row.substr((unsigned int)column, (unsigned int)len);
    }
    else if (dir == Direction::Vertical){
        string ret = "";
        for (unsigned int i= (unsigned int)row; i < row + len; i++){
            ret.push_back(this -> getRow(page,row).at((unsigned int)column));
        }
        return ret;
    }
    else{
        throw invalid_argument("no such direction");
    }
}
// simply writes len ~ characters into a specific spot
void ariel::Notebook::erase(int page, int row, int column, Direction dir, int len)
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
        this -> write(page,row,column,dir,_row);
    }
    else if(dir == Direction::Vertical){
        string _column = "";
        for (int i=0; i < len; i++){
            _column.push_back('~');
        }
        this -> write(page,row,column,dir,_column);
    }
    else{
        throw(invalid_argument("no such direction"));
    }
}

void ariel::Notebook::show(int page) const
{
    int j=0;
    printf("\n ~Page number %d \n", page);
    printf("%s\n%s\n%s\n", C_COLUMNS, EVEN_COLUMNS, ODD_COLUMNS);
    printPage(page);
}

int pow(int base, int pow){
    if(pow == 0)
        return 1;
    for(int i=1; i< pow; i++){
        base *= base;
    }
    return base;
}
int log(int num, int base){
    int l = 0;
    int temp = num;
    while(temp > 1){
        l++;
        temp /=10;
    }
    return l;
}
void ariel::Notebook::printPage(int numPage) const
{
    string spaces = "";
    int rows = this -> max_row.at(numPage);
    for (int i=0; i<= log(rows, 10) + 1; i++){
        spaces.push_back(' ');
    }
    for(int i=0 ;i< rows; i++){
       // printf("%d ",pow(10,log(i, 10)));
            if (pow(10,log(i, 10)) == i){
            spaces.erase(spaces.begin());
        }
        if (i ==0){
            printf("%d) %s ",i, spaces.c_str());
        }
        else{
            printf("%d) %s  ",i, spaces.c_str());
        }
        printNextRow(numPage, i);
    }
}

void ariel::Notebook::printNextRow(int numPage, int row) const
{
    cout << this -> getRow(numPage, row) << endl;
}

unordered_map<int, string> ariel::Notebook::getPage(int numPage)  const 
{
    if (this -> _pages.find(numPage) == _pages.end()){
        throw invalid_argument("getPage, page not found");
    }
    return _pages.at(numPage);
} 
string ariel::Notebook::getRow(int pageNum, int numRow) const
{
    if (!this -> validifyRowExistence(pageNum,numRow)){
        return EMPTY_ROW;
    }
    return this -> _pages.at(pageNum).at(numRow);
}

void ariel::Notebook::addPage(const int numPage){
    unordered_map<int,string> rows;
    this -> _pages[numPage]= rows;
    this -> max_row[numPage] = 10;
    this -> _numPages +=1;
}

bool ariel::Notebook::validifyRowExistence(const int numPage, const int rowNum) const
{
    //if exists cool
    //if not then add a new row to the map contains only _
    if (this -> _pages.find(numPage) == this -> _pages.end()){
        return false;
    }
    else{
        if (this -> _pages.at(numPage).find(rowNum) == this -> _pages.at(numPage).end()){
            return false;
        }
        else{
            return true;
        }
    }
}
void ariel::Notebook::update_row(int pageNum, int row, string & _row)
{
    if (pageNum <= 0 || row <0)
        throw invalid_argument("update row, received lt eq");
    if (row > this -> max_row.at(pageNum))
       this -> max_row[pageNum] = row + 1;
    this -> _pages[pageNum][row] = _row;
}


