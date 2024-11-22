_English Version_
# StateFlow
A robust and intuitive framework for designing and managing finite state machines in C++.

## StateBase


---
_中文版_

# StateFlow
一个用`C++`开发的状态机框架，用于设计并管理有限状态机。

# StateBase
`StateBase`是状态机的状态基类。

用户要定义自己的状态类，需要继承`StateBase`并实现`OnEnter`和`OnExit`方法。同时需要在`StateType`中添加新的状态类型。