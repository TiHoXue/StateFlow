#ifndef STATEFLOWLIB_STATEBASE_HPP
#define STATEFLOWLIB_STATEBASE_HPP

#include "stateflow/TypeDefine.hpp"
namespace stateflow {

// State Base Class
class StateBase {
public:
  StateBase(StateType type);
  StateBase(const StateBase &) = delete;
  StateBase &operator=(const StateBase &) = delete;
  StateBase(StateBase &&) = delete;
  StateBase &operator=(StateBase &&) = delete;

  virtual ~StateBase() = default;

  virtual void OnEnter() {}
  virtual void OnExit() {}

  template <typename... Args> bool Handle(EventType event, Args &&...args) {
    auto handler = _eventHandlers.find(event);
    if (handler != _eventHandlers.end()) {
      auto params = std::make_tuple(std::forward<Args>(args)...);
      return handler->second(std::any(params));
    }
    return false;
  }

  void AddTransition(EventType event, StateType nextState);
  template <typename... Args>
  void AddEventHandler(EventType event, EventHandler<Args...> handler) {
    _eventHandlers[event] = [handler](const std::any &packed_args) {
      auto args = std::any_cast<std::tuple<Args...>>(packed_args);
      return std::apply(handler, args);
    };
  }

  StateType GetType() const;
  StateType GetNextState(EventType event) const;

private:
  StateType _type;
  TransitionMap _transitions;
  EventHandlerMap _eventHandlers;
};

} // namespace stateflow

#endif
