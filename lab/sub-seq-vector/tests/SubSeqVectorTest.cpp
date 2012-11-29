#include "gtest/include/gtest/gtest.h"

#include "../SubSeqVector.h"

TEST(SubSeqVectorTest, Simple) {
   double vals[] = {2.2, 3.4, 5.1, 7.7, 11.6};

   SubSeqVector<double> test;
   EXPECT_EQ(0U, test.size());

   SubSeqVector<double> v1(vals, vals+5);
   EXPECT_EQ(5U, v1.size());
   EXPECT_EQ(2.2, v1[0]);
   EXPECT_EQ(3.4, v1[1]);
   EXPECT_EQ(5.1, v1[2]);
   EXPECT_EQ(7.7, v1[3]);
   EXPECT_EQ(11.6, v1[4]);

   SubSeqVector<double> v2(v1.begin(), v1.end());
   EXPECT_EQ(5U, v2.size());
   for (int i = 0; i < 5; ++i)
      EXPECT_EQ(v1[i], v2[i]);

   //SubSeqVector v3 = v1.SubSeq(3, 4);
   //EXPECT_EQ(1U, v3.size());
   //EXPECT_EQ(7.7, v3[0]);

   EXPECT_EQ(7.7, v1.SubSeq(3, 4)[0]);
   EXPECT_EQ(3.4, *v2.SubSeq(1, 3).SubSeq(0, 1).begin());
   EXPECT_EQ(11.6, *(v2.SubSeq(1, 5).end()-1));
}
