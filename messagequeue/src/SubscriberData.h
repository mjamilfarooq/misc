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

using Messages = std::queue<std::string>;

class SubscriberData {
private:

	Messages messages;

public:
	SubscriberData();

	std::string GetMessage();
	void PutMessage(const std::string & message);

	~SubscriberData();
};

#endif /* SUBSCRIBERDATA_H_ */
