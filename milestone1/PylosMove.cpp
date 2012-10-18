#include "MyLib.h"
#include "PylosMove.h"
#include "PylosBoard.h"

std::vector<PylosMove *> PylosMove::mFreeList;

void *PylosMove::operator new(size_t sz)
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

void PylosMove::operator delete(void *p)
{
   mFreeList.push_back((PylosMove *)p);
   mOutstanding--;
}

bool PylosMove::operator==(const Board::Move &rhs) const
{
   const PylosMove &oRhs = dynamic_cast<const PylosMove &>(rhs);

   return mType == oRhs.mType && mLocs.size() == oRhs.mLocs.size()
    && std::equal(mLocs.begin(), mLocs.end(), oRhs.mLocs.begin());
}

// Sort by target loc, then by move type, then source locs
// by lexicographic sort
bool PylosMove::operator<(const Board::Move &rhs) const
{
   int ndx = 0;
   const PylosMove &oRhs = dynamic_cast<const PylosMove &>(rhs);

   if (mLocs[0] != oRhs.mLocs[0])
      return mLocs[0] < oRhs.mLocs[0];

   if (mType != oRhs.mType)
      return mType < oRhs.mType;

   for (ndx = 1; ndx < 4; ndx++) {
      if (mLocs.size() > ndx && oRhs.mLocs.size() > ndx) {
         if (mLocs[ndx] != oRhs.mLocs[ndx])
            return mLocs[ndx] < oRhs.mLocs[ndx];
      } else {
         break;
      }
   }

   return mLocs.size() < oRhs.mLocs.size();
}

// TODO test
PylosMove::operator std::string() const
{
   std::string str;
   LocVector::const_iterator itr = mLocs.begin();

   if (mType == kReserve) {
      str = FString("Play at [%d, %d]", itr->first, itr->second);
      itr++;
   }
   else {
      str = FString("Promote from [%d, %d] to [%d, %d]", mLocs[0].first,
       mLocs[0].second, mLocs[1].first, mLocs[1].second);
      itr += 2;
   }

   if (itr != mLocs.end()) {
      str += FString(" taking [%d, %d]", itr->first, itr->second);
      itr++;
   }

   if (itr != mLocs.end())
      str += FString(" and [%d, %d]", itr->first, itr->second);

   return str;
}

// TODO test
void PylosMove::operator=(const std::string &src)
{
   char wd1[11], wd2[11], wd3[11], extra;
   std::pair<short, short> p1, p2, p3, p4;
   int res;
   short type;
   LocVector temp;

   sscanf(src.c_str(), "%10s", wd1);
   if (!strcmp(wd1, "Play")) {
      type = kReserve;
      res = sscanf(src.c_str(), " Play at [ %hd , %hd ] %6s [ %hd , %hd ] %3s "
       "[ %hd , %hd ] %c", &p1.first, &p1.second, wd1, &p2.first, &p2.second,
       wd2, &p3.first, &p3.second, &extra);

      if (res == 2 ||
          res == 5 && !strcmp(wd1, "taking") ||
          res == 8 && !strcmp(wd1, "taking") && !strcmp(wd2, "and")) {
         temp.push_back(p1);
         if (res == 5)
            temp.push_back(p2);
         if (res == 8) {
            if (p2 > p3)
               throw BaseException(FString("Bad Pylos move: %s", src.c_str()));
            temp.push_back(p3);
         }
      }
      else {
         throw BaseException(FString("Bad Pylos move: %s", src.c_str()));
      }
   }
   else if (!strcmp(wd1, "Promote")) {
      type = kPromote;
      res = sscanf(src.c_str(), " Promote from [ %hd , %hd ] %2s [ %hd , %hd ] "
       "%6s [ %hd , %hd ] %3s [ %hd , %hd ] %c", &p1.first, &p1.second, wd1,
       &p2.first, &p2.second, wd2, &p3.first, &p3.second, wd3, extra);

      if (res == 5 && !strcmp(wd1, "to") ||
          res == 8 && !strcmp(wd1, "to") && !strcmp(wd2, "taking") ||
          res == 11 && !strcmp(wd1, "to") && !strcmp(wd2, "taking") &&
           !strcmp(wd3, "and")) {
         temp.push_back(p1);
         temp.push_back(p2);
         if (res == 8)
            temp.push_back(p3);
         if (res == 11) {
            if (p3 > p4)
               throw BaseException(FString("Bad Pylos move: %s", src.c_str()));
            temp.push_back(p4);
         }
      }
      else {
         throw BaseException(FString("Bad Pylos move: %s", src.c_str()));
      }
   }
   else {
      throw BaseException(FString("Bad Pylos move: %s", src.c_str()));
   }

   for (LocVector::const_iterator iter = temp.begin(); iter != temp.end();
        iter++) {
      if (!InRange<short>(0, iter->first, PylosBoard::kDim) ||
          !InRange<short>(0, iter->second, PylosBoard::kDim)) {
         throw BaseException(FString("Out of bounds Pylos move: %s",
          src.c_str()));
      }
   }

   mType = type;
   mLocs = temp;
}

Board::Move *PylosMove::Clone() const
{
   return new PylosMove(mLocs, mType);
}

std::ostream &PylosMove::Write(std::ostream &os) const
{
   char size = mLocs.size();
   short temp;
   int ndx;

   os.write((char *)&mType, sizeof(mType));
   os.write((char *)&size, sizeof(size));
   for (ndx = 0; ndx < size; ndx++) {
      temp = EndianXfer(mLocs[ndx].first);
      os.write((char *)&temp, sizeof(short));
      temp = EndianXfer(mLocs[ndx].second);
      os.write((char *)&temp, sizeof(short));
   }
   return os;
}

std::istream &PylosMove::Read(std::istream &is)
{
   char size = 0;
   short temp;
   int ndx;

   is.read((char *)&mType, sizeof(mType));
   is.read((char *)&size, sizeof(size));
   for (ndx = 0; ndx < size; ndx++) {
      is.read((char *)&temp, sizeof(temp));
      mLocs[ndx].first = EndianXfer(temp);
      is.read((char *)&temp, sizeof(temp));
      mLocs[ndx].second = EndianXfer(temp);
   }
   return is;
}
