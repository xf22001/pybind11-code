#
#
#================================================================
#   
#   
#   文件名称：Makefile
#   创 建 者：肖飞
#   创建日期：2021年02月05日 星期五 14时35分25秒
#   修改日期：2021年02月05日 星期五 16时33分01秒
#   描    述：
#
#================================================================
include $(default_rules)

c_files := example.cpp

shared_lib_name := example$(shell python3-config --extension-suffix | sed 's:.so::g')

LOCAL_CFLAGS += -g -Wall -fPIC
LOCAL_CFLAGS += $(shell pybind11-config --includes)
LOCAL_CFLAGS += -I$(top)/c/utils

LOCAL_LDFLAGS += -L$(top)/c/utils/out/lib -Wl,-Bstatic -lxiaofei -Wl,-Bdynamic
LOCAL_LDFLAGS += -lpthread -lrt
LOCAL_DEPS := $(top)/c/utils/out/lib/libxiaofei.so $(top)/c/utils/out/lib/libxiaofei.a

include $(BUILD_SO)

include $(ADD_TARGET)

local_targets:
	mv out/lib/libexample.cpython-38-x86_64-linux-gnu.so example.so
	$(info "compile ok!")
