#ifndef STATEFLOWLIB_STATEMACHINE_HPP
#define STATEFLOWLIB_STATEMACHINE_HPP

#include "stateflow/StateBase.hpp"
#include <unordered_map>

namespace stateflow {

class StateMachine {
public:
  StateMachine();
  ~StateMachine();

public:
  void AddState(StateBase *state);
  void Initialize(StateType state);
  void Start();
  void Stop();

  template <typename... Args>
  void HandleEvent(EventType event, Args &&...args) {
    if (!_isInitialized || !_isRunning) {
      return;
    }
    _currentState->Handle(event, std::forward<Args>(args)...);
    auto nextState = _currentState->GetNextState(event);
    if (nextState == StateType::None) {
      Stop();
      return;
    }
    if (nextState != _currentState->GetType()) {
      _currentState->OnExit();
      _currentState = _states[nextState];
      _currentState->OnEnter();
    }
  }

  StateType GetCurrentState() const { return _currentState->GetType(); }
  bool IsRunning() const { return _isRunning; }

private:
  StateBase *_currentState;
  std::unordered_map<StateType, StateBase *> _states;
  bool _isInitialized;
  bool _isRunning;
};

} // namespace stateflow

#endif // STATEFLOWLIB_STATEMACHINE_HPP
