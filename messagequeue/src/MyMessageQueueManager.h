/*
 * MyMessageQueueManager.h
 *
 *  Created on: 24/01/2019
 *      Author: jamil
 */

#ifndef MYMESSAGEQUEUEMANAGER_H_
#define MYMESSAGEQUEUEMANAGER_H_

#include <set>
#include <unordered_map>

#include "IMessageQueueManager.h"
#include "SubscriberData.h"

using SubscriptionMap = std::unordered_map<std::string, std::set<SubscriptionHandle>>;
using SubscriberDataMap = std::unordered_map<SubscriptionHandle, SubscriberData>;

class MyMessageQueueManager: public IMessageQueueManager {
private:

	SubscriptionMap subscriptionMap;	//hold list of active subscriber against each queue
	SubscriptionHandle subscriptionCounter;		//counter to hold unique id for each subscriber
	SubscriberDataMap subscriberDataMap;	//hold messages/data against each active subscriber


public:

	MyMessageQueueManager():subscriptionCounter(0) {}

	bool CreateMessageQueue(const std::string& in_queueName) override;
	bool PostMessage(const std::string& in_queueName, const std::string& in_message) override;
	bool CreateSubscription(const std::string& in_queueName, SubscriptionHandle& out_handle) override;
	bool GetNextMessage(SubscriptionHandle in_handle, std::string& out_message) override;

	~MyMessageQueueManager() = default;	//must override destructor to deallocate members

};

#endif /* MYMESSAGEQUEUEMANAGER_H_ */
