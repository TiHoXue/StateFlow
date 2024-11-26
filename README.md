_English Version_
# StateFlow
A robust and intuitive framework for designing and managing finite state machines in C++.

This state machine is event-driven, with each event having a corresponding handler function. After processing an event, the state machine will automatically transition to the next state associated with that event. If the next state corresponding to a particular event is `None`, the state machine will halt.

## StateBase
`StateBase` is the base class for states in the state machine.

To define your own state class, you first need to add a new state type in `StateType` and a new state event in `EventType`. Then, you can inherit from the `StateBase` class, set the corresponding state type in the constructor, and add state transitions and event handler functions. If necessary, you can also override the `OnEnter` and `OnExit` methods.

---
_中文版_

# StateFlow
一个用`C++`开发的状态机框架，用于设计并管理有限状态机。

这个状态机是事件驱动的，每一个事件都有对应的处理函数，在处理完这个事件之后，状态机会自动转换到该事件对应的下一个状态。如果某个事件对应的下一个状态是`None`，那么状态机就会停止。

# StateBase
`StateBase`是状态机的状态基类。

如果要定义自己的状态类，首先需要在`StateType`中添加新的状态类型，并在`EventType`中添加新的状态事件。然后可以继承`StateBase`类，在构造函数中设置好对应的状态类型，并添加状态的转换和事件处理函数。如果需要的话，还可以重写`OnEnter`和`OnExit`方法。