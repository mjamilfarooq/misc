/*
 * Subscriber.h
 *
 *  Created on: 24/01/2019
 *      Author: jamil
 */

#ifndef SUBSCRIBERDATA_H_
#define SUBSCRIBERDATA_H_

#include <unordered_map>
#include <string>
#include <queue>

#include "Message.h"

using Messages = std::queue<MessageRef>;

class SubscriberData {
private:

	Messages messages;

public:
	SubscriberData();

	std::string GetMessage();
	void PutMessage(MessageRef& message);

	~SubscriberData();
};

#endif /* SUBSCRIBERDATA_H_ */
