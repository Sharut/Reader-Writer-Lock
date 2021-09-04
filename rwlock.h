#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

struct read_write_lock{
	pthread_mutex_t readlock;
	pthread_mutex_t writelock;
	pthread_mutex_t check_writer;
	pthread_mutex_t check_reader;
	int readers;
	int writers;
};

void InitalizeReadWriteLock(struct read_write_lock * rw);
void ReaderLock(struct read_write_lock * rw);
void ReaderUnlock(struct read_write_lock * rw);
void WriterLock(struct read_write_lock * rw);
void WriterUnlock(struct read_write_lock * rw);
