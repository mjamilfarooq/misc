#pragma once

#include <string>
#include <memory>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// IMessageQueueManager
//
// A message queue is a FIFO container for string messages. Messages are posted to the queue and then read in FIFO order by an arbitrary number of subscribers.
// Each subscriber can independently subscribe/get a message from the queue, hence each subscriber effectively maintains its own position in the
// primary message queue. The state for a single subscriber is referred to as a "subscription" and represented by a SubscriptionHandle in the IMessageQueueManager class.
//
// AN IMPORTANT FEATURE OF MESSAGE QUEUES is that they only store the subset of messages that are yet to be read by subscribers. Thus:
// - If a message is posted to a queue that has no subscribers, that message is discarded
// - Once all subscribers have read a particular message, it is discarded
//
// IMPLEMENTATION NOTES
// - You may use any methods or classes from the C++ Standard Library and STL
// - Add code comments to explain your code where applicable
// - *Single threaded only*, all methods will be called from a single thread, so multi threaded support is *not* required.
// - Over the lifetime of the class, the total number of subscriptions *and* messages processed will be smaller than the range of a uint64_t. So where
//   uint64_t is used for handles/counters you do not need to worry about counter wrapping/overflow
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Provide an implementation of this method in a .cpp file that returns your concrete IMessageQueueManager class
std::unique_ptr<class IMessageQueueManager> CreateMessageQueueManager();

// Message Queue subscriptions are uniquely identified by a SubscriptionHandle, which must be a unique uint64_t
typedef uint64_t SubscriptionHandle;

// Abstract base class for a message queue manager
class IMessageQueueManager
{
public:
	// Create a Message Queue with the given name.
	//
	// Returns false on failure, or if the given queue already exists
	virtual bool CreateMessageQueue(const std::string& in_queueName) = 0;

	// Post a message to a message queue.
	// - Posting an empty message is considered a failure case.
	// - Messages should be stored internally until all subscribers have received them via a GetNextMessage call.
	//
	// Returns false on failure, or if the given queue does not exist.
	virtual bool PostMessage(const std::string& in_queueName, const std::string& in_message) = 0;

	// Create a unique subscription to a given message queue.
	// - Returns a handle to the subscription in out_handle
	// - The subscription must only receive *new* messages created by PostMessage calls that occur *after* the CreateSubscription call
	//
	// Returns false on failure, or if the given queue does not exist
	virtual bool CreateSubscription(const std::string& in_queueName, SubscriptionHandle& out_handle) = 0;

	// Get the next message from the message queue for a given subscription
	// - Returns the message in out_message, and advances the subscription to the following message
	// - If there are no more messages for the subscription, returns true and out_message is set to an empty string
	// 
	// Returns false on failure 
	virtual bool GetNextMessage(SubscriptionHandle in_handle, std::string& out_message) = 0;

	virtual ~IMessageQueueManager() = default;
};
