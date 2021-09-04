#include "rwlock.h"

void InitalizeReadWriteLock(struct read_write_lock * rw)
{
	rw->readers = 0;
  	pthread_mutex_init(&rw->readlock, NULL);						// Initialise value of semaphore readlock = 1	
  	pthread_mutex_init(&rw->writelock, NULL);						// Initialise value of semaphore writerlock = 1
}

void ReaderLock(struct read_write_lock * rw)
{
	pthread_mutex_lock(&rw->readlock);
	rw->readers++;
	if (rw->readers == 1) pthread_mutex_lock(&rw->writelock);   // First reader acquires writelock
	pthread_mutex_unlock(&rw->readlock);
}

void ReaderUnlock(struct read_write_lock * rw)
{
	pthread_mutex_lock(&rw->readlock);
	rw->readers--;
	if (rw->readers == 0) pthread_mutex_unlock(&rw->writelock); // Last reader releases writelock
	pthread_mutex_unlock(&rw->readlock);
}

void WriterLock(struct read_write_lock * rw)
{
  	pthread_mutex_lock(&rw->writelock);
}

void WriterUnlock(struct read_write_lock * rw)
{
	pthread_mutex_unlock(&rw->writelock);
}