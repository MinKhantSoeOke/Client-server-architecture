#ifndef COMMON_03_H_
#define COMMON_03_H_

#define ATTACH_POINT "calculator_service"

#define MSG_TYPE_ORDER 'o'
#define MSG_TYPE_REGISTER 'r'
#define MSG_TYPE_ANSWER 'a'

#define OP_ADD '+'
#define OP_SUB '-'
#define OP_MUL '*'
#define OP_DIV '/'

typedef struct {
    char msg_type; // 'r' for request, 'e' for register
    char operation; // '+', '-', '*', '/'
    int arg1, arg2;
    int result;
    int rcvid; // Receiver ID for the reply
} myMsg_t;

// Structure for registration messages
typedef struct {
    char msg_type;
    char operation; // '+', '-', '*', '/'
    int client_rcvid; // Client identifier
} registration;

#endif /* COMMON_03_H_ */