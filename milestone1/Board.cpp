#include <limits>
#include "Board.h"

// static
const long Board::kWinVal = std::numeric_limits<int>::max();

// static
long Board::Move::mOutstanding = 0;

// static
long Board::Key::mOutstanding = 0;
