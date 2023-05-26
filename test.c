#include <stdio.h>
#include <signal.h>

void signalHandler(int signum) {
    printf("Received signal %d\n", signum);
}

int main() {
    // Register signal handler for SIGINT (Ctrl+C)
    signal(SIGINT, signalHandler);

    // Infinite loop to keep the program running
    while (1) {}

    return 0;
}