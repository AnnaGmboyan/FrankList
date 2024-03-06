#include <iostream>
#include "franklist.h"
int main()
{
		FrankList<int> list;

		list.push_back(3);
		list.push_back(5);
		list.push_back(9);
		list.push_back(2);
		list.push_back(4);
		std::cout << list.size() << std::endl;

		
		FrankList<int> list2 {1,5,3,2,9,6};
	//	list2.pprint();
	//	std::cout << std::endl;
	//	list.pprint();
		list2.print();
		list2.print(1);
		list2.print(0,1);
//		list2.print(1,1);

		std::cout << std::endl;
/*
		list2.print(1);
		std::cout << std::endl;
//		list2.print(0,1);
		std::cout << std::endl;
	//	list2.print(1,1);
		std::cout << std::endl;
//		list2.print(1,1);
		std::cout << std::endl;


		list2.resize(3);
		list2.push_front(10);
		std::cout << list2.front() << std::endl;
		list2.front() = 5;
		std::cout << list2.front() << std::endl;
		std::cout << list2.back() << std::endl;
		list2.back() = 12;
		std::cout << list2.back() << std::endl;
		std::cout << list2.empty()<< std::endl;
		std::cout << list2.size() << std::endl;
		
*/
	return 0;
}
