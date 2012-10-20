#include <assert.h>
#include <iostream>
#include <string>
#include <vector>

#define TEST(x) static void x()
#define STR_VALUE(x) #x
#define ADD_TEST(x)                    \
   do {                                \
      TestObj temp(STR_VALUE(x), &x);  \
      mTests.push_back(temp);          \
   } while (0)
#define RUN_TEST(x)  \
   int main() {      \
      x test;        \
      test.Run();    \
   }

class Test {
public:
   typedef void (*TestFunc)();
   struct TestObj {
      TestObj(std::string name, TestFunc func) : name(name), func(func) { }

      std::string name;
      TestFunc func;
   };

   template <typename T>
   static void AssertEq(T ob1, T ob2) {
      if (ob1 != ob2)
         std::cout << "AssertEq FAILED: " << ob1 << " != " << ob2 << std::endl;
   }

   void Run() {
      for (std::vector<TestObj>::const_iterator iter = mTests.begin();
           iter != mTests.end(); iter++) {
         std::cout << "Running " << iter->name << "... ";
         (*(iter->func))();
         std::cout << "PASSED" << std::endl;
      }
   }

protected:
   std::vector<TestObj> mTests;
};
