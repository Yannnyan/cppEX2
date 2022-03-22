#include "doctest.h"
#include "Notebook.hpp"
#include "Direction.hpp"
#include <string.h>
#include <iostream>
#include <limits.h>

using namespace ariel;
using namespace std;

enum args{
    page,
    column,
    row,
    custom
};
enum func{
    write,
    read,
    erase
};
TEST_CASE("Good input"){
    Notebook book;
    // checking write func
    book.write(1,10,10,Direction::Horizontal,"+++++=====hello world!======++++");
    book.write(1,1000,10,Direction::Horizontal, "+++++=====hello world!======++++");
    book.write(1,0,0,Direction::Horizontal, "this is my special notebook and here i write about my nightmares from first year");
    book.write(1,0,97,Direction::Horizontal, "xd");
    book.write(1,1,50,Direction::Horizontal, "mexican ground karate");
    book.write(1,49,9,Direction :: Horizontal, "carpet");


    book.write(1,50,10,Direction::Horizontal,"I I I I I I I I I I I");
    book.write(1,51,10,Direction::Horizontal,"I Q Q Q Q Q Q Q Q Q I");
    book.write(1,52,10,Direction::Horizontal,"I Q I I I I I I I Q I");
    book.write(1,53,10,Direction::Horizontal,"I Q I Q Q Q Q Q I Q I");
    book.write(1,54,10,Direction::Horizontal,"I Q I Q I I I Q I Q I");
    book.write(1,55,10,Direction::Horizontal,"I Q I Q I Q I Q I Q I");
    book.write(1,56,10,Direction::Horizontal,"I Q I Q I I I Q I Q I");
    book.write(1,57,10,Direction::Horizontal,"I Q I Q Q Q Q Q I Q I");
    book.write(1,58,10,Direction::Horizontal,"I Q I I I I I I I Q I");
    book.write(1,59,10,Direction::Horizontal,"I Q Q Q Q Q Q Q Q Q I");
    book.write(1,60,10,Direction::Horizontal,"I I I I I I I I I I I");


    book.write(1,80,10,Direction::Vertical,"I I I I I I I I I I I");
    book.write(1,81,10,Direction::Vertical,"I Q Q Q Q Q Q Q Q Q I");
    book.write(1,82,10,Direction::Vertical,"I Q I I I I I I I Q I");
    book.write(1,83,10,Direction::Vertical,"I Q I Q Q Q Q Q I Q I");
    book.write(1,84,10,Direction::Vertical,"I Q I Q I I I Q I Q I");
    book.write(1,85,10,Direction::Vertical,"I Q I Q I Q I Q I Q I");
    book.write(1,86,10,Direction::Vertical,"I Q I Q I I I Q I Q I");
    book.write(1,87,10,Direction::Vertical,"I Q I Q Q Q Q Q I Q I");
    book.write(1,88,10,Direction::Vertical,"I Q I I I I I I I Q I");
    book.write(1,89,10,Direction::Vertical,"I Q Q Q Q Q Q Q Q Q I");
    book.write(1,90,10,Direction::Vertical,"I I I I I I I I I I I");

    // checking read func
    CHECK(book.read(1,10,10,Direction::Horizontal,32).compare("+++++=====hello world!======++++"));
    CHECK(book.read(1,1000,10,Direction::Horizontal,32).compare("+++++=====hello world!======++++"));
    CHECK(book.read(1,1,50,Direction::Horizontal,6).compare("carpet"));
    CHECK(book.read(1,0,97,Direction::Horizontal,2).compare("xd"));
    CHECK(book.read(1,55,10,Direction::Horizontal,11).compare("Q"));
    


    // checking erase func
    book.erase(1,1000,10,Direction::Horizontal,32);
    CHECK(book.read(1,1000,10,Direction::Horizontal,32).compare("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"));
    book.erase(1,0,0,Direction::Horizontal,80);
    string str = "";
    for(int i=0; i< 80; i++)
        str.append("~");
    CHECK(book.read(1,0,0,Direction::Horizontal, 80).compare(str));

}

int checkFunction(func foo, args arg, Notebook book, Direction dir = Direction::Vertical, string str = "hello", int len = 1){
    if (foo == func::write){
        if(arg == args::page){
            // CHECK PAGE
            CHECK_THROWS(book.write(INT_MAX,1,1,dir,str));
            CHECK_THROWS(book.write(INT_MIN,1,1,dir,str));
            
            for(int i=-1; i> -100; i--)
                CHECK_THROWS(book.write(-1,1,1,dir,str));
        }
        else if(arg == args::row){
            // CHECK ROW
            CHECK_THROWS(book.write(1,INT_MAX,1,dir,str));
            CHECK_THROWS(book.write(1,INT_MIN,1,dir,str));
            
            for(int i=-1; i> -100; i--)
                CHECK_THROWS(book.write(1,i,1,dir,str));
        }
        else if(arg == args::column){
            // CHECK COLUMN

            CHECK_THROWS(book.write(1,1,INT_MAX,dir,str));
            CHECK_THROWS(book.write(1,1,INT_MIN,dir,str));
            CHECK_THROWS(book.write(1,1,101,dir,str));
            CHECK_THROWS(book.write(1,1,2000,dir,str));
            CHECK_THROWS(book.write(1,1,123456678,dir,str));
            for(int i=-1; i> -100; i--)
                CHECK_THROWS(book.write(1,1,-1,dir,str));
        }
        else if(arg == args::custom){
            // CHECK str, dir
            CHECK_THROWS(book.write(1,1,1,dir,str));
        }
    }
    else if(foo == func::read){
        // CHECK PAGE
        if(arg == args::page){
            CHECK_THROWS(book.read(INT_MAX,1,1,dir,1));
            CHECK_THROWS(book.read(INT_MIN,1,1,dir,1));
            for(int i=-1; i> -100; i--)
                CHECK_THROWS(book.read(i,1,1,dir,1));
        }
        //CHECK ROW
        else if(arg == args::row){
            CHECK_THROWS(book.read(1,INT_MIN,1,dir,1));
            for(int i=-1; i> -100; i--)
                CHECK_THROWS(book.read(1,i,1,dir,1));
        }
        // CHECK COLUMN
        else if(arg == args::column){
            CHECK_THROWS(book.read(1,1,INT_MAX,dir,1));
            CHECK_THROWS(book.read(1,1,INT_MIN,dir,1));
            CHECK_THROWS(book.read(1,1,101,dir,1));
            for(int i=-1; i> -100; i--)
                CHECK_THROWS(book.read(1,1,i,dir,1));
        }
        else if(arg == args::custom){
            // CHECK str, dir
            CHECK_THROWS(book.read(page,row,column,dir, len));
        }
    }
    else if(foo == func::erase){
        if(dir == Direction::Horizontal){
            // check negative length erasing
            CHECK_THROWS(book.erase(1,1,1,dir,-1));
            CHECK_THROWS(book.erase(1,1,1,dir,-50));
            CHECK_THROWS(book.erase(1,1,1,dir,-1000));
            CHECK_THROWS(book.erase(1,1,1,dir,-151511));
            // check out of row bounds
            for(int i=0; i< 100; i++)
                CHECK_THROWS(book.erase(1,1,i,Direction::Horizontal,100 - i + 1));
            CHECK_THROWS(book.erase(1,1,101,Direction::Horizontal,1));
            CHECK_THROWS(book.erase(1,1,1000,Direction::Horizontal,100));
            CHECK_THROWS(book.erase(1,1,1000,Direction::Horizontal,1));
            CHECK_THROWS(book.erase(1,1,1234567,Direction::Horizontal,10));
            // check erase 0 letters
            CHECK_THROWS(book.erase(1,1,1,dir,0));
        }
        else if(dir == Direction::Vertical){
            // check negative length erasing
            CHECK_THROWS(book.erase(1,1,1,dir,-1));
            CHECK_THROWS(book.erase(1,1,1,dir,-50));
            CHECK_THROWS(book.erase(1,1,1,dir,-1000));
            CHECK_THROWS(book.erase(1,1,1,dir,-151511));
            
            // check erase 0 letters
            CHECK_THROWS(book.erase(1,1,1,dir,0));
        }
        else if(arg == args::custom){
            // CHECK str, dir
            CHECK_THROWS(book.erase(1,1,1,dir,len));
        }
    }
    return 0;
}

TEST_CASE("Bad input"){
    Notebook book;
    Direction ver = Direction::Vertical;
    Direction hor = Direction::Horizontal;
    
    // check write
    checkFunction(func::write,args::column,book,hor);
    checkFunction(func::write,args::column,book,ver);
    // check read
    checkFunction(func::read,args::column,book,hor);
    checkFunction(func::read,args::column,book,ver);
    // check erase
    checkFunction(func::erase,args::column,book,hor);
    checkFunction(func::erase,args::column,book,ver);
    
    // check different keywords
    checkFunction(func::write,args::custom,book,hor,"~");
    checkFunction(func::write,args::custom,book,hor,"!!!!!!!!~!!!!!!!");
    string str = "";
    for(int i=0; i< 100; i++){
        str.append("@");
    }
    checkFunction(func::write,args::custom,book,hor,str);
    str.append("&");
    checkFunction(func::write,args::custom,book,hor,str);
    
}




