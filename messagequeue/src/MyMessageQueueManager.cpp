/*
 * MyMessageQueueManager.cpp
 *
 *  Created on: 24/01/2019
 *      Author: jamil
 */

#include "MyMessageQueueManager.h"
#include <iostream>

#define log(l,x) std::cout<<l<<x<<std::endl

bool MyMessageQueueManager::CreateMessageQueue(const std::string & in_queueName)
{
	auto retval = true;
	try
	{
		if (in_queueName == "")
			throw std::logic_error("queue must have a name");

		//if queue doesn't exist register it
		auto status = subscriptionMap.insert({in_queueName, SubscriptionSet()});

		if (!status.second)
		{
			throw std::logic_error("given queue already exist");
		}


	}
	catch(std::exception& ex)
	{
		log("MyMessageQueueManager::CreateMessageQueue: ", ex.what());
		retval = false;
	}
	//otherwise send false;
	return retval;
}

bool MyMessageQueueManager::PostMessage(const std::string& in_queueName, const std::string& in_message)
{

	auto retval = true;
	try
	{
		if (in_message=="") throw std::logic_error("empty message not acceptable");

		auto queue = subscriptionMap.find(in_queueName);
		if (queue==subscriptionMap.end())
			throw std::logic_error("queue doesn't exist: "+ in_queueName); //queue doesn't exist

		//if exist get subscription list
		auto& subscription_list = queue->second;

		//and for each subscriber
		auto message = std::make_shared<Message>(in_message);
		for (auto subscriber: subscription_list)
		{
			auto& subscriber_data = subscriberDataMap[subscriber]; //get data against each subscriber
			subscriber_data.PutMessage(message);	//push the message in messages list for the subscriber
		}
	}
	catch (std::exception& ex)
	{
		log("MyMessageQueueManager::PostMessage: ", ex.what());
		retval = false;
	}

	return retval;
}

bool MyMessageQueueManager::CreateSubscription(const std::string & in_queueName, SubscriptionHandle & out_handle)
{
	auto retval = true;
	try
	{
		auto queue = subscriptionMap.find(in_queueName);
		if (queue==subscriptionMap.end())
			throw std::logic_error("queue doesn't exist: "+ in_queueName); //queue doesn't exist

		auto& subscription_list = queue->second;

		out_handle = subscriptionCounter++;	//assign new id
		subscription_list.emplace(out_handle);
	}
	catch (std::exception& ex)
	{
		log("MyMessageQueueManager::CreateSubscription: ", ex.what());
		retval = false;
	}

	return retval;
}

bool MyMessageQueueManager::GetNextMessage(SubscriptionHandle in_handle, std::string& out_message)
{

	auto retval = true;
	try
	{
		auto& subscriber_data = subscriberDataMap[in_handle];
		out_message = subscriber_data.GetMessage();
	}
	catch (std::exception& ex)
	{
		log("MyMessageQueueManager::GetNextMessage: ", ex.what());
		retval = false;
	}

	return retval;
}

