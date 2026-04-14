/*
 * bartender.c (her name is rebecca)
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <time.h>
#include "globals.h"
#include "bartender.h"

/**
 * Code for bartender thread.
 * Do not touch.
 */
void *bartender(void *args) {
	for (int i = 0; i < num_threads; i++) {
		waitForCustomer();
		makeDrink();
		receivePayment();
	}
	return NULL;
}

/**
 * Waits in a closet until a customer enters.
 * TODO - SYNCHRONIZE ME
 */
void waitForCustomer() {
	printf("\t\t\t\t\t\t\t\t\t\t\t| Bartender\n");
	sem_post(bar_available);
}

/**
 * When a customer places an order it takes the Bartender
 * a random amount of time between 5 ms and 1000 ms to make the drink.
 * TODO - SYNCHRONIZE ME
 */
void makeDrink() {
	sem_wait(cust_ordered);
	sem_post(order_received);
	printf("\t\t\t\t\t\t\t\t\t\t\t| \t\tBartender\n");
	srand(time(NULL));
	int r = rand();
	int time = r % (1000 - 5) + 6;
	usleep(time * 1000);
	sem_post(drink_finished);
}

/**
 * Gets payment from the correct customer
 * TODO - SYNCHRONIZE ME
 */
void receivePayment() {
	// at the register waiting for customer to pay
	printf("\t\t\t\t\t\t\t\t\t\t\t| \t\t\t\tBartender\n");

	sem_wait(cust_at_reg);
	sem_wait(cust_paid);

	// got paid by the customer!
	printf("\t\t\t\t\t\t\t\t\t\t\t| \t\t\t\t\t\tBartender\n");
	sem_post(pay_received);
	sem_wait(cust_left);
}