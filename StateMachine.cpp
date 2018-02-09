#include "StateMachine.h"
#include "IStateController.h"

int StateMachine<IStateController>::currentState;
std::vector<IStateController*> StateMachine<IStateController>::stack;

