#Auto generated, please dont edit. Editing might result in build failure or may render project unable to build.

SRC = src
SOURCES = $(shell find $(SRC) -name "*.cpp")
SOURCESC = $(shell find $(SRC) -name "*.c")
OPENSDK_ROOT = /opt/opensdk
PKG_ROOT = /usr/local/pkg_root/
#MD5VALUE = $(shell md5sum VaxAlprDetector/data_support/output/VAXDNN_ML2_EMBEDDED_CPU.bin | cut -d ' ' -f 1)


###################  DO NOT EDIT - BEGIN #########################
#version_begin
VERSION = 5.00
#version_end

#include_begin
INCL = $(OPENSDK_ROOT)/opensdk-$(VERSION)/common/inc/ "/opt/opensdk/opensdk-4.00/wnSeriesArmCompiler/arm-linux-gnueabi/sysroot/usr/include/" 
#include_end

#pp5_begin
CXXFLAGS5 = -O2 -g -Wall -fmessage-length=0
#pp5_end

#pp6_begin
CXXFLAGS6 = -O2 -g -Wall -fmessage-length=0
#pp6_end

# #pp7_begin
# CXXFLAGS7 = -O2 -g -Wall -fmessage-length=0
# #pp7_end

#pp8_begin
CXXFLAGS8 = -O2 -g -Wall -fmessage-length=0
#pp8_end

#pp9_begin
CXXFLAGS9 = -O2 -g -Wall -fmessage-length=0
#pp9_end

#lib5_begin
LIBS5 = -Llibs -lapphelper_wn5
#lib5_end

#lib6_begin
LIBS6 = -Llibs -lapphelper_s3l
#lib6_end

# #lib7_begin
# LIBS7 = -Llibs -lapphelper_cv2 -ldatatx
# #lib7_end

#lib8_begin
LIBS8 = -Llibs -lapphelper_wn7 -pthread -lcurl -lcrypto -lrt -lssl
#lib8_end

#lib9_begin
#LIBS9 = -Llibs -lapphelper_cv2x -pthread -lrt -lcurl -lssl -lcrypto
LIBS9 = -Llibs -lapphelper_cv2x -pthread -lrt -Wl,-Bstatic -lcurl -lssl -lcrypto -Wl,-Bdynamic
#lib9_end
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
TARGET5 = bin/Pseries_AI_pyramid_sample_wn5

PATH6 = $(OPENSDK_ROOT)/opensdk-$(VERSION)/linaro-armv7ahf-2015.11-gcc5.2/bin
CXX6 = $(PATH6)/arm-linux-gnueabihf-g++
TOOLS_PATH6 = $(PATH6)/../arm-linux-gnueabihf/libc
INC6 = -I$(TOOLS_PATH6)/usr/include/
OBJS6 = $(patsubst $(SRC)%.cpp, $(SRC)%_s3l.o, $(SOURCES))
APP_HELPER_PATH6 = $(TOOLS_PATH6)/usr/lib
TARGET6 = bin/Pseries_AI_pyramid_sample_s3l

# PATH7 = $(OPENSDK_ROOT)/opensdk-$(VERSION)/linaro-aarch64-2018.08-gcc8.2/bin
# CXX7 = $(PATH7)/aarch64-linux-gnu-g++
# TOOLS_PATH7 = $(PATH7)/../aarch64-linux-gnu/libc
# INC7 = -I$(TOOLS_PATH7)/usr/include/
# OBJS7 = $(patsubst $(SRC)%.cpp, $(SRC)%_cv2.o, $(SOURCES))
# APP_HELPER_PATH7 = $(TOOLS_PATH7)/usr/lib
# TARGET7 = bin/Pseries_AI_pyramid_sample_cv2

PATH8 = $(OPENSDK_ROOT)/opensdk-$(VERSION)/armv7-wn7-linux-gnueabihf/bin
CXX8 = $(PATH8)/armv7-wn7-linux-gnueabihf-g++
TOOLS_PATH8 = $(PATH8)/../armv7-wn7-linux-gnueabihf/sysroot
INC8 = -I$(TOOLS_PATH8)/usr/include/
OBJS8 = $(patsubst $(SRC)%.cpp, $(SRC)%_wn7.o, $(SOURCES))
OBJSC9 = $(patsubst $(SRC)%.c, $(SRC)%_wn7.o, $(SOURCESC))
APP_HELPER_PATH8 = $(TOOLS_PATH8)/usr/lib
LD_FLAGS9 = -Wl,-E,-rpath-link=$(APP_HELPER_PATH9)
TARGET8 = bin/VaxALPR_wn7
CAP8 = wn7/VaxALPR.cap
PKG_PATH8 = $(PKG_ROOT)wn7/
INC8PKG = -I$(PKG_PATH8)include
# INC8VAXEMBEDDED = -I$(PKG_PATH9)include/vaxembedded
LIB8PKG = -L$(PKG_PATH8)lib

PATH9 = $(OPENSDK_ROOT)/opensdk-$(VERSION)/linaro-aarch64-2020.09-gcc10.2-linux5.4/bin
CXX9 = $(PATH9)/aarch64-linux-gnu-g++
C9 = $(PATH9)/aarch64-linux-gnu-gcc
TOOLS_PATH9 = $(PATH9)/../aarch64-linux-gnu/libc
INC9 = -I$(TOOLS_PATH9)/usr/include/ -I/usr/local/openssl/include
OBJS9 = $(patsubst $(SRC)%.cpp, $(SRC)%_cv2x.o, $(SOURCES))
OBJSC9 = $(patsubst $(SRC)%.c, $(SRC)%_cv2x.o, $(SOURCESC))
APP_HELPER_PATH9 = $(TOOLS_PATH9)/lib_cv2x
LD_FLAGS9 = -Wl,-E,-rpath-link=$(APP_HELPER_PATH9)
TARGET9 = bin/VaxALPR_cv2x
CAP9 = cv2x/VaxALPR.cap
PKG_PATH9 = $(PKG_ROOT)cv2x/
INC9PKG = -I$(PKG_PATH9)include
# INC9VAXEMBEDDED = -I$(PKG_PATH9)include/vaxembedded
LIB9PKG = -L$(PKG_PATH9)lib

# .PHONY: wn5 wn7 cv2x directories ln5 ln7 ln8
.PHONY: wn5 wn7 cv2x directories ln5 ln8 ln9
all:
	@echo "armv7-wn7-linux-gnueabihf armv7-cortex_A7-linux-gnueabihf or aarch64-linux-gnu"
armv7-wn7-linux-gnueabihf: directories clean_bin ln8 $(CAP8)
aarch64-linux-gnu: directories clean_bin ln9 $(CAP9)

directories:
	mkdir -p bin wn5 wn7 cv2x
	
$(TARGET5): clean_bin $(OBJS5)
	$(CXX5) $(OPENSDK_ROOT)/opensdk-$(VERSION)/templates/libs/main_wn5.o $(OBJS5) -o $@ -L$(APP_HELPER_PATH5) $(LIBS5)
#strip5_begin
	$(PATH5)/armv7-cortex_A7-linux-gnueabihf-strip --strip-all $@
	#strip5_end

$(CAP8): $(TARGET8)
	cp IPCameraManifest-armv7-wn7-linux-gnueabihf.xml IPCameraManifest.xml
	/opt/opensdk/opensdk-$(VERSION)/common/bin/opensdk_packager

$(CAP9): $(TARGET9)
	cp IPCameraManifest-aarch64-linux-gnu.xml IPCameraManifest.xml
	/opt/opensdk/opensdk-$(VERSION)/common/bin/opensdk_packager

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

# $(TARGET7): clean_bin $(OBJS7)
# 	$(CXX7) $(OPENSDK_ROOT)/opensdk-$(VERSION)/templates/libs/main_cv2.o $(OBJS7) -o $@ -L$(APP_HELPER_PATH7) $(LIBS7)
# #strip7_begin
# 	$(PATH7)/aarch64-linux-gnu-strip --strip-all $@
# 	#strip7_end


$(TARGET8): clean_bin $(OBJS8) $(OBJSC8)
	@echo 'Bilding Target8'
	$(CXX8) $(OPENSDK_ROOT)/opensdk-$(VERSION)/templates/libs/main_wn7.o $(OBJS8) $(OBJSC9) -o $@ -L$(APP_HELPER_PATH8) $(LIBS8) $(LD_FLAGS9) $(LIB9PKG)
#strip8_begin
	$(PATH8)/armv7-wn7-linux-gnueabihf-strip --strip-all $@
	#strip8_end
#strip8_end

src/%_wn7.o: src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	$(CXX8) $(CXXFLAGS8) -c -o '$@' '$<' $(INC8) $(INC) $(INC_APP)
	@echo 'Finished building: $<'
	@echo ' '

$(TARGET9): clean_bin $(OBJS9) $(OBJSC9)	
	@echo 'Bilding Target9'
	$(CXX9) $(OPENSDK_ROOT)/opensdk-$(VERSION)/templates/libs/main_cv2x.o $(OBJS9) $(OBJSC9) -o $@ -L$(APP_HELPER_PATH9) $(LIBS9) $(LD_FLAGS9) $(LIB9PKG)
#strip9_begin
	$(PATH9)/aarch64-linux-gnu-strip --strip-all $@
#strip9_end

src/%_cv2x.o: src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	$(CXX9) $(CXXFLAGS9) -c -o '$@' '$<' $(INC9) $(INC) $(INC_APP)
	@echo 'Finished building: $<'
	@echo ' '

src/%_cv2x.o: src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	$(C9) $(CFLAGS9) -c -o '$@' '$<' $(INC9) $(INC) $(INC_APP)
	@echo 'Finished building: $<'
	@echo ' '


clean_bin:
	@rm -f bin/*

clean: clean_bin
	# rm -f $(OBJS8) $(OBJSC8) $(OBJS9) $(OBJSC9) wn5/* wn7/* cv2x/* libs/*.so*
	rm -f $(OBJS8) $(OBJSC8) $(OBJS9) $(OBJSC9) wn5/* wn7/* cv2x/*
