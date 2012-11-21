#include <cstdlib>
#include "gtest/include/gtest/gtest.h"
#include "../Heap.h"

TEST(HeapTest, Simple) {
   Heap<int> heap(5);
   EXPECT_EQ(0, heap.Count());

   //
   // 1(0)
   //
   heap.Add(1);
   EXPECT_EQ(1, heap.Count());
   EXPECT_EQ(0, heap.map[0]);
   EXPECT_EQ(LONG_MIN, heap.free);

   //
   //   2(1)
   //  /
   // 1(0)
   //
   heap.Add(2);
   EXPECT_EQ(2, heap.Count());
   EXPECT_EQ(1, heap.map[0]);
   EXPECT_EQ(0, heap.map[1]);

   //
   //   3(2)
   //  /   \
   // 1(0)  2(1)
   //
   heap.Add(3);
   EXPECT_EQ(3, heap.Count());
   EXPECT_EQ(1, heap.map[0]);
   EXPECT_EQ(2, heap.map[1]);
   EXPECT_EQ(0, heap.map[2]);

   //
   //   2(1)
   //  /
   // 1(0)
   //
   int top;
   heap.Remove(&top);
   EXPECT_EQ(3, top);
   EXPECT_EQ(2, heap.Count());
   EXPECT_EQ(1, heap.map[0]);
   EXPECT_EQ(0, heap.map[1]);

   //
   //   5(2)
   //  /   \
   // 1(0)  2(1)
   //
   heap.Add(5);
   EXPECT_EQ(3, heap.Count());
   EXPECT_EQ(1, heap.map[0]);
   EXPECT_EQ(2, heap.map[1]);
   EXPECT_EQ(0, heap.map[2]);

   //
   //   2(1)
   //  /
   // 1(0)
   //
   heap.Remove(&top);
   EXPECT_EQ(5, top);
   EXPECT_EQ(2, heap.Count());
   EXPECT_EQ(1, heap.map[0]);
   EXPECT_EQ(0, heap.map[1]);

   //
   //   1(0)
   //
   heap.Remove(&top);
   EXPECT_EQ(2, top);
   EXPECT_EQ(1, heap.Count());
   EXPECT_EQ(0, heap.map[0]);

   heap.Remove(&top);
   EXPECT_EQ(1, top);
   EXPECT_EQ(0, heap.Count());
}

TEST(HeapTest, Simple2) {
   Heap<int> heap(1);

   heap.Add(1);
   heap.Add(2);
   heap.Add(3);
   heap.Add(4);
   heap.Add(5);

   int top;
   for (int i = 0; i < 5; i++) {
      heap.Remove(&top);
      EXPECT_EQ(5-i, top);
   }
}

TEST(HeapTest, Remove1) {
   Heap<int> heap(5);

   //
   //   5(2)
   // /     \
   // 3(1)  4(0)
   // /   \
   // 2(3) 1(4)
   //
   heap.Add(4);
   heap.Add(3);
   heap.Add(5);
   heap.Add(2);
   heap.Add(1);

   //
   //   4(0)
   // /     \
   // 3(1)  1(4)
   // /
   // 2(3)
   //
   int top;
   heap.Remove(&top);
   EXPECT_EQ(5, top);
   EXPECT_EQ(-2, heap.free);
   EXPECT_EQ(LONG_MIN, heap.map[2]);

   //
   //   3(1)
   // /     \
   // 2(3)  1(4)
   //
   heap.Remove(&top);
   EXPECT_EQ(4, top);
   EXPECT_EQ(0, heap.free);
   EXPECT_EQ(-2, heap.map[0]);
   EXPECT_EQ(LONG_MIN, heap.map[2]);

   //
   //   2(3)
   //   /
   // 1(4)
   //
   heap.Remove(&top);
   EXPECT_EQ(3, top);
   EXPECT_EQ(0, heap.free);
   EXPECT_EQ(-1, heap.map[0]);
   EXPECT_EQ(-2, heap.map[1]);
   EXPECT_EQ(LONG_MIN, heap.map[2]);

   //
   //  1(4)
   //
   heap.Remove(&top);
   EXPECT_EQ(2, top);
   EXPECT_EQ(0, heap.free);
   EXPECT_EQ(-1, heap.map[0]);
   EXPECT_EQ(-2, heap.map[1]);
   EXPECT_EQ(-3, heap.map[2]);
   EXPECT_EQ(LONG_MIN, heap.map[3]);

   //
   //
   heap.Remove(&top);
   EXPECT_EQ(1, top);
   EXPECT_EQ(0, heap.free);
   EXPECT_EQ(-1, heap.map[0]);
   EXPECT_EQ(-2, heap.map[1]);
   EXPECT_EQ(-3, heap.map[2]);
   EXPECT_EQ(-4, heap.map[3]);
   EXPECT_EQ(LONG_MIN, heap.map[4]);
}

TEST(HeapTest, Random1) {
   srand(1);
   Heap<int> heap(10);

   for (int i = 0; i < 4; ++i)
      heap.Add(rand());

   int top, oldTop;
   heap.Remove(&oldTop);
   for (int i = 1; i < 2; ++i) {
      heap.Remove(&top);
      EXPECT_TRUE(top <= oldTop);
      oldTop = top;
   }

   for (int i = 0; i < 4; ++i)
      heap.Add(rand());

   heap.Remove(&oldTop);
   for (int i = 1; i < 6; ++i) {
      heap.Remove(&top);
      EXPECT_TRUE(top <= oldTop);
      oldTop = top;
   }
}

TEST(HeapTest, Random2) {
   srand(1);
   Heap<int> heap(10);

   // Add 100 numbers and remove 50.
   for (int i = 0; i < 100; ++i)
      heap.Add(rand());
   EXPECT_EQ(100, heap.Count());

   int top, oldTop;
   heap.Remove(&oldTop);
   for (int i = 1; i < 50; ++i) {
      heap.Remove(&top);
      EXPECT_TRUE(top <= oldTop);
      oldTop = top;
   }
   EXPECT_EQ(50, heap.Count());

   // Add 100 more and remove all 150.
   for (int i = 0; i < 100; ++i)
      heap.Add(rand());
   EXPECT_EQ(150, heap.Count());

   heap.Remove(&oldTop);
   for (int i = 1; i < 150; ++i) {
      heap.Remove(&top);
      EXPECT_TRUE(top <= oldTop);
      oldTop = top;
   }
   EXPECT_EQ(0, heap.Count());
}

TEST(HeapTest, Random3) {
   srand(3);
   Heap<int> heap(100);

   // Add 10000 numbers and remove them.
   for (int i = 0; i < 10000; ++i)
      heap.Add(rand());
   EXPECT_EQ(10000, heap.Count());

   int top, oldTop;
   heap.Remove(&oldTop);
   for (int i = 1; i < 10000; ++i) {
      heap.Remove(&top);
      EXPECT_TRUE(top <= oldTop);
      oldTop = top;
   }
   EXPECT_EQ(0, heap.Count());

   // Add 10000 numbers and remove them.
   for (int i = 0; i < 10000; ++i)
      heap.Add(rand());
   EXPECT_EQ(10000, heap.Count());

   heap.Remove(&oldTop);
   for (int i = 1; i < 10000; ++i) {
      heap.Remove(&top);
      EXPECT_TRUE(top <= oldTop);
      oldTop = top;
   }
   EXPECT_EQ(0, heap.Count());
}
