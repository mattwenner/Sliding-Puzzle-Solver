#include "heap.h"
#include "gtest/gtest.h"
#include <iostream>
#include <string>

using namespace std;


class HeapTest: public testing::Test{
protected:

	HeapTest(): minHeap(2, lcomp), maxHeap(4, gcomp), maxStringHeap(3, gscomp){}
	virtual ~HeapTest(){}

	virtual void SetUp(){}

	virtual void TearDown(){}

	//comparators
	less<int>lcomp;
	greater<int>gcomp;
	greater<string>gscomp;

	//initialize heaps
	Heap<int, less<int> > minHeap;
	Heap<int, greater<int> > maxHeap;
	Heap<string, greater<string> > maxStringHeap;

};

//testing empty, push, pop, and top for int min heap
TEST_F(HeapTest, minNominal){
	EXPECT_EQ(minHeap.empty(), 1);
	minHeap.push(5);
	EXPECT_EQ(minHeap.empty(), 0);
	minHeap.push(7);
	minHeap.push(9);
	minHeap.push(2);
	minHeap.push(10);
	minHeap.push(0);
	minHeap.push(-1);
	minHeap.push(-2);
	minHeap.push(-3);
	EXPECT_EQ(minHeap.top(), -3);
	minHeap.pop();
	minHeap.pop();
	minHeap.push(-10);
	EXPECT_EQ(minHeap.top(), -10);
	minHeap.pop();
	minHeap.pop();
	minHeap.pop();
	EXPECT_EQ(minHeap.top(), 2);
	minHeap.pop();
	minHeap.pop();
	EXPECT_EQ(minHeap.top(), 7);
	minHeap.pop();
	minHeap.pop();
	minHeap.pop();
	EXPECT_EQ(minHeap.empty(), 1);

}

//testing empty, push, pop, and top for int max heap
TEST_F(HeapTest, maxNominal){
	EXPECT_EQ(maxHeap.empty(), 1);
	maxHeap.push(5);
	EXPECT_EQ(maxHeap.empty(), 0);
	maxHeap.push(-5);
	maxHeap.push(20);
	maxHeap.push(10);
	maxHeap.push(50);
	maxHeap.push(40);
	maxHeap.push(30);
	maxHeap.push(25);
	maxHeap.push(21);
	EXPECT_EQ(maxHeap.top(), 50);
	maxHeap.pop();
	maxHeap.pop();
	maxHeap.push(60);
	EXPECT_EQ(maxHeap.top(), 60);
	maxHeap.pop();
	maxHeap.pop();
	maxHeap.pop();
	maxHeap.pop();
	EXPECT_EQ(maxHeap.top(), 20);
	maxHeap.pop();
	maxHeap.pop();
	EXPECT_EQ(maxHeap.top(), 5);
	maxHeap.pop();
	EXPECT_EQ(maxHeap.top(), -5);
	maxHeap.pop();
	EXPECT_EQ(maxHeap.empty(), 1);
}

//testing empty, push, pop, and top for string max heap
TEST_F(HeapTest, stringNominal){
	EXPECT_EQ(maxStringHeap.empty(), 1);
	maxStringHeap.push("acorn");
	EXPECT_EQ(maxStringHeap.empty(), 0);
	maxStringHeap.push("zeta");
	maxStringHeap.push("aaron");
	maxStringHeap.push("zebra");
	maxStringHeap.push("aaardvark");
	maxStringHeap.push("zz");
	maxStringHeap.push("zzz");
	maxStringHeap.push("zzzz");
	maxStringHeap.push("zzzzz");
	EXPECT_EQ(maxStringHeap.top(), "zzzzz");
	maxStringHeap.pop();
	maxStringHeap.pop();
	maxStringHeap.push("zzzzzz");
	EXPECT_EQ(maxStringHeap.top(), "zzzzzz");
	maxStringHeap.pop();
	maxStringHeap.pop();
	maxStringHeap.pop();
	EXPECT_EQ(maxStringHeap.top(), "zeta");
	maxStringHeap.pop();
	EXPECT_EQ(maxStringHeap.top(), "zebra");
	maxStringHeap.pop();
	EXPECT_EQ(maxStringHeap.top(), "acorn");
	maxStringHeap.pop();
	EXPECT_EQ(maxStringHeap.top(), "aaron");
	maxStringHeap.pop();
	EXPECT_EQ(maxStringHeap.top(), "aaardvark");
	maxStringHeap.pop();
}