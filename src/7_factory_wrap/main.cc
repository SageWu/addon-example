#include <node.h>
#include "my-object.h"

using namespace v8;

void MyObjectFactory(const FunctionCallbackInfo<Value>& info) {
  HandleScope scope();
  MyObject::NewInstance(info);
}

void Init(Local<Object> exports) {
  MyObject::Init();

  NODE_SET_METHOD(exports, "MyObjectFactory", MyObjectFactory);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, Init)