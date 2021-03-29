#include "my-object.h"

Persistent<Function> MyObject::constructor;

void MyObject::Init() {
  Isolate* isolate = Isolate::GetCurrent();
  Local<Context> context = isolate->GetCurrentContext();

  // 创建构造函数模板并设置名称
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, MyObject::New);
  tpl->SetClassName(String::NewFromUtf8(isolate, "MyObject"));
  // 实例模板设置内部存储槽以及属性访问器
  tpl->InstanceTemplate()->SetInternalFieldCount(1);
  tpl->InstanceTemplate()->SetAccessor(String::NewFromUtf8(isolate, "value"), MyObject::Getter);

  // 获取构造函数并持久化
  Local<Function> tplFn = tpl->GetFunction(context).ToLocalChecked();
  constructor.Reset(isolate, tplFn);
}

void MyObject::NewInstance(const FunctionCallbackInfo<Value>& info) {
  Isolate* isolate = Isolate::GetCurrent();
  Local<Context> context = isolate->GetCurrentContext();
  HandleScope scope(isolate);

  const int argc = 1;
  Local<Value> argv[argc] = { info[0] };
  // 拿到构造函数，实例化对象
  Local<Function> cons = Local<Function>::New(isolate, constructor);
  info.GetReturnValue().Set(cons->NewInstance(context, argc, argv).ToLocalChecked());
}

void MyObject::New(const FunctionCallbackInfo<Value>& info) {
  Isolate* isolate = Isolate::GetCurrent();
  Local<Context> context = isolate->GetCurrentContext();
  HandleScope scope(isolate);

  double value = info[0]->NumberValue(context).ToChecked();
  MyObject* obj = new MyObject(value);
  // c++对象与实例关联
  obj->Wrap(info.This());
  info.GetReturnValue().Set(info.This());
}

void MyObject::Getter(Local<String> key, const PropertyCallbackInfo<Value>& info) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  std::string keyStr(*String::Utf8Value(isolate, key));
  // 提取关联的c++对象
  MyObject* obj = node::ObjectWrap::Unwrap<MyObject>(info.Holder());
  if (keyStr == "value") {
    info.GetReturnValue().Set(Number::New(isolate, obj->_value));
  } else {
    info.GetReturnValue().SetUndefined();
  }
}

MyObject::MyObject(double value): _value(value) {

}

MyObject::~MyObject() {

}