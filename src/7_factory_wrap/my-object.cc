#include "my-object.h"

Persistent<Function> MyObject::constructor;

// 初始化构造函数
void MyObject::Init() {
  Isolate* isolate = Isolate::GetCurrent();
  Local<Context> context = isolate->GetCurrentContext();

  // 创建构造函数模板
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, MyObject::New);
  // 设置构造函数名称
  tpl->SetClassName(String::NewFromUtf8(isolate, "MyObject"));

  // 实例内部分配存储槽
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // 设置原型方法
  NODE_SET_PROTOTYPE_METHOD(tpl, "add", MyObject::Add);

  // 持久化构造函数
  Local<Function> tplFn = tpl->GetFunction(context).ToLocalChecked();
  constructor.Reset(isolate, tplFn);
}

// 创建实例
void MyObject::NewInstance(const FunctionCallbackInfo<Value>& info) {
  Isolate* isolate = Isolate::GetCurrent();
  Local<Context> context = isolate->GetCurrentContext();
  HandleScope scope();

  const int argc = 1;
  Local<Value> argv[argc] = { info[0] };
  // 获取构造函数
  Local<Function> cons = Local<Function>::New(isolate, constructor);

  // 创建实例并返回
  info.GetReturnValue().Set(cons->NewInstance(context, argc, argv).ToLocalChecked());
}

void MyObject::New(const FunctionCallbackInfo<Value>& info) {
  Isolate* isolate = Isolate::GetCurrent();
  Local<Context> context = isolate->GetCurrentContext();
  HandleScope scope();

  // 判断是否通过 new
  if (info.IsConstructCall()) {
    // 参数处理
    double value;
    if (info[0]->IsUndefined()) {
      value = 0;
    } else {
      value = info[0]->NumberValue(context).ToChecked();
    }

    // 创建c++对象
    MyObject* myObject = new MyObject(value);
    // 关联
    myObject->Wrap(info.This());

    // 返回创建的实例
    info.GetReturnValue().Set(info.This());
  } else {
    MyObject::NewInstance(info);
  }
}

// 增加数值
void MyObject::Add(const FunctionCallbackInfo<Value>& info) {
  Isolate* isolate = Isolate::GetCurrent();
  Local<Context> context = isolate->GetCurrentContext();
  HandleScope scope();

  // 参数处理
  if (!info[0]->IsNumber()) {
    isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "需传入数值")));
  }
  double num = info[0]->NumberValue(context).ToChecked();

  // 提取关联的c++对象
  MyObject* myObject = ObjectWrap::Unwrap<MyObject>(info.Holder());
  myObject->_value += num;

  // 返回相加后的值
  info.GetReturnValue().Set(Number::New(isolate, myObject->_value));
}

MyObject::MyObject(double value): _value(value) {

}

MyObject::~MyObject() {
  
}