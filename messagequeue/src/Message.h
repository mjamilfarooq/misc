/*
 * Message.h
 *
 *  Created on: 25/03/2019
 *      Author: jamil
 */

#ifndef MESSAGE_H_
#define MESSAGE_H_

#include <string>
#include <memory>

class Message
{
public:
	Message(const std::string& message):message(std::move(message)){
	}

	std::string& getMessage()
	{
		return message;
	}

private:
	std::string message;

};

using MessageRef = std::shared_ptr<Message>;

#endif /* MESSAGE_H_ */
