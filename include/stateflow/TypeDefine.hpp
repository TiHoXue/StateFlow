#ifndef STATEFLOWLIB_TYPEDEFINE_HPP
#define STATEFLOWLIB_TYPEDEFINE_HPP

#include <any>
#include <functional>
#include <unordered_map>

namespace stateflow {

enum class EventType {
  None,
  // For test
  RobotStartEvent,
  RobotFireEvent,
  RobotStopEvent,
};

// Event Handler
template <typename... Args> using EventHandler = std::function<bool(Args...)>;
// Event Handler Base
using EventHandlerBase = std::function<bool(const std::any &)>;
using EventHandlerMap = std::unordered_map<EventType, EventHandlerBase>;

enum class StateType {
  None,
  // For test
  PrepareState,
  BattleState,
  EndState,
};
// Transition Map: EventType -> Next State
//
// Note: If StateType::None, it means the state machine will stop,
//       and if don't want to change the current state, just set the same
//       state type as the current state.
using TransitionMap = std::unordered_map<EventType, StateType>;

} // namespace stateflow

#endif