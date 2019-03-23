#ifndef STATES_H
#define STATES_H

#include <fsm.h>

namespace RouterFW
{

class StateMenu : public State
{
  public:
  static StateMenu* instance()
  {
    static StateMenu state;
    return &state;
  }

  void enter(FSM& fsm);
  void execute(FSM& fsm);

  private:
  StateMenu() : menuPos(0)
  {
  }
  virtual ~StateMenu() = default;
  StateMenu(const StateMenu&);
  StateMenu& operator=(const StateMenu&);
  size_t menuPos;
};

class StateMove : public State
{
  public:
  static StateMove* instance()
  {
    static StateMove state;
    return &state;
  }

  void execute(FSM& fsm);

  private:
  StateMove() : routerPos(0)
  {
  }
  virtual ~StateMove() = default;
  StateMove(const StateMove&);
  StateMove& operator=(const StateMove&);
  int32_t routerPos;
};

} // namespace RouterFW

#endif /* STATES_H */