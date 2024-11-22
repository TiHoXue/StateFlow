#include "stateflowlib/StateBase.hpp"

namespace stateflow {

StateBase::StateBase(StateType type) : _type(type) {}

bool StateBase::Handle(EventType event) {
  auto handler = _eventHandlers.find(event);
  if (handler != _eventHandlers.end()) {
    return handler->second();
  }
  return false;
}

void StateBase::AddTransition(EventType event, StateType nextState) {
  _transitions[event] = nextState;
}

void StateBase::AddEventHandler(EventType event, EventHandler handler) {
  _eventHandlers[event] = handler;
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
