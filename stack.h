typedef struct Stack Stack;

/*DECLARATION OF FUNCTIONS*/
struct Stack* createStack(unsigned capacity);
int isFull(struct Stack* stack);
int isEmpty(struct Stack* stack);
void push(struct Stack* stack, int item);
int pop(struct Stack* stack);
int getTop(struct Stack* stack);
int getSubTop(struct Stack* stack);