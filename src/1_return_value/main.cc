#include <node.h>

void GetString(const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Isolate* isolate = info.GetIsolate();
  // 设置返回值
  info.GetReturnValue().Set(v8::String::NewFromUtf8(isolate, "hello world"));
}

// 初始化模块
void Init(v8::Local<v8::Object> exports) {
  // 导出 getString 方法
  NODE_SET_METHOD(exports, "getString", GetString);
}

// 声明模块
NODE_MODULE(NODE_GYP_MODULE_NAME, Init)