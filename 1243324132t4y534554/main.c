#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sys/types.h"

char HexChar [16] = { '0', '1', '2', '3', '4', '5', '6', '7',
                      '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };


static void addDecValue (int * pHexArray, int nElements, int value)
{
    int carryover = value;
    int tmp = 0;
    int i;

    /* start at the bottom of the array and work towards the top
     *
     * multiply the existing array value by 10, then add new value.
     * carry over remainder as you work back towards the top of the array
     */
    for (i = (nElements-1); (i >= 0); i--)
    {
        tmp = (pHexArray[i] * 10) + carryover;
        pHexArray[i] = tmp % 16;
        carryover = tmp / 16;
    }
}

static int * initHexArray (char * pDecStr, int * pnElements)
{
    int * pArray = NULL;
    int lenDecStr = strlen (pDecStr);
    int i;

    /* allocate an array of integer values to store intermediate results
     * only need as many as the input string as going from base 10 to
     * base 16 will never result in a larger number of digits, but for values
     * less than "16" will use the same number
     */

    pArray = (int *) calloc (lenDecStr,  sizeof (int));

    for (i = 0; i < lenDecStr; i++)
    {
        addDecValue (pArray, lenDecStr, pDecStr[i] - '0');
    }

    *pnElements = lenDecStr;

    return (pArray);
}

static void printHexArray (int * pHexArray, int nElements)
{
    int start = 0;
    int i;

    /* skip all the leading 0s */
    while ((pHexArray[start] == 0) && (start < (nElements-1)))
    {
        start++;
    }

    for (i = start; i < nElements; i++)
    {
        printf ("%c", HexChar[pHexArray[i]]);
    }

    printf ("\n");
}

int main() {

  int choice, bit, nrelements, *pHexArray;
  char *op, *opp;
  double first, second;
  printf("Choose which calculator you use:\n");
  printf("1. Basic Calculator\n");
  printf("2. Bit Calculator\n");
  printf("3. Exit\n");
  printf("Use 1, 2 or 3 to choose:");
  scanf("%d", &choice);
  printf("\n");
  if (choice == 1) {
  printf("You have chosen Basic Calculator\n");
  printf("Enter an operator (+, -, *, /): ");
  scanf("%s", op);
  printf("\n");
  printf("Enter two operands: ");
  scanf("%lf %lf", &first, &second);

  if(strcmp(op, "+") == 0) {
      printf("%.1lf + %.1lf = %.1lf", first, second, first + second);
      return 0;
  } else if(strcmp(op, "-") == 0) {
      printf("%.1lf - %.1lf = %.1lf", first, second, first - second);
      return 0;
  } else if(strcmp(op, "*") == 0) {
      printf("%.1lf * %.1lf = %.1lf", first, second, first * second);
      return 0;
  } else if(strcmp(op, "/") == 0) {
      printf("%.1lf / %.1lf = %.1lf", first, second, first / second);
      return 0;
  }
    // operator doesn't match any case constant
      printf("Error! operator is not correct");
  }
  else if (choice == 2) {
    printf("You have chosen Bit Calculator\n");
    printf("Enter an operation , 10_2(base 10 into base 2), 10_16(base 10 into 16): ");
    opp = malloc(sizeof(char)*5);
    scanf("%c", opp);
    printf("\nEnter operand: ");
    if( strcmp(opp, "10_2") == 0 ) {;
    scanf("%d", &bit);
    //turn bit into binary using shift
    for(int i = 15; i >= 0; i--) {
        printf("%d", (bit >> i) & 1);
    }
    }
    else if( strcmp(opp, "10_16") == 0 ) {
    //turn bit into hex
    char *hex;
    scanf("%c", hex);
    pHexArray = initHexArray (hex, &nrelements);
    printHexArray (pHexArray, nrelements);
    }
    else {
        printf("Error! operator is not correct");

  }
  }
  else if (choice == 3) {
    printf("You have chosen Exit\n");
    printf("Thank you for using our calculator\n");
  }
  else {
    printf("Error! operator is not correct");
  }
  return 0;
}
