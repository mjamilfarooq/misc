################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/MessageQueueManager.cpp \
../src/MyMessageQueueManager.cpp \
../src/SubscriberData.cpp \
../src/messagequeue.cpp 

OBJS += \
./src/MessageQueueManager.o \
./src/MyMessageQueueManager.o \
./src/SubscriberData.o \
./src/messagequeue.o 

CPP_DEPS += \
./src/MessageQueueManager.d \
./src/MyMessageQueueManager.d \
./src/SubscriberData.d \
./src/messagequeue.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


