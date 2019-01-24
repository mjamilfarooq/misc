/*
 * AllTests.h
 *
 *  Created on: 24/01/2019
 *      Author: jamil
 */

#ifndef ALLTESTS_H_
#define ALLTESTS_H_

#include <cassert>

#include "IMessageQueueManager.h"


#define TEST_CREATEQUEUE(qname) \
			assert(manager->CreateMessageQueue(qname) == true)

#define TEST_CREATEQUEUE_FAILURE(qname) \
			assert(manager->CreateMessageQueue(qname) == false)

#define TEST_SUBSCRIPTION(qname, subscriber, id) \
	SubscriptionHandle subscriber; \
	assert(manager->CreateSubscription(qname, subscriber) == true); \
	assert(subscriber == id);

#define TEST_SUBSCRIPTION_FAILURE(qname, subscriber) \
	SubscriptionHandle subscriber; \
	assert(manager->CreateSubscription(qname, subscriber) == false);

#define TEST_POSTMESSAGE(qname, message) \
	assert(manager->PostMessage(qname, message) == true);

#define TEST_POSTMESSAGE_FAILURE(qname, message) \
	assert(manager->PostMessage(qname, message) == false);

#define TEST_GETMESSAGE(subscriber, comparewith) \
		{ \
	std::string message; \
	assert(manager->GetNextMessage(subscriber, message) == true); \
	assert(message == comparewith); \
		}

#endif /* ALLTESTS_H_ */
