void setupUART();
unsigned char UART_read();
void UART_write(unsigned char a);
#define MAX_BUFFER_SIZE 100

int memory = 0;
unsigned char ch;
int x;
int y;
int z;

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

void backspace(char* buffer, int* index_buff, char* buffer_num, int* index_num){
    if (*index_num > 0) { // Ensure index doesn't go below 0
        (*index_num)--; // Move back in buffer
        buffer_num[*index_num] = '\0'; // Clear the last character from the buffer
    }
    if (*index_buff > 0){
        (*index_buff)--;
        buffer[*index_buff] = '\0';
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

void mPlus(){
    memory += z; 
    uart_write_string(" [M+ Done]");
}

void mMinus(){
    memory -= z; 
    uart_write_string(" [M- Done]");
}

void mRecal(){
    x = memory; 
    uart_write_string(" [MR: Memory Recalled: ");
    getChar(memory); 
    uart_write_string("]");
    ch = UART_read();
}

void mClear(){
    memory = 0; 
    uart_write_string(" [MC: Memory Cleared]");
}

int main(void){
    setupUART();
    while(1){
        char num1[MAX_BUFFER_SIZE];
        char num2[MAX_BUFFER_SIZE];
        char buffer[MAX_BUFFER_SIZE];
        int index_num1 = 0;
        int index_num2 = 0;
        int index_buffer = 0;
        uart_write_string("\n\r");
        uart_write_string("Solve: ");
        while (index_num1 < MAX_BUFFER_SIZE - 1){
            ch = UART_read();
            buffer[index_buffer++] = ch;
            buffer[index_buffer] = '\0';
            if (ch == '+'){
                UART_write('+');
                while (index_num2 < MAX_BUFFER_SIZE - 1){
                    ch = UART_read();
                    buffer[index_buffer++] = ch;
                    buffer[index_buffer] = '\0';
                    if (ch == '\n' || ch == '\r'){
                        break; // End of input
                    }
                    else if (ch == 0x08){ // Backspace detected
                        backspace(buffer, &index_buffer, num2, &index_num2);
                        if (index_num2 == 0){
                            break;
                        }
                    }
                    else{
                        UART_write(ch); // Echo input to terminal
                        num2[index_num2++] = ch; // Add character to num2 buffer
                        num2[index_num2] = '\0'; // Null-terminate num2
                    }
                }
                if (index_num2 != 0){
                    x = getNum(num1, index_num1);
                    y = getNum(num2, index_num2);
                    z = x + y;
                    uart_write_string("\n\r");
                    getChar(z);
                    break;
                }
            }
            else if (ch == '-'){
                UART_write('-');
                while (index_num2 < MAX_BUFFER_SIZE - 1){
                    ch = UART_read();
                    if (ch == '\n' || ch == '\r'){
                        break;
                    }
                    else if (ch == 0x08){ // Backspace detected
                        backspace(buffer, &index_buffer, num2, &index_num2);
                        if (index_num2 == 0){
                            break;
                        }
                    }
                    else{
                        UART_write(ch);
                        num2[index_num2++] = ch;
                        num2[index_num2] = '\0';
                    }
                }
                if (index_num2 != 0){
                    x = getNum(num1, index_num1);
                    y = getNum(num2, index_num2);
                    z = x - y;
                    uart_write_string("\n\r");
                    getChar(z);
                    break;
                }
            }
            else if (ch == '*'){
                UART_write('*');
                while (index_num2 < MAX_BUFFER_SIZE - 1){
                    ch = UART_read();
                    if (ch == '\n' || ch == '\r'){
                        break;
                    }
                    else if (ch == 0x08){ // Backspace detected
                        backspace(buffer, &index_buffer, num2, &index_num2);
                        if (index_num2 == 0){
                            break;
                        }
                    }
                    else{
                        UART_write(ch);
                        num2[index_num2++] = ch;
                        num2[index_num2] = '\0';
                    }
                }
                if (index_num2 != 0){
                    x = getNum(num1, index_num1);
                    y = getNum(num2, index_num2);
                    z = x * y;
                    uart_write_string("\n\r");
                    getChar(z);
                    break;
                }
            }
            else if (ch == '/'){
                UART_write('/');
                while (index_num2 < MAX_BUFFER_SIZE - 1){
                    ch = UART_read();
                    if (ch == '\n' || ch == '\r'){
                        break;
                    }
                    else if (ch == 0x08){ // Backspace detected
                        backspace(buffer, &index_buffer, num2, &index_num2);
                        if (index_num2 == 0){
                            break;
                        }
                    }
                    else{
                        UART_write(ch);
                        num2[index_num2++] = ch;
                        num2[index_num2] = '\0';
                    }
                }
                if (index_num2 != 0){
                    x = getNum(num1, index_num1);
                    y = getNum(num2, index_num2);
                    z = x / y;
                    uart_write_string("\n\r");
                    getChar(z);
                    break;
                }
            }
            else if (ch == '%'){
                UART_write('%');
                while (index_num2 < MAX_BUFFER_SIZE - 1){
                    ch = UART_read();
                    if (ch == '\n' || ch == '\r'){
                        break;
                    }
                    else if (ch == 0x08){ // Backspace detected
                        backspace(buffer, &index_buffer, num2, &index_num2);
                        if (index_num2 == 0){
                            break;
                        }
                    }
                    else{
                        UART_write(ch);
                        num2[index_num2++] = ch;
                        num2[index_num2] = '\0';
                    }
                }
                if (index_num2 != 0){
                    x = getNum(num1, index_num1);
                    y = getNum(num2, index_num2);
                    z = x % y;
                    uart_write_string("\n\r");
                    getChar(z);
                    break;
                }
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
                    mPlus();
                } else if (ch == '-') {
                    mMinus();
                } else if (ch == 'C') {
                   mClear();
                } else if (ch == 'R') {
                   mRecal();
                   if (ch == '+'){
                    UART_write('+');
                    while (index_num2 < MAX_BUFFER_SIZE - 1){
                        ch = UART_read();
                        buffer[index_buffer++] = ch;
                        buffer[index_buffer] = '\0';
                        if (ch == '\n' || ch == '\r'){
                            break; // End of input
                        }
                        else if (ch == 0x08){ // Backspace detected
                            backspace(buffer, &index_buffer, num2, &index_num2);
                            if (index_num2 == 0){
                                break;
                            }
                        }
                        else{
                            UART_write(ch); // Echo input to terminal
                            num2[index_num2++] = ch; // Add character to num2 buffer
                            num2[index_num2] = '\0'; // Null-terminate num2
                        }
                    }
                    if (index_num2 != 0){
                        y = getNum(num2, index_num2);
                        z = x + y;
                        uart_write_string("\n\r");
                        getChar(z);
                        break;
                    }
                }
            else if (ch == '-'){
                UART_write('-');
                while (index_num2 < MAX_BUFFER_SIZE - 1){
                    ch = UART_read();
                    if (ch == '\n' || ch == '\r'){
                        break;
                    }
                    else if (ch == 0x08){ // Backspace detected
                        backspace(buffer, &index_buffer, num2, &index_num2);
                        if (index_num2 == 0){
                            break;
                        }
                    }
                    else{
                        UART_write(ch);
                        num2[index_num2++] = ch;
                        num2[index_num2] = '\0';
                    }
                }
                if (index_num2 != 0){
                    y = getNum(num2, index_num2);
                    z = x - y;
                    uart_write_string("\n\r");
                    getChar(z);
                    break;
                }
            }
            
            else if (ch == '/'){
                UART_write('/');
                while (index_num2 < MAX_BUFFER_SIZE - 1){
                    ch = UART_read();
                    if (ch == '\n' || ch == '\r'){
                        break;
                    }
                    else if (ch == 0x08){ // Backspace detected
                        backspace(buffer, &index_buffer, num2, &index_num2);
                        if (index_num2 == 0){
                            break;
                        }
                    }
                    else{
                        UART_write(ch);
                        num2[index_num2++] = ch;
                        num2[index_num2] = '\0';
                    }
                }
                if (index_num2 != 0){
                    y = getNum(num2, index_num2);
                    z = x / y;
                    uart_write_string("\n\r");
                    getChar(z);
                    break;
                }
            }

            else if (ch == '*'){
                UART_write('*');
                while (index_num2 < MAX_BUFFER_SIZE - 1){
                    ch = UART_read();
                    if (ch == '\n' || ch == '\r'){
                        break;
                    }
                    else if (ch == 0x08){ // Backspace detected
                        backspace(buffer, &index_buffer, num2, &index_num2);
                        if (index_num2 == 0){
                            break;
                        }
                    }
                    else{
                        UART_write(ch);
                        num2[index_num2++] = ch;
                        num2[index_num2] = '\0';
                    }
                }
                if (index_num2 != 0){
                    y = getNum(num2, index_num2);
                    z = x * y;
                    uart_write_string("\n\r");
                    getChar(z);
                    break;
                }
            }

            else if (ch == '%'){
                UART_write('%');
                while (index_num2 < MAX_BUFFER_SIZE - 1){
                    ch = UART_read();
                    if (ch == '\n' || ch == '\r'){
                        break;
                    }
                    else if (ch == 0x08){ // Backspace detected
                        backspace(buffer, &index_buffer, num2, &index_num2);
                        if (index_num2 == 0){
                            break;
                        }
                    }
                    else{
                        UART_write(ch);
                        num2[index_num2++] = ch;
                        num2[index_num2] = '\0';
                    }
                }
                if (index_num2 != 0){
                    y = getNum(num2, index_num2);
                    z = x % y;
                    uart_write_string("\n\r");
                    getChar(z);
                    break;
                }
            }

            else if(ch == '!'){
                UART_write('!');
                
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
                break;
            }

                }
            }
            else if (ch == 0x08) { // Backspace detected
                backspace(buffer, &index_buffer, num1, &index_num1);
            }
            else{
                UART_write(ch);
                num1[index_num1++] = ch;
                num1[index_num1] = '\0';
            }
        }
    }
    return 0;
}
