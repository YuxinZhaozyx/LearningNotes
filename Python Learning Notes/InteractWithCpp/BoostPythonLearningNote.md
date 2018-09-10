# boost::python 学习笔记

## 基本使用

### 导出函数
cpp:
```c++
#include<string>
#include<boost/python.hpp>

using namespace std;
using namespace boost::python;

char const * greet()
{
    return "hello,world";
}

BOOST_PYTHON_MODULE(hello_ext)
{
    def("greet", greet);
}
```
python:
```python
import hello_ext
print hello_ext.greet()
```


### 导出类
#### 类方法
c++：
```c++
#include<string>
#include<boost/python.hpp>

using namespace std;
using namespace boost::python;

struct World
{
    void set(string msg) { this->msg = msg; }
    string greet() { return msg; }

    string msg;
};

BOOST_PYTHON_MODULE(hello) 
{
    class_<World>("World")
        .def("greet", &World::greet)
        .def("set", &World::set);
}
```
python:
```python
import hello 
planet = hello.World() # 调用默认构造函数，产生类对象
planet.set("howdy")   # 调用对象的方法
print planet.greet() # 调用对象的方法
```

#### 自定义构造函数
c++：
```c++
#include<string>
#include<boost/python.hpp>

using namespace std;
using namespace boost::python;

struct World
{
    World(string msg):msg(msg){} //增加构造函数
    World(double a, double b):a(a),b(b) {} //另外一个构造函数
    void set(string msg) { this->msg = msg; }
    string greet() { return msg; }
    double sum_s() { return a + b; }
    string msg;
    double a;
    double b;
};

BOOST_PYTHON_MODULE(hello) 
{
    class_<World>("World",init<string>()) 
        .def(init<double,double>()) // expose another construct
        .def("greet", &World::greet)
        .def("set", &World::set)
        .def("sum_s", &World::sum_s);
}
```
python:
```python
import hello
planet = hello.World(5,6)
planet2 = hello.World("hollo world")

print planet.sum_s()
print planet2.greet()
```

若不想导出任何构造函数，即不想从python端能够生成该类，则使用 no_init
```
class_<Abstract>("Abstract",no_init)
```

#### 类的数据成员
c++：
```c++
#include<string>
#include<boost/python.hpp>

using namespace std;
using namespace boost::python;

struct Var
{
    Var(string name):name(name),value(){}
    string const name;

    float value;
};

BOOST_PYTHON_MODULE(hello_var)
{
    class_<Var>("Var", init<string>())
        .def_readonly("name", &Var::name) //只读
        .def_readwrite("value", &Var::value); //读写
}
```
python:
```python
import hello_var

var = hello_var.Var("hello_var")
var.value = 3.14
# var.name = 'hello' # error
print var.name
```

#### 类的属性
c++：
```c++
#include<string>
#include<boost/python.hpp>

using namespace std;
using namespace boost::python;

struct Num
{
    Num(){}
    float get() const { return val; }
    void set(float val) { this->val = val; }
    float val;
};

BOOST_PYTHON_MODULE(hello_num)
{
    class_<Num>("Num")
        .add_property("rovalue", &Num::get) // 对外：只读
        .add_property("value", &Num::get, &Num::set);// 对外读写 .value值会改变.rovalue值，存储着同样的数据。
}
```
python:
```python
import hello_num
num = hello_num.Num()
num.value = 10
print num.rovalue #  result: 10
```

#### 类的继承关系
c++：
```c++
#include<string>
#include<iostream>
#include<boost/python.hpp>

using namespace std;
using namespace boost::python;

struct Base {
    virtual ~Base() {};
    virtual string getName() { return "Base"; }

    string str;
};

struct Derived : Base {
    string getName() { return "Derived"; }
};


void b(Base *base) { cout << base->getName() << endl; };

void d(Derived *derived) { cout << derived->getName() << endl; };

Base * factory() { return new Derived; }

/*
    下面的额外的代码如果去掉会报错。
    解决地址：http://stackoverflow.com/questions/38261530/unresolved-external-symbols-since-visual-studio-2015-update-3-boost-python-link/38291152#38291152
*/
namespace boost
{
    template <>
    Base const volatile * get_pointer<class Base const volatile >(
        class Base const volatile *c)
    {
        return c;
    }
}

BOOST_PYTHON_MODULE(hello_derived)
{
    class_<Base>("Base")
        .def("getName", &Base::getName)
        .def_readwrite("str", &Base::str);


    class_<Derived, bases<Base> >("Derived")
        .def("getName", &Derived::getName)
        .def_readwrite("str", &Derived::str);

    def("b", b);
    def("d", d);

    def("factory", factory,
        return_value_policy<manage_new_object>());//

}
```
python:
```python
import hello_derived
derive = hello_derived.factory()
hello_derived.d(derive)
```

#### 类的虚函数
c++：
```c++
/* 类的虚函数，实现的功能是：可以编写Python类，来继承C++类 */

#include<boost/python.hpp>
#include<boost/python/wrapper.hpp>
#include<string>
#include<iostream>

using namespace boost::python;
using namespace std;

struct Base
{
    virtual ~Base() {}
    virtual int f() { return 0; };
};


struct BaseWrap : Base, wrapper<Base>
{
    int f()
    {
        if (override f = this->get_override("f"))
            return f(); //如果函数进行重载了，则返回重载的
        return Base::f(); //否则返回基类
    }
    int default_f() { return this->Base::f(); }
};

BOOST_PYTHON_MODULE(hello_virtual)
{
    class_<BaseWrap, boost::noncopyable>("Base")
        .def("f", &Base::f, &BaseWrap::default_f);


}
```
python:
```python
import hello_virtual 

base = hello_virtual.Base()
# 定义派生类，继承C++类
class Derived(hello_virtual.Base):
    def f(self):
        return 42

derived = Derived()

print base.f()
print derived.f()
```

#### 类的运算符/特殊函数
c++：
```c++
#include<string>
#include<iostream>

// #include<boost/python.hpp> 如果仅包含该头文件，会出错

#include <boost/python/operators.hpp>
#include <boost/python/class.hpp>
#include <boost/python/module.hpp>
#include <boost/python/def.hpp>
#include <boost/operators.hpp>

using namespace std;
using namespace boost::python;

class FilePos
{
public:
    FilePos() :len(0) {}
    operator double()const { return len; };//重载类型转换符
    int len;
};

// operator 方法

FilePos operator+(FilePos pos, int a)
{
    pos.len = pos.len + a;
    return pos; //返回的是副本
}

FilePos operator+(int a, FilePos pos)
{
    pos.len = pos.len + a;
    return pos; //返回的是副本
}


int operator-(FilePos pos1, FilePos pos2)
{
    return (pos1.len - pos2.len);
}

FilePos operator-(FilePos pos, int a)
{
    pos.len = pos.len - a;
    return pos;
}

FilePos &operator+=(FilePos & pos, int a)
{
    pos.len = pos.len + a;
    return pos;
}

FilePos &operator-=(FilePos & pos, int a)
{
    pos.len = pos.len - a;
    return pos;
}

bool operator<(FilePos  pos1, FilePos pos2)
{
    if (pos1.len < pos2.len)
        return true;
    return false;
}


//特殊的方法

FilePos pow(FilePos pos1, FilePos pos2)
{
    FilePos res;
    res.len = std::pow(pos1.len, pos2.len);
    return res;
}
FilePos abs(FilePos pos)
{
    FilePos res;
    res.len = std::abs(pos.len);
    return res;
}

ostream& operator<<(ostream& out, FilePos pos)
{
    out << pos.len;
    return out;
}

BOOST_PYTHON_MODULE(hello_operator)
{
    class_<FilePos>("FilePos")
        .def_readwrite("len",&FilePos::len)
        .def(self + int())
        .def(int() + self)
        .def(self - self)
        .def(self - int())
        .def(self += int())
        .def(self -= other<int>())
        .def(self < self)
        .def(float_(self))//特殊方法 ,     __float__
        .def(pow(self, other<FilePos>()))  // __pow__
        .def(abs(self))         //  __abs__
        .def(str(self));                //  __str__ for ostream
}
```
python:
```python
import hello_operator

filepos1 = hello_operator.FilePos()
filepos1.len = 10

filepos2 = hello_operator.FilePos()
filepos2.len = 20;

print filepos1 - filepos2
```

### 函数
#### 函数的调用策略
c++:
```c++
#include<string>
#include<iostream>

#include<boost/python.hpp>

using namespace std;
using namespace boost::python;

struct X
{
    string str;
};
struct Z
{
    int value;
};

struct Y
{
    X x;
    Z *z;
    int z_value() { return z->value; }
};

X & f(Y &y, Z*z)
{
    y.z = z;
    return y.x;  //因为x是y的数据成员，x的声明周期与y进行了绑定。因为我们的目的是：Python接口应尽可能的反映C++接口
}

BOOST_PYTHON_MODULE(hello_call_policy)
{
    class_<Y>("Y")
        .def_readwrite("x", &Y::x)
        .def_readwrite("z", &Y::z)
        .def("z_value", &Y::z_value);
    class_<X>("X")
        .def_readwrite("str", &X::str);
    class_<Z>("Z")
        .def_readwrite("value", &Z::value);
    // return_internal_reference<1 表示返回的值与第一个参数有关系：即第一个参数是返回对象的拥有者（y和x都是引用的形式)。
    // with_custodian_and_ward<1, 2> 表示第二个参数的生命周期依赖于第一个参数的生命周期。
    def("f", f, return_internal_reference<1, with_custodian_and_ward<1, 2> >());
}
```

#### 函数重载
c++:
```c++
#include<string>
#include<iostream>

#include<boost/python.hpp>

using namespace std;
using namespace boost::python;

struct X
{

    bool f(int a)
    {
        return true;
    }
    bool f(int a, double b)
    {
        return true;
    }
    bool f(int a, double b, char c)
    {
        return true;
    }
    int f(int a, int b, int c)
    {
        return a + b + c;
    }
};
bool (X::*fx1)(int) = &X::f;
bool(X::*fx2)(int, double) = &X::f;
bool(X::*fx3)(int, double,char) = &X::f;
int(X::*fx4)(int, int,int) = &X::f;

BOOST_PYTHON_MODULE(hello_overloaded)
{
    class_<X>("X")
        .def("f", fx1)
        .def("f", fx2)
        .def("f", fx3)
        .def("f", fx4);
}
```
python:
```python
import hello_overloaded

x = hello_overloaded.X() # create a new object

print x.f(1)  # default int type
print x.f(2,double(3))
print x.f(4,double(5),chr(6))  # chr(6) convert * to char 
print x.f(7,8,9)
```

#### 函数的默认参数
##### 普通函数的默认参数
c++:
```c++
int f(int,double = 3.14,char const * = "hello");
int f1(int x){ return f(x);}
int f2(int x,double y){return f(x,y)}

//int module init
def("f",f); // 所有参数
def("f",f2); //两个参数
def("f",f1); //一个参数
```

还可利用宏批量完成上述功能
c++:
```c++
#include<string>
#include<iostream>

#include<boost/python.hpp>

using namespace std;
using namespace boost::python;

void foo(int a, char b = 1, unsigned c = 2, double d = 3)
{
    return;
}

BOOST_PYTHON_FUNCTION_OVERLOADS(foo_overloads, foo, 1, 4); // 参数个数的最小为1，最大为4

BOOST_PYTHON_MODULE(hello_overloaded)
{
    def("foo", foo, foo_overloads()); //实现导出带有默认参数的函数
}
```
python:
```python
import hello_overloaded


hello_overloaded.foo(1)

hello_overloaded.foo(1,chr(2))

hello_overloaded.foo(1,chr(2),3)  # 3对应的C++为unsigned int

hello_overloaded.foo(1,chr(2),3,double(4))
```

##### 成员函数的默认参数
c++:
```c++
#include<string>
#include<iostream>

#include<boost/python.hpp>

using namespace std;
using namespace boost::python;

struct george
{
    void wack_em(int a, int b = 0, char c = 'x')
    {
        return;
    }
};


BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(george_overloads, wack_em, 1, 3); // 参数个数的最小为1，最大为3

BOOST_PYTHON_MODULE(hello_member_overloaded)
{
    class_<george>("george")
        .def("wack_em", &george::wack_em, george_overloads());
}
```
python:
```python
import hello_member_overloaded

c = hello_member_overloaded.george()

c.wack_em(1)
c.wack_em(1,2)
c.wack_em(1,2,chr(3))
```
###### 利用init和optional实现构造函数的重载
```c++
#include<string>
#include<iostream>
#include<boost/python.hpp>

using namespace std;
using namespace boost::python;

struct X
{
    X(int a, char b = 'D', string c = "constructor", double b = 0.0) {}
};

BOOST_PYTHON_MODULE(hello_construct_overloaded)
{
    class_<X>("X")
        .def(init<int, optional<char, string, double> >()); // init 和 optional
}
```

### 对象接口
Python 是动态类型的语言，C++是静态类型的。Python变量可能是：integer, float, list, dict, tuple, str, long,等等，还有其他类型。从Boost.Python和C++的观点来看，Python中的变量是类object的实例
#### 基本接口
c++：
```c++
#include<string>
#include<iostream>
#include<boost/python.hpp>
#include <numpy/arrayobject.h>
using namespace std;
using namespace boost::python;

namespace bp = boost::python;

void f(object x)
{
    int y = extract<int>(x); // retrieve an int from x
}

int g(object x)
{
    extract<int> get_int(x);
    if (get_int.check())
        return get_int();
    else
        return 0;
}

int test(object &x)
{
    dict d = extract<dict>(x.attr("__dict__"));
    d["whatever"] = 4;
    return 0;
}

int test2(dict & d)
{
    d["helloworld"] = 3;
    return 0;
}

class A {
public:
    list lst;
    void listOperation(list &lst) {};
};

// 传入np.array数组对象，让C++进行处理
int add_arr_1(object & data_obj, object rows_obj, object cols_obj)
{
    PyArrayObject* data_arr = reinterpret_cast<PyArrayObject*>(data_obj.ptr());
    float * data = static_cast<float *>(PyArray_DATA(data_arr));
    // using data
    int rows = extract<int>(rows_obj);
    int cols = extract<int>(cols_obj);
    for (int i = 0; i < rows*cols; i++)
    {
        data[i] += 1;
    }
    return 0;
}

BOOST_PYTHON_MODULE(hello_object)
{
    def("test", test);
    def("test2", test2);
    def("add_arr_1", add_arr_1);
}
```
python:
```python
import hello_object

dic1 = {"whatever":1}
hello_object.test2(dic1)

arr = np.array([1,2,3],dtype = float32)
print arr.dtype
print arr
hello_object.add_arr_1(arr,1,3)
print arr
```
## cv::Mat 与 numpy.ndarray 交互示例

### C++端源文件

```c++
/* source.cpp */
#include <iostream>
#include <boost/python.hpp>
#include <opencv2/core/core.hpp>
#include <cstdlib>

namespace bp = boost::python;

class Converter
{
public:
    static cv::Mat fromStrToMat(bp::str img_data, int rows, int cols, int channels, int dtype);
    static bp::list fromMatToList(const cv::Mat& img);
    template<typename T>
    static void CopyDataToList(bp::list& dataList, const cv::Mat& img);
};

cv::Mat Converter::fromStrToMat(bp::str img_data, int rows, int cols, int channels, int dtype)
{
    void* data = (void*)((const char*)bp::extract<const char*>(img_data));
    int depth;
    switch(dtype)
    {
        case 0: depth = CV_8U; break;
        case 1: depth = CV_8S; break;
        case 2: depth = CV_16U; break;
        case 3: depth = CV_16S; break;
        case 4: depth = CV_32S; break;
        case 5: depth = CV_32F; break;
        case 6: depth = CV_64F; break;
        default:
        	std::cerr << "Unknown Data Type\n";
        	std::exit(-1);
    }
    return cv::Mat(rows, cols, CV_MAKETYPE(depth,channels), data);
}

template<typename T>
void Converter::CopyDataToList(bp::list& dataList, const cv::Mat& img)
{
	dataList = bp::list();
	for (size_t nrow = 0; nrow < img.rows; nrow++)
	{
		for(size_t ncol = 0; ncol < img.cols * img.channels(); ncol++)
		{
			dataList.append<T>(img.at<T>(nrow,ncol));
		}
	}
}

bp::list Converter::fromMatToList(const cv::Mat& img)
{
	bp::list img_data = bp::list();

	int depth;
	switch(img.depth())
	{
		case CV_8U:  depth = 0; CopyDataToList<uchar>(img_data, img);  break;
		case CV_8S:  depth = 1; CopyDataToList<uchar>(img_data, img);  break;
		case CV_16U: depth = 2; CopyDataToList<ushort>(img_data, img); break;
		case CV_16S: depth = 3; CopyDataToList<short>(img_data, img);  break;
		case CV_32S: depth = 4; CopyDataToList<int>(img_data, img);    break;
		case CV_32F: depth = 5; CopyDataToList<float>(img_data, img);  break;
		case CV_64F: depth = 6; CopyDataToList<double>(img_data, img); break;
		default: depth = 7;
	}

	bp::list info = bp::list();
	info.append<int>(img.rows);
	info.append<int>(img.cols);
	info.append<int>(img.channels());
	info.append<int>(depth);

	bp::list ret_list = bp::list();
	ret_list.append<bp::list>(info);
	ret_list.append<bp::list>(img_data);

	return ret_list;
}

bp::list fun1(int dtype)
{
    cv::Mat src;
    switch(dtype)
    {
    	case 0: src = (Mat_<uchar>(3,3) << 0,1,2,3,4,5,6,7,8); break;
    	case 1: src = (Mat_<char>(3,3) << 0,-1,2,-3,4,5,6,7,8); break;
    	case 2: src = (Mat_<ushort>(3,3) << 0,1,2,3,4,5,6,7,8); break;
    	case 3: src = (Mat_<short>(3,3) << 0,-1,2,-3,4,5,6,7,8); break;
    	case 4: src = (Mat_<int>(3,3) << 0,1,-2,3,-4,5,6,7,8); break;
    	case 5: src = (Mat_<float>(3,3) << 0.4,1.5,-2.6,3,4,5,6,7,8); break;
    	case 6: src = (Mat_<double>(3,3) << 0.4,1.5,-2.6,3,4,5,6,7,8); break;
    	default: std::cout <<"error\n";
	}
	
	return Converter::fromMatToList(src);
}

void fun2(bp::str img_data, int rows, int cols, int channels, int dtype)
{
    cv::Mat m = Converter::fromStrToMat(img_data, rows, cols, channels, dtype);
    std::cout << m << std::endl;
    std::cout << m.depth() << std::endl;
    std::cout << "(" << m.rows << ',' << m.cols << ',' << m.channels << ")\n";
}

BOOST_PYTHON_MODULE(interact)
{
	bp::def("fun1",&fun1);
	bp::def("fun2",&fun2);
}
```

### python端源文件
```python
#coding=utf-8

import numpy as np
import interact

class Converter:
	@staticmethod
	def fromListToNdarray(dataList):
		if dataList[0][3] == 0:
			dtype = np.uint8
		elif dataList[0][3] == 1:
			dtype = np.int8
		elif dataList[0][3] == 2:
			dtype = np.uint16
		elif dataList[0][3] == 3:
			dtype = np.int16
		elif dataList[0][3] == 4:
			dtype = np.int32
		elif dataList[0][3] == 5:
			dtype = np.float32
		elif dataList[0][3] == 6:
			dtype = np.float64
		else:
			raise Exception("Unknown data type",dtype)
		
		dataArray = np.array(dataList[1])
		dataArray = dataArray.astype(dtype)
		if dataList[0][2] != 1:
			dataArray = dataArray.reshape(dataList[0][0], dataList[0][1], dataList[0][2])
		else:
			dataArray = dataArray.reshape(dataList[0][0], dataList[0][1])

		return dataArray

	@staticmethod
	def fromNdarrayToStr(dataArray):
		if dataArray.dtype.type is np.uint8:
			dtype = 0
		elif dataArray.dtype.type is np.int8:
			dtype = 1
		elif dataArray.dtype.type is np.uint16:
			dtype = 2
		elif dataArray.dtype.type is np.int16:
			dtype = 3
		elif dataArray.dtype.type is np.int32:
			dtype = 4
		elif dataArray.dtype.type is np.float32:
			dtype = 5
		elif dataArray.dtype.type is np.float64:
			dtype = 6
		else:
			raise Exception("Unknown data type", dataArray.dtype.type)
		
		dataStr = dataArray.tostring()

		if len(dataArray.shape) == 2:
			shape = (dataArray.shape[0], dataArray.shape[1], 1)
		else:
			shape = dataArray.shape

		return dataStr,shape,dtype
    
def fun1(dtype):
	dataList = interact.fun1(dtype)
	dataArray = Converter.fromListToNdarray(dataList)
	return dataArray

def fun2(dataArray):
	dataStr, shape, dtype = Converter.fromNdarrayToStr(dataArray)
	interact.fun2(dataStr,shape[0],shape[1],shape[2],dtype)
	
if __name__ == '__main__':
	for i in range(7):
		dataArray = fun1(i)
		print dataArray
		print dataArray.dtype
		print dataArray.shape

	l = [ [[0,1,2],[3,4,5],[-6,7,8]],
		[[9,10,11],[12,13,14],[15,16,17]] ]
	
	arr = np.array(l)
	arr = arr.astype(np.int8)
	fun2(arr)
```

### Makefile 示例

```makefile
interact.so : source.o
	g++ -o interact.so source.o -fPIC -shared -lpython2.7 -lboost_python -lboost_system

source.o : 
	g++ -c source.cpp -o source.o -fPIC
	
clean :
	rm -rf source.o example.so
```
## cv::Rect 与 boost::python::list 间的转换
```
#include <boost/python.hpp>
#include <opencv2/core/core.hpp>

namesapce bp = boost::python;

class Converter
{
public:
	static bp::list fromRectToList(const cv::Rect& rect);

	static cv::Rect fromListToRect(const bp::list lst);
};


static bp::list Converter::fromRectToList(const cv::Rect& rect)
{
	bp::list lst;
	lst.append(rect.x);
	lst.append(rect.y);
	lst.append(rect.width);	
	lst.append(rect.height);
	return lst;
}

static cv::Rect Converter::fromListToRect(const bp::list lst)
{
	int x = (int)bp::extract<int>(lst[0]);
	int y = (int)bp::extract<int>(lst[1]);
	int w = (int)bp::extract<int>(lst[2]);
	int h = (int)bp::extract<int>(lst[3]);
	return cv::Rect(x,y,w,h);
}
```

## std::vector 与 boost::python::list 间的转换
```c++
#include <boost/python.hpp>
#include <boost/python/stl_iterator.hpp>
#include <vector>

namesapce bp = boost::python;

class Converter
{
public:
	template<typename T>
	static bp::list fromVectorToList(const std::vector<T>& vec);

	template<typename T>
	static std::vector<T> fromListToVector(const bp::list& lst);
};

template<typename T>
static bp::list Converter::fromVectorToList(const std::vector<T>& vec)
{
	bp::list ret_list;
	for(auto it = vec.begin(); it != vec.end(); ++it)
	{
		ret_list.append<T>(*it);
	}
	return ret_list;
}

template<typename T>
static std::vector<T> Converter::fromListToVector(const bp::list& lst)
{
	bp::stl_input_iterator<T> begin(lst), end;
	std::vector<T> ret_vector;
	ret_vector.insert(ret_vector.end(),begin,end);
	return ret_vector;
}

```