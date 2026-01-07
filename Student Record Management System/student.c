//header Files
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

// student informations
struct student_info
{
    char stu_firstname[50];
    char stu_middlename[50];
    char stu_lastname[50];

    char stu_fathername[100];
    char stu_mothername[100];
    char stu_father_occu[50];
    char stu_mother_occu[50];

    char stu_dob[11];                              // DD/MM/YYYY
    char stu_gender;                               // M / F / O
    char stu_caste[20];
    
    char stu_email[100];                           // Should contain "@gmail.com"
    char stu_mobile_number[15];   
    char stu_father_number[15];
    
    char stu_street[50];
    char stu_area[50];
    char stu_city[50];
    char stu_state[50];
    int stu_zipcode;                               // Only 6 Digits

    // Auto Generate Items

    int Stu_registration_number;                   // Auto Generate From 1000
    char Stu_School_email[100];                    // Auto Generate By Combining firstname + lastname + registration_number + "@cprojects.com"

};

// Dashboard (Main Menu)

void main_menu(){
    printf("\n=========================================================\n");
    printf("                  School Managment School                  \n");
    printf("\n=========================================================\n");
    printf("1. Student Dashboard\n");
    printf("2. Teacher Dashboard\n");
    printf("3. Parent Dashboard\n");
    printf("4. Exit\n");
}

// Student Dashboard

void student_dashboard(){
    printf("\n=========================================================\n");
    printf("                     Student Dashboard                     \n");
    printf("\n=========================================================\n");
    printf("1. Add Student Personal Details");
    printf("2. Add Academic Details\n");
    printf("3. Update Student Information\n");
    printf("4. View All Students\n");
    printf("5. View Courses & Teachers Assigned\n");
    printf("6. Search Student\n");
    printf("7. Sort Student Records\n");
    printf("8. View Student Result\n");
    printf("9. Count Total Students\n");
    printf("10. Delete Student Record\n");
    printf("11. Exit\n");
}

// Check Int Input in optoin choose

int readInt(int *var){
    if (scanf("%d",var)!=1)
    {
        printf("Invalid option! Please enter a number.\n");
        while (getchar() != '\n');                  // Clear Buffer
        return 0;                                   // Failure
    }
    return 1;                                       // Success
}

// Student Feature Select

void student_features(int feature_choice){
    switch (feature_choice)
    {
    case 1:
        add_student_personal_info();
        break;
    case 2:
        add_student_academic_info();
        break;
    case 3:
        update_student_info();
        break;
    case 4:
        view_all_students();
        break;
    case 5:
        view_course_teacher();
        break;
    case 6:
        search_student();
        break;
    case 7:
        sort_student_record();
        break;
    case 8:
        view_student_result();
        break;
    case 9:
        count_total_student();
        break;
    case 10:
        delete_student();
        break;
    case 11:
        printf("Exiting....\n");
        break;
    default:
        printf("Invalid Choice! Try Again.\n");
        break;
    }
}


// Main Function
int main(){
    int dashboard_option,student_option;
    while (dashboard_option!=4)
    {

        // Calling main Dashboard Function
        main_menu();
        printf("Enter Dashboard (1,2,3,4) : ");
        
        // Invalid Option Check

        if (!readInt(&dashboard_option))
        {
            continue;
        }

        // Switch Case to Select Dashboard
        
        switch (dashboard_option)
        {
        case 1:
        // Calling Student Dashboard
            student_dashboard();

            printf("Enter your choice = ");

            // Invalid Option Check

            if (!readInt(&student_dashboard))
            {
                continue;
            }
            while (student_dashboard!=11)
            {
                student_Features(student_dashboard);
            }
            
            break;
        case 2:
            teacher_dashboard();
            break;
        case 3:
            parent_dashboard();
            break;
        case 4:
            printf("Exiting....\n");
            exit(0);
            break;
        default:
            printf("Invalid Choice! Try Again.\n");
            break;
        }
    }
    return 0;
}