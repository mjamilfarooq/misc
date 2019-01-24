/*
 * MessageQueueManager.cpp
 *
 *  Created on: 24/01/2019
 *      Author: jamil
 */


#include "MyMessageQueueManager.h"

std::unique_ptr<class IMessageQueueManager> CreateMessageQueueManager()
{
	return std::unique_ptr<MyMessageQueueManager>(new MyMessageQueueManager());
}

