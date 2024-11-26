#Auto generated, please dont edit. Editing might result in build failure or may render project unable to build.

SRC = src
SOURCES = $(shell find $(SRC) -name "*.cpp")
OPENSDK_ROOT = /opt/opensdk/

###################  DO NOT EDIT - BEGIN #########################
#version_begin
VERSION = 5.00
#version_end

#include_begin
INCL = $(OPENSDK_ROOT)/opensdk-$(VERSION)/common/inc/
#include_end

#pp5_begin
CXXFLAGS5 = -O2 -g -Wall -fmessage-length=0
#pp5_end

#pp6_begin
CXXFLAGS6 = -O2 -g -Wall -fmessage-length=0
#pp6_end

#pp7_begin
CXXFLAGS7 = -O2 -g -Wall -fmessage-length=0
#pp7_end

#pp8_begin
CXXFLAGS8 = -O2 -g -Wall -fmessage-length=0
#pp8_end

#pp9_begin
CXXFLAGS9 = -O2 -g -Wall -fmessage-length=0
#pp9_end

#pp10_begin
CXXFLAGS10 = -O2 -g -Wall -fmessage-length=0
#pp10_end

#lib5_begin
LIBS5 = -Llibs -lapphelper_wn5
#lib5_end

#lib6_begin
LIBS6 = -Llibs -lapphelper_s3l -lrt
#lib6_end

#lib7_begin
LIBS7 = -Llibs -lapphelper_cv2 -lrt
#lib7_end

#lib8_begin
LIBS8 = -Llibs -lapphelper_wn7 -lrt
#lib8_end

#lib9_begin
LIBS9 = -Llibs -lapphelper_cv2x -lrt
#lib9_end

#lib10_begin
LIBS10 = -Llibs -lapphelper_mt8137 -lrt
#lib10_end
###################  DO NOT EDIT - END  #########################

APP_HEADERS = $(shell find inc -name "*.h")
INC_APP = $(addprefix -I, $(sort $(dir $(APP_HEADERS))))
INC = $(addprefix -I, $(INCL))

PATH5 = $(OPENSDK_ROOT)/opensdk-$(VERSION)/armv7-cortex_A7-linux-gnueabihf/bin
CXX5 = $(PATH5)/armv7-cortex_A7-linux-gnueabihf-g++
TOOLS_PATH5 = $(PATH5)/../armv7-cortex_A7-linux-gnueabihf/sysroot
INC5 = -I$(TOOLS_PATH5)/usr/include/
OBJS5 = $(patsubst $(SRC)%.cpp, $(SRC)%_wn5.o, $(SOURCES))
APP_HELPER_PATH5 = $(TOOLS_PATH5)/usr/lib
TARGET5 = bin/test_BestShot_wn5

PATH6 = $(OPENSDK_ROOT)/opensdk-$(VERSION)/linaro-armv7ahf-2017.08-gcc7.1/bin
CXX6 = $(PATH6)/arm-linux-gnueabihf-g++
TOOLS_PATH6 = $(PATH6)/../arm-linux-gnueabihf/libc
INC6 = -I$(TOOLS_PATH6)/usr/include/
OBJS6 = $(patsubst $(SRC)%.cpp, $(SRC)%_s3l.o, $(SOURCES))
APP_HELPER_PATH6 = $(TOOLS_PATH6)/usr/lib
TARGET6 = bin/test_BestShot_s3l

PATH7 = $(OPENSDK_ROOT)/opensdk-$(VERSION)/linaro-aarch64-2018.08-gcc8.2/bin
CXX7 = $(PATH7)/aarch64-linux-gnu-g++
TOOLS_PATH7 = $(PATH7)/../aarch64-linux-gnu/libc
INC7 = -I$(TOOLS_PATH7)/usr/include/
OBJS7 = $(patsubst $(SRC)%.cpp, $(SRC)%_cv2.o, $(SOURCES))
APP_HELPER_PATH7 = $(TOOLS_PATH7)/lib_cv2
LD_FLAGS7 = -Wl,-E,-rpath-link=$(APP_HELPER_PATH7)
TARGET7 = bin/test_BestShot_cv2

PATH8 = $(OPENSDK_ROOT)/opensdk-$(VERSION)/armv7-wn7-linux-gnueabihf/bin
CXX8 = $(PATH8)/armv7-wn7-linux-gnueabihf-g++
TOOLS_PATH8 = $(PATH8)/../armv7-wn7-linux-gnueabihf/sysroot
INC8 = -I$(TOOLS_PATH8)/usr/include/
OBJS8 = $(patsubst $(SRC)%.cpp, $(SRC)%_wn7.o, $(SOURCES))
APP_HELPER_PATH8 = $(TOOLS_PATH8)/usr/lib
TARGET8 = bin/test_BestShot_wn7

PATH9 = $(OPENSDK_ROOT)/opensdk-$(VERSION)/linaro-aarch64-2020.09-gcc10.2-linux5.4/bin
CXX9 = $(PATH9)/aarch64-linux-gnu-g++
TOOLS_PATH9 = $(PATH9)/../aarch64-linux-gnu/libc
INC9 = -I$(TOOLS_PATH9)/usr/include/
OBJS9 = $(patsubst $(SRC)%.cpp, $(SRC)%_cv2x.o, $(SOURCES))
APP_HELPER_PATH9 = $(TOOLS_PATH9)/lib_cv2x
LD_FLAGS9 = -Wl,-E,-rpath-link=$(APP_HELPER_PATH9)
TARGET9 = bin/test_BestShot_cv2x

PATH10 = $(OPENSDK_ROOT)opensdk-$(VERSION)/aarch64-poky-linux/sysroots/x86_64-oesdk-linux/usr/bin/aarch64-poky-linux
CXX10 = $(PATH10)/aarch64-poky-linux-clang++
TOOLS_PATH10 =  $(OPENSDK_ROOT)opensdk-$(VERSION)/aarch64-poky-linux/sysroots/aarch64-poky-linux/lib
INC10 = -I$(OPENSDK_ROOT)opensdk-$(VERSION)/aarch64-poky-linux/sysroots/aarch64-poky-linux/usr/include
OBJS10 = $(patsubst $(SRC)%.cpp, $(SRC)%_mt8137.o, $(SOURCES))
APP_HELPER_PATH10 = $(TOOLS_PATH10)/lib_mt8137
LD_FLAGS10 = -Wl,-E,-rpath-link=$(APP_HELPER_PATH10)
TARGET10 = bin/test_BestShot_mt8137

all: $(TARGET9) 

$(TARGET5): clean_bin $(OBJS5)
	$(CXX5) $(OPENSDK_ROOT)/opensdk-$(VERSION)/templates/libs/main_wn5.o $(OBJS5) -o $@ -L$(APP_HELPER_PATH5) $(LIBS5)
#strip5_begin
	$(PATH5)/armv7-cortex_A7-linux-gnueabihf-strip --strip-all $@
#strip5_end

src/%_wn5.o: src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	$(CXX5) $(CXXFLAGS5) -c -o '$@' '$<' $(INC5) $(INC) $(INC_APP)
	@echo 'Finished building: $<'
	@echo ' '

$(TARGET6): clean_bin $(OBJS6)
	$(CXX6) $(OPENSDK_ROOT)/opensdk-$(VERSION)/templates/libs/main_s3l.o $(OBJS6) -o $@ -L$(APP_HELPER_PATH6) $(LIBS6)
#strip6_begin
	$(PATH6)/arm-linux-gnueabihf-strip --strip-all $@
#strip6_end

src/%_s3l.o: src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	$(CXX6) $(CXXFLAGS6) -c -o '$@' '$<' $(INC6) $(INC) $(INC_APP)
	@echo 'Finished building: $<'
	@echo ' '

$(TARGET7): clean_bin $(OBJS7)
	$(CXX7) $(OPENSDK_ROOT)/opensdk-$(VERSION)/templates/libs/main_cv2.o $(OBJS7) -o $@ -L$(APP_HELPER_PATH7) $(LIBS7) $(LD_FLAGS7)
#strip7_begin
	$(PATH7)/aarch64-linux-gnu-strip --strip-all $@
#strip7_end

src/%_cv2.o: src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	$(CXX7) $(CXXFLAGS7) -c -o '$@' '$<' $(INC7) $(INC) $(INC_APP)
	@echo 'Finished building: $<'
	@echo ' '

$(TARGET8): clean_bin $(OBJS8)
	$(CXX8) $(OPENSDK_ROOT)/opensdk-$(VERSION)/templates/libs/main_wn7.o $(OBJS8) -o $@ -L$(APP_HELPER_PATH8) $(LIBS8)
#strip8_begin
	$(PATH8)/armv7-wn7-linux-gnueabihf-strip --strip-all $@
#strip8_end

src/%_wn7.o: src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	$(CXX8) $(CXXFLAGS8) -c -o '$@' '$<' $(INC8) $(INC) $(INC_APP)
	@echo 'Finished building: $<'
	@echo ' '

$(TARGET9): clean_bin $(OBJS9)
	$(CXX9) $(OPENSDK_ROOT)/opensdk-$(VERSION)/templates/libs/main_cv2x.o $(OBJS9) -o $@ -L$(APP_HELPER_PATH9) $(LIBS9) $(LD_FLAGS9)
#strip9_begin
	$(PATH9)/aarch64-linux-gnu-strip --strip-all $@
#strip9_end

src/%_cv2x.o: src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	$(CXX9) $(CXXFLAGS9) -c -o '$@' '$<' $(INC9) $(INC) $(INC_APP)
	@echo 'Finished building: $<'
	@echo ' '

$(TARGET10): clean_bin $(OBJS10)
	$(CXX10) $(OPENSDK_ROOT)opensdk-$(VERSION)/templates/libs/main_mt8137.o $(OBJS10) -o $@ -L$(APP_HELPER_PATH10) $(LIBS10) $(LD_FLAGS10)
#strip10_begin
	$(PATH10)/aarch64-poky-linux-strip --strip-all $@
#strip10_end

src/%_mt8137.o: src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	$(CXX10) -O2 -Wall -c -fPIC -fmessage-length=0 -o '$@' '$<' $(INC10) $(INC) $(INC_APP)
	@echo 'Finished building: $<'
	@echo ' '

clean_bin:
	@rm -f bin/*

clean:
	rm -f bin/* $(OBJS9)  *.cap
