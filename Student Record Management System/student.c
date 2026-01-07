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

// Gennerate Registration Number

int generate_registration_number(){
    FILE *fp;
    struct student_info st_info;

    fp = fopen("Student_information.dat", "rb");

    // If File not exist -> First Student
    if (fp==NULL)
    {
        return 1000;
    }
    
    // Go To End of File
    fseek(fp, 0 , SEEK_END);

    // If File Is Empty
    if (ftell(fp) == 0) {
        fclose(fp);
        return 1000;
    }

    // Move pointer to last student record
    fseek(fp, -sizeof(struct student_info), SEEK_END);

    // Read last student
    fread(&st_info, sizeof(struct student_info), 1, fp);

    //Close File
    fclose(fp);

    return st_info.Stu_registration_number+1;
}

// Function For required Inputs

void readrequiredstring(const char *msg, char *str, int size) {
    do {
        printf("%s", msg);
        fgets(str, size, stdin);

        // remove newline character
        str[strcspn(str, "\n")] = '\0';

        if (strlen(str) == 0) {
            printf("This field is required. Please enter a value.\n");
        }

    } while (strlen(str) == 0);
}

// Function For Optional Inputs

void readoptionalstring(const char *msg, char *str, int size) {
    printf("%s", msg);
    fgets(str, size, stdin);

    // remove newline character
    str[strcspn(str, "\n")] = '\0';
}

// Checks Gender

void readgender(char *msg, char *str){
    
    // To Check the Full input string
    char input[10];

    do {
        printf("%s", msg);
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';

        if (strlen(input) == 1) {

            //Make The Character Uppercase
            char g = toupper(input[0]);

            if (g == 'M' || g == 'F' || g == 'O') {
                *str = g;
                return;
            }
        }

        printf("Invalid input! Enter M (Male), F (Female), or O (Other).\n");

    } while (1);
}

// Checks Gender

void readgender(char *msg, char *str, int size){
    while (1)
    {
        printf("%s", msg);

        if (fgets(str, size, stdin) == NULL)
            continue;

        // Remove newline
        str[strcspn(str, "\n")] = '\0';

        // Convert to uppercase
        for (int i = 0; str[i] != '\0'; i++) {
            str[i] = toupper((unsigned char)str[i]);
        }

        // Validate caste
        if (strcmp(str, "GEN") == 0 ||
            strcmp(str, "OBC") == 0 ||
            strcmp(str, "SC")  == 0 ||
            strcmp(str, "ST")  == 0)
        {
            return;   // valid input → exit function
        }

        printf("Invalid caste! Please enter Gen, OBC, SC or ST.\n");
    }
    
}

// Add Student Personal Info

void add_student_personal_info(){
    FILE *fp;
    struct student_info st_in;
    int ch;

    // clear buffer safely
    while ((ch = getchar()) != '\n' && ch != EOF);

    // Registration Number
    st_in.Stu_registration_number = generate_registration_number();

    readrequiredstring("Enter First Name : ", st_in.stu_firstname,sizeof(st_in.stu_firstname));             // Enter First Name
    readoptionalstring("Enter Middle Name : ",st_in.stu_middlename,sizeof(st_in.stu_middlename));           // Enter Middle Name
    readrequiredstring("Enter Last Name : ",st_in.stu_lastname,sizeof(st_in.stu_lastname));
    readrequiredstring("Enter Father's Name : ",st_in.stu_fathername,sizeof(st_in.stu_fathername));
    readrequiredstring("Enter Mother's Name : ",st_in.stu_mothername,sizeof(st_in.stu_mothername));
    readrequiredstring("Enter Father's Occupation : ",st_in.stu_father_occu,sizeof(st_in.stu_father_occu));
    readrequiredstring("Enter Mother's Occupation : ",st_in.stu_mother_occu,sizeof(st_in.stu_mother_occu));
    readrequiredstring("Enter D.O.B (DD/MM/YYYY): ",st_in.stu_dob,sizeof(st_in.stu_dob));
    readgender("Enter Gender (M/F/O) : ",st_in.stu_gender);
    readcaste("Enter Caste (Gen/OBC/SC/ST) : ",st_in.stu_caste,sizeof(st_in.stu_caste));
}

// Student Feature Select

void student_features(int feature_choice){
    switch (feature_choice)
    {
    case 1:
        add_student_personal_info();                // Add Student Personal Information
        break;
    case 2:
        add_student_academic_info();                // Add Student Academic Information
        break;
    case 3:
        update_student_info();                      // Update Student Information
        break;
    case 4:
        view_all_students();                        // View All Students
        break;
    case 5:
        view_course_teacher();                      // View Course and Teacher Enrolled of a Student
        break;
    case 6:
        search_student();                           // Search Student according to - id, Registration number, gmail, name etc.
        break;
    case 7:
        sort_student_record();                      // Sort all Student Details by name, registration number, etc.
        break;
    case 8:
        view_student_result();                      // View Student Result
        break;
    case 9:
        count_total_student();                      // View number of students in school, class and section
        break;
    case 10:
        delete_student();                           // Delete Student Detail
        break;
    case 11:
        printf("Exiting....\n");                    // Exit Student Feature
        break;
    default:
        printf("Invalid Choice! Try Again.\n");     // Invalid Choice
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