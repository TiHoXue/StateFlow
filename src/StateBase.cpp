#include "stateflow/StateBase.hpp"

namespace stateflow {

StateBase::StateBase(StateType type) : _type(type) {}

void StateBase::AddTransition(EventType event, StateType nextState) {
  _transitions[event] = nextState;
}

StateType StateBase::GetType() const { return _type; }

StateType StateBase::GetNextState(EventType event) const {
  StateType nextState = StateType::None;
  auto transition = _transitions.find(event);
  if (transition != _transitions.end()) {
    nextState = transition->second;
  }
  return nextState;
}

} // namespace stateflow
