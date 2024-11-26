#include "stateflow/StateBase.hpp"
#include "stateflow/TypeDefine.hpp"
#include "stateflow/StateMachine.hpp"
#include <functional>
#include <gtest/gtest.h>
#include <iostream>

// PrepareState:
//   StartEvent -> BattleState
// BattleState:
//   FireEvent -> EndState
// EndState:
//   StopEvent -> Stop

class PrepareState : public stateflow::StateBase {
public:
  PrepareState() : StateBase(stateflow::StateType::PrepareState) {
    AddTransition(stateflow::EventType::RobotStartEvent,
                  stateflow::StateType::BattleState);
    AddEventHandler(stateflow::EventType::RobotStartEvent,
                    std::function<bool()>([this]() -> bool {
                      std::cout << "Robot start" << std::endl;
                      return true;
                    }));
  }
};

class BattleState : public stateflow::StateBase {
public:
  BattleState()
      : StateBase(stateflow::StateType::BattleState), _bullet(100) {
    AddTransition(stateflow::EventType::RobotFireEvent,
                  stateflow::StateType::EndState);
    AddEventHandler(stateflow::EventType::RobotFireEvent,
                    std::function<bool(int)>([this](int bullet) -> bool {
                      std::cout << "Robot fire " << bullet << " bullets"
                                << std::endl;
                      _bullet -= bullet;
                      std::cout << "Bullet left: " << _bullet << std::endl;
                      return true;
                    }));
  }

private:
  int _bullet;
};

class EndState : public stateflow::StateBase {
public:
  EndState() : StateBase(stateflow::StateType::EndState) {
    AddTransition(stateflow::EventType::RobotStopEvent,
                  stateflow::StateType::None);
    AddEventHandler(stateflow::EventType::RobotStopEvent,
                    std::function<bool()>([this]() -> bool {
                      std::cout << "Robot stop" << std::endl;
                      return true;
                    }));
  }
};

class RobotStateMachine : public stateflow::StateMachine {
public:
  RobotStateMachine() {
    AddState(new PrepareState());
    AddState(new BattleState());
    AddState(new EndState());
  }

  ~RobotStateMachine() = default;
};

TEST(StateMachineBaseTest, StateMachine) {
  RobotStateMachine machine;
  machine.Initialize(stateflow::StateType::PrepareState);
  EXPECT_EQ(machine.GetCurrentState(), stateflow::StateType::PrepareState);

  machine.Start();

  machine.HandleEvent(stateflow::EventType::RobotStartEvent);
  EXPECT_EQ(machine.GetCurrentState(), stateflow::StateType::BattleState);

  machine.HandleEvent(stateflow::EventType::RobotFireEvent, 10);
  EXPECT_EQ(machine.GetCurrentState(), stateflow::StateType::EndState);

  machine.HandleEvent(stateflow::EventType::RobotStopEvent);
  EXPECT_FALSE(machine.IsRunning());
}
