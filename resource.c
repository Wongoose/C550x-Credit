#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// function to check for valid card length
int is_valid_length(long numbers) {
    int length = 0;
    
    while (numbers > 0) {
        length++;
        numbers /= 10;
    }
    
    if (length == 13 || length == 15 || length == 16) return (1);
    return (0);
}

// function to get the first 2 digits of the card
int get_first_2digits(long input)
{
    long res = input;

    while (res >= 100) 
    {
        res /= 10;
    }

    return res;
}

// function just to duplicate a src string to print result (not necessary)
char    *strdup(char *src) {
    int i = 0;
    char *dest;
    
    while (src[i] != '\0')
        i++;
    dest = (char *) malloc(sizeof(char) * (i + 1));
    i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return (dest);
}

// function to check the type of card (VISA, AMEX, MASTERCARD)
char    *type_of_card(long input) {
    int start_num = get_first_2digits(input);
    char *result;
    
    if (start_num / 10 == 4) {
        result = strdup("VISA");
        return (result);
    }
        
    switch (start_num) {
        case (34):
        case (37):
            result = strdup("AMEX");
            break ;
        case (51):    
        case (52):    
        case (53):    
        case (54):    
        case (55):
            result = strdup("MASTERCARD");
            break ;
        default:
            result = strdup("INVALID");
            break ;
    }
    return (result);
}

// functino to sum any 2 digits during the checksum calculation
int reformat_product(int product) {
    int res = 0;
    
    product *= 2;
    if (product > 9)
        res = (product / 10 + product % 10);    
    else
        res = product;
        
    // printf("Product: %d\t Res: %d\n", product, res);
    return (res);
}

// function to get checksum
int get_checksum(long input) {
    int sum = 0;
    int is_alternate = -1;
    long card_num;
    
    card_num = input;
    while (card_num > 0) {
        if (is_alternate == 1) { // to sum alternate digits starting from the 2nd last
            sum += reformat_product(card_num % 10);
        }
        is_alternate *= -1;
        card_num /= 10;
    }
    
    // then, sum the rest of the digits
    card_num = input;
    is_alternate = 1;
    while (card_num > 0) {
        if (is_alternate == 1) {
            sum += (card_num % 10);
        }
        is_alternate *= -1;
        card_num /= 10;
    }
    
    return (sum % 10 == 0);
}

int main(int argc, char** argv) {
    // get cardNumber from argument (argv)
    long cardNumber = atol(argv[1]);

    // checks for valid length and checksum
    if (!(is_valid_length(cardNumber) && get_checksum(cardNumber))) {
        printf("INVALID");
    } else {
        printf("%s\n", type_of_card(cardNumber));
    }
    return (0);
}