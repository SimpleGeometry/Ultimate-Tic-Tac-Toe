#include <core/mark.h>

namespace ultimate_tictactoe {
  
Mark::Mark() : mark(MarkData::kNone) {}
  
Mark::Mark(MarkData mark) : mark(mark) {}

WinState Mark::GetWinner() const {
  if (mark == MarkData::kPlayer1) {
    return WinState::kPlayer1Win;
  } else if (mark == MarkData::kPlayer2) {
    return WinState::kPlayer2Win;
  } else {
    return WinState::kInProgress;
  }
}

bool Mark::IsComplete() const {
  return mark != MarkData::kNone;
}

const Mark::MarkData& Mark::GetState() const {
  return mark;
}

void Mark::SetState(const MarkData& new_mark) {
  mark = new_mark;
}

}  // namespace ultimate_tictactoe

