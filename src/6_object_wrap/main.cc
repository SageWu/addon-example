#include <node.h>
#include "vector.h"

using namespace v8;

// 初始化模块
void Init(Local<Object> exports) {
  // 初始化 Vector 构造函数
  Vector::Init(exports);
}

// 声明模块
NODE_MODULE(NODE_GYP_MODULE_NAME, Init)