

/*================================================================
 *
 *
 *   文件名称：example.cpp
 *   创 建 者：肖飞
 *   创建日期：2021年02月05日 星期五 15时20分59秒
 *   修改日期：2021年02月05日 星期五 16时48分28秒
 *   描    述：
 *
 *================================================================*/
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>
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

PYBIND11_MODULE(example, m)
{
	m.doc() = "pybind11 example plugin"; // optional module docstring

	m.def("add", &add, "A function which adds two numbers");
	m.def("set_data", &set_data, "Get NumPy arrays");
	m.def("set_str", &set_str, "Set str");
	m.def("get_str", &get_str, "Get str");
}
