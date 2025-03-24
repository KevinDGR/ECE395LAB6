void setupUART();
unsigned char UART_read();
void UART_write(unsigned char a);
#define MAX_BUFFER_SIZE 100
/*
Modified by Bryan Galecio
Change - Made index_num1/index_num2 local so it resets to 0 everytime the program does
Removed all indexx and ensured correct utilization of index_num1 and index_num2
*/

int memory =0;

void uart_write_string(const char *str){
    while(*str){
        UART_write(*str);
        str++;
    }
}

int getNum(char num[], int size) {
    int result = 0;
    for (int i = 0; i < size; i++) {
        if (num[i] >= 0x30 && num[i] <= 0x39) {
            result = (result * 10) + (num[i] - 0x30);
        } else {
            return result; // Stop parsing on non-digit
        }
    }
    return result;
}

void getChar(int result){
    char answer[MAX_BUFFER_SIZE];
    int temp1 = result;
    int temp2 = result;
    int size = 0;

    while(1){
        if ((temp2 / 10) != 0){
            temp2 = temp2 / 10;
            size ++;
        }
        else{
            break;
        }
    }

    for (int i = size; i >= 0 ; i--){
        answer[i] = (temp1 % 10) + 0x30;
        temp1 = temp1 /10;
    }
    answer[size + 1] = '\0';

    uart_write_string(answer);
}

/*
Modified by Bryan Galecio
Change - Implemented backspace function for reducing repetitive code
- Added factorial function
- Added isPrime function
Suggestion - create pointer functions for calculator operations
*/
void backspace(char* buffer, int* index){
    if (*index > 0) { // Ensure index doesn't go below 0
        (*index)--; // Move back in buffer
        buffer[*index] = '\0'; // Clear the last character from the buffer
        UART_write('\b'); // Move the cursor back
        UART_write(' '); // Overwrite the character with a space
        UART_write('\b'); // Move the cursor back again
    }
}

int factorial(int z){
    if(z == 0 || z == 1){
        return 1;
    }
    return z * factorial(z-1);
}

void isPrime(int z){
    if (z == 0 || z == 1){
        uart_write_string("\n\rNot prime");
        return;
    }
    else if (z == 2 || z == 3){
        uart_write_string("\n\rPrime");
        return;
    }
    if (z % 2 == 0){
        uart_write_string("\n\rNot prime");
        return;
    }
    for (int factor = 3; factor < z; factor += 2){
        if(z % factor == 0){
            uart_write_string("\n\rNot prime");
            return;
        }
    }
    uart_write_string("\n\rPrime");
}

int main(void){
    setupUART();
    //uart_write_string("Solve: ");
    while(1){
        char num1[MAX_BUFFER_SIZE];
        char num2[MAX_BUFFER_SIZE];
        unsigned char ch;
        int x;
        int y;
        int z;
        int index_num1 = 0;
        int index_num2 = 0;
        uart_write_string("\n\r");
        uart_write_string("Solve: ");
        while (index_num1 < MAX_BUFFER_SIZE - 1){
            /*
            Modified by Bryan Galecio
            Change - Read the first input first
            */
            ch = UART_read();
            UART_write(ch);
            num1[index_num1++] = ch;
            num1[index_num1] = '\0';
            if (ch == '+'){
                UART_write('+');
                while (index_num2 < MAX_BUFFER_SIZE - 1){
                    ch = UART_read();
                    if (ch == '\n' || ch == '\r'){
                        break; // End of input
                    }
                    else if (ch == 0x08){ // Backspace detected
                        backspace(num2, &index_num2);
                    }
                    else{
                        UART_write(ch); // Echo input to terminal
                        num2[index_num2++] = ch; // Add character to num2 buffer
                        num2[index_num2] = '\0'; // Null-terminate num2
                    }
                }
                x = getNum(num1, index_num1);
                y = getNum(num2, index_num2);
                z = x + y;
                uart_write_string("\n\r");
                getChar(z);
                break;
            }
            else if (ch == '-'){
                UART_write('-');
                while (index_num2 < MAX_BUFFER_SIZE - 1){
                    ch = UART_read();
                    if (ch == '\n' || ch == '\r'){
                        break;
                    }
                    UART_write(ch);
                    num2[index_num2++] = ch;
                    num2[index_num2] = '\0';
                }
                x = getNum(num1, index_num1);
                y = getNum(num2, index_num2);
                z = x - y;
                uart_write_string("\n\r");
                getChar(z);
                break;
            }
            else if (ch == '/'){
                UART_write('/');
                while (index_num2 < MAX_BUFFER_SIZE - 1){
                    ch = UART_read();
                    UART_write(ch);
                    if (ch == '\n' || ch == '\r'){
                        break;
                    }
                    num2[index_num2++] = ch;
                    num2[index_num2] = '\0';
                }
                x = getNum(num1, index_num1);
                y = getNum(num2, index_num2);
                z = x / y;
                uart_write_string("\n\r");
                getChar(z);
                break;
            }
            else if (ch == '*'){
                UART_write('*');
                while (index_num2 < MAX_BUFFER_SIZE - 1){
                    ch = UART_read();
                    if (ch == '\n' || ch == '\r'){
                        break;
                    }
                    UART_write(ch);
                    num2[index_num2++] = ch;
                    num2[index_num2] = '\0';
                }
                x = getNum(num1, index_num1);
                y = getNum(num2, index_num2);
                z = x * y;
                uart_write_string("\n\r");
                getChar(z);
                break;
            }
            else if (ch == '%'){
                UART_write('%');
                while (index_num2 < MAX_BUFFER_SIZE - 1){
                    ch = UART_read();
                    if (ch == '\n' || ch == '\r'){
                        break;
                    }
                    UART_write(ch);
                    num2[index_num2++] = ch;
                    num2[index_num2] = '\0';
                }
                x = getNum(num1, index_num1);
                y = getNum(num2, index_num2);
                z = x % y;
                uart_write_string("\n\r");
                getChar(z);
                break;
            }

            else if (ch == '!'){
                UART_write('!');
                x = getNum(num1, index_num1);
                z = x;
                z = factorial(z);
                uart_write_string("\n\r");
                getChar(z);
                break;
            }
            else if(ch == '?'){
                UART_write('?');
                x = getNum(num1, index_num1);
                z = x;
                isPrime(z);
                break;
            }
            else if (ch == 'M') {
                ch = UART_read(); 
                
                if (ch == '+') {
                    memory += z; 
                    uart_write_string(" [M+ Done]");
                } else if (ch == '-') {
                    memory -= z; 
                    uart_write_string(" [M- Done]");
                } else if (ch == 'C') {
                    memory = 0; 
                    uart_write_string(" [MC: Memory Cleared]");
                } else if (ch == 'R') {
                    x = memory; 
                    uart_write_string(" [MR: Memory Recalled: ");
                    getChar(memory); 
                    uart_write_string("]");
                    ch = UART_read();
            if(ch == '+'){
                UART_write('+');
                index_num2 = 0;
                while (index_num2 < MAX_BUFFER_SIZE - 1){
                    ch = UART_read();
                    UART_write(ch);
                    index_num2 ++;
                    num2[index_num2++] = ch;
                    num2[index_num2] = '\0';
                    if (ch == '\n' || ch == '\r'){
                        break;
                    }else if (ch == 0x08) { // Backspace detected
                        if (index_num2 > 0) { // Ensure index_num2 doesn't go below 0
                            index_num2--; // Move back in buffer
                            num2[index_num2] = '\0'; // Clear the last character from the buffer
                            UART_write('\b'); // Move the cursor back
                            UART_write(' '); // Overwrite the character with a space
                            UART_write('\b'); // Move the cursor back again
                        }
                    }
                    
                }
                //x = getNum(num1, index_num1);
                y = getNum(num2, index_num2);
                z = x + y;
                uart_write_string("\n\r");
                (getChar(z));
                break;
            }
            else if(ch == '-'){
                UART_write('-');
                int index_num2 = 0;
                while (index_num2 < MAX_BUFFER_SIZE - 1){
                    ch = UART_read();
                    UART_write(ch);
                    index_num2 ++;
                    num2[index_num2++] = ch;
                    num2[index_num2] = '\0';
                    if (ch == '\n' || ch == '\r'){
                        break;
                    }
                }
                
                y = getNum(num2, index_num2);
                z = x - y;
                uart_write_string("\n\r");
                (getChar(z));
                break;
            }
            
            else if(ch == '/'){
                UART_write('/');
                int index_num2 = 0;
                while (index_num2 < MAX_BUFFER_SIZE - 1){
                    ch = UART_read();
                    UART_write(ch);
                    index_num2 ++;
                    num2[index_num2++] = ch;
                    num2[index_num2] = '\0';
                    if (ch == '\n' || ch == '\r'){
                        break;
                    }
                }
                
                y = getNum(num2, index_num2);
                z = x / y;
                uart_write_string("\n\r");
                (getChar(z));
                break;
            }

            else if(ch == '*'){
                UART_write('*');
                int index_num2 = 0;
                while (index_num2 < MAX_BUFFER_SIZE - 1){
                    ch = UART_read();
                    UART_write(ch);
                    index_num2 ++;
                    num2[index_num2++] = ch;
                    num2[index_num2] = '\0';
                    if (ch == '\n' || ch == '\r'){
                        break;
                    }
                }
                
                y = getNum(num2, index_num2);
                z = x * y;
                uart_write_string("\n\r");
                (getChar(z));
                break;
            }

            else if(ch == '%'){
                UART_write('%');
                int index_num2 = 0;
                while (index_num2 < MAX_BUFFER_SIZE - 1){
                    ch = UART_read();
                    UART_write(ch);
                    index_num2 ++;
                    num2[index_num2++] = ch;
                    num2[index_num2] = '\0';
                    if (ch == '\n' || ch == '\r'){
                        break;
                    } 
                }
                
                y = getNum(num2, index_num2);
                z = x % y;
                uart_write_string("\n\r");
                (getChar(z));
                break;
            }

            else if(ch == '!'){
                UART_write('!');
                
                
                //y = getNum(num2, index_num2);
                z = x;
                for(int i = x -1; i>0; i--){
                    z = z*i; 
                } 
                uart_write_string("\n\r");
                (getChar(z));
                break;
            }

            else if(ch == '?'){
                UART_write('?');
                
                
                //y = getNum(num2, index_num2);
                z = x;
                int count =0;
                for (int i =1; i<=z; i++){
                        if (z%i == 0){
                            count++;
                        }
                }
                
                if (count >2){
                    uart_write_string("\nNot prime");
                }
                else{
                    uart_write_string("\nIs prime");
                }
            
                uart_write_string("\n\r");
                //(getChar(z));
                break;
            }

                }
            }
            else if (ch == 0x08) { // Backspace detected
                if (index_num2 > 0) { // Ensure index_num2 doesn't go below 0
                    index_num2--; // Move back in buffer
                    index_num1--; // Decrement number of valid digits in num1
                    num1[index_num2] = '\0'; // Clear the last character from the buffer
                    UART_write('\b'); // Move the cursor back
                    UART_write(' '); // Overwrite the character with a space
                    UART_write('\b'); // Move the cursor back again
                }
            }
            else{
                UART_write(ch);
                index_num1++;
                num1[index_num2++] = ch;
                num1[index_num2] = '\0';
            }
        }
    }
    return 0;
}