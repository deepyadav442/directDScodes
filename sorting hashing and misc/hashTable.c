//Implementation of 
//1) Hash table using array. 
//2) Handle collisions using Linear probing and chaining with replacement.

#include<stdio.h>
#include<string.h>
#define SIZE 10

struct Student
{
    int rno;
    char name[20];
    float percentage;
    int chain;
};

typedef struct Student Student;

void initializeTable(Student table[])
{
    int i;
    for(i =0 ; i< SIZE; i++)
    {
        table[i].rno = -1;
        strcpy(table[i].name, "");
        table[i].percentage = 0; 
        table[i].chain = -1; 
    }
}

int isFull(Student table[])
{
    int i;
    for(i =0; i< SIZE; i++)
    {
        if(table[i].rno == -1)
            return 0;//false
    }
    return 1; //true
}

int hash(int r)
{//mathematical function : modulo division method
    return r % SIZE ;
}

void addRecord(Student table[])
{
    if(! isFull(table))
    {
        Student temp;
        int  key;

        printf("\n Enter rno ");
        scanf("%d", &temp.rno);
        printf("\n enter name ");
        scanf("%19s", temp.name);
        printf("\n enter percentage ");
        scanf("%f", &temp.percentage);
        temp.chain = -1;
        
        //generate key based in attribute rno
        key = hash(temp.rno);
        
        if(table[key].rno == -1)
        {//empty position found
        //write record at position : key
            table[key] = temp;
        }
        else
        {//position occupied by a record
         //test for the records hash value against its position
         
            int tempkey;
            int i, x, w;
            
            tempkey = hash(table[key].rno);
            if(tempkey == key)
            {//two records hash to same key
             //Collision   
             //linear probing and chaining   
                for(i = (key+1)%SIZE; i != key; i= (i+1)%SIZE)
                {
                    if(table[i].rno == -1)
                    {//store temp at position i
                        table[i] = temp;

                        //chaining
                        w = key;
                        x = table[key].chain;
                        while(x != -1)
                        {
                            w = x;//shadow
                            x = table[x].chain;
                        }
                        table[w].chain = i;
                        
                        break;
                    }
                }
            }
            else
            {//replacement
                for(i = (key+1)%SIZE; i != key; i = (i+1)%SIZE)
                {
                    if(table[i].rno == -1)
                    {//empty position found
                        table[i] = table[key];
                        //update chain
                        w = tempkey;//0
                        x = table[tempkey].chain;
                        while(x != key)
                        {
                            w = x;//shadow
                            x = table[x].chain;
                        }
                        table[w].chain = i;
                        //place temp at its correct position
                        table[key] = temp;
                        break;
                    }
                }
            }
        }//else
    }    
    else
        printf("\n table is full ");
}

void viewAll(Student table[])
{
    int i;
    for(i =0; i< SIZE; i++)
    {
        printf("\n %3d %10s %3.2f %d", table[i].rno, table[i].name, table[i].percentage, table[i].chain);
    }
}

void search(Student table[])
{
    int r, key, flag, x;
    
    printf("\n Enter rno to search ");
    scanf("%d", &r);
    
    key = hash(r);
    
    if(table[key].rno == r)
    {//direct access
        printf("\n %3d %20s %3.2f", table[key].rno, table[key].name, table[key].percentage);
    }
    else
    { 
        //chain to search
        flag = 0;
        x = key;
        while(table[x].chain != -1)
        {
            x = table[x].chain;
            if(table[x].rno == r)
            {
                printf("\n %3d %20s %3.2f", table[x].rno, table[x].name, table[x].percentage);
                flag = 1;
                break;
            }
        }
    
        if(flag == 0)
            printf("\n Record with rno %d not found ", r);
    }//else
}//search

void modify(Student table[])
{
    int r, key, flag, x;
    
    printf("\n Enter rno to modify ");
    scanf("%d", &r);
    
    key = hash(r);
    
    if(table[key].rno == r)
    {//direct access
        printf("\n %3d %20s %3.2f", table[key].rno, table[key].name, table[key].percentage);
        printf("\n Enter new data ");
        printf("\n Name ");
        scanf("%19s", table[key].name);
        printf("\n Percentage ");
        scanf("%f", &table[key].percentage);        
                
    }
    else
    { 
        //chain to search and modify
        flag = 0;
        x = key;
        while(table[x].chain != -1)
        {
            x = table[x].chain;
            if(table[x].rno == r)
            {
                printf("\n %3d %20s %3.2f", table[x].rno, table[x].name, table[x].percentage);
                printf("\n Enter new data ");
                printf("\n Name ");
                scanf("%19s", table[x].name);
                printf("\n Percentage ");
                scanf("%f", &table[x].percentage);        
                flag = 1;
                break;
            }
        }
    
        if(flag == 0)
            printf("\n Record with rno %d not found ", r);
    }//else
}//modify

void deleteRecord(Student table[])
{
    int r, key, flag, x, w;
    
    printf("\n Enter rno to delete ");
    scanf("%d", &r);
    
    key = hash(r);
    
    if(table[key].rno == r)
    {//direct access
        printf("\n Deleting : %3d %20s %3.2f", table[key].rno, table[key].name, table[key].percentage);
        
        //check its chain for synonyms replacement
        if(table[key].chain != -1)
        {//record at pos chain will take its place
            x = table[key].chain;
            table[key] = table[x];
            //clear location x
            table[x].rno = -1;
            strcpy(table[x].name, "");
            table[x].percentage = 0;
            table[x].chain = -1;
        }
        else
        {//no synonym
            //clear location key
            table[key].rno = -1;
            strcpy(table[key].name, "");
            table[key].percentage = 0;
            table[key].chain = -1;
        }
    }
    else
    { 
        //chain to search and delete
        flag = 0;
        x = key;//0
        while(table[x].chain != -1)
        {
            w = x;//5
            x = table[x].chain;//4
            if(table[x].rno == r)
            {
                printf("\n Deleting %3d %20s %3.2f", table[x].rno, table[x].name, table[x].percentage);
                table[x].rno = -1;
                strcpy(table[x].name, "");
                table[x].percentage = 0;
                
                //update the chain
                table[w].chain = table[x].chain;
                table[x].chain = -1;
                
                flag = 1;
                break;
            }
        }
    
        if(flag == 0)
            printf("\n Record with rno %d not found ", r);
    }//else
}//delete


int main()
{
    Student table[SIZE];
    int ch;
    int flag = 1;
    
    initializeTable(table);
    
    do
    {
        printf("\n 1. Add Record ");
        printf("\n 2. Modify Record ");        
        printf("\n 3. Delete Record ");
        printf("\n 4. Search Record ");
        printf("\n 5. View All Record ");
        printf("\n 6. Exit ");
        printf("\n Enter Choice ");
        scanf("%d", &ch);
        
        switch(ch)
        {
            case 1: //add record
                addRecord(table);
                break;
            case 2: //modify record
                modify(table);
                break;
            case 3: //delete record
                deleteRecord(table);
                break;
            case 4: //search record
                search(table);
                break;
            case 5: //view all records
                viewAll(table);
                break;
            case 6: //exit
                flag = 0;
                break;
            default:
                printf("\n Wrong choice ");
                break;
        }//switch
    }while(flag == 1);
    
    return 0;
}

/*
A hash table is an array/file that
stores records based on their key 
values. 
 
A key value is calculated by applying 
a mathematical function on one of the 
records attributes. 
 
Next for storing or searching the record 
its key is used as an address. 
 
This process is termed as "hashing". 
 
Advantage of hashing is direct access. 
 
Challenge for hashing method
-------------------------- 
It must try to generate a unique
key per input attribute. 
 
In case it generates a duplicate 
key then two records tend to store 
at the same address. 
 
This event is termed as "collision". 
 
Collision is to be handled by some  
resolution technique. 
 
One of the collision resolution technique 
is "linear probing". 
 
 
 
 
 
 
 
 
 */