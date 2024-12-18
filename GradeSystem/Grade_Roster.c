/*
    This program simulates a grading system for students.
    It allows users to perform various operations on student grades, 
    such as loading default scores, printing a grade table, 
    retrieving grades for a specific student or exam, and managing grade updates.

    Features:
    - Load default scores for students and exams using 'load_default'.
    - Display a complete grade table with 'print_table'.
    - Print grades for a specific student with 'print_student' or for a specific exam using 'print_exam'.
    - Alert users about all grades below a threshold for a specific exam with 'grade_alert_all'.
    - Add a specific value to all grades in an exam with 'add_value'.
    - Replace a specific student's grade for an exam with 'replace'.
    
    With these options, users, such as teachers, can effectively view and manage student grades.
*/

#include <stdio.h>

#define MAX_STUDENTS 10
#define MAX_EXAMS 4

void load_default(int st_no, int exam_no, int scores[][MAX_EXAMS]);
void print_table(int st_no, int exam_no, int scores[][MAX_EXAMS]);
void print_student(int stID, int st_no, int exam_no, int scores[][MAX_EXAMS]);
void print_exam(int examID, int st_no, int exam_no, int scores[][MAX_EXAMS]);
void grade_alert_all(int exam_ID, int st_no, int exam_no, int scores[][MAX_EXAMS]);
void add_value(int exam_ID, int value, int st_no, int exam_no, int scores[][MAX_EXAMS]);
void replace(int st_ID, int exam_ID, int new_grade, int st_no, int exam_no, int scores[][MAX_EXAMS]);

int main(){
    int scores[MAX_STUDENTS][MAX_EXAMS];  // This array would be used often to pass data
    int num_st = MAX_STUDENTS;
    int num_exams = MAX_EXAMS;
    int choice=-1, st_ID=-1, exam_ID=-1,value=-1,new_grade=-1;
    
    printf("This program simulates a grade roster for 10 students with 4 exams.\n");
    do{
        printf("\n0-exit\n");
        printf("1-load\n");
        printf("2-print all\n");
        printf("3-print student info (given studentID, prints all exam grades and average exam grade)\n");
        printf("4-print by exam (give Exam ID, prints all grades for this exam)\n");
        printf("5-low grade alert (give exam ID, prints all students who have below 60 in this exam\n");
        printf("6-add value (given exam ID and value to be added, adds that value to that exam for all students)\n");
        printf("7-replace (given exam ID, student ID and new grade, replaces the old grade with the new one)\n");
        printf("\n---Enter your choice: ");
        scanf("%d", &choice);
        switch (choice){
        case 0: break;
        case 1:
            load_default(num_st, num_exams, scores);
            printf("The data was successfully loaded.\n");
            break;
        case 2:
            print_table(num_st, num_exams, scores);
            break;
        case 3:
            printf("Please enter the student ID (0-%d): ", num_st-1);
            scanf("%d", &st_ID);
            print_student(st_ID, num_st, num_exams, scores);
            break;
        case 4:
            printf("Please enter the exam ID(1-%d):",num_exams);
            scanf("%d",&exam_ID);
            print_exam(exam_ID, num_st, num_exams, scores);
            break;
        case 5:
            printf("Please enter the exam ID (1-%d):",num_exams);
            scanf("%d",&exam_ID);
            grade_alert_all(exam_ID ,num_st ,num_exams ,scores);
            break;
        case 6:
            printf("Please enter the exam ID and the value to be added:");
            scanf("%d%d",&exam_ID,&value);
            add_value(exam_ID, value, num_st, num_exams, scores);
            break;
        case 7:
            printf("Please enter studentID, examID and new grade (in this order):");
            scanf("%d%d%d",&st_ID,&exam_ID,&new_grade);
            replace(st_ID, exam_ID, new_grade, num_st, num_exams, scores);
            break;
        default:
            printf("Invalid choice.\n");
        }
    } while (choice!=0);
    printf("\nGood bye!\n");
    return 0;
}

void load_default(int st_no, int exam_no, int scores[][MAX_EXAMS]){ // These are hardcoded values, in pratice we should obtain
    int hardcoded[MAX_STUDENTS][MAX_EXAMS] = {                     // student grade from Database or when user upload new grades
                            {58, 67, 0, 0},
                            {72, 67, 56, 65},
                            {65, 50, 20, 30},
                            {62, 48, 80, 32},
                            {35, 0, 0, 0},
                            {89, 60, 90, 86},
                            {67, 70, 96, 100},
                            {100, 90, 66, 100},
                            {100, 59, 100, 97},
                            {70, 89, 34, 79}
                            };
    int st, exam;
    for(st=0; st<st_no; st++){
        for(exam=0; exam<exam_no; exam++){
            scores[st][exam] = hardcoded[st][exam];
        }
    }
}

void print_table(int st_no, int exam_no, int scores[][MAX_EXAMS]){ // The print tabel would be handle by front end and UI design for 
    int b=0,c=1,d=2,e=3;                                          //  better user experience 
        printf("---------------------------------------\n");
        printf("|stID | Exam1 | Exam2 | Exam3 | Exam4 |\n");
        printf("---------------------------------------\n");
    for(st_no=0;st_no<MAX_STUDENTS;st_no++){
        printf("|%4d |%6d |%6d |%6d |%6d |\n",st_no, scores[st_no][b],scores[st_no][c],scores[st_no][d],scores[st_no][e]);
        printf("----------------------------------------\n");
    }
}

void print_student(int stID, int st_no, int exam_no, int scores[][MAX_EXAMS]){
    float avg;
    printf("---------------------------------------\n");
    printf("|stID | Exam1 | Exam2 | Exam3 | Exam4 |\n");
    printf("---------------------------------------\n");
    printf("|%4d |%6d |%6d |%6d |%6d |\n",stID, scores[stID][0],scores[stID][1],scores[stID][2],scores[stID][3]);
    printf("---------------------------------------\n");
    float total=scores[stID][0]+scores[stID][1]+scores[stID][2]+scores[stID][3];
    avg=total/4;
    printf("Average Exam Score:%.2f",avg);
}

void print_exam(int examID, int st_no, int exam_no, int scores[][MAX_EXAMS]){
    int R;
    printf("|Exam%d grades:\n",examID);
    printf("|stID | Exam%d |\n",examID);
    for(R=0;R<MAX_STUDENTS;R++){
        printf("|%4d |%6d |\n",R,scores[R][examID-1]);
    }

}

void grade_alert_all(int exam_ID, int st_no, int exam_no, int scores[][MAX_EXAMS]){ // This section would allow
    int S,F;                                                                       // teachers to monitor student performance
    printf("Exam %d ALERT grades lower than 60:\n",exam_ID);
    printf("|stID| Exam%d|\n",exam_ID);
    for(S=0;S<st_no;S++){
        F=scores[S][exam_ID-1];
        if(F<60){
            printf("|%4d|%6d|\n",S,scores[S][exam_ID-1]);
        }
    }
}

void add_value(int exam_ID, int value, int st_no, int exam_no, int scores[][MAX_EXAMS]){
    int old;
    printf("Exam%d change all grades by adding %d\n",exam_ID,value);
    printf("|stID |  old  |  new  |\n");
    for(int old=0;old<st_no;old++){
        printf("|%4d |%6d |",old,scores[old][exam_ID-1]); //print the old score before updating them
        int Gra=scores[old][exam_ID-1]; // -1 exam to obtain the correct place holder array for exam ID 
            Gra=Gra+value;
            printf("%6d |\n",Gra);
        scores[old][exam_ID-1]=Gra; // update complete, next student
    }
}

void replace(int st_ID, int exam_ID, int new_grade, int st_no, int exam_no, int scores[][MAX_EXAMS]){ // This function specefially selects a student and
    int A;                                                                                           // chances their specefic exam grade
    A=scores[st_ID][exam_ID-1];
    A=A+new_grade;
    scores[st_ID][exam_ID-1]=A;
}