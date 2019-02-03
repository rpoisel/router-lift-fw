#ifndef FSM_H
#define FSM_H

class FSM;

class State
{
  public:
    State() = default;
    virtual ~State() = default;

    virtual void enter(FSM* fsm) {}
    virtual void execute(FSM* fsm) = 0;
    virtual void exit(FSM* fsm) {}
};

class FSM
{
  public:
    FSM() = default;
    FSM(State* curState) :curState(curState) {}
    virtual ~FSM() = default;

    void update()
    {
      if (!curState)
      {
        return;
      }
      curState->execute(this);
    }
    void setState(State* newState)
    {
      if (!newState)
      {
        return;
      }

      if (curState)
      {
        curState->exit(this);
      }
      curState = newState;
      curState->enter(this);
    }
  private:
    State* curState;
};

#endif /* FSM_H */