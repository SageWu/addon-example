#include <node.h>
#include "my-object.h"

using namespace v8;

void CreateObject(const FunctionCallbackInfo<Value>& info) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);
  MyObject::NewInstance(info);
}

void Add(const FunctionCallbackInfo<Value>& info) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  MyObject* obj1 = node::ObjectWrap::Unwrap<MyObject>(info[0]->ToObject(isolate));
  MyObject* obj2 = node::ObjectWrap::Unwrap<MyObject>(info[1]->ToObject(isolate));
  double sum = obj1->_value + obj2->_value;
  info.GetReturnValue().Set(sum);
}

void Init(Local<Object> exports) {
  MyObject::Init();

  NODE_SET_METHOD(exports, "createObject", CreateObject);
  NODE_SET_METHOD(exports, "add", Add);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, Init)