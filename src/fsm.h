#ifndef FSM_H
#define FSM_H

class FSM;

class State
{
  public:
  State() = default;
  virtual ~State() = default;

  virtual void enter(FSM& fsm)
  {
    (void)fsm;
  }
  virtual void execute(FSM& fsm) = 0;
  virtual void exit(FSM& fsm)
  {
    (void)fsm;
  }
};

class FSM
{
  public:
  FSM() : curState(StateNull::instance())
  {
  }
  virtual ~FSM() = default;

  void update()
  {
    curState->execute(*this);
  }
  void setState(State* newState)
  {
    curState->exit(*this);
    curState = newState;
    curState->enter(*this);
  }

  private:
  class StateNull : public State
  {
public:
    static StateNull* instance()
    {
      static StateNull state;
      return &state;
    }

    void execute(FSM& fsm)
    {
      (void)fsm;
    }

private:
    StateNull() = default;
    virtual ~StateNull() = default;
    StateNull(const StateNull&);
    StateNull& operator=(const StateNull&);
  };

  State* curState;
};

#endif /* FSM_H */