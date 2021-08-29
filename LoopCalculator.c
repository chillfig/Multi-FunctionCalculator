#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
//#include <dirent.h>

// Enumeration of operations
enum operators {Add = '+', Subtract = '-', Multiply = '*', Divide = '/', Power = '^', Factorial = '!',
                SquareRoot = 'v', BitAnd = '&', BitOr = '|', BitLeft = '<', BitRight = '>'} ;

// Add function returns sum
float add(float num1, float num2)
{
    float result = num1 + num2;
    return result;
}

// Subtract function returns difference
float subtract(float num1,float num2)
{
    float result = num1 - num2;
    return result;
}

// Multiply function returns product
float multiply(float num1,float num2)
{
    float result = num1 * num2;
    return result;
}

// Divide function returns quotient
float divide(float num1,float num2)
{
    assert(num2 != 0);  // prevent division by 0
    float result = num1 / num2;
    return result;
}

// Power function returns the exponent of a base
float power(float base, float exp)
{
    float result = 1;
    while(exp)
    {
        result *= base;
        exp--;
    }
    return result;
}

// Factorial function returns factorial
float factorial(float num)
{
    if(num <= 1)
	{
		return 1;
	}
	else
	{
		return num * factorial(num-1);
	}
}

// SqRoot function accepts a number and alters result from reference pass. Returns Void
void SqRoot(float num, float* result)
{
    float sqrt = num / 2;
    float temp = 0;

    while(sqrt != temp)
    {
        temp = sqrt;
        sqrt = (num / temp + temp) / 2;
    }
    *result = sqrt;
}

/* Bitwise AND function compares the bits of 2 floats given as input from the user. These float
variables are typecasted into integers. The result is modified by function and passed by reference.*/
void bitAnd(float num1, float num2, float* result)
{
    *result = (int) num1 & (int) num2;
}

/* Bitwise OR function compares the bits of 2 floats given as input from the user. These float
variables are typecasted into integers. The result is modified by function and passed by reference.*/
void bitOr(float num1, float num2, float* result)
{
    *result = (int) num1 | (int) num2;
}

/* Bitwise shift right function shifts the bits of the first float number given from the user to the right
in the amount provided from the user as the second float. The result is modified by function and passed by reference.*/
void bitRight(float num1, float num2, float* result)
{
    *result = (int) num1 >> (int) num2;
}

/* Bitwise shift right function shifts the bits of the first float number given from the user to the left
in the amount provided from the user as the second float. The result is modified by function and passed by reference.*/
void bitLeft(float num1, float num2, float* result)
{
    *result = (int) num1 << (int) num2;
}

// Determine arithmetic, execute appropriate function, and return result
float determine(float num1, float num2, char operation)
{
    float result;                          // Declare result that will be returned
    enum operators selection = operation; // Assign the raw character to an enum type variable

    switch(selection)
    {
        case Add :
        result = add(num1,num2);
        break;

        case Subtract :
        result = subtract(num1,num2);
        break;

        case Multiply :
        result = multiply(num1,num2);
        break;

        case Divide :
        result = divide(num1,num2);
        break;

        case Power :
        result = power(num1, num2);
        break;

        case Factorial :
        result = factorial(num1);
        break;

        case SquareRoot :
        SqRoot(num1, &result);
        break;

        case BitAnd :
        bitAnd(num1, num2, &result);
        break;

        case BitOr :
        bitOr(num1, num2, &result);
        break;

        case BitRight :
        bitRight(num1, num2, &result);
        break;

        case BitLeft :
        bitLeft(num1, num2, &result);
        break;
    }
    return result;
} 

// Print results according to the operation selected by the user
void printResults(int lcv, float nums[150][150], float results[150], char operators[150])
{
        if(operators[lcv] == Add || operators[lcv] == Subtract || operators[lcv] == Multiply || operators[lcv] == Divide || 
        operators[lcv] == Power || operators[lcv] == BitAnd || operators[lcv] == BitOr || operators[lcv] == BitLeft || operators[lcv] == BitRight)
        {
            if((operators[lcv] == BitAnd || operators[lcv] == BitOr || operators[lcv] == BitLeft || operators[lcv] == BitRight) && (nums[lcv][0] / (int) nums[lcv][0]) != 1)
            {
                printf("%f is not an integer.\n", nums[lcv][0]);
            }
            else if((operators[lcv] == BitAnd || operators[lcv] == BitOr || operators[lcv] == BitLeft || operators[lcv] == BitRight) && (nums[lcv][1] / (int) nums[lcv][1] != 1))
            {
                printf("%f is not an integer.\n", nums[lcv][1]);
            }
            else if((operators[lcv] == BitLeft || operators[lcv] == BitRight) && ((nums[lcv][1] / (int) nums[lcv][1] != 1) || (nums[lcv][1] < 0 || nums[lcv][1] > 16)))
            {
                printf("%f is not an integer between 0 and 16.\n", nums[lcv][1]);
            }
            else
            {
                printf("%f %c %f = %f\n", nums[lcv][0], operators[lcv], nums[lcv][1], results[lcv]); 
            }
        }
        else if(operators[lcv] == Factorial || operators[lcv] == SquareRoot)
        {
            printf("%f %c = %f\n", nums[lcv][0], operators[lcv], results[lcv]);
        }
        else
        {
            printf("\"%c\" entered in line %d is an invalid operation\n", operators[lcv], lcv+1);
        }
}

// Write results. Pass file pointer, 
void writeResults(FILE* writeFile, int lcv, float nums[150][150], float results[150], char operators[150])
{
        //printf("The value of lcv is: %d\n The value of current nums[lcv][0] is %f\n the current value of nums[lcv][1] is: %f\n and the value of operators[lcv] is: %c\n\n",lcv, nums[lcv][0],nums[lcv][1],operators[lcv]);
        if(operators[lcv] == Add || operators[lcv] == Subtract || operators[lcv] == Multiply || operators[lcv] == Divide || 
        operators[lcv] == Power || operators[lcv] == BitAnd || operators[lcv] == BitOr || operators[lcv] == BitLeft || operators[lcv] == BitRight)
        {
            if((operators[lcv] == BitAnd || operators[lcv] == BitOr || operators[lcv] == BitLeft || operators[lcv] == BitRight) && (nums[lcv][0] / (int) nums[lcv][0]) != 1)
            {
                fprintf(writeFile, "%f is not an integer.\n", nums[lcv][0]);
            }
            else if((operators[lcv] == BitAnd || operators[lcv] == BitOr || operators[lcv] == BitLeft || operators[lcv] == BitRight) && (nums[lcv][1] / (int) nums[lcv][1] != 1))
            {
                fprintf(writeFile, "%f is not an integer.\n", nums[lcv][1]);
            }
            else if((operators[lcv] == BitLeft || operators[lcv] == BitRight) && ((nums[lcv][1] / (int) nums[lcv][1] != 1) || (nums[lcv][1] < 0 || nums[lcv][1] > 16)))
            {
                fprintf(writeFile, "%f is not an integer between 0 and 16.\n", nums[lcv][1]);
            }
            else
            {
                fprintf(writeFile, "%f %c %f = %f\n", nums[lcv][0], operators[lcv], nums[lcv][1], results[lcv]); 
            }
        }
        else if(operators[lcv] == Factorial || operators[lcv] == SquareRoot)
        {
            fprintf(writeFile, "%f %c = %f\n", nums[lcv][0], operators[lcv], results[lcv]);
        }
        else
        {
            fprintf(writeFile, "\"%c\" entered in line %d is an invalid operation\n", operators[lcv], lcv+1);
        }
}

// main function returns integer
int main()
{
    // variable declaration
    FILE *fp;   // user input file pointer
    FILE *fpo = fopen("output.txt", "w");;  // output file pointer
    bool done = false;
    bool inputTypeValid = false; // check true when user selects a valid input type
    char *token;    // pointer to character address
    char loop;      // user's keyboard entry that determines exit of the program or not               
    char fname[20];         // the name of the input file
    char inputType[13];     // the user's keyboard entry for which input type to use
    char singleLine[150];   // a single line parsed from the input file
    char operators[150];  // operations for each equation 
    float nums[150][150]; // column indexed 0 contains first number column indexed 1 contains second number
    float results[150];   // results of calaculations chronilogically
    int i = 0;      // number of lines parsed from text file (number of equations)
    int lcv = 0;    // loop control variable used for indexing through equations for output 
    int numTokens;  // number of delimited tokens in a line of the file
    //int ch = getc(fp);
    //DIR *dir = opendir("/Volumes/PcMac/Toolkit/Mirror/cProgramming/Cgate2/support");
    // Print introduction statement
    printf("Loop Calculator\n"
    "Available operations with thier operation sign are listed below.\n\n"
    "Addition:       +\n"
    "Subtraction:    -\n"
    "Multiplication: *\n"
    "Division:       /\n"
    "Power:          ^\n"
    "Factorial:      !\n"
    "Square Root:    v\n"
    "BitAnd:         &\n"
    "BitOr:          |\n"
    "BitLeft:        <\n"
    "BitRight:       >\n");
    printf("\n");
   
    // Calcaulate according to user input preference
    do
    {
        // Prompt the user for the input type  
        printf("Enter \"command line\" if you'd like to enter equations throught the command line \n"
        "Enter \"file\" if you'd like to enter equations through a local file:\n"); 
        fflush(stdin);
        fgets(inputType, sizeof(inputType), stdin); // read string
        
        if(strspn(inputType,"file") == strlen("file"))                          // if the char array contains "file" return true
        {
            printf("\nEnsure that the expressions within your input file are formatted with spaces in between each number and operation.\n"
            "Make certain that you only use integers for the bitwise operations: & | < >\n"
            "Furthermore, for the shift operations, only use integers between 0 and 16 for the second number of positions to shift left or right.\n\n"
            "Sample input file contents:\n"
            "\"1.2 * -1\"\n"
            "\"6 < 3\"\n"
            "\"6 ^\"\n"
            "\"9 !\"\n\n");
            do
            {
                printf("Enter the file name:\n");
                fflush(stdin);
                scanf("%s", &fname);
                printf("\n");
                fp = fopen(fname, "r");
                assert(fp != NULL); // prevent reading in file that does not exist 

                if(fp == NULL) 
                {
                    printf("Unable to open file!\n");
                }
            } while (fp == NULL);

            while(!feof(fp))
            {    
                numTokens = 0;
                fgets(singleLine, 150, fp);
                token = strtok(singleLine," ");
                nums[i][0] = strtof(token,NULL); // 1st number
                while(token != NULL)
                {
                    if(numTokens == 1)
                    {
                    operators[i] = token[0];   
                    }
                    else if(numTokens == 2)
                    {
                        nums[i][1] = strtof(token, NULL); // 2nd number
                    }
                    token = strtok(NULL, " ");
                    numTokens++;
                }
                results[i] = determine(nums[i][0], nums[i][1], operators[i]);
                i++;
            }
            
            // Output results to user and text file
            for(lcv = 0; lcv < i; lcv++)
            {
                printResults(lcv, nums, results, operators);
                writeResults(fpo, lcv, nums, results, operators);
            }

            fclose(fp);                           // free up computer memory
            fclose(fpo);                          // free up computer memory
            inputTypeValid = true;
        }
        else if(strspn(inputType, "command line") == strlen("command line"))    // if the char array contains "commmand line" return true
        {
            do 
            {
            
                printf("\nEnter the operation sign of the operation that want performed:\n");
                fflush(stdin);
                scanf("%c", &operators[i]); // REQ2: Read in the choice of operation (+, -, *, /) and store it in a char variable

               
                // Verify that the user's choice for the operator is one of the program's functions
                if (operators[i] != Add & operators[i] != Subtract & operators[i] != Multiply & operators[i] != Divide & operators[i] != Power & 
                operators[i] != Factorial & operators[i] != SquareRoot & operators[i] != BitAnd & operators[i] != BitOr & operators[i] != BitRight &
                operators[i] != BitLeft) // Invalid input check
                {
                    printf("\nEnter a valid operation on next run\n");
                    continue;
                }
                
                // Prompt the user to input a first number, read and store it in a float variable. If a bitwise operation was selected, prompt for integer.
                if (operators[i] == BitAnd || operators[i] == BitOr || operators[i] == BitLeft || operators[i] == BitRight)
                {
                    printf("\nEnter the first number to the calculation as an integer:\n");
                }
                else 
                {
                    // Prompt the user to input a first number, read and store it in a float variable
                    printf("\nEnter the first number to the calculation:\n");
                }

                // Accept first number. Verify that an integer is given if bitwise operation is selected.
                fflush(stdin);
                int checknum1 = scanf("%f", &nums[i][0]);
                
                // Invalid input check
                if(checknum1 != 1) 
                {
                    printf("\nEnter a valid number on next run\n");
                    continue;
                }
                else if((operators[i] == BitAnd || operators[i] == BitOr || operators[i] == BitLeft || operators[i] == BitRight) && (nums[i][0] / (int) nums[i][0] != 1))
                {
                    printf("\nEnter the first number as an integer for the bitwise operation on next run\n");
                    continue;
                } 
              

                // Accept second number. Verify that an integer is given if bitwise operation is selected.
                if(operators[i] != Factorial & operators[i] != SquareRoot)
                {    
                    // Prompt message to user for a request of a second numeber
                    if(operators[i] == BitLeft || operators[i] == BitRight)
                    {
                        printf("\nEnter the second number for the bit shift operation. Use an integer between 0 and 16:\n");
                    }    
                    else
                    {
                        printf("\nEnter the second number to the calculation:\n");
                    }
                    
                    // Flush and accept input
                    fflush(stdin);
                    int checknum2 = scanf("%f", &nums[i][1]);

                    // Invalid input check
                    if (checknum2 != 1) 
                    {
                        printf("\nEnter a valid number on next run\n");
                        continue;
                    }
                    else if((operators[i] == BitAnd || operators[i] == BitOr) && (nums[i][1] / (int) nums[i][1] != 1))
                    {
                    	printf("\nEnter the second number as an integer for the bitwise operation on next run\n");
                    	continue;
                    } 
                    // Check for Bitwise shift operations that the second number is either not an integer or is not within required numerical range.
                    else if((operators[i] == BitLeft || operators[i] == BitRight) && ((nums[i][1] / (int) nums[i][1] != 1) || (nums[i][1] < 0 || nums[i][1] > 16)))
                    {
                        printf("\nEnter the second number as an integer between 0 and 16 for the bitwise shift oeprations on next run\n");
                    	continue;
                    }
                }
                
                // Save result of expression
                results[i] = determine(nums[i][0], nums[i][1], operators[i]); // call arithmetic to be performed

                // Print result to user
                printResults(i, nums, results, operators);

                // Write result to text file
                writeResults(fpo, i, nums, results, operators);

                printf("\nPerform another calculation? Enter 'N' for No. Enter any other key for Yes: \n");
                fflush(stdin);
                scanf("%c",&loop);
                if(loop == 'N')
                {
                    done = true;
                    printf("Exiting...\n");
                }
                i++;
            } while(!done);
            fclose(fpo); // free up computer memory
            inputTypeValid = true;
        }
        else                                                                    // if the char array doesn't match let them know and try again
        {
            printf("Please enter a valid input option\n\n");
        }
    } while(!inputTypeValid);
    printf("\n");
    return 0;
}