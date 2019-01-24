/*
 * Subscriber.cpp
 *
 *  Created on: 24/01/2019
 *      Author: jamil
 */

#include "SubscriberData.h"

SubscriberData::SubscriberData() {
}


std::string SubscriberData::GetMessage()
{
	std::string message = "";

	if (messages.size()>0)			//and message list is not empty
	{
		message = messages.front();	//get message on the front
		messages.pop();				//delete the front message
	}


	return message;
}

void SubscriberData::PutMessage(const std::string & message)
{
	//insert the message for the queue name
	messages.push(message);
}

SubscriberData::~SubscriberData() {
}

