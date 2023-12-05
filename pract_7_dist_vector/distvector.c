#include <stdio.h>
#include <string.h>

#define INFINITY 9999
#define MAX_ROUTERS 10

struct Router {
    char name;
    int routing_table[MAX_ROUTERS];
};

void updateRoutingTable(struct Router *router, char neighbor, int cost) {
    router->routing_table[neighbor - 'A'] = cost;
}

void printRoutingTable(struct Router *router) {
    printf("Routing Table for Router %c:\n", router->name);
    for (int i = 0; i < MAX_ROUTERS; i++) {
        printf("To %c: Cost %d\n", 'A' + i, router->routing_table[i]);
    }
    printf("\n");
}

void broadcastRoutingTable(struct Router *routers, int numRouters) {
    for (int i = 0; i < numRouters; i++) {
        for (int j = 0; j < numRouters; j++) {
            if (i != j) {
                char neighbor = 'A' + j;
                int *neighborTable = routers[j].routing_table;

                // Simulate updating the routing table of the neighbor
                updateRoutingTable(&routers[i], neighbor, neighborTable[i]);
            }
        }
    }
}

int main() {
    int numRouters = 3;
    struct Router routers[numRouters];

    // Initialize routers A, B, and C
    for (int i = 0; i < numRouters; i++) {
        routers[i].name = 'A' + i;
        for (int j = 0; j < numRouters; j++) {
            routers[i].routing_table[j] = INFINITY;
        }
    }

    // Set initial costs
    updateRoutingTable(&routers[0], 'B', 1);
    updateRoutingTable(&routers[0], 'C', 3);
    updateRoutingTable(&routers[1], 'A', 1);
    updateRoutingTable(&routers[1], 'C', 1);
    updateRoutingTable(&routers[2], 'A', 3);
    updateRoutingTable(&routers[2], 'B', 1);

    // Display initial routing tables
    for (int i = 0; i < numRouters; i++) {
        printRoutingTable(&routers[i]);
    }

    // Simulate broadcasting routing tables
    broadcastRoutingTable(routers, numRouters);

    // Display routing tables after broadcasting
    printf("After Broadcasting:\n");
    for (int i = 0; i < numRouters; i++) {
        printRoutingTable(&routers[i]);
    }

    return 0;
}
