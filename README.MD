# 基本概念

## Isolate
每个`Isolate`都代表着一个`v8引擎`实例。\
各自之间的状态是相互独立的，拥有各自的堆栈，比如在某个`Isolate`中创建的对象不可以在其它`Isolates`中使用。\
`Isolate`包括堆管理器、垃圾回收器等。\
一个`Isolate`在任何时刻，只能有一个线程进入并占有它。

## Context
`JavaScript`沙箱执行上下文。\
`Context`包含内建对象和内建函数在`global`对象上。\
在某个`Isolate`中，可以有多个`Context`同时存在，不同`Context`之间的`global`对象相互不影响，并共享在堆中的其它所有对象。

## Context::Scope
为所有在当前scope中执行的操作设置执行上下文。

## HandleScope
管理`local handles`的生命周期。

## FunctionTemplate
用来创建运行时函数的模板，在一个`Context`中，只能有一个`Function`从模板中创建出来。\
可以在`FunctionTemplate`上设置属性，即为创建的函数对象的属性。\
每个`FunctionTemplate`都有对应的`InstanceTemplate`，用来创建对象实例，当从函数模板创建出来的函数被用作构造函数时。添加到实例模板上的属性，即为对象实例的属性。\
每个`FunctionTemplate`都有对应的`PrototypeTemplate`，用来创建运行时函数的原型对象。\
函数模板可以继承其他函数模板。

## ObjectTemplate
用来创建运行时对象的模板。
