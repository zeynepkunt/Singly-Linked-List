#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Creating the struct
struct Student
{
    char name[50];
    char gender;
    struct Student * next;
};
struct Student * insertNode (char *name,char gender, struct Student * list)
{
    struct Student *s;
    //Allocate memory for node (mallocoperation)
    s = malloc (sizeof (struct Student));
    if (s == NULL)
    {
        printf ("Memory allocation failed.");
        return list;
    }
    strcpy(s->name, name);
    s->gender = gender;
    s->next = list; //list is the startof the list
    list = s;

    return list;
}

//merge the left side and right side
struct Student* mergeSort(struct Student* left1, struct Student* left2) {
    //control for empty list
    if (left1 == NULL) {
        return left2;
    }
    if (left2 == NULL) {
        return left1;
    }

    struct Student *mergedList;

    //conditions of head point for list
    if ( left1->gender < left2->gender || (left1->gender == left2->gender && left1->gender=='F' && strcmp(left1->name, left2->name)<0)) {
        mergedList = left1;
        left1 = left1->next;
    }
    else if ( left1->gender == left2->gender && left1->gender=='F' && strcmp(left1->name, left2->name)<0){
        mergedList = left2;
        left2 = left2->next;
    }
    else if ( left1->gender == left2->gender && left1->gender=='M' && strcmp(left1->name, left2->name)>0){
        mergedList = left1;
        left1 = left1->next;
    }
    else {
        mergedList = left2;
        left2 = left2->next;
    }


    // merging the remaining of lists
    struct Student *current = mergedList;
    while (left1 != NULL && left2 != NULL) {
        if ( left1->gender < left2->gender || (left1->gender == left2->gender && left1->gender=='F' && strcmp(left1->name, left2->name)<0)) {
            current->next = left1;
            left1 = left1->next;
        }
        else if ( left1->gender == left2->gender && left1->gender=='F' && strcmp(left1->name, left2->name)<0){
            current->next = left2;
            left2 = left2->next;
        }
        else if ( left1->gender == left2->gender && left1->gender=='M' && strcmp(left1->name, left2->name)>0){
            current->next = left1;
            left1 = left1->next;
        }else{
            current->next = left2;
            left2 = left2->next;
        }
        current = current->next;
    }

    // control for any of remaining nodes if the other one is empty
    if (left1 != NULL) {
        current->next = left1;
    } else {
        current->next = left2;
    }

    return mergedList;
}

//finding method for mid point of list
struct Student * findingMidPoint(struct Student *leftLast,struct Student *mid,struct Student *rightLast){
    while (rightLast!=NULL && rightLast->next!=NULL){//defining midpoint and ending points for left and right parts
        leftLast=mid;
        mid=mid->next;
        rightLast=rightLast->next->next;
    }
    leftLast->next=NULL;//dividing list
    return mid;
}

/*
 *  Ah/M -> Sed/M -> Mer/F -> Ays/F -> Meh/M -> Tug/F -> Ok/M -> Es/F -> Cey/F -> Cen/M
 *  Ah/M -> Sed/M    Mer/F -> Ays/F -> Meh/M    Tug/F -> Ok/M    Es/F -> Cey/F -> Cen/M
 *  Ah/M    Sed/M    Mer/F    Ays/F -> Meh/M    Tug/F    Ok/M    Es/F    Cey/F -> Cen/M
 *  Ah/M    Sed/M    Mer/F    Ays/F    Meh/M    Tug/F    Ok/M    Es/F    Cey/F    Cen/M
 */
//Sorting function
struct Student * sortList (struct Student *list){
    if(list==NULL||list->next==NULL){
        //if we have 1 or 2 nodes, we don't need to sort
        return list;
    }

    struct Student *leftLast=list;
    struct Student *mid=list;
    struct Student *rightLast=list;

    mid=findingMidPoint(leftLast,mid,rightLast);

    //to control starting points
    //printf ("%s\t%c\n", list->name, list->gender);
    //printf ("%s\t%c\n", mid->name, mid->gender);

    struct Student* left= sortList(list);//starting point of left part
    struct Student* right=sortList(mid);//starting point of right part
    return mergeSort(left,right);
}

//Printing function
void printList (struct Student * list)
{
    while (list != NULL)
    {
        printf ("%s\t%c\n", list->name, list->gender);
        list = list->next;
    }
}

int main ()
{
    //Creating an Initial Node Variable
    struct Student * head=NULL;
    //Call to functions
    head = insertNode("Cenk", 'M', head);
    head = insertNode("Ceyda", 'F', head);
    head = insertNode("Esra", 'F', head);
    head = insertNode("Okan", 'M', head);
    head = insertNode("Tugce", 'F', head);
    head = insertNode("Mehmet", 'M', head);
    head = insertNode("Ayse", 'F', head);
    head = insertNode("Merve", 'F', head);
    head = insertNode("Sedat", 'M', head);
    head = insertNode("Ahmet", 'M', head);
    //call to sorting function
    head = sortList(head);
    printList(head);
}
