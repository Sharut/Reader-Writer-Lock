#include "rwlock.h"

void InitalizeReadWriteLock(struct read_write_lock * rw)
{
	pthread_mutex_init(&rw->check_writer, NULL);
  	pthread_mutex_init(&rw->check_reader, NULL); 
	pthread_mutex_init(&rw->readlock, NULL);       // Initialise value of semaphore readlock = 1
	pthread_mutex_init(&rw->writelock, NULL);	   // Initialise value of semaphore writerlock = 1
	rw->readers = 0;
	rw->writers = 0;
}

void ReaderLock(struct read_write_lock * rw) 
{
	pthread_mutex_lock(&rw->check_reader);
	pthread_mutex_lock(&rw->readlock);
	rw->readers++;
	if (rw->readers == 1) pthread_mutex_lock(&rw->writelock); // First reader acquires writelock
	pthread_mutex_unlock(&rw->readlock);
	pthread_mutex_unlock(&rw->check_reader);
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
	pthread_mutex_lock(&rw->check_writer);
	rw->writers++;
	if (rw->writers == 1) pthread_mutex_lock(&rw->check_reader); // First reader acquires check_reader lock
    pthread_mutex_unlock(&rw->check_writer);
    pthread_mutex_lock(&rw->writelock);
}

void WriterUnlock(struct read_write_lock * rw)
{
	pthread_mutex_lock(&rw->check_writer);
	pthread_mutex_unlock(&rw->writelock);
	rw->writers--;
	if (rw->writers == 0) pthread_mutex_unlock(&rw->check_reader); // Last reader releases check_reader lock to enable writing
	pthread_mutex_unlock(&rw->check_writer);
}