#pragma once
#include "boost\thread\mutex.hpp"
#include "boost\thread\condition.hpp"

/*
Author: Benjamin Allardet-Servent.
Heavily inspired from http://askldjd.wordpress.com/2010/01/14/pipeline-concurrency-pattern/
This fine defines the PipelineManager Class.
This is not actually a pipeline.

There are two pointers we work with: A and B.
Access to those pointers is thread safe: a call to readRequest will place a lock on that pointer,
a call to readRelease will release the lock. Same goes for writeRelease and writeRequest.
*/

template <class workType>
class PipelineManager
{
private:
	
	//Our two pointers a and b
	workType *a, *b;

	//Those booleans indicate wether the pointers are available to be read or written on.
	bool aAvailable,bAvailable;

	//Which is the pointer to read from/to write on? true means a false means b
	bool currentWrite, currentRead; 
	boost::mutex mutex;
	boost::condition condAAvailable, condBAvailable;

	//Count the number of writes to avoid multiple reads in a row if one of the processes is slower than the other 
	//(make wait til we have a new worktype to read)
	int count;

public:

	PipelineManager(void);
	~PipelineManager(void);

	/**
	* Place a lock on the variable we want to write on, get the pointer. The function is thread safe (locks the PipelineManager class).
	* @return a pointer to the worktype
	*/
	workType* writeRequest(void);
	/**
	* Release the lock on the variable we want to write on. The function is thread safe (locks the PipelineManager class).
	*/
	void writeRelease();

	/**
	* Place a lock on the variable we want to read from, get the pointer. The function is thread safe (locks the PipelineManager class).
	* @return a pointer to the worktype
	*/
	workType* readRequest(void);
	/**
	* Release the lock on the variable we want to read from. The function is thread safe (locks the PipelineManager class).
	*/
	void readRelease(void);

};


template <class workType>
PipelineManager<workType>::PipelineManager(void)
{
	aAvailable=true;
	bAvailable=true;
	a=new workType();
	b=new workType();
	currentRead=false;
	currentWrite=true;
	count=0;
}

template <class workType>
PipelineManager<workType>::~PipelineManager(void)
{
}


template <class workType>
workType* PipelineManager<workType>::writeRequest(void)
{
	boost::mutex::scoped_lock guard(mutex);
	if(currentWrite)
	{  //currently writing on A
		if(!aAvailable)
			condAAvailable.wait(guard); //this will release the scoped_lock until the conditionAAvailable is notified
		aAvailable=false;
		return a;
	}
	else //currently writing on B
	{   
		if(!bAvailable)
			condBAvailable.wait(guard);
		bAvailable=false;
		//cout<< "Write taking b"<< endl;
		return b;
	}

}

template <class workType>
void PipelineManager<workType>::writeRelease()
{
	boost::mutex::scoped_lock guard(mutex);

	if (currentWrite)
	{
		//a=obj;
		aAvailable=true;
		currentWrite=false;
		//cout<< "write Releasing a"<< endl;
		count=1;
		condAAvailable.notify_one(); //notify that A is available
	}
	else
	{
		//b=obj;
		bAvailable=true;
		currentWrite=true;
		//cout<< "write Releasing b"<< endl;
		count=1;
		condBAvailable.notify_one();
	}

}

template <class workType>
workType* PipelineManager<workType>::readRequest(void)
{
	boost::mutex::scoped_lock guard(mutex);
	if(currentRead)
	{
		if(!aAvailable || count<=0)
			condAAvailable.wait(guard);
		count--;
		aAvailable=false;
		//cout<< "Read taking a "<< endl;
		return a;
	}
	else
	{

		if(!bAvailable || count<=0)
			condBAvailable.wait(guard);
		count--;
		bAvailable=false;
		//cout<< "Read taking b "<< endl;
		return b;
	}


}


template <class workType>
void PipelineManager<workType>::readRelease(void)
{
	boost::mutex::scoped_lock guard(mutex);
	if (currentRead)
	{
		aAvailable=true;
		currentRead=false;
		//cout<< "read Releasing a"<< endl;
		condAAvailable.notify_one();
	}
	else
	{
		bAvailable=true;
		currentRead=true;
		//cout<< "read Releasing b"<< endl;
		condBAvailable.notify_one();
	}

}