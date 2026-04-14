/*
 * thebar.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include "globals.h"
#include "customer.h"
#include "bartender.h"

void printBanner();
void init();
void cleanup();

int num_threads;

sem_t* bar_available;
sem_t* cust_ordered;
sem_t* cust_at_reg;
sem_t* drink_finished;
sem_t* cust_paid;
sem_t* cust_left;
sem_t* pay_received;
sem_t* order_received;

/**
 * Main function
 */
int main(int argc, char *argv[]) {

	if (argc != 2) {
		printf("usage: %s <num-customers>\n", argv[0]);
		return -1;
	}

	num_threads = atoi(argv[1]);

	printBanner();
	cleanup();
	init(); // initialize semaphores

	pthread_t tids[num_threads];
	int threadIDs[num_threads];
	for (int i = 0; i < num_threads; i++) {
		threadIDs[i] = i;
		pthread_create(&tids[i], NULL, customer, &threadIDs[i]);
	}

	// TODO - spawn bartender thread

	pthread_t bartenderTid;
	pthread_create(&bartenderTid, NULL, bartender, NULL);

	for (int i = 0; i < num_threads; i++) {
		pthread_join(tids[i], NULL);
	}
	pthread_join(bartenderTid, NULL);

	cleanup(); // cleanup and destroy semaphores
	return 0;
}

/**
 * Prints the activity banner.
 * Do not touch.
 */
void printBanner() {
	printf("Customer:\t\t\t\t\t\t\t\t\t\t| Employee:\n");
	printf("Traveling\tArrived\t\tOrdering\tBrowsing\tAt Register\tLeaving");
	printf("\t| Waiting\tMixing Drinks\tAt Register\tPayment Recv\n");
	printf("----------------------------------------------------------------------------------------+");
	printf("-----------------------------------------------------------\n");
}

/**
 * Create and initialize semaphores
 */
void init() {
	bar_available = sem_open("/bar_open_nova", O_CREAT, 0600, 0);
	cust_ordered = sem_open("/ordered_nova", O_CREAT, 0600, 0);
	cust_at_reg = sem_open("/at_reg_nova", O_CREAT, 0600, 0);
	drink_finished = sem_open("/finished_nova", O_CREAT, 0600, 0);
	cust_paid = sem_open("/paid_nova", O_CREAT, 0600, 0);
	cust_left = sem_open("/left_nova", O_CREAT, 0600, 0);
	pay_received = sem_open("/received_nova", O_CREAT, 0600, 0);
	order_received = sem_open("/received_order", O_CREAT, 0600, 0);
}

/**
 * Cleanup and destroy semaphores
 */
void cleanup() {
	sem_close(bar_available);
	sem_close(cust_ordered);
	sem_close(cust_at_reg);
	sem_close(drink_finished);
	sem_close(cust_paid);
	sem_close(cust_left);
	sem_close(pay_received);

	sem_unlink("/bar_open_nova");
	sem_unlink("/ordered_nova");
	sem_unlink("/at_reg_nova");
	sem_unlink("/finished_nova");
	sem_unlink("/paid_nova");
	sem_unlink("/left_nova");
	sem_unlink("/received_nova");
}