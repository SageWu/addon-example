#ifndef VECTOR_H
#define VECTOR_H

#include <node.h>
#include <node_object_wrap.h>

using namespace v8;

class Vector: public node::ObjectWrap {
  public:
    static void Init(Local<Object> exports);

    Vector(double x, double y);
    ~Vector();

  private:
    static void New(const FunctionCallbackInfo<Value>& info);
    static void Getter(Local<String> key, const PropertyCallbackInfo<Value>& info);
    static void Setter(Local<String> key, Local<Value> value, const PropertyCallbackInfo<void>& info);
    static void GetX(const FunctionCallbackInfo<Value>& info);
    static void GetY(const FunctionCallbackInfo<Value>& info);
    static Persistent<Function> constructor;

    double _x;
    double _y;
};

#endif