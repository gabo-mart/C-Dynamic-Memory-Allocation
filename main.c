#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum subject {SER=0, EGR, CSE, EEE};

struct Course {
    int course_num;
    int credit_hours;
    enum subject sub;
    char teacher[256];
};
// forward declarations
void course_insert();
void schedule_print();
void course_drop();

// Global Variables
struct Course* CourseCollection = NULL;
int courseCounter = 0;
int totalCredits = 0;


// entry point
int main() {
    char input;


    printf("Welcome to ASU Class Schedule\n");
    do {
        printf("Menu Options\n");
        printf("--------------------------------\n");
        printf("a: Add a class\n");
        printf("d: Drop a class\n");
        printf("s: Show your classes\n");
        printf("q: Quit\n");
        printf("\n Total Credits: %d\n", totalCredits);
        printf("\nPlease enter a choice ---> ");
        scanf(" %c", &input);
        switch(input){
            case 'a' :
                course_insert();
                break;
            case 'd' :
                course_drop();
                break;
            case 's' :
                schedule_print();
                break;
            default :
                break;
        }
    }while(input != 'q');
    free(CourseCollection);
    return 0;
}


// additional functions for the program

// adds courses to the collection and keeps them sorted by course number
void course_insert(){
    struct Course* course;
    if(courseCounter == 0) {
        course = (struct Course *) malloc(sizeof(struct Course));
        CourseCollection = course;
    } else {
        course = (struct Course*)realloc(CourseCollection, (courseCounter + 1)*sizeof(struct Course));
        CourseCollection = course;
    }
    printf("What is the subject? (SER=0, EGR=1, CSE=2, EEE=3)\n");
    scanf("%d", &course[courseCounter].sub);
    printf("What is the number (e.g. 240)?\n");
    scanf("%d", &course[courseCounter].course_num);
    printf("How many credits is the class (e.g. 3)?\n");
    scanf(" %d", &course[courseCounter].credit_hours);
    totalCredits += course[courseCounter].credit_hours;
    printf("What is the name of the teacher?\n");
    scanf(" %s", course[courseCounter].teacher);

    courseCounter++;
}

// display the contents of the CourseCollection array with Subject Number Credits Teacher
// use a switch statement here
void schedule_print() {
    int i;
    printf("Class Schedule: \n");
    for(i = 0; i < courseCounter; i++) {
        char subj[4];
        switch(CourseCollection[i].sub) {
            case 0 :
                strcpy(subj, "SER");
                break;
            case 1 :
                strcpy(subj, "EGR");
                break;
            case 2 :
                strcpy(subj, "CSE");
                break;
            case 3 :
                strcpy(subj, "EEE");
                break;
        }
        printf("\n%s%d\t%d\t%s", subj, CourseCollection[i].course_num, CourseCollection[i].credit_hours, CourseCollection[i].teacher);
    }
    printf("\n\n");
}


// remove a course from Course Collection
void course_drop() {
    int course_number, course_index = -1;
    printf("\nEnter the course number of the course that you would like to drop:\n");
    scanf("%d", &course_number);

    // search through the CourseCollection to see if the input course number was found
    for(int i = 0; i < courseCounter; i++){
        if(CourseCollection[i].course_num == course_number) {
            course_index = i;
        }
    }
    if(course_index != -1) {
        totalCredits -= CourseCollection[course_index].credit_hours;
        for (int j = course_index; j < courseCounter - 1; j++) {
            CourseCollection[j] = CourseCollection[j + 1];
        }
        courseCounter--;
        (struct Course *) realloc(CourseCollection, (courseCounter) * sizeof(struct Course));
    } else {
        printf("\nClass not found!\n");
    }

}
