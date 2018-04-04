#include "DynamicArray.h"
#include "Song.h"
#include <iostream>

int main() {
	{
		DynamicArray arr1{};
		DynamicArray arr2 = arr1; // DynamicArray arr2{arr1};
		DynamicArray arr3{};
		arr3 = arr1;
	}
	{
		Song s{"a", "b", 6};
		std::cout << s.getTitle() << '\n';
	}
	return 0;
}