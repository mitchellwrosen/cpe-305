#include "../MyLib.h"
#include "Test.h"

#include <vector>

class MyLibTest : public Test {
public:
   TEST(EndianXfer) {
      // ushort
      ushort us = 0x1122;
      us = ::EndianXfer(us);
      assert(us == 0x2211);

      // short
      short s = 0x1122;
      s = ::EndianXfer(s);
      assert(s == 0x2211);

      s = 0xFF00;
      s = ::EndianXfer(s);
      assert(s == 0x00FF);

      // uint
      uint ui = 0x11223344;
      ui = ::EndianXfer(ui);
      assert(ui == 0x44332211);

      // int
      int i = 0x11223344;
      i = ::EndianXfer(i);
      assert(i == 0x44332211);

      i = 0xFF332211;
      i = ::EndianXfer(i);
      assert(i == 0x112233FF);
   }

   MyLibTest() {
      ADD_TEST(EndianXfer);
   }
};

int main() {
   MyLibTest test;
   test.Run();
}
