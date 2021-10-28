#include <iostream>

using namespace std;

#include "SquareList.h"

/**
  Main program to test SquareList data structure.
  This is just a basic test. You should write your own
  test programs to thoroughly exercise all the methods.
  Grading will include other test programs using larger
  data sets.

  @author 
  @version 08/20/2019
*/

int main() {
	cout << "Basic Test for Project 1:" << endl;

	SquareList sqrList;
	int t;

	// Step 1: add a bunch of integers
	cout << "\nStep 1: Add initial items." << endl;

	sqrList.addFirst(12); sqrList.addFirst(10); sqrList.addFirst(999);
	sqrList.addFirst(999); sqrList.addFirst(9); sqrList.addFirst(8);
	sqrList.addFirst(999); sqrList.addFirst(7);

	sqrList.addLast(14); sqrList.addLast(996); sqrList.addLast(15);
	sqrList.addLast(995); sqrList.addLast(16); sqrList.addLast(17);
	sqrList.addLast(18); sqrList.addLast(994);

	sqrList.addFirst(997); sqrList.addFirst(5); sqrList.addFirst(992);
	sqrList.addFirst(991); sqrList.addFirst(2); sqrList.addFirst(989);
	sqrList.addFirst(988); sqrList.addFirst(987);

	sqrList.addLast(20); sqrList.addLast(993); sqrList.addLast(990);
	// sqrList.dump();

	cout << "After Step 1:" << endl;
	for (int i = 0; i < sqrList.size(); i++) {  // very slow!
		cout << sqrList.get(i) << " ";
	}
	cout << endl;


	// Step 2: trim some items
	cout << "\nStep 2: remove some items." << endl;

	t = sqrList.removeFirst();
	t = sqrList.removeFirst();
	t = sqrList.remove(sqrList.size() - 1);
	t = sqrList.remove(sqrList.size() - 1);

	cout << "After Step 2:" << endl;
	for (int i = 0; i < sqrList.size(); i++) {  // very slow!
		cout << sqrList.get(i) << " ";
	}
	cout << endl;


	//Step 3: set a few values
	cout << "\nStep 3: change some items." << endl;

	sqrList.set(0, 1); sqrList.set(2, 3); sqrList.set(3, 4); sqrList.set(5, 6);

	cout << "After Step 3:" << endl;
	for (int i = 0; i < sqrList.size(); i++) {  // very slow!
		cout << sqrList.get(i) << " ";
	}
	cout << endl;


	//Step 4: remove some items
	cout << "\nStep 4: remove some more items." << endl;

	t = sqrList.remove(7); t = sqrList.remove(9); t = sqrList.remove(9);
	t = sqrList.remove(12); t = sqrList.remove(13);

	cout << "After Step 4:" << endl;
	for (int i = 0; i < sqrList.size(); i++) {  // very slow!
		cout << sqrList.get(i) << " ";
	}
	cout << endl;


	//Step 5: insert some times
	cout << "\nStep 5: insert some items." << endl;

	sqrList.add(10, 799); sqrList.add(12, 13);

	cout << "After Step 5:" << endl;
	for (int i = 0; i < sqrList.size(); i++) {  // very slow!
		cout << sqrList.get(i) << " ";
	}
	cout << endl;


	//Step 6: change some items
	cout << "\nStep 6: change some more items." << endl;

	sqrList.set(10, 11); sqrList.set(18, 19);


	cout << "After Step 6:" << endl;
	for (int i = 0; i < sqrList.size(); i++) {  // very slow!
		cout << sqrList.get(i) << " ";
	}
	cout << endl;

	cout << "\n\nDATA DUMP" << endl;
	sqrList.dump();


	//Step 7: Add even more items, to cause merges
	cout << "\n\nStep 7: add items to cause merges." << endl;

	for (int i = 21; i <= 101; i++) {
		sqrList.addLast(i);
	}

	cout << "After Step 7:" << endl;
	cout << "DATA DUMP" << endl;
	sqrList.dump();


	//Step 8: Remove lots of items, to cause splits
	cout << "\n\nStep 8: remove items to cause splits." << endl;

	for (int i = 1; i <= 47; i++) {
		t = sqrList.removeFirst();
	}

	cout << "After Step 8:" << endl;
	cout << "DATA DUMP" << endl;
	sqrList.dump();


	//Step 9: Remove even more items, to cause splits
	cout << "\n\nStep 9: remove more items to cause more splits." << endl;

	for (int i = 1; i <= 34; i++) {
		t = sqrList.removeFirst();
	}

	cout << "After Step 9:" << endl;
	cout << "DATA DUMP" << endl;
	sqrList.dump();

	return 0;
}

