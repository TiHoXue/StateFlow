#ifndef STATEFLOWLIB_STATEBASE_HPP
#define STATEFLOWLIB_STATEBASE_HPP

#include <functional>
#include <unordered_map>
namespace stateflow {

// Event Type
enum class EventType {
  None,
};

using EventHandler = std::function<bool()>;
using EventHandlerMap = std::unordered_map<EventType, EventHandler>;

// State Type
enum class StateType {
  None,
};

using TransitionMap = std::unordered_map<EventType, StateType>;

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

  bool Handle(EventType event);

  void AddTransition(EventType event, StateType nextState);
  void AddEventHandler(EventType event, EventHandler handler);

  StateType GetType() const;
  StateType GetNextState(EventType event) const;

private:
  StateType _type;
  TransitionMap _transitions;
  EventHandlerMap _eventHandlers;
};

} // namespace stateflow

#endif
