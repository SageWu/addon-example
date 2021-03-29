#ifndef MY_OBJECT_H
#define MY_OBJECT_H

#include <node.h>
#include <node_object_wrap.h>

using namespace v8;

class MyObject: public node::ObjectWrap {
  public:
    static void Init();
    static void NewInstance(const FunctionCallbackInfo<Value>& info);

    double _value;

  private:
    static void New(const FunctionCallbackInfo<Value>& info);
    static void Getter(Local<String> key, const PropertyCallbackInfo<Value>& info);
    static Persistent<Function> constructor;

    MyObject(double value);
    ~MyObject();
};

#endif