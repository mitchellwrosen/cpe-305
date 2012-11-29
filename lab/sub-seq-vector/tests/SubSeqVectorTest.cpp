#include "gtest/include/gtest/gtest.h"

#include "../SubSeqVector.h"

TEST(SubSeqVectorTest, Constructor) {
   SubSeqVector<int> vec;
   EXPECT_EQ(0U, vec.size());
}

TEST(SubSeqVectorTest, Destructor) {
   static int numDestructed = 0;

   struct Foo {
      Foo() { }
      ~Foo() { numDestructed++ }
   };

   Foo foo1, foo2, foo3;

   SubSeqVector<Foo> vec;
   vec.push_back(foo1);
   vec.push_back(foo2);
   vec.push_back(foo3);

   ~vec();
   EXPECT_EQ(3, numDestructed);
}
