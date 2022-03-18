/**
 * Demo program for notebook exercise.
 * 
 * Author: Erel Segal-Halevi
 * Edited by: Tal Zichlinsky
 * Since : 2022-01
 */

#include "Notebook.hpp"
#include "Direction.hpp"
using ariel::Direction;

#include <iostream>
#include <stdexcept>
using namespace std;

int main() {
	ariel::Notebook notebook;
	notebook.write(/*page=*/100, /*row=*/100, /*column=*/50, Direction::Horizontal, "abcd");
	cout << notebook.read(/*page=*/100, /*row=*/99, /*column=*/51, Direction::Vertical, /*length=*/3) << endl;  
		// prints "_b_" (starts at row 99 which is empty; then at row 100 there is "b"; then row 101 is empty again).
	notebook.write(/*page=*/100, /*row=*/99, /*column=*/52, Direction::Vertical, "xyz");
		// throws error because writing the letter y will intersect with the letter c
	notebook.erase(/*page=*/100, /*row=*/99, /*column=*/51, Direction::Vertical, /*length=*/3);
		// writes ~ instead of _ in line 99, b in line 100 and _ again in line 99

	notebook.show(100); // shows the notebook's page in a reasonable way. For example:
		//    98:  _________
		//    99:  ___~_____
		//    100: __a~cd___
		//    101: ___~_____
		//    102: _________
}

