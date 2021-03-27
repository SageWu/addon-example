#include <node.h>

using namespace v8;

void Run(const FunctionCallbackInfo<Value>& info) {
  Isolate* isolate = info.GetIsolate();
  Local<Context> context = isolate->GetCurrentContext();
  // 创建scope
  HandleScope scope();

  // 检查参数
  if (info.Length() < 1) {
    isolate->ThrowException(Exception::Error(String::NewFromUtf8(isolate, "需传入回调")));
  }
  if (!info[0]->IsFunction()) {
    isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "需传入回调函数")));
  }

  Local<Function> cb = Local<Function>::Cast(info[0]);
  // 调用回调函数
  const int argc = 1;
  Local<Value> argv[argc] = { String::NewFromUtf8(isolate, "data") };
  cb->Call(context, Null(isolate), argc, argv);
}

// 初始化模块
void Init(Local<Object> exports) {
  NODE_SET_METHOD(exports, "run", Run);
}

// 声明模块
NODE_MODULE(NODE_GYP_MODULE_NAME, Init);