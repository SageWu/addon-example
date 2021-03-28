#ifndef MY_OBJECT_H
#define MY_OBJECT_H

#include <node.h>
#include <node_object_wrap.h>

using namespace v8;

class MyObject: public node::ObjectWrap {
  public:
    static void Init();
    static void NewInstance(const FunctionCallbackInfo<Value>& info);

    MyObject(double value);
    ~MyObject();
  
  private:
    static void New(const FunctionCallbackInfo<Value>& info);
    static void Add(const FunctionCallbackInfo<Value>& info);
    static Persistent<Function> constructor;

    double _value;
};

#endif