//============================================================================
// Name        : messagequeue.cpp
// Author      : Muhammad Jamil Farooq
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include <iostream>
#include <cassert>

#include "AllTests.h"

using namespace std;


int main()
{
	auto manager = CreateMessageQueueManager();

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Add unit test code here to demonstrate that your manager works correctly

	std::cout<<"Starting Tests"<<std::endl;

	//create message queue
	TEST_CREATEQUEUE("queue1");
	TEST_CREATEQUEUE("queue2");

	//trying to register duplicate queue
	TEST_CREATEQUEUE_FAILURE("queue1");

	//queue name must not be empty
	TEST_CREATEQUEUE_FAILURE("");

	//registering subscriber
	TEST_SUBSCRIPTION("queue1", subscriber1, 0);
	TEST_SUBSCRIPTION("queue2", subscriber2, 1);


	//create subscription to non-existent queue
	TEST_SUBSCRIPTION_FAILURE("queue3", subscriber4);

	//posting messages on queue
	TEST_POSTMESSAGE("queue1", "message1");
	TEST_POSTMESSAGE("queue1", "message2");
	TEST_POSTMESSAGE("queue2", "message1");
	TEST_POSTMESSAGE("queue2", "message2");

	//if queue doesn't exist
	TEST_POSTMESSAGE_FAILURE("queue3", "This is message one to q3 non existent");
	TEST_POSTMESSAGE_FAILURE("queue3", "This is message two to q3 non existent");

	//posting empty message
	TEST_POSTMESSAGE_FAILURE("queue1", "");
	TEST_POSTMESSAGE_FAILURE("queue2", "");


	//normal case where subscriber were already subscribed before message was posted
	std::string message;

	TEST_GETMESSAGE(subscriber1, "message1");
	TEST_GETMESSAGE(subscriber1, "message2");
	TEST_GETMESSAGE(subscriber2, "message1");
	TEST_GETMESSAGE(subscriber2, "message2");


	//subscribing to queue after messages has been posted
	TEST_SUBSCRIPTION("queue1", subscriber3, 2);
	TEST_GETMESSAGE(subscriber3, "");



	//Now posting new message to queue1 subscriber 1 and 3 must get these messages
	TEST_POSTMESSAGE("queue1", "repeated message1");
	TEST_POSTMESSAGE("queue1", "repeated message2");
	TEST_POSTMESSAGE("queue1", "repeated message3");

	TEST_GETMESSAGE(subscriber1, "repeated message1");
	TEST_GETMESSAGE(subscriber1, "repeated message2");
	TEST_GETMESSAGE(subscriber1, "repeated message3");
	TEST_GETMESSAGE(subscriber1, "");

	//same for subscriber3 should also consume its message queue
	TEST_GETMESSAGE(subscriber3, "repeated message1");
	TEST_GETMESSAGE(subscriber3, "repeated message2");
	TEST_GETMESSAGE(subscriber3, "repeated message3");
	TEST_GETMESSAGE(subscriber3, "");

	//queue2 shouldn't have anything
	TEST_GETMESSAGE(subscriber2, "");


	//Bulk Messaging
	auto bulk = 10000;
	for (auto i =0; i<bulk; i++)
	{
		TEST_POSTMESSAGE("queue1", "message " + to_string(i));
	}

	for (auto i =0; i<bulk; i++)
	{
		TEST_GETMESSAGE(subscriber1, "message "+ to_string(i));
		TEST_GETMESSAGE(subscriber3, "message "+ to_string(i));
	}

	cout<<"Test Cases End"<<endl;
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	return 0;
}


