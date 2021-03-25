#include <node.h>

using namespace v8;

void Add(const FunctionCallbackInfo<Value>& info) {
  Isolate* isolate = info.GetIsolate();

  // 参数检查
  if (info.Length() < 2) {
    isolate->ThrowException(Exception::Error(String::NewFromUtf8(isolate, "需传入两个数值")));
  }
  if (!info[0]->IsNumber() || !info[1]->IsNumber()) {
    isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "参数类型需为数值")));
  }

  // 相加
  Local<Context> context = isolate->GetCurrentContext();
  double num1 = info[0]->NumberValue(context).ToChecked();
  double num2 = info[1]->NumberValue(context).ToChecked();
  double sum = num1 + num2;

  // 返回结果
  info.GetReturnValue().Set(sum);
}

// 初始化模块
void Init(Local<Object> exports) {
  // 导出 add 方法
  NODE_SET_METHOD(exports, "add", Add);
}

// 声明模块
NODE_MODULE(NODE_GYP_MODULE_NAME, Init)