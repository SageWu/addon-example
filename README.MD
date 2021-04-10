# 使用Addon的原因
* 使用现有C/C++库或项目
* 访问操作系统的能力
* 计算型任务

# Addon实现方式

## Direct Use of V8
本仓库所使用的方式。

## NAN(Native Abstractions for Node.js)
针对`v8`引擎实现，需更新`nan`当`nodejs`所使用的`v8`更新时。[示例](https://github.com/SageWu/nan-example)。

## NAPI(Node-API)
JS引擎无关，向后兼容，无需重新编译。使用`node-addon-api`，则可以以面向对象的模式使用`napi`的接口，开发体验更友好。

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

## Handle
代表对象引用，内部存在一个指针指向`v8`创建的对象。\
由`v8`的垃圾回收器进行管理，跟踪对象是否还存在引用，以及更新其内部指针当对象发生移动的时候。\
`handle`分成`local`和`persistent`两种，`persistent handle`需明确地进行销毁，而`local handle`则可通过`HandleScope`进行管理。

## FunctionTemplate
用来创建运行时函数的模板，在一个`Context`中，只能有一个`Function`从模板中创建出来。\
可以在`FunctionTemplate`上设置属性，即为创建的函数对象的属性。\
每个`FunctionTemplate`都有对应的`InstanceTemplate`，用来创建对象实例，当从函数模板创建出来的函数被用作构造函数时。添加到实例模板上的属性，即为对象实例的属性。\
每个`FunctionTemplate`都有对应的`PrototypeTemplate`，用来创建运行时函数的原型对象。\
函数模板可以继承其他函数模板。

## ObjectTemplate
用来创建运行时对象的模板。

# 构建工具

## node-gyp
基于谷歌的`GYP(Generate You Projects)`构建工具。该工具根据操作系统生成对应的项目构建配置文件，并使用平台特定的编译工具，完成项目的构建。例如：`Linux`平台下生成`Makefile`，`Mac`平台下生成`.xcodeproj`，`Windows`平台下生成`.sln`和`.vcproject`。

优点：`nodejs`自带，配置相对简单。\
缺点：有所限制。

## CMake.js
基于`CMake`。

优点：对于已经使用`CMake`的项目或库友好，可配置性强。

## 预构建
node-pre-gyp，prebuild