#include "vector.h"

Persistent<Function> Vector::constructor;

// 初始化并导出 Vector 构造函数
void Vector::Init(Local<Object> exports) {
  Isolate* isolate = Isolate::GetCurrent();
  Local<Context> context = isolate->GetCurrentContext();

  // 创建函数模板
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, Vector::New);
  // 设置构造函数名称
  tpl->SetClassName(String::NewFromUtf8(isolate, "Vector"));

  // 每个从实例模板创建出来的实例，内部分配 1 个存储槽，用来存放关联的c++对象
  tpl->InstanceTemplate()->SetInternalFieldCount(1);
  // 实例设置属性访问器
  tpl->InstanceTemplate()->SetAccessor(
    String::NewFromUtf8(isolate, "x"),
    Getter,
    Setter
  );
  tpl->InstanceTemplate()->SetAccessor(
    String::NewFromUtf8(isolate, "y"),
    Getter,
    Setter
  );

  // 在构造函数的原型对象上设置方法
  NODE_SET_PROTOTYPE_METHOD(tpl, "getX", Vector::GetX);
  NODE_SET_PROTOTYPE_METHOD(tpl, "getY", Vector::GetY);

  Local<Function> tplFn = tpl->GetFunction(context).ToLocalChecked();
  // 持久化 Vector 构造函数
  constructor.Reset(isolate, tplFn);
  // 导出构造函数
  exports->Set(String::NewFromUtf8(isolate, "Vector"), tplFn);
}

// 创建实例
void Vector::New(const FunctionCallbackInfo<Value>& info) {
  Isolate* isolate = Isolate::GetCurrent();
  Local<Context> context = isolate->GetCurrentContext();
  HandleScope scope();

  // 判断是否通过 new 方式
  if (info.IsConstructCall()) {
    // 获取参数
    double x, y;
    if (info[0]->IsUndefined()) {
      x = 0;
    } else {
      x = info[0]->NumberValue(context).ToChecked();
    }
    if (info[1]->IsUndefined()) {
      y = 0;
    } else {
      y = info[1]->NumberValue(context).ToChecked();
    }

    // 创建c++对象
    Vector* vector = new Vector(x, y);
    // c++对象存放在创建的实例内部
    vector->Wrap(info.This());
    // 返回创建的实例
    info.GetReturnValue().Set(info.This());
  } else {
    // 直接调用函数处理
    Local<Function> cons = Local<Function>::New(isolate, constructor);
    const int argc = 2;
    Local<Value> argv[argc] = {
      info[0],
      info[1]
    };
    info.GetReturnValue().Set(cons->NewInstance(context, argc, argv).ToLocalChecked());
  }
}

// 实例属性 getter
void Vector::Getter(Local<String> key, const PropertyCallbackInfo<Value>& info) {
  Isolate* isolate = Isolate::GetCurrent();
  // 转为c++字符串
  std::string keyStr(*String::Utf8Value(isolate, key));
  // 获取存放在实例内部的c++对象 
  Vector* vector = ObjectWrap::Unwrap<Vector>(info.Holder());
  // 根据 key 返回属性值
  if (keyStr == "x") {
    info.GetReturnValue().Set(vector->_x);
  } else if (keyStr == "y") {
    info.GetReturnValue().Set(vector->_y);
  }
}

// 实例属性 setter
void Vector::Setter(Local<String> key, Local<Value> value, const PropertyCallbackInfo<void>& info) {
  Isolate* isolate = Isolate::GetCurrent();
  Local<Context> context = isolate->GetCurrentContext();
  // 处理参数
  std::string keyStr(*String::Utf8Value(isolate, key));
  double valueNum = value->NumberValue(context).ToChecked();
  // 获取存放在实例内部的c++对象 
  Vector* vector = ObjectWrap::Unwrap<Vector>(info.Holder());
  // 根据 key 设置属性值
  if (keyStr == "x") {
    vector->_x = valueNum;
  } else if (keyStr == "y") {
    vector->_y = valueNum;
  }
}

// 获取 x
void Vector::GetX(const FunctionCallbackInfo<Value>& info) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope();

  // 获取存放在实例内部的c++对象
  Vector* vector = ObjectWrap::Unwrap<Vector>(info.Holder());
  // 返回值 x
  info.GetReturnValue().Set(Number::New(isolate, vector->_x));
}

// 获取 y
void Vector::GetY(const FunctionCallbackInfo<Value>& info) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope();

  // 获取存放在实例内部的c++对象
  Vector* vector = ObjectWrap::Unwrap<Vector>(info.Holder());
  // 返回值 y
  info.GetReturnValue().Set(Number::New(isolate, vector->_y));
}

Vector::Vector(double x, double y): _x(x), _y(y) {

}

Vector::~Vector() {

}