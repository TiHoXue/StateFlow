#ifndef STATEFLOWLIB_STATEFACTORY_HPP
#define STATEFLOWLIB_STATEFACTORY_HPP

#include "stateflowlib/StateBase.hpp"
#include <unordered_map>
namespace stateflow {

class StateFactory {
public:
  static StateFactory &GetInstance();
  void RegisterStateCreator(StateType type,
                            std::function<StateBase *(StateType)> creator);
  StateBase *CreateState(StateType type);

private:
  StateFactory() = default;
  StateFactory(const StateFactory &) = delete;
  StateFactory &operator=(const StateFactory &) = delete;
  StateFactory(StateFactory &&) = delete;
  StateFactory &operator=(StateFactory &&) = delete;

  ~StateFactory() = default;

private:
  std::unordered_map<StateType, std::function<StateBase *(StateType)>>
      _stateCreators;
};

#define REGISTER_STATE_CREATOR(type, className)                                \
  StateFactory::GetInstance().RegisterStateCreator(                            \
      type, [](StateType type) { return new className(type); })
#define CREATE_STATE(type) StateFactory::GetInstance().CreateState(type)

} // namespace stateflow

#endif
