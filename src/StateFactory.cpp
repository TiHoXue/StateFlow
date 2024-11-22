#include "stateflowlib/StateFactory.hpp"

namespace stateflow {

StateFactory &StateFactory::GetInstance() {
  static StateFactory instance;
  return instance;
}

void StateFactory::RegisterStateCreator(
    StateType type, std::function<StateBase *(StateType)> creator) {
  _stateCreators[type] = creator;
}

StateBase *StateFactory::CreateState(StateType type) {
  auto creator = _stateCreators.find(type);
  if (creator != _stateCreators.end()) {
    return creator->second(type);
  }
  return nullptr;
}

} // namespace stateflow
