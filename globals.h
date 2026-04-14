/*
 * globals.h
 */

#ifndef GLOBALS_H_
#define GLOBALS_H_

// number of customer threads
extern int num_threads;

extern sem_t* bar_available;
extern sem_t* cust_ordered;
extern sem_t* cust_at_reg;
extern sem_t* drink_finished;
extern sem_t* cust_paid;
extern sem_t* cust_left;
extern sem_t* pay_received;
extern sem_t* order_received;

#endif /* GLOBALS_H_ */