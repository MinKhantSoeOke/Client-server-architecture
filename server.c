#include "common_03.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/dispatch.h>
#include <sys/neutrino.h>
#include <sys/netmgr.h>
#include <errno.h>

registration registrations[100];

void register_client(myMsg_t msg, int rcvid);


int main() {
    int rcvid;
    name_attach_t *attach;
    int find_status = 0;
    int i;

    /* Create a local name (/dev/name/local/...) */
    if ((attach = name_attach(NULL, ATTACH_POINT, 0)) == NULL) {
        perror("Failed to attach name");
        return EXIT_FAILURE;
    }

    printf("Main server is running.\n");



    /* Do your MsgReceive's here now with the chid */
    while (1) {
        myMsg_t msg;
        rcvid = MsgReceive(attach->chid, &msg, sizeof(msg), NULL);

        if (rcvid == -1) {/* Error condition, exit */
            perror("MsgReceive failed");
            break;
        }else if (rcvid == 0){/* Pulse received */
            printf("Received a pulse\n");
            continue;
        }

        /* A message received, handle */


        if (msg.msg_type == MSG_TYPE_ORDER) {
             printf("Main server received order: %d %c %d\n", msg.arg1, msg.operation, msg.arg2);

             for(i = 0; i < 100; i++) {
                     if (registrations[i].operation == msg.operation) {
                         msg.rcvid = rcvid;
                         MsgReply(registrations[i].client_rcvid, 0, &msg, sizeof(msg));
                         find_status = 1;
                     }
                 }
             if (find_status == 0){
                // Operation not supported, send error response
                 myMsg_t resp;
                resp.msg_type = 'e';
                MsgReply(rcvid, EOK, &resp, sizeof(resp));
             }
             find_status = 0;
         } else if (msg.msg_type == MSG_TYPE_REGISTER) {
             register_client(msg, rcvid);
             printf("Main server received registration: %c\n", msg.operation);
         } else if (msg.msg_type == MSG_TYPE_ANSWER) {
             printf("Main server received answer: %d \n", msg.result);
             MsgReply(msg.rcvid, 0, &msg, sizeof(msg));
         }
    }

    name_detach(attach, 0);
    return EXIT_SUCCESS;
}

void register_client(myMsg_t msg, int rcvid) {
    int i;
    for (i = 0; i < 100; i++) {
        if (registrations[i].client_rcvid == 0) { // Assuming 0 is unused
            registrations[i].operation = msg.operation;
            registrations[i].client_rcvid = rcvid;
            break;
        }
    }
}