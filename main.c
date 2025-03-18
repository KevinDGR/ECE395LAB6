void setupUART();
unsigned char UART_read();
void UART_write(unsigned char a);
#define MAX_BUFFER_SIZE 100
int indexx = 0;
int index_num1 =0;
int index_num2 =0;
int memory =0;
int z =0;
void uart_write_string(const char *str){
    while(*str){
        UART_write(*str);
        str++;
    }
}// 2 dig + 3 dig adds first 2 not last 3rd
// with 3 first it just prints the first 3 digits, doesnt add, just spit out same 3 digits as first entered

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

int main(void){   
    

    setupUART();
    //uart_write_string("Solve: ");
while(1){
    char num1[MAX_BUFFER_SIZE];
    char num2[MAX_BUFFER_SIZE];
    unsigned char ch; 
    int x =0 ;
    int y =0;
    indexx = 0;
    uart_write_string("\n");
    uart_write_string("Solve: ");
    while (indexx < MAX_BUFFER_SIZE - 1){
        ch = UART_read();
        if(ch == '+'){
            UART_write('+');
             indexx = 0;
             while (indexx < MAX_BUFFER_SIZE - 1){
                ch = UART_read();
                if (ch == '\n' || ch == '\r') {
                    break; // End of input
                } else if (ch == 0x08) { // Backspace detected
                    if (index_num2 > 0) { // Ensure index_num2 doesn't go below 0
                        index_num2--; // Move back in buffer
                        num2[index_num2] = '\0'; // Clear the last character from the buffer
                        UART_write('\b'); // Move the cursor back
                        UART_write(' '); // Overwrite the character with a space
                        UART_write('\b'); // Move the cursor back again
                    }
                } else {
                    UART_write(ch); // Echo input to terminal
                    num2[index_num2++] = ch; // Add character to num2 buffer
                    num2[index_num2] = '\0'; // Null-terminate num2
                }
            }
            x = getNum(num1, index_num1);
            y = getNum(num2, index_num2);
            z = x + y;
            uart_write_string("\r\n");
            (getChar(z));
            break;
        }

        else if(ch == '-'){
            UART_write('-');
            int indexx = 0;
            while (indexx < MAX_BUFFER_SIZE - 1){
                ch = UART_read();
                UART_write(ch);
                index_num2 ++;
                num2[indexx++] = ch;
                num2[indexx] = '\0';
                if (ch == '\n' || ch == '\r'){
                    break;
                }
            }
            x = getNum(num1, index_num1);
            y = getNum(num2, index_num2);
            z = x - y;
            uart_write_string("\r\n");
            (getChar(z));
            break;
        }
        
        else if(ch == '/'){
            UART_write('/');
            int indexx = 0;
            while (indexx < MAX_BUFFER_SIZE - 1){
                ch = UART_read();
                UART_write(ch);
                index_num2 ++;
                num2[indexx++] = ch;
                num2[indexx] = '\0';
                if (ch == '\n' || ch == '\r'){
                    break;
                }
            }
            x = getNum(num1, index_num1);
            y = getNum(num2, index_num2);
            z = x / y;
            uart_write_string("\r\n");
            (getChar(z));
            break;
        }

        else if(ch == '*'){
            UART_write('*');
            int indexx = 0;
            while (indexx < MAX_BUFFER_SIZE - 1){
                ch = UART_read();
                UART_write(ch);
                index_num2 ++;
                num2[indexx++] = ch;
                num2[indexx] = '\0';
                if (ch == '\n' || ch == '\r'){
                    break;
                }
            }
            x = getNum(num1, index_num1);
            y = getNum(num2, index_num2);
            z = x * y;
            uart_write_string("\r\n");
            (getChar(z));
            break;
        }

        else if(ch == '%'){
            UART_write('%');
            int indexx = 0;
            while (indexx < MAX_BUFFER_SIZE - 1){
                ch = UART_read();
                UART_write(ch);
                index_num2 ++;
                num2[indexx++] = ch;
                num2[indexx] = '\0';
                if (ch == '\n' || ch == '\r'){
                    break;
                } 
            }
            x = getNum(num1, index_num1);
            y = getNum(num2, index_num2);
            z = x % y;
            uart_write_string("\r\n");
            (getChar(z));
            break;
        }

        else if(ch == '!'){
            UART_write('!');
            
            x = getNum(num1, index_num1);
            //y = getNum(num2, index_num2);
            z = x;
            for(int i = x -1; i>0; i--){
                z = z*i; 
            } 
            uart_write_string("\r\n");
            (getChar(z));
            break;
        }

        else if(ch == '?'){
            UART_write('?');
            
            x = getNum(num1, index_num1);
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
         
            uart_write_string("\r\n");
            //(getChar(z));
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
             indexx = 0;
            while (indexx < MAX_BUFFER_SIZE - 1){
                ch = UART_read();
                UART_write(ch);
                index_num2 ++;
                num2[indexx++] = ch;
                num2[indexx] = '\0';
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
            uart_write_string("\r\n");
            (getChar(z));
            break;
        }
        else if(ch == '-'){
            UART_write('-');
            int indexx = 0;
            while (indexx < MAX_BUFFER_SIZE - 1){
                ch = UART_read();
                UART_write(ch);
                index_num2 ++;
                num2[indexx++] = ch;
                num2[indexx] = '\0';
                if (ch == '\n' || ch == '\r'){
                    break;
                }
            }
            
            y = getNum(num2, index_num2);
            z = x - y;
            uart_write_string("\r\n");
            (getChar(z));
            break;
        }
        
        else if(ch == '/'){
            UART_write('/');
            int indexx = 0;
            while (indexx < MAX_BUFFER_SIZE - 1){
                ch = UART_read();
                UART_write(ch);
                index_num2 ++;
                num2[indexx++] = ch;
                num2[indexx] = '\0';
                if (ch == '\n' || ch == '\r'){
                    break;
                }
            }
            
            y = getNum(num2, index_num2);
            z = x / y;
            uart_write_string("\r\n");
            (getChar(z));
            break;
        }

        else if(ch == '*'){
            UART_write('*');
            int indexx = 0;
            while (indexx < MAX_BUFFER_SIZE - 1){
                ch = UART_read();
                UART_write(ch);
                index_num2 ++;
                num2[indexx++] = ch;
                num2[indexx] = '\0';
                if (ch == '\n' || ch == '\r'){
                    break;
                }
            }
            
            y = getNum(num2, index_num2);
            z = x * y;
            uart_write_string("\r\n");
            (getChar(z));
            break;
        }

        else if(ch == '%'){
            UART_write('%');
            int indexx = 0;
            while (indexx < MAX_BUFFER_SIZE - 1){
                ch = UART_read();
                UART_write(ch);
                index_num2 ++;
                num2[indexx++] = ch;
                num2[indexx] = '\0';
                if (ch == '\n' || ch == '\r'){
                    break;
                } 
            }
            
            y = getNum(num2, index_num2);
            z = x % y;
            uart_write_string("\r\n");
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
            uart_write_string("\r\n");
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
         
            uart_write_string("\r\n");
            //(getChar(z));
            break;
        }

            }
        }
        
        else if (ch == 0x08) { // Backspace detected
            if (indexx > 0) { // Ensure indexx doesn't go below 0
                indexx--; // Move back in buffer
                index_num1--; // Decrement number of valid digits in num1
                num1[indexx] = '\0'; // Clear the last character from the buffer
                UART_write('\b'); // Move the cursor back
                UART_write(' '); // Overwrite the character with a space
                UART_write('\b'); // Move the cursor back again
            }
        }

        else{
            UART_write(ch);
            index_num1++;
            num1[indexx++] = ch;
            num1[indexx] = '\0';
        }
    }
}
 // Keep the program running (typical for embedded systems)
    while (1){
 // Additional functionality could be added here
    }
    return 0;
}
// detect if character entered is number or letter
// do calculation
// convert answer from number to character