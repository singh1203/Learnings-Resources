// Raw Program Example for const in C++

// Points to be remembered:
// 0. const get evaluated(bind-up) during compile-time of the program 
// 1. If const is on the left of *, data is const
// 2. if const is on right of *, pointer is const

#include <iostream>
using namespace std;

int main() {
	const int = 9;
	// i = 6; Error as read only variable hence no reassignment 
	
 	const int *p1 = &i; // data is const but data is not
	p1++; 		    // will compile successfully
	
	int* const p2; 	    // pointer is const, data is not
	
	const int* const p3; // Both data and pointer is const
	
	int const *p4 = &i;  // Both the assignment means data is const 
	const int *p4 = &i;  // and can be done either way
	

	// 2nd part 
	// Taking the example i = 6
	const_cast<int&>(i) = 6; // cast away the constness of variable

	int j;
	static_cast<int&>(j) = 7; // Convert between types using combination of implicit and user-defined converstions.
	

	return 0;
}

