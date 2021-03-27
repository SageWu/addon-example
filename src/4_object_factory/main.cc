#include <node.h>

using namespace v8;

void CreateObject(const FunctionCallbackInfo<Value>& info) {
  Isolate* isolate = Isolate::GetCurrent();
  // 创建scope
  HandleScope scope();

  // 创建对象
  Local<Object> obj = Object::New(isolate);
  obj->Set(String::NewFromUtf8(isolate, "msg"), info[0]);

  // 返回对象
  info.GetReturnValue().Set(obj);
}

// 初始化模块
void Init(Local<Object> exports) {
  NODE_SET_METHOD(exports, "createObject", CreateObject);
}

// 声明模块
NODE_MODULE(NODE_GYP_MODULE_NAME, Init)