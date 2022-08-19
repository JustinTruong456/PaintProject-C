/*
    Your task is to write a program to read sales records from a file,
    print the records to screen, and write a report of sales by item.

    The data file contains:

    1,High Gloss,Paint,2,25.99
    2,2.5in Trim,Brush,1,12.99
    3,9in Roller,Pan,2,5.99
    4,High Gloss,Paint,5,25.99
    5,9in Roller,Pan,1,5.99
    6,2.5in Trim,Brush,3,12.99
    7,High Gloss,Paint,3,25.99
    8,9in Roller,Pan,5,5.99

    The data are:

    integer id
    string item
    string type
    integer qty
    double price

    This task will be easier if you code you program in this order:

    1. Include libraries
    2. Write constants
    3. Write structs
    4. Write empty main (except return 0;)
    5. Write create_list function
    6. Write print_sale function
    7. Write print_list function
    8. Write read_sales function
    9. Test all functions in main
        a. create_list function
        b. read_sales function
        c. print_list function
    10. Write write_report function
    11. Test write_report function in main
    12. Submit this file to Canvas.

    Good luck!
*/


// 1. Include libraries here
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ITEM_SIZE 25
#define TYPE_SIZE 15
#define SALE_LIST_LENGTH 100
#define NUM_DEPTS 5

// 2. Constants and global data here
/*
    A constant called ITEM_SIZE with value 25
    A constant called TYPE_SIZE with value 15
    A constant called SALE_LIST_LENGTH with value 100
    A constant called NUM_DEPTS with value 5
*/

// Free code!! - The 3 items from the data
//char items[][ITEM_SIZE] = {"High Gloss", "2.5in Trim", "9in Roller"};



// 3. Structs here
/*
    Write code for a struct named sale_t that contains:
    An integer named id
    A string named item with length ITEM_SIZE
    A string named type with length TYPE_SIZE
    An integer named qty
    A double named price
*/
typedef struct{
int id;
char item[ITEM_SIZE];
char type[TYPE_SIZE];
int qty;
double price;
}sale_t;

typedef struct{
sale_t array[SALE_LIST_LENGTH];
int length;
int count;
}sale_list_t;

/*
    Write code for a list struct named sale_list_t
    An array of sale_t named array with length SALE_LIST_LENGTH
    An integer named length
    An integer named count
*/



// Prototypes here
sale_list_t create_list();
void print_sale(sale_t p);
void print_list(sale_list_t p);
int read_sales(sale_list_t *p, char filename[]);
void write_report(sale_list_t p, char filename[]);


// 4. Main function here
/*
    The main function should:
    1. Create a sale_list_t
    2. Read the sales from the file to the list
    3. Print the list to screen
    4. Write the report to file
*/
int main(){
sale_list_t p = create_list();
int recs = read_sales(&p, "PaintPlace.csv");
printf("%d records are read\n", recs);
print_list(p);
write_report(p,"PaintReport.txt");
    return 0;
}


// 5. create_list function
/*
    Write a function named create_list that accepts nothing and returns
    a sale_list_t with length set to SALE_LIST_LENGTH and count to zero.
*/
sale_list_t create_list(){
sale_list_t p;
p.length = SALE_LIST_LENGTH;
p.count=0;

return p;
}


// 6. print_sale function
/*
    Write a function named print_sale that accepts a sale_t and prints
    all the data on one line, separated by spaces.  Example:

    1 High Gloss Paint 2 $25.99
*/
void print_sale(sale_t p){
    printf("%d %s %s %d $%.2lf\n", p.id, p.item, p.type, p.qty, p.price);
}


// 7. print_list function
/*
    Write a function named print_list that accepts a sale_list_t and prints
    a header and all the elements by calling print_sale.  Example:

    Paint Place Sales

    1 High Gloss Paint 2 $25.99
    2 2.5in Trim Brush 1 $12.99
    3 9in Roller Pan 2 $5.99
    4 High Gloss Paint 5 $25.99
    5 9in Roller Pan 1 $5.99
    6 2.5in Trim Brush 3 $12.99
    7 High Gloss Paint 3 $25.99
    8 9in Roller Pan 5 $5.99
*/
void print_list(sale_list_t p){
    printf("Paint Place Sales\n\n");
    for(int i =0; i<p.count; i++){
        print_sale(p.array[i]);
    }
}

// 8. read_sales function
/*
    Write a function named read_sales that accepts a sale_list_t pointer
    and a string containing the file name, and returns the number of records
    read.  Make sure to check that the file opened correctly (not NULL) and
    close the file when done reading.  The function should open the file,
    read all its records into the sale_list_t (make sure to update count),
    close the file and return the count of records read.
*/
//1,High Gloss,Paint,2,25.99
int read_sales(sale_list_t *p, char filename[]){
    FILE *file = fopen(filename, "r");
    char line[100];
    int recs =0;
    if (file == NULL){
        perror("File didn't open");
        exit(1);
    }

    while (fgets(line, 100, file) != NULL){
        //printf("%s\n", line);
        line[strlen(line)-1]='\0';
        p->array[recs].id= atoi(strtok(line,","));
        strcpy(p->array[recs].item, strtok(NULL,","));
        strcpy(p->array[recs].type, strtok(NULL,","));
        p->array[recs].qty = atoi(strtok(NULL,","));
        p->array[recs].price = atof(strtok(NULL,","));
        p->count +=1;
        recs++;
    }

    fclose(file);
    return recs;
}

// 10. write_report function
/*
    Write a function named write_report that accepts a sale_list_t and
    a string file name, and returns nothing.  Make sure to check that
    the file opened correctly (not NULL) and close the file when done
    reading. The function should open the file, write the header, write
    the totals for each dept, write the grand total, and close the file.

    Hint: The outer loop should iterate through all items and the inner
    loop should iterate through all sale_t in the sale_list_t.  Use an
    if statement to accumulate a total for each item.

    The report should look like:

    Paint Place Sales Report

    High Gloss: $259.90
    2.5in Trim: $51.96
    9in Roller: $47.92

    Total sales: $359.78

*/
void write_report(sale_list_t p, char filename[]){
    FILE*file = fopen(filename, "w");
    double finaltotal =0;
    double highgloss_total=0;
    double trim_total=0;
    double roller_total=0;

    if (file == NULL){
        perror("File didn't open");
        exit(1);
    }

    fprintf(file,"Paint Place Sales Report\n\n");
    for (int i =0; i<p.count; i++){
        finaltotal = finaltotal + (p.array[i].qty*p.array[i].price);
        if(strcmp(p.array[i].item,"High Gloss") == 0){
            highgloss_total = highgloss_total + (p.array[i].qty*p.array[i].price);
        }
        else if (strcmp(p.array[i].item,"2.5in Trim")== 0){
            trim_total = trim_total + (p.array[i].qty*p.array[i].price);
        }
        else if (strcmp(p.array[i].item,"9in Roller")==0){
            roller_total = roller_total + (p.array[i].qty*p.array[i].price);
        }


    }
    fprintf(file,"High Gloss: $%.2lf\n", highgloss_total);
    fprintf(file,"2.5in Trim:  $%.2lf\n",trim_total);
    fprintf(file, "9in Roller: $%.2lf\n\n", roller_total);
    fprintf(file,"Total sales: $%.2lf", finaltotal);
    fclose(file);
}


