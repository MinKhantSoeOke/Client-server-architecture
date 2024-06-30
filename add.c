#include "common_03.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/dispatch.h>
#include <sys/neutrino.h>

int main(void) {
    int server_coid, ret;

    if ((server_coid = name_open(ATTACH_POINT, 0)) == -1) {
            perror("name_open failed - server not found!");
            return EXIT_FAILURE;
    }


        myMsg_t msg;

          msg.msg_type = MSG_TYPE_REGISTER;
          msg.operation = OP_ADD;

          ret = MsgSend(server_coid, &msg, sizeof(msg), &msg, sizeof(msg));
                        if( ret == -1 ){
                            perror("MsgSend Failed 1");
                        }

          while(1){

              if (msg.msg_type == MSG_TYPE_ORDER){
                  printf("Addition Client received order.\n");
                  msg.msg_type = MSG_TYPE_ANSWER;
                  msg.result = msg.arg1 + msg.arg2;
                  if (MsgSend(server_coid, &msg, sizeof(msg), &msg, sizeof(msg)) == -1) {
                      perror("MsgSend Failed 2");
                      break;
                  }
              }
          }

          return EXIT_SUCCESS;
}