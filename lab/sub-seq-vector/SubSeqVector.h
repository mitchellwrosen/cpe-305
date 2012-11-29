#include <cstdlib>
#include <vector>

template <typename T> class SubSeqVector : public std::vector<T> {
public:
   SubSeqVector() : std::vector<T>() { }
   template <typename I> SubSeqVector(I a, I b) : std::vector<T>(a, b) { }
   SubSeqVector SubSeq(int start, int end) {
      return SubSeqVector(this->begin() + start, this->begin() + end);
   }
};
