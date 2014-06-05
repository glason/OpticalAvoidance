################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/farneBack.cpp \
../src/main.cpp \
../src/motion2color.cpp \
../src/pyrlk.cpp \
../src/video.cpp 

OBJS += \
./src/farneBack.o \
./src/main.o \
./src/motion2color.o \
./src/pyrlk.o \
./src/video.o 

CPP_DEPS += \
./src/farneBack.d \
./src/main.d \
./src/motion2color.d \
./src/pyrlk.d \
./src/video.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


