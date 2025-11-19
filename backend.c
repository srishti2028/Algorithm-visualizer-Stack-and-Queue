#include <stdio.h>
#include <stdlib.h>
// STACK (ARRAY IMPLEMENTATION)
#define MAX_SIZE 100
int stackArr[MAX_SIZE];
int topArr = -1;

void stackArray_push(int value) {
    if (topArr == MAX_SIZE - 1) {
        printf("{\"type\":\"error\",\"msg\":\"Stack Overflow\"}\n");
        return;
    }
    stackArr[++topArr] = value;

    printf("{\"type\":\"stack_array_push\",\"value\":%d,\"top\":%d}\n",
        value, topArr);
}

void stackArray_pop() {
    if (topArr == -1) {
        printf("{\"type\":\"error\",\"msg\":\"Stack Underflow\"}\n");
        return;
    }

    int popped = stackArr[topArr--];
    printf("{\"type\":\"stack_array_pop\",\"value\":%d,\"top\":%d}\n",
        popped, topArr);
}

//STACK(LL REPRESENTATION)

typedef struct SNode {
    int data;
    struct SNode* next;
} SNode;

SNode* stackLL_top = NULL;

void stackLL_push(int value) {
    SNode* newNode = (SNode*)malloc(sizeof(SNode));
    newNode->data = value;
    newNode->next = stackLL_top;
    stackLL_top = newNode;

    printf("{\"type\":\"stack_ll_push\",\"value\":%d}\n", value);
}

void stackLL_pop() {
    if (!stackLL_top) {
        printf("{\"type\":\"error\",\"msg\":\"Stack Underflow\"}\n");
        return;
    }

    int val = stackLL_top->data;
    SNode* temp = stackLL_top;
    stackLL_top = stackLL_top->next;
    free(temp);

    printf("{\"type\":\"stack_ll_pop\",\"value\":%d}\n", val);
}

//QUEUE(ARRAY REPRESENTATION)

int queueArr[MAX_SIZE];
int frontArr = -1, rearArr = -1;

void queueArray_enqueue(int value) {
    if (rearArr == MAX_SIZE - 1) {
        printf("{\"type\":\"error\",\"msg\":\"Queue Overflow\"}\n");
        return;
    }

    if (frontArr == -1) frontArr = 0;

    queueArr[++rearArr] = value;

    printf(
        "{\"type\":\"queue_array_enqueue\",\"value\":%d,\"front\":%d,\"rear\":%d}\n",
        value, frontArr, rearArr
    );
}

void queueArray_dequeue() {
    if (frontArr == -1 || frontArr > rearArr) {
        printf("{\"type\":\"error\",\"msg\":\"Queue Underflow\"}\n");
        return;
    }

    int val = queueArr[frontArr++];
    printf(
        "{\"type\":\"queue_array_dequeue\",\"value\":%d,\"front\":%d,\"rear\":%d}\n",
        val, frontArr, rearArr
    );
}

//QUEUE(LL REPRESENTATION)

typedef struct QNode {
    int data;
    struct QNode* next;
} QNode;

QNode *frontLL = NULL, *rearLL = NULL;

void queueLL_enqueue(int value) {
    QNode* newNode = (QNode*)malloc(sizeof(QNode));
    newNode->data = value;
    newNode->next = NULL;

    if (!rearLL) {
        frontLL = rearLL = newNode;
    } else {
        rearLL->next = newNode;
        rearLL = newNode;
    }

    printf("{\"type\":\"queue_ll_enqueue\",\"value\":%d}\n", value);
}

void queueLL_dequeue() {
    if (!frontLL) {
        printf("{\"type\":\"error\",\"msg\":\"Queue Underflow\"}\n");
        return;
    }

    int val = frontLL->data;
    QNode* temp = frontLL;
    frontLL = frontLL->next;
    if (!frontLL) rearLL = NULL;
    free(temp);

    printf("{\"type\":\"queue_ll_dequeue\",\"value\":%d}\n", val);
}

//COMMAND HANDLER FOR FRONTEND

int main() {
    char cmd[50];
    int value;

    while (scanf("%s", cmd) != EOF) {

        //Stack Array 
        if (strcmp(cmd, "sa_push") == 0) {
            scanf("%d", &value);
            stackArray_push(value);
        }
        else if (strcmp(cmd, "sa_pop") == 0) {
            stackArray_pop();
        }

        // Stack Linked LisT
        else if (strcmp(cmd, "sll_push") == 0) {
            scanf("%d", &value);
            stackLL_push(value);
        }
        else if (strcmp(cmd, "sll_pop") == 0) {
            stackLL_pop();
        }

        // Queue Array 
        else if (strcmp(cmd, "qa_enqueue") == 0) {
            scanf("%d", &value);
            queueArray_enqueue(value);
        }
        else if (strcmp(cmd, "qa_dequeue") == 0) {
            queueArray_dequeue();
        }

        // Queue Linked List
        else if (strcmp(cmd, "qll_enqueue") == 0) {
            scanf("%d", &value);
            queueLL_enqueue(value);
        }
        else if (strcmp(cmd, "qll_dequeue") == 0) {
            queueLL_dequeue();
        }
    }
    return 0;
}
