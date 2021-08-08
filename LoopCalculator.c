#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
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
    }
    return result;
} 

// Print results
void printResults(int lcv, float nums[150][150], float results[150], char operators[150])
{
        if(operators[lcv] != '!' & operators[lcv] != 'v')
        {
            printf("%f %c %f = %f\n", nums[lcv][0], operators[lcv], nums[lcv][1], results[lcv]); 
        }
        else
        {
            printf("%f %c = %f\n", nums[lcv][0], operators[lcv], results[lcv]);
        }
}

// main function returns integer
int main()
{
    // variable declaration
    FILE *fp;  
    bool done = false;
    bool inputTypeValid = false; // check true when user selects a valid input type
    char *token;    // pointer to character address
    char loop;              
    char fname[20];
    char inputType[13];
    char singleLine[150];
    char operators[150];  // operations for each equation 
    float nums[150][150]; // column indexed 0 contains first number column indexed 1 contains second number
    float results[150];   // results of calaculations chronilogically
    int i = 0;      // number of lines parsed from text file (number of equations)
    int lcv = 0;    // loop control variable used for indexing through equations 
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
            do
            {
                printf("Enter the file name:\n");
                fflush(stdin);
                scanf("%s", &fname);
                fp = fopen(fname, "r");

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
            
            // Output results
            for(lcv = 0; lcv < i; lcv++)
            {
                printResults(lcv, nums, results, operators);
            }

            fclose(fp);                           // free up computer memory
            inputTypeValid = true;
        }
        else if(strspn(inputType, "command line") == strlen("command line"))    // if the char array contains "commmand line" return true
        {
            do 
            {
            
                printf("\nEnter the operation sign of the operation that want performed:\n");
                fflush(stdin);
                scanf("%c", &operators[i]); // REQ2: Read in the choice of operation (+, -, *, /) and store it in a char variable

                //enum operators selection = operators[i];

                if (operators[i] != '+' & operators[i] != '-' & operators[i] != '*' & operators[i] != '/' & operators[i] != '^' & operators[i] != '!' & operators[i] != 'v' ) // Invalid input check
                {
                    printf("Enter a valid operation on next run\n");
                    continue;
                }
                // Prompt the user to input a first number, read and store it in a float variable
                printf("\nEnter the first number to the calculation:\n");
             
                // Accept first number and validate
                fflush(stdin);
                int checknum1 = scanf("%f", &nums[i][0]);
                if(checknum1 != 1) // Invalid input check
                {
                    printf("Enter a valid number on next run\n");
                    continue;
                }
              

                // Accept second number and validate   
                if(operators[i] != '!' & operators[i] != 'v')
                {    
                    printf("\nEnter the second number to the calculation:\n");
                    fflush(stdin);
                    int checknum2 = scanf("%f", &nums[i][1]);

                    if (checknum2 != 1) // Invalid input check
                    {
                        printf("Enter a valid number on next run\n");
                        continue;
                    }
                }
                
                // Save result of expression
                results[i] = determine(nums[i][0], nums[i][1], operators[i]); // call arithmetic to be performed

                // Print result to user
                printResults(i, nums, results, operators);

                printf("\nPerform another calculation? Enter Y for Yes or N for No: \n");
                fflush(stdin);
                scanf("%c",&loop);
                if(loop == 'N')
                {
                    done = true;
                    printf("Exiting...\n");
                }
                i++;
            } while(!done);
            inputTypeValid = true;
        }
        else                                                                    // if the char array doesn't match let them know and try again
        {
            printf("Please enter a valid input option\n\n");
        }
    } while(!inputTypeValid);
    
    return 0;
}