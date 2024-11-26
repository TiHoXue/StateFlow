#include "stateflow/StateMachine.hpp"

namespace stateflow {

StateMachine::StateMachine()
    : _isInitialized(false), _isRunning(false), _currentState(nullptr) {}

StateMachine::~StateMachine() {
  for (auto &state : _states) {
    delete state.second;
  }
}

void StateMachine::AddState(StateBase *state) {
  _states[state->GetType()] = state;
}

void StateMachine::Initialize(StateType state) {
  _currentState = _states[state];
  _isInitialized = true;
}

void StateMachine::Start() {
  if (!_isInitialized) {
    return;
  }
  _currentState->OnEnter();
  _isRunning = true;
}

void StateMachine::Stop() { _isRunning = false; }

} // namespace stateflow
