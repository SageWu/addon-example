#include <node.h>

using namespace v8;

void MyFunction(const FunctionCallbackInfo<Value>& info) {
  Isolate* isolate = Isolate::GetCurrent();
  // 创建scope
  HandleScope scope();

  // 返回值
  info.GetReturnValue().Set(String::NewFromUtf8(isolate, "I am function"));
}

void CreateFunction(const FunctionCallbackInfo<Value>& info) {
  Isolate* isolate = Isolate::GetCurrent();
  Local<Context> context = isolate->GetCurrentContext();
  // 创建scope
  HandleScope scope();

  // 创建函数
  Local<FunctionTemplate> fnTpl = FunctionTemplate::New(isolate, MyFunction);
  Local<Function> fn = fnTpl->GetFunction(context).ToLocalChecked();
  // 函数设置名称，不设置则为匿名函数
  fn->SetName(String::NewFromUtf8(isolate, "MyFunction"));

  // 返回函数
  info.GetReturnValue().Set(fn);
}

// 初始化模块
void Init(Local<Object> exports) {
  NODE_SET_METHOD(exports, "createFunction", CreateFunction);
}

// 声明模块
NODE_MODULE(NODE_GYP_MODULE_NAME, Init)