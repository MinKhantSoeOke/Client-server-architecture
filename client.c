#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/dispatch.h>
#include "common_03.h"

int main(int argc, char *argv[]) {
    char operation, c;
    int num1, num2, argsNum;
    myMsg_t send_msg, reply_msg;

    int server_coid;

    if ((server_coid = name_open(ATTACH_POINT, 0)) == -1) {
            perror("name_open failed - server not found!");
            return EXIT_FAILURE;
    }
    printf("rtos-03-client started, server found\n");


    // here is how to implement (just) the *console part* of the "end-user-client"
    while(1){
        printf("Enter [number] [operator] [number]: "); fflush(stdout);
        argsNum = scanf("%d %c %d", &num1, &operation, &num2);
        if( argsNum != 3 ){
            printf("Wrong! Try again - "); fflush(stdout);
            while((c = getchar()) != '\n' && c != EOF) /* discard */ ;
            continue; // retry the scanf
        } else if( operation == 'q' ) // e.g. "0 q 0" will terminate the client
            break;
        if( strchr( "*+-/", operation)!=NULL ){
            printf(" >> Thanks, you entered: %d %c %d\n", num1, operation, num2);

            send_msg.arg1 = num1;
            send_msg.arg2 = num2;
            send_msg.operation = operation;
            send_msg.msg_type = MSG_TYPE_ORDER;

            if (MsgSend(server_coid, &send_msg, sizeof(send_msg), &reply_msg, sizeof(reply_msg)) == -1) {
                  perror("MsgSend Failed");
                  break;
            }

            printf("    MsgSend( ... &send_msg, ..., &reply_msg, ... );\n");
            printf("    ... result of operation is %d ...\n", reply_msg.result);
        } else {
            printf(" >> Operation %c is not + - * /. Try again - ", operation); flushall();
        }
    }
    printf("Console client exists correctly\n");
    return EXIT_SUCCESS;
}