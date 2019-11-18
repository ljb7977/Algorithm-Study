#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "customer_manager.h"

#define UNIT_ARRAY_SIZE 1024

enum {HASH_MULTIPLIER = 65599};

struct UserInfo
{
    char *name;                // customer name
    char *id;                  // customer id
    int purchase;              // purchase amount (> 0)
    struct UserInfo *next;     // point to next node
};

typedef struct hashtable
{
    int curArrSize;                 //current size of Hashtable
    const struct UserInfo **pHarray;  //address of Hashtable array
} Hashtable;

typedef Hashtable* Hash_T;

struct DB
{
    Hash_T h_name;             // id of hashtable
    Hash_T h_id;               // name of hashtable
    int numItems;              // # of stored items, needed to determine
    // # whether the array should be expanded
    // # or not
};

/*--------------------------------------------------------------------*/
Hash_T
Create_HashTable(void)
{
    //Create HashTable
    Hash_T t;

    t = (Hash_T) calloc(1, sizeof(Hash_T));
    if (t == NULL)
    {
        fprintf(stderr, "Can't allocate a memory for Hash_T\n");
        return NULL;
    }
    t->curArrSize = UNIT_ARRAY_SIZE; // start with 1024 elements
    t->pHarray = (struct UserInfo **)calloc(t->curArrSize,
                                            sizeof(struct UserInfo*));
    if (t->pHarray == NULL)
    {
        fprintf(stderr, "Can't allocate a memory for array of size %d\n",
                t->curArrSize);
        free(t);
        return NULL;
    }
    return t;
}
/*--------------------------------------------------------------------*/

static int hash_function(const char *pcKey, int iBucketCount)

/* Return a hash code for pcKey that is between 0 and iBucketCount-1,
   inclusive. Adapted from the EE209 lecture notes. */
{
    int i;
    unsigned int uiHash = 0U;
    for (i = 0; pcKey[i] != '\0'; i++)
        uiHash = uiHash * (unsigned int)HASH_MULTIPLIER
                 + (unsigned int)pcKey[i];
    return (int)(uiHash % (unsigned int)iBucketCount);
}

int table_expand(DB_T d)
{
    struct UserInfo **new_h_name_array;
    struct UserInfo **new_h_id_array;
    struct UserInfo * p;
    int i;
    int h;

    int newSize = d->h_name->curArrSize * 2;
    //printf("newsize :%d\n", newSize);
    if(d->h_name->curArrSize > 1000000)
        return 0;

    new_h_name_array = (struct UserInfo **)calloc(newSize, sizeof(struct UserInfo*));
    if(new_h_name_array == 0){
        return 0;
    }
    new_h_id_array = (struct UserInfo **)calloc(newSize, sizeof(struct UserInfo*));
    if(new_h_id_array == 0){
        free(new_h_name_array);
        return 0;
    }


    for(i = 0; i<d->h_name->curArrSize; i++){
        for(p = d->h_name->pHarray[i]; p != NULL; p = d->h_name->pHarray[i]){
            d->h_name->pHarray[i] = p->next;
            h = hash_function(p->name, newSize);

            p->next = new_h_name_array[h];
            new_h_name_array[h] = p;
        }
    }
    free(d->h_name->pHarray);

    for(i = 0; i<d->h_id->curArrSize; i++){
        for(p = d->h_id->pHarray[i]; p != NULL; p = d->h_id->pHarray[i]){
            d->h_id->pHarray[i] = p->next;
            h = hash_function(p->id, newSize);

            p->next = new_h_id_array[h];
            new_h_id_array[h] = p;
        }
    }
    free(d->h_id->pHarray);

    //printf("newsize :%d\n", newSize);
    d->h_id->pHarray = new_h_id_array;
    d->h_name->pHarray = new_h_name_array;
    d->h_id->curArrSize = newSize;
    d->h_name->curArrSize = newSize;
    return 1;
}

/*--------------------------------------------------------------------*/
DB_T
CreateCustomerDB(void)
{
    DB_T d;

    d = (DB_T) calloc(1, sizeof(struct DB));
    if (d == NULL){
        fprintf(stderr, "Can't allocate a memory for DB_T\n");
        return NULL;
    }

    d->h_id = Create_HashTable();
    if (d->h_id == NULL){
        free(d->h_id);
        return NULL;
    }

    d->h_name = Create_HashTable();
    if (d->h_name == NULL){
        free(d->h_id);
        free(d->h_name);
        return NULL;
    }
    return d;
}
/*--------------------------------------------------------------------*/

void
DestroyCustomerDB(DB_T d)
{
    /* fill out this function */
    struct UserInfo *p;
    struct UserInfo *nextp;
    struct UserInfo *q;
    struct UserInfo *nextq;

    int i;

    for (i=0; i < d->h_id->curArrSize ; i++){
        for (p=(struct UserInfo**)(d->h_id->pHarray[i]); p!=NULL; p=nextp){
            nextp = p->next;
            free(p);
        }
    }

    for (i=0; i < d->h_name->curArrSize; i++){
        for ( q=(struct UserInfo**)(d->h_name->pHarray[i]); q!=NULL; q=nextq){
            nextq = q->next;
            free(q);
        }
    }

    free(d->h_id);
    free(d->h_name);
    free(d);

    /*as mentioned in ch10_DsAlg_ppt*/
}
/*--------------------------------------------------------------------*/
int
RegisterCustomer(DB_T d, const char *id,
                 const char *name, const int purchase)
{
    /* fill out this function */
    int h1;
    int h2;
    struct UserInfo *p;
    struct UserInfo *q;

    struct UserInfo *New_user;

    if (id == NULL)
        return (-1);

    if (name == NULL)
        return (-1);

    if (purchase <= 0)
        return(-1);

    h1 = hash_function(id, d->h_id->curArrSize);
    h2 = hash_function(name, d->h_name->curArrSize);
    for (p = d->h_id->pHarray[h1]; p != NULL; p = p->next){
        if (strcmp(p->id, id) == 0)
            return (-1);
    }

    for (p = d->h_name->pHarray[h2]; p != NULL; p = p->next)
    {
        if (strcmp(p->name,name) == 0)
            return(-1);
    }

    New_user = (struct UserInfo*)malloc(sizeof(struct UserInfo));

    New_user->name = strdup(name);
    New_user->id = strdup(id);
    New_user->purchase = purchase;
    New_user->next = NULL;

    if(d->h_id->pHarray[h1] == NULL){
        d->h_id->pHarray[h1] = New_user;
    } else {
        for (p = d->h_id->pHarray[h1]; p->next != NULL; p = p->next);
        p->next = New_user;
    }

    New_user = (struct UserInfo*)malloc(sizeof(struct UserInfo));

    New_user->name = strdup(name);
    New_user->id = strdup(id);
    New_user->purchase = purchase;
    New_user->next = NULL;

    if(d->h_name->pHarray[h2] == NULL){
        d->h_name->pHarray[h2] = New_user;
    } else {
        for (q = d->h_name->pHarray[h2]; q->next != NULL; q = q->next);
        q->next = New_user;
    }

    d->numItems++;
    //Extra Credit...?
    if(d->numItems >= 0.75*(d->h_id->curArrSize) && d->h_id->curArrSize < 1000000){
        table_expand(d);
        //printf("newsize :%d\n", d->h_id->curArrSize);
    }
    return 0;
}
/*--------------------------------------------------------------------*/
int
UnregisterCustomerByID(DB_T d, const char *id)
{
    /* fill out this function */
    int h1;
    int h2;

    struct UserInfo *p;
    struct UserInfo *prev;
    struct UserInfo *temp1;
    struct UserInfo *q;
    struct UserInfo *temp2;

    char *pname;

    if (d == NULL)
        return (-1);

    if (id == NULL)
        return (-1);

    h1 = hash_function(id, d->h_id->curArrSize);
    p = d->h_id->pHarray[h1];
    if(p == NULL)
        return (-1);

    if(strcmp(p->id, id) == 0){
        d->h_id->pHarray[h1] = p->next;
        pname = strdup(p->name);
        free(p->id);
        free(p->name);
        free(p);

        h2 = hash_function(pname, d->h_name->curArrSize);
        q = d->h_name->pHarray[h2];
        if(strcmp(q->name, pname) == 0){  // if the first element should be deleted
            d->h_name->pHarray[h2] = q->next;
            free(q->name);
            free(q->id);
            free(q);
            free(pname);
            d->numItems--;
            return 0;
        }
        prev = d->h_name->pHarray[h2];
        for(q = d->h_name->pHarray[h2]->next; q != NULL; q = q->next){
            if(strcmp(q->name, pname) == 0){
                prev->next = q->next;
                free(q->name);
                free(q->id);
                free(q);
                free(pname);
                d->numItems--;
                return 0;
            }
        }
    }
    prev = d->h_id->pHarray[h1];
    for (p = d->h_id->pHarray[h1]->next; p != NULL; p = p->next){
        if (strcmp(p->id, id) == 0){
            prev->next = p->next;
            pname = strdup(p->name);
            free(p->id);
            free(p->name);
            free(p);

            h2 = hash_function(pname, d->h_name->curArrSize);
            if(strcmp(q->name, pname) == 0)   // if the first element should be deleted
            {
                d->h_name->pHarray[h2] = q->next;
                free(q->name);
                free(q->id);
                free(q);
                free(pname);
                d->numItems--;
                return 0;
            }
            prev = d->h_name->pHarray[h2];
            for(q = d->h_name->pHarray[h2]->next; q != NULL; q = q->next){
                if(strcmp(q->name, pname) == 0){
                    prev->next = q->next;
                    free(q->name);
                    free(q->id);
                    free(q);
                    free(pname);
                    d->numItems--;
                    return 0;
                }
            }
        }
    }
    return (-1);
}

/*--------------------------------------------------------------------*/
int
UnregisterCustomerByName(DB_T d, const char *name)
{
    /* fill out this function */
    int h1;
    int h2;

    struct UserInfo *p;
    struct UserInfo *prev;
    struct UserInfo *temp1;
    struct UserInfo *q;
    struct UserInfo *temp2;

    char *pid;

    if (d == NULL)
        return (-1);

    if (name == NULL)
        return (-1);

    h2 = hash_function(name, d->h_name->curArrSize);
    p = d->h_name->pHarray[h2];
    if(p == NULL)
        return (-1);

    if(strcmp(p->name, name) == 0){
        d->h_name->pHarray[h2] = p->next;
        pid = strdup(p->id);
        free(p->id);
        free(p->name);
        free(p);

        h1 = hash_function(pid, d->h_id->curArrSize);
        q = d->h_id->pHarray[h1];
        if(strcmp(q->id, pid) == 0){  // if the first element should be deleted
            d->h_id->pHarray[h1] = q->next;
            free(q->name);
            free(q->id);
            free(q);
            free(pid);
            d->numItems--;
            return 0;
        }
        prev = d->h_id->pHarray[h1];
        for(q = d->h_id->pHarray[h1]->next; q != NULL; q = q->next){
            if(strcmp(q->id, pid) == 0){
                prev->next = q->next;
                free(q->name);
                free(q->id);
                free(q);
                free(pid);
                d->numItems--;
                return 0;
            }
        }
    }
    prev = d->h_name->pHarray[h2];
    for (p = d->h_name->pHarray[h2]->next; p != NULL; p = p->next){
        if (strcmp(p->name, name) == 0){
            prev->next = p->next;
            pid = strdup(p->id);
            free(p->id);
            free(p->name);
            free(p);

            h1 = hash_function(pid, d->h_id->curArrSize);
            if(strcmp(q->id, pid) == 0)   // if the first element should be deleted
            {
                d->h_id->pHarray[h1] = q->next;
                free(q->name);
                free(q->id);
                free(q);
                free(pid);
                d->numItems--;
                return 0;
            }
            prev = d->h_id->pHarray[h1];
            for(q = d->h_id->pHarray[h1]->next; q != NULL; q = q->next){
                if(strcmp(q->id, pid) == 0){
                    prev->next = q->next;
                    free(q->name);
                    free(q->id);
                    free(q);
                    free(pid);
                    d->numItems--;
                    return 0;
                }
            }
        }
    }
    return (-1);
}
/*--------------------------------------------------------------------*/
int
GetPurchaseByID(DB_T d, const char* id)
{
    /* fill out this function */
    int h;
    struct UserInfo *p;

    if (d == NULL)
        return (-1);

    if (id == NULL)
        return (-1);

    h = hash_function(id, d->h_id->curArrSize);

    for (p = (struct UserInfo**)(d->h_id->pHarray[h]); p != NULL; p = p->next){
        if (strcmp(p->id, id) == 0){
            return p->purchase;
        }
    }

    return (-1);
}
/*--------------------------------------------------------------------*/
int
GetPurchaseByName(DB_T d, const char* name)
{
    /* fill out this function */
    int h;

    struct UserInfo *p;

    if (d == NULL)
        return (-1);

    if (name == NULL)
        return (-1);

    h = hash_function(name, d->h_name->curArrSize);

    for (p = (struct UserInfo**)(d->h_name->pHarray[h]); p != NULL; p = p->next){
        if (strcmp(p->name, name) == 0){
            return p->purchase;
        }
    }

    return (-1);
}
/*--------------------------------------------------------------------*/
int
GetSumCustomerPurchase(DB_T d, FUNCPTR_T fp)
{
    /* fill out this function */
    int i;
    int sum=0;

    struct UserInfo *p;

    if (d == NULL)
        return (-1);

    if (fp == NULL)
        return (-1);

    for(i=0; i < d->h_id->curArrSize; i++){
        for(p=d->h_id->pHarray[i] ; p!=NULL; p=p->next){
            sum+=fp(p->id, p->name, p->purchase);
        }
    }
    return sum;
}

