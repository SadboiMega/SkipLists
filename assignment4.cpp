// Mohammad Adyan Zahid
// HW 4 Skiplist
#include "skiplist.h"
#include <iostream>

using namespace std; 
//testing adding function of skiplist depth 1
void test1() {
    SkipList s(1); // lvl 1

    s.Add(9);
    s.Add(30); 
    s.Add(41); 
    s.Add(91); 
    // printing the list
    cout << s << endl; 
    cout << "Test 1 complete" << endl;
    cout << endl;

}
//tests contains function depth 2
void test2() {
    SkipList s(2);

    s.Add(4);
    s.Add(20);
    s.Add(11);
    s.Add(2);

    cout << s << endl;
    //testing contains function
    if (s.Contains(11)) {
        cout << "SkipList does contain 11:" << endl; 
    } else {
        cout << "SkipList does not contain 11:" << endl;
    }
    cout << "SkipList does contain 11: " << s.Contains(11) << endl; 
    cout << "Test 2 complete" << endl;
    cout << endl;

}
//checks remove add and contains functions for list depth 3
void test3() {
    SkipList s(3);
    s.Add(3);
    s.Add(10);
    s.Add(2);
    s.Add(9);
    cout << s << endl;
    //making sure we have 2 in the list
    cout << "1st check for 2:" << endl;
    if (s.Contains(2)) {
        cout << "SkipList does contain 2:" << endl;
    }
    else {
        cout << "SkipList does not contain 2:" << endl;
    }
    
    s.Add(30);
    s.Add(20); 
    cout << s << endl;
    s.Remove(2);
    cout << "2nd check for 2:" << endl;
    //testing remove function
    if (s.Contains(11)) {
        cout << "SkipList does contain 2:" << endl;
    }
    else {
        cout << "SkipList does not contain 2:" << endl;
    } 
    s.Add(90);
    s.Add(100);
    cout << s << endl;
    cout << "Test 3 complete" << endl;

}
//given test
void test4() {
    SkipList s(5);
    for (int i = 0; i < 20; ++i) {
    int number = rand() % 100;
    s.Add(number);
    cout << "After adding " << number << endl;
    cout << s << endl;
    }
    cout << "Test 4 Done" << endl;
}
//combines all of the tests
void testAll() {
    cout << "Test 1 start" << endl;
    test1();
    cout << "Test 2 start" << endl;
    test2();
    cout << "Test 3 start" << endl;
    test3();
    cout << "Test 4 start" << endl;
    test4();
}
int main() {
    // calling all tests
    testAll();
}
