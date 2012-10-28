#include <sstream>
#include "MyLib.h"
#include "CheckersMove.h"
#include "CheckersBoard.h"

// static
std::vector<CheckersMove *> CheckersMove::mFreeList;

CheckersMove::CheckersMove(const Location &src, const Location &dst) :
 mToKing(false)
{
   mLocs.push_back(src);
   mLocs.push_back(dst);
}

bool CheckersMove::operator==(const Board::Move &rhs) const
{
   const CheckersMove &other = dynamic_cast<const CheckersMove &>(rhs);
   if (mLocs.size() != other.mLocs.size())
      return false;
   for (LocVector::const_iterator iter1 = mLocs.begin(),
    iter2 = other.mLocs.begin(); iter1 != mLocs.end(); iter1++, iter2++) {
      if (*iter1 != *iter2)
         return false;
   }

   return true;
}

bool CheckersMove::operator<(const Board::Move &rhs) const
{
   const CheckersMove &other = dynamic_cast<const CheckersMove &>(rhs);

   // Compare each location in order, until we get to the end of one list.
   LocVector::const_iterator iter1, iter2;
   for (iter1 = mLocs.begin(), iter2 = other.mLocs.begin();
    iter1 != mLocs.end() && iter2 != other.mLocs.end(); iter1++, iter2++) {
      if (*iter1 < *iter2)
         return true;
   }

   // At this point, the only way this can be true is if the other is longer.
   if (iter1 == mLocs.end() && iter2 != other.mLocs.end())
      return true;
   return false;
}

CheckersMove::operator std::string() const
{
   std::stringstream ss;
   if (mLocs.empty())
      return "";

   ss << (char) ('A' + mLocs[0].first) << mLocs[0].second + 1;
   for (unsigned int i = 1; i < mLocs.size(); i++) {
      ss << " -> ";
      ss << (char) ('A' + mLocs[i].first) << mLocs[i].second + 1;
   }

   return ss.str();
}

void CheckersMove::operator=(const std::string &src)
{
   char ch1, ch2;
   bool scanCell = true; // set to false to scan a '->'
   int row, col;
   LocVector tempLocs;
   std::stringstream ss(src);

   do {
      if (scanCell) {
         ss >> std::skipws >> ch1 >> ch2;
         row = toupper(ch1) - 'A';
         col = ch2 - '0' - 1;
         if (!InRange<int>(0, row, CheckersBoard::kDim) ||
          !InRange<int>(0, col, CheckersBoard::kDim)) {
            throw BaseException(FString("Bad Checkers move: %s", src.c_str()));
         }
         tempLocs.push_back(std::make_pair(row, col));
         scanCell = false;
      } else {
         ss >> ch1 >> std::noskipws >> ch2;
         if (ch1 != '-' || ch2 != '>')
            throw BaseException(FString("Bad Checkers move: %s", src.c_str()));
         scanCell = true;
      }
   } while (ss.peek(), !ss.eof());

   // not allowed to end on a '->', or with only one cell
   if (scanCell || tempLocs.size() == 1)
      throw BaseException(FString("Bad Checkers move: %s", src.c_str()));

   mLocs = tempLocs;
}

Board::Move *CheckersMove::Clone() const
{
   return new CheckersMove(mLocs);
}

void *CheckersMove::operator new(size_t sz)
{
   void *temp;

   if (mFreeList.size()) {
      temp = mFreeList.back();
      mFreeList.pop_back();
   } else {
      temp = ::new char[sz];
   }

   mOutstanding++;
   return temp;
}

void CheckersMove::operator delete(void *p)
{
   mFreeList.push_back((CheckersMove *)p);
   mOutstanding--;
}


std::ostream &CheckersMove::Write(std::ostream &os) const
{
   uint8_t size = mLocs.size();

   // Number of steps in the move, row/col pairs giving the position of each
   // step
   os.write((char *) &size, sizeof(uint8_t));

   for (unsigned int i = 0; i < size; i++) {
      os.write((char *) &mLocs[i].first, sizeof(uint8_t));
      os.write((char *) &mLocs[i].second, sizeof(uint8_t));
   }

   return os;
}

std::istream &CheckersMove::Read(std::istream &is)
{
   uint8_t size, row, col;
   is.read((char *) &size, sizeof(uint8_t));

   mLocs.clear();
   for (int i = 0; i < size; i++) {
      is.read((char *) &row, sizeof(uint8_t));
      is.read((char *) &col, sizeof(uint8_t));
      mLocs.push_back(std::make_pair(row, col));
   }

   return is;
}
