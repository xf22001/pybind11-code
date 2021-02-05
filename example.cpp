

/*================================================================
 *
 *
 *   文件名称：example.cpp
 *   创 建 者：肖飞
 *   创建日期：2021年02月05日 星期五 15时20分59秒
 *   修改日期：2021年02月05日 星期五 17时25分17秒
 *   描    述：
 *
 *================================================================*/
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>

#include <iostream>
#include <memory>


#include "util_log.h"

namespace py = pybind11;

int add(int i, int j)
{
	return i + j;
}

void set_data(py::array_t<char> input)
{
	util_log *log = util_log::get_instance();
	py::buffer_info buffer_info = input.request();
	printf("dim:%ld \n", buffer_info.ndim);

	for (int cnt = 0; cnt < buffer_info.ndim; cnt++) {
		log->printf("dim %ld size %d\n", cnt, buffer_info.shape[cnt]);
	}

	log->dump((const char *)buffer_info.ptr, buffer_info.size);
}

void set_str(std::string s)
{
	util_log *log = util_log::get_instance();
	log->printf("%s\n", s.c_str());
}

std::vector<std::string> get_str(void)
{
	std::vector<std::string> v;
	v.push_back("xiaofei");
	v.push_back("xiaofei");
	return v;
}

template< typename T >
class MyHolder
{
public:
	explicit MyHolder( T *ptr = nullptr ) : ptr_( ptr ) {}

	template< typename U > MyHolder( MyHolder< U > ptr ) :
		ptr_( dynamic_cast< T * >( ptr.get() ) ) {}

	MyHolder( const MyHolder &other, T *ptr ) : ptr_(ptr) {}

	T *get() const
	{
		return ptr_;
	}

	T *operator-> () const
	{
		return ptr_;
	}

private:
	T *ptr_;
};

class A
{
public:
	virtual ~A() = default;
	virtual void foo() const = 0;
};

class B
{
public:
	virtual ~B() = default;
	virtual void bar() const = 0;
};

class C : public A, public B
{
public:
	C() = default;
	virtual ~C() = default;
	virtual void foo() const override
	{
		std::cout << "foo" << std::endl;
	}
	virtual void bar() const override
	{
		std::cout << "bar" << std::endl;
	}
};

void testA(MyHolder<A> ptr)
{
	ptr->foo();
}

void testB(MyHolder<B> ptr)
{
	ptr->bar();
}

PYBIND11_MODULE(example, m)
{
	m.doc() = "pybind11 example plugin"; // optional module docstring

	m.def("add", &add, "A function which adds two numbers");
	m.def("set_data", &set_data, "Get NumPy arrays");
	m.def("set_str", &set_str, "Set str");
	m.def("get_str", &get_str, "Get str");
	m.def("testa", &testA, "testA");
	m.def("testb", &testB, "testB");
	py::class_<MyHolder<char *>>(m, "MyHolder", py::dynamic_attr()).def(py::init<>());
	py::class_<A>(m, "A", py::dynamic_attr());
	py::class_<B>(m, "B", py::dynamic_attr());
	py::class_<C>(m, "C", py::dynamic_attr()).def(py::init<>());
}
