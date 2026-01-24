// header Files
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

// Subejct Deatils

#define MAX_SUBJECTS 10
#define SUBJECT_LEN 30

#define MAX_BEFORE_DIVIDE 40
#define MAX_AFTER_DIVIDE 30
#define SHIFT_COUNT 10

#define MAX_CLASSES 3
#define MAX_SUBJECT_TEACH 4
#define MAX_TEACHERS 200

int LAST_FOUND_REGISTRATION = -1;

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

    char stu_dob[11];    // DD/MM/YYYY
    char stu_gender[10]; // M / F / O
    char stu_caste[20];

    char stu_email[100]; // Should contain "@gmail.com"
    char stu_mobile_number[15];
    char stu_father_number[15];

    char stu_street[50];
    char stu_area[50];
    char stu_city[50];
    char stu_state[50];
    int stu_zipcode; // Only 6 Digits

    // Auto Generate Items

    int Stu_registration_number; // Auto Generate From 1000
    char Stu_School_email[100];  // Auto Generate By Combining firstname + lastname + registration_number + "@cprojects.com"
};

// Student Acaedmic Data

struct student_academic_information
{
    int stu_registration_number; // Student Registration Number

    int stu_class;    // Student Current Class
    char stu_section; // Student Class Section
    int stu_section_count;
    char stream[10]; // Stream of student only if the class is greater than 10

    int stu_subject_count;                        // Number of subject Enrolled
    char stu_subjects[MAX_SUBJECTS][SUBJECT_LEN]; // Subjects Enrolled to student
    int stu_subject_numbers[MAX_SUBJECTS];

    float stu_last_percentage; // Last Year Percentage
    char stu_last_school[100]; // Last School Name

    char stu_last_address_street[100]; // Last School Street Name When Not Same
    char stu_last_address_area[100];   // Last School Area Name When Not Same
    char stu_last_address_city[100];   // Last School City Name When Not Same
    char stu_last_address_state[100];  // Last School State Name When Not Same

    char stu_last_session_year[10]; // Last Session Year in 'YYYY-YYYY' Format
    char stu_academic_year[10];     // Current Session Year in 'YYYY-YYYY' Foramt
};

// Teacher Information

struct teacher_info
{
    char teach_firstname[50];
    char teach_middlename[50];
    char teach_lastname[50];

    char teach_email[100]; // Should contain "@gmail.com"
    char teach_mobile_number[15];

    char teach_DOB[11];    // DD/MM/YYYY
    char teach_gender[10]; // M / F / O
    char teach_caste[20];

    char teach_street[50];
    char teach_area[50];
    char teach_city[50];
    char teach_state[50];
    int teach_zipcode; // Only 6 Digits

    // Auto Generate Items

    int teach_registration_number; // Auto Generate From 10000
    char teach_School_email[100];  // Auto Generate By Combining firstname + lastname + registration_number + "@cprojects.com"
};

// Teacher Academic Data

struct teacher_academic_information
{

    int teacher_registration_number; // Unique Teacher Registration Number

    char teacher_designation[50];     // Designation (PRT, TGT, PGT, Professor, Assistant Professor)
    char teacher_employment_type[20]; // Permanent / Contract / Visiting

    char teacher_highest_qualification[100]; // Highest Qualification
    char teacher_specialization[100];        // Subject Specialization
    int teacher_experience_years;            // Total Teaching Experience in Years
    int teacher_joining_year;                // Year of Joining the Institution

    char teaching_level[20]; // Pre-Primary / Primary / Secondary / Senior Secondary

    int teacher_subject_count;                        // Number of Subjects Taught
    char teacher_subjects[MAX_SUBJECTS][SUBJECT_LEN]; // Subjects Taught

    int teacher_preferred_class_count;          // Number of Preferred Classes
    int teacher_preferred_classes[MAX_CLASSES]; // Preferred Classes (e.g., 6,7,8,9,10)
};

// Dashboard (Main Menu)

void main_menu()
{
    printf("\n=========================================================\n");
    printf("                  School Managment School                  \n");
    printf("\n=========================================================\n");
    printf("1. Student Dashboard\n");
    printf("2. Teacher Dashboard\n");
    printf("3. Parent Dashboard\n");
    printf("4. Exit\n");
}

// Student Dashboard

void student_dashboard()
{
    printf("\n=========================================================\n");
    printf("                     Student Dashboard                     \n");
    printf("\n=========================================================\n");
    printf("1. Add Student Personal Details\n");
    printf("2. Add Academic Details\n");
    printf("3. See Student Academic Details.\n");
    printf("4. Update Student Information\n");
    printf("5. View All Students\n");
    printf("6. View Courses Assigned\n");
    printf("7. Search Student\n");
    printf("8. View Student Result\n");
    printf("9. Count Total Students\n");
    printf("10. Delete Student Record\n");
    printf("11. Exit\n");
}

// Teacher Dashboard

void teacher_dashboard()
{
    printf("\n==================== TEACHER DASHBOARD ====================\n");
    printf("1. Add Teacher Personal Details\n");
    printf("2. Add Teacher Professional Details\n");
    printf("3. Update Teacher Information\n");
    printf("4. View All Teachers\n");
    printf("5. View Students Assigned to Teacher\n");
    printf("6. View Courses Assigned to Teacher\n");
    printf("7. Count Total Teachers\n");
    printf("8. View Classes Assigned to Teacher\n");
    printf("9. Assign Class to Teacher\n");
    printf("10. Search Teacher\n");
    printf("11. View Student Result\n");
    printf("12. View Class Result\n");
    printf("13. Add Marks\n");
    printf("14. Exit\n");
}

// ==============================================================================
// ============================== Student Function ==============================
// ==============================================================================

// Check Int Input in optoin choose

int readInt(int *var)
{
    if (scanf("%d", var) != 1)
    {
        printf("Invalid input! Please enter a number.\n");
        while (getchar() != '\n')
            ;
        return 0;
    }
    return 1;
}

// ========================== Add Student Personal Info Function Items==========================

// Gennerate Registration Number

int generate_student_registration_number()
{
    FILE *fp;
    struct student_info st_info;

    fp = fopen("Student_information.dat", "rb");

    // If File not exist -> First Student
    if (fp == NULL)
    {
        return 1000;
    }

    // Go To End of File
    fseek(fp, 0, SEEK_END);

    // If File Is Empty
    if (ftell(fp) == 0)
    {
        fclose(fp);
        return 1000;
    }

    // Move pointer to last student record
    fseek(fp, -sizeof(struct student_info), SEEK_END);

    // Read last student
    if (fread(&st_info, sizeof(struct student_info), 1, fp) != 1)
    {
        fclose(fp);
        return 1000;
    }

    // Close File
    fclose(fp);

    return st_info.Stu_registration_number + 1;
}

// Function For required Inputs

void readrequiredstring(const char *msg, char *str, int size)
{
    do
    {
        printf("%s", msg);
        fgets(str, size, stdin);

        // remove newline character
        str[strcspn(str, "\n")] = '\0';

        if (strlen(str) == 0)
        {
            printf("This field is required. Please enter a value.\n");
        }

    } while (strlen(str) == 0);
}

// Function For Optional Inputs

void readoptionalstring(const char *msg, char *str, int size)
{
    printf("%s", msg);
    fgets(str, size, stdin);

    // remove newline character
    str[strcspn(str, "\n")] = '\0';
}

// Checks DOB in format "DD/MM/YYYY"

void readdob(char *msg, char *str, int size)
{
    int day, month, year;

    while (1)
    {
        printf("%s", msg);

        if (fgets(str, size, stdin) == NULL)
            continue;

        // Remove newline
        str[strcspn(str, "\n")] = '\0';

        // Check length: DD/MM/YYYY → 10 chars
        if (strlen(str) != 10)
        {
            printf("Invalid DOB format! Use DD/MM/YYYY\n");
            continue;
        }

        // Check separators
        if (str[2] != '/' || str[5] != '/')
        {
            printf("Invalid DOB format! Use DD/MM/YYYY\n");
            continue;
        }

        // Check digits
        for (int i = 0; i < 10; i++)
        {
            if (i == 2 || i == 5)
                continue;

            if (!isdigit((unsigned char)str[i]))
            {
                printf("Invalid DOB format! Use DD/MM/YYYY\n");
                goto retry;
            }
        }

        // Extract values
        day = (str[0] - '0') * 10 + (str[1] - '0');
        month = (str[3] - '0') * 10 + (str[4] - '0');
        year = (str[6] - '0') * 1000 +
               (str[7] - '0') * 100 +
               (str[8] - '0') * 10 +
               (str[9] - '0');

        // Validate ranges
        if (day < 1 || day > 31 ||
            month < 1 || month > 12 ||
            year < 1900 || year > 2100)
        {
            printf("Invalid DOB values!\n");
            continue;
        }

        return; // VALID DOB

    retry:
        continue;
    }
}

// Checks Gender

void readgender(char *msg, char *str, int size)
{
    while (1)
    {
        printf("%s", msg);
        if (fgets(str, size, stdin) == NULL)
            continue;

        // Remove newline
        str[strcspn(str, "\n")] = '\0';

        // Make the Lenght Only 1
        if (strlen(str) != 1)
        {
            printf("Enter Gender in The Format - 'M'/'F'/'O'\n ");
            continue;
        }

        // Make the Character in Uppercase
        str[0] = toupper((unsigned char)str[0]);

        if (str[0] != 'M' && str[0] != 'F' && str[0] != 'O')
        {
            printf("Enter Gender in The Format - 'M'/'F'/'O'\n ");
            continue;
        }
        return; // Valid input
    }
}

// Checks Caste

void readcaste(char *msg, char *str, int size)
{
    while (1)
    {
        printf("%s", msg);

        if (fgets(str, size, stdin) == NULL)
            continue;

        // Remove newline
        str[strcspn(str, "\n")] = '\0';

        // Convert to uppercase
        for (int i = 0; str[i] != '\0'; i++)
        {
            str[i] = toupper((unsigned char)str[i]);
        }

        // Validate caste
        if (strcmp(str, "GEN") == 0 ||
            strcmp(str, "OBC") == 0 ||
            strcmp(str, "SC") == 0 ||
            strcmp(str, "ST") == 0)
        {
            return; // valid input → exit function
        }

        printf("Invalid Caste! Please Enter Gen, OBC, SC or ST.\n");
    }
}

// Checks Email Address

void readmail(char *msg, char *str, int size)
{
    while (1)
    {
        printf("%s", msg);

        if (fgets(str, size, stdin) == NULL)
            continue;

        // Remove newline
        str[strcspn(str, "\n")] = '\0';

        // Check if "@gmail.com" exists
        if (strstr(str, "@gmail.com") != NULL)
        {
            return; // valid email → exit function
        }

        printf("Invalid Email Address!\n");
    }
}

// Checks Mobile Number

void readmobilenumber(char *msg, char *str, int size)
{
    while (1)
    {
        printf("%s", msg);

        if (fgets(str, size, stdin) == NULL)
            continue;

        // Remove newline
        str[strcspn(str, "\n")] = '\0';

        // Length must be exactly 10
        if (strlen(str) != 10)
        {
            printf("Invalid Mobile Number\n");
            continue;
        }

        // First digit check (Indian numbers)
        if (str[0] < '6' || str[0] > '9')
        {
            printf("Invalid Mobile Number\n");
            continue;
        }

        // All characters must be digits
        int valid = 1;
        for (int i = 0; i < 10; i++)
        {
            if (!isdigit((unsigned char)str[i]))
            {
                valid = 0;
                break;
            }
        }

        if (!valid)
        {
            printf("Invalid Mobile Number\n");
            continue;
        }

        return;
    }
}

// Checks Zipcode

void readzipcode(char *msg, int *zipcode_number)
{
    while (1)
    {
        printf("%s", msg);

        if (scanf("%d", zipcode_number) != 1)
        {
            printf("Invalid input! Enter numbers only.\n");

            // Clear input buffer
            while (getchar() != '\n')
                ;
            continue;
        }

        if (*zipcode_number < 100000 || *zipcode_number > 999999)
        {
            printf("Please enter a valid 6-digit zipcode.\n");
            continue;
        }

        // Clear leftover newline
        while (getchar() != '\n')
            ;

        return; // valid zipcode
    }
}

// Generate School Gmail Id

void generate_school_email(char *firstname, char *lastname, int reg_num, char *email, int size)
{
    char fname[50], lname[50];

    // Copy names safely
    strncpy(fname, firstname, sizeof(fname));
    strncpy(lname, lastname, sizeof(lname));

    fname[sizeof(fname) - 1] = '\0';
    lname[sizeof(lname) - 1] = '\0';

    // Convert to lowercase
    for (int i = 0; fname[i] != '\0'; i++)
        fname[i] = tolower((unsigned char)fname[i]);

    for (int i = 0; lname[i] != '\0'; i++)
        lname[i] = tolower((unsigned char)lname[i]);

    // Generate email
    snprintf(email, size, "%s.%s.%d@gmail.com", fname, lname, reg_num);
}

// Add Student Personal Info

void add_student_personal_info()
{
    FILE *fp;
    struct student_info st_in;
    int ch;

    // clear buffer safely
    while ((ch = getchar()) != '\n' && ch != EOF)
        ;

    fp = fopen("Student_academic.dat", "ab");
    if (fp == NULL)
    {
        printf("Error: Unable to open academic file!\n");
        return;
    }

    // Registration Number
    st_in.Stu_registration_number = generate_student_registration_number();

    readrequiredstring("Enter First Name : ", st_in.stu_firstname, sizeof(st_in.stu_firstname));                   // Enter First Name
    readoptionalstring("Enter Middle Name : ", st_in.stu_middlename, sizeof(st_in.stu_middlename));                // Enter Middle Name
    readrequiredstring("Enter Last Name : ", st_in.stu_lastname, sizeof(st_in.stu_lastname));                      // Enter Last Name
    readrequiredstring("Enter Father's Name : ", st_in.stu_fathername, sizeof(st_in.stu_fathername));              // Enter Father's Name
    readrequiredstring("Enter Mother's Name : ", st_in.stu_mothername, sizeof(st_in.stu_mothername));              // Enter Mother's Name
    readrequiredstring("Enter Father's Occupation : ", st_in.stu_father_occu, sizeof(st_in.stu_father_occu));      // Enter Father's Occupation
    readrequiredstring("Enter Mother's Occupation : ", st_in.stu_mother_occu, sizeof(st_in.stu_mother_occu));      // Enter Mother's Occupation
    readdob("Enter D.O.B (DD/MM/YYYY): ", st_in.stu_dob, sizeof(st_in.stu_dob));                                   // Enter DOB in DD/MM//YYYY Format
    readgender("Enter Gender (M/F/O) : ", st_in.stu_gender, sizeof(st_in.stu_gender));                             // Enter Gender in 'M'/'F'/'O'
    readcaste("Enter Caste (Gen/OBC/SC/ST) : ", st_in.stu_caste, sizeof(st_in.stu_caste));                         // Enter Caste - 'OBC'/'GEN'/'ST'/'SC'
    readmail("Enter Gmail Address : ", st_in.stu_email, sizeof(st_in.stu_email));                                  // Enter Personal Gmail Address
    readmobilenumber("Enter Mobile Number : ", st_in.stu_mobile_number, sizeof(st_in.stu_mobile_number));          // Enter Student Mobile Number
    readmobilenumber("Enter Father's Mobile Number : ", st_in.stu_father_number, sizeof(st_in.stu_father_number)); // Enter Father's Mobile Number
    readrequiredstring("Enter Street Name : ", st_in.stu_street, sizeof(st_in.stu_street));                        // Enter Street Name
    readrequiredstring("Enter Area : ", st_in.stu_area, sizeof(st_in.stu_area));                                   // Enter Area Name
    readrequiredstring("Enter City Name : ", st_in.stu_city, sizeof(st_in.stu_city));                              // Enter City Name
    readrequiredstring("Enter State : ", st_in.stu_state, sizeof(st_in.stu_state));                                // Enter State
    readzipcode("Enter Zipcode : ", &st_in.stu_zipcode);                                                           // Enter Zipcode in 6 digit only

    generate_school_email( // School Gmail Id (Autogenerate)
        st_in.stu_firstname,
        st_in.stu_lastname,
        st_in.Stu_registration_number,
        st_in.Stu_School_email,
        sizeof(st_in.Stu_School_email));
    printf("Generated Registration Number : %d\n", st_in.Stu_registration_number);
    printf("Generated School Gmail Id : %s", st_in.Stu_School_email);
    fp = fopen("Student_information.dat", "ab");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    fwrite(&st_in, sizeof(struct student_info), 1, fp);
    fclose(fp);
}

// ========================== add_student_academic_info Function Items ==========================

// Course Enrolled

void assign_subjects(struct student_academic_information *stu_aca_info)
{
    stu_aca_info->stu_subject_count;

    if (stu_aca_info->stu_class <= 5 && stu_aca_info->stu_class >= 1)
    {
        strcpy(stu_aca_info->stu_subjects[0], "ENGLISH");
        strcpy(stu_aca_info->stu_subjects[1], "HINDI");
        strcpy(stu_aca_info->stu_subjects[2], "MATHEMATICS");
        strcpy(stu_aca_info->stu_subjects[3], "ENVIRONMENTAL STUDIES");
        strcpy(stu_aca_info->stu_subjects[4], "GENERAL KNOWLEDGE");
        strcpy(stu_aca_info->stu_subjects[5], "COMPUTER");
        stu_aca_info->stu_subject_count = 6;
    }
    else if (stu_aca_info->stu_class <= 8)
    {
        strcpy(stu_aca_info->stu_subjects[0], "ENGLISH");
        strcpy(stu_aca_info->stu_subjects[1], "HINDI");
        strcpy(stu_aca_info->stu_subjects[2], "SANSKRIT");
        strcpy(stu_aca_info->stu_subjects[3], "MATHEMATICS");
        strcpy(stu_aca_info->stu_subjects[4], "SCIENCE");
        strcpy(stu_aca_info->stu_subjects[5], "SOCIAL STUDIES");
        strcpy(stu_aca_info->stu_subjects[6], "COMPUTER");
        stu_aca_info->stu_subject_count = 7;
    }
    else if (stu_aca_info->stu_class <= 10)
    {
        strcpy(stu_aca_info->stu_subjects[0], "ENGLISH");
        strcpy(stu_aca_info->stu_subjects[1], "MATHEMATICS");
        strcpy(stu_aca_info->stu_subjects[2], "SCIENCE");
        strcpy(stu_aca_info->stu_subjects[3], "SOCIAL STUDIES");
        strcpy(stu_aca_info->stu_subjects[4], "COMPUTER");
        stu_aca_info->stu_subject_count = 5;
    }
    else
    {
        if (strcmp(stu_aca_info->stream, "PCM") == 0)
        {
            strcpy(stu_aca_info->stu_subjects[0], "ENGLISH");
            strcpy(stu_aca_info->stu_subjects[1], "PHYSICS");
            strcpy(stu_aca_info->stu_subjects[2], "CHEMISTRY");
            strcpy(stu_aca_info->stu_subjects[3], "MATHEMATICS");
            strcpy(stu_aca_info->stu_subjects[4], "COMPUTER");
            strcpy(stu_aca_info->stu_subjects[5], "YOGA");
            stu_aca_info->stu_subject_count = 6;
        }
        else if (strcmp(stu_aca_info->stream, "PCB") == 0)
        {
            strcpy(stu_aca_info->stu_subjects[0], "ENGLISH");
            strcpy(stu_aca_info->stu_subjects[1], "PHYSICS");
            strcpy(stu_aca_info->stu_subjects[2], "CHEMISTRY");
            strcpy(stu_aca_info->stu_subjects[3], "BIOLOGY");
            strcpy(stu_aca_info->stu_subjects[4], "COMPUTER");
            strcpy(stu_aca_info->stu_subjects[5], "YOGA");
            stu_aca_info->stu_subject_count = 6;
        }
        else if (strcmp(stu_aca_info->stream, "PCMB") == 0)
        {
            strcpy(stu_aca_info->stu_subjects[0], "ENGLISH");
            strcpy(stu_aca_info->stu_subjects[1], "PHYSICS");
            strcpy(stu_aca_info->stu_subjects[2], "CHEMISTRY");
            strcpy(stu_aca_info->stu_subjects[3], "MATHEMATICS");
            strcpy(stu_aca_info->stu_subjects[4], "BIOLOGY");
            strcpy(stu_aca_info->stu_subjects[5], "COMPUTER");
            strcpy(stu_aca_info->stu_subjects[6], "YOGA");
            stu_aca_info->stu_subject_count = 7;
        }
        else if (strcmp(stu_aca_info->stream, "COMMERCE") == 0)
        {
            strcpy(stu_aca_info->stu_subjects[0], "ENGLISH");
            strcpy(stu_aca_info->stu_subjects[1], "ACCOUNTANCY");
            strcpy(stu_aca_info->stu_subjects[2], "BUSINESS STUDIES");
            strcpy(stu_aca_info->stu_subjects[3], "ECONOMICS");
            strcpy(stu_aca_info->stu_subjects[4], "COMPUTER");
            strcpy(stu_aca_info->stu_subjects[5], "APPLIED MATHS");
            strcpy(stu_aca_info->stu_subjects[6], "YOGA");
            stu_aca_info->stu_subject_count = 7;
        }
        else if (strcmp(stu_aca_info->stream, "ARTS") == 0)
        {
            strcpy(stu_aca_info->stu_subjects[0], "ENGLISH");
            strcpy(stu_aca_info->stu_subjects[1], "HISTORY");
            strcpy(stu_aca_info->stu_subjects[2], "GEOGRAPHY");
            strcpy(stu_aca_info->stu_subjects[3], "POLITICAL SCIENCE");
            strcpy(stu_aca_info->stu_subjects[4], "ECONOMICS");
            strcpy(stu_aca_info->stu_subjects[5], "SOCIOLOGY");
            strcpy(stu_aca_info->stu_subjects[6], "PSYCHOLOGY");
            stu_aca_info->stu_subject_count = 7;
        }
    }
}

// Check Registration Number exist or not

int check_student_registration_number(int reg_number)
{
    FILE *fp;
    struct student_info stu_info;
    fp = fopen("Student_information.dat", "rb");
    if (fp == NULL)
        return 0; // no student file invalid

    while (fread(&stu_info, sizeof(stu_info), 1, fp))
    {
        if (stu_info.Stu_registration_number == reg_number)
        {
            fclose(fp);
            return 1; // found
        }
    }

    fclose(fp);
    return 0; // not found
}

// Assign the Section

int is_split_needed(int stu_class)
{
    FILE *fp;
    struct student_academic_information st;
    int countA = 0;

    fp = fopen("Student_academic.dat", "rb");
    if (!fp)
        return 0;

    while (fread(&st, sizeof(st), 1, fp))
    {
        if (st.stu_class == stu_class && st.stu_section == 'A')
            countA++;
    }

    fclose(fp);
    return countA >= 40;
}

// Checks Class

void readclass(const char *msg, int *stu_class)
{
    int ch;

    while (1)
    {
        printf("%s", msg);

        if (scanf("%d", stu_class) != 1)
        {
            printf("Invalid input! Please enter a number.\n");
            while ((ch = getchar()) != '\n' && ch != EOF)
                ;
            continue;
        }

        // clear buffer
        while ((ch = getchar()) != '\n' && ch != EOF)
            ;

        if (*stu_class < 1 || *stu_class > 12)
        {
            printf("Invalid class! Enter class between 1 and 12.\n");
            continue;
        }

        return; // valid input
    }
}

// Autogenerate Section

char auto_generate_section(int stu_class)
{
    FILE *fp;
    struct student_academic_information st;
    int section_count[26] = {0};
    char max_section = 'A';

    fp = fopen("Student_academic.dat", "rb");
    if (fp == NULL)
        return 'A'; // first student of this class

    while (fread(&st, sizeof(st), 1, fp))
    {
        if (st.stu_class == stu_class)
        {
            int idx = st.stu_section - 'A';
            section_count[idx]++;

            if (st.stu_section > max_section)
                max_section = st.stu_section;
        }
    }
    fclose(fp);

    /* Find first section with available space */
    for (int i = 0; i <= max_section - 'A'; i++)
    {
        int limit = (i == 0) ? MAX_BEFORE_DIVIDE : MAX_AFTER_DIVIDE;

        if (section_count[i] < limit)
            return 'A' + i;
    }

    /* All existing sections are full → create new section */
    return max_section + 1;
}

// Split Section

void split_section(int stu_class, char section)
{
    FILE *fp, *temp;
    struct student_academic_information st;
    int count = 0;

    fp = fopen("Student_academic.dat", "rb");
    temp = fopen("temp_academic.dat", "wb");

    if (fp == NULL || temp == NULL)
    {
        printf("Error: Unable to split section.\n");
        return;
    }

    while (fread(&st, sizeof(st), 1, fp))
    {
        if (st.stu_class == stu_class && st.stu_section == section)
        {
            count++;

            // Move last 10 students to next section
            if (count > 30)
            {
                st.stu_section = section + 1; // A → B
            }
        }

        fwrite(&st, sizeof(st), 1, temp);
    }

    fclose(fp);
    fclose(temp);

    // Replace old file with updated file
    remove("Student_academic.dat");
    rename("temp_academic.dat", "Student_academic.dat");
}

// Check Section

void readsection(const char *msg, int stu_class, char *stu_section)
{
    int ch;

    while (1)
    {
        printf("%s", msg);

        if (scanf(" %c", stu_section) != 1)
        {
            printf("Invalid input! Enter a section letter.\n");
            while ((ch = getchar()) != '\n' && ch != EOF)
                ;
            continue;
        }

        // clear buffer
        while ((ch = getchar()) != '\n' && ch != EOF)
            ;

        // normalize to uppercase
        if (*stu_section >= 'a' && *stu_section <= 'z')
            *stu_section -= 32;

        // basic validation
        if (*stu_section < 'A' || *stu_section > 'Z')
        {
            printf("Invalid section! Enter A–Z only.\n");
            continue;
        }

        // check section exists for the class
        if (!is_section_valid_for_class(stu_class, *stu_section))
        {
            printf("Section %c does not exist for Class %d.\n",
                   *stu_section, stu_class);
            continue;
        }

        return; // valid section
    }
}

// Read Year Session in format - 'YYYY-YYYY'

void readsession(const char *msg, char *str, int size)
{
    while (1)
    {
        printf("%s", msg);

        if (fgets(str, size, stdin) == NULL)
            continue;

        // Remove newline
        str[strcspn(str, "\n")] = '\0';

        // Length must be exactly 9 (YYYY-YYYY)
        if (strlen(str) != 9)
        {
            printf("Invalid format! Use YYYY-YYYY\n");
            continue;
        }

        int valid = 1;

        for (int i = 0; i < 9; i++)
        {
            if (i == 4)
            {
                if (str[i] != '-')
                {
                    valid = 0;
                    break;
                }
            }
            else
            {
                if (!isdigit((unsigned char)str[i]))
                {
                    valid = 0;
                    break;
                }
            }
        }

        if (valid)
            return;

        printf("Invalid format! Use YYYY-YYYY\n");
    }
}

// Check the School Details If Same as C PROJECT SCHOOL

void readschooldetail(struct student_academic_information *add_stu_aca_det)
{
    readrequiredstring("Enter School Street : ", add_stu_aca_det->stu_last_address_street, sizeof(add_stu_aca_det->stu_last_address_street));
    readrequiredstring("Enter School Area : ", add_stu_aca_det->stu_last_address_area, sizeof(add_stu_aca_det->stu_last_address_area));
    readrequiredstring("Enter School City : ", add_stu_aca_det->stu_last_address_city, sizeof(add_stu_aca_det->stu_last_address_city));
    readrequiredstring("Enter School State : ", add_stu_aca_det->stu_last_address_state, sizeof(add_stu_aca_det->stu_last_address_state));
}

// Check School Name

void readschool(const char *msg, char *str, int size, struct student_academic_information *stu_last_detail)
{
    const char *CURRENT_SCHOOL = "C PROJECT SCHOOL";
    do
    {
        printf("%s", msg);

        if (fgets(str, size, stdin) == NULL)
            continue;

        // remove newline character
        str[strcspn(str, "\n")] = '\0';

        if (strlen(str) == 0)
        {
            printf("This field is required. Please enter a value.\n");
        }

    } while (strlen(str) == 0);

    // Convert to uppercase for comparison
    for (int i = 0; str[i] != '\0'; i++)
    {
        str[i] = toupper((unsigned char)str[i]);
    }

    // If school is different, ask for address details
    if (strcmp(str, CURRENT_SCHOOL) != 0)
    {
        readschooldetail(stu_last_detail);
    }
    else
    {
        strcpy(stu_last_detail->stu_last_address_street, "C Street");
        strcpy(stu_last_detail->stu_last_address_area, "C Area");
        strcpy(stu_last_detail->stu_last_address_city, "C City");
        strcpy(stu_last_detail->stu_last_address_state, "C State");
    }
}

// Check the Stream for 11 and 12

void readstream(const char *msg, char *stream, int size)
{
    int ch;

    while (1)
    {
        printf("%s", msg);

        if (fgets(stream, size, stdin) == NULL)
        {
            printf("Invalid input. Try again.\n");
            continue;
        }

        // remove newline
        stream[strcspn(stream, "\n")] = '\0';

        // convert to uppercase
        for (int i = 0; stream[i]; i++)
            stream[i] = toupper((unsigned char)stream[i]);

        // validate stream
        if (strcmp(stream, "PCM") == 0 ||
            strcmp(stream, "PCB") == 0 ||
            strcmp(stream, "PCMB") == 0 ||
            strcmp(stream, "COMMERCE") == 0 ||
            strcmp(stream, "ARTS") == 0)
        {
            return; // valid stream
        }

        printf("Invalid stream! Allowed values: PCM, PCB, PCMB, COMMERCE, ARTS\n");

        // clear buffer if needed
        while ((ch = getchar()) != '\n' && ch != EOF)
            ;
    }
}

// Student Academic Info

void add_student_academic_info()
{
    FILE *fp;
    struct student_academic_information st_academic;
    int ch, valid_reg = 0;

    // clear buffer safely
    while ((ch = getchar()) != '\n' && ch != EOF)
        ;

    fp = fopen("Student_academic.dat", "ab");
    if (fp == NULL)
    {
        printf("Error: Unable to open academic file!\n");
        return;
    }

    while (!valid_reg)
    {
        printf("Enter Registration Number : ");

        if (scanf("%d", &st_academic.stu_registration_number) != 1)
        {
            printf("Invalid input! Enter numbers only.\n");
            while ((ch = getchar()) != '\n' && ch != EOF)
                ;
            continue;
        }

        // clear buffer
        while ((ch = getchar()) != '\n' && ch != EOF)
            ;

        if (!check_student_registration_number(st_academic.stu_registration_number))
        {
            printf("Registration number not found! Please enter a valid one.\n");
            continue;
        }

        valid_reg = 1; // exit loop
    }

    readclass("Enter Class : ", &st_academic.stu_class);

    if (is_split_needed(st_academic.stu_class))
    {
        split_section(st_academic.stu_class, 'A');
    }

    // Autogenerate Section
    st_academic.stu_section = auto_generate_section(st_academic.stu_class);

    if (st_academic.stu_class > 10)
    {
        readstream("Enter Stream (PCM/PCB/PCMB/COMMERCE/ARTS) : ", st_academic.stream, sizeof(st_academic.stream));
    }
    else
    {
        strcpy(st_academic.stream, "NA");
    }

    // Autoassign Subjects
    st_academic.stu_subject_count = auto_assign_subject(st_academic.stu_class, st_academic.stu_subjects);

    // Last Year Percentage
    printf("Enter Last Year Percentage : ");
    scanf("%f", &st_academic.stu_last_percentage);

    // clear buffer safely
    while ((ch = getchar()) != '\n' && ch != EOF)
        ;

    // Last School Name
    readschool("Enter Last School Name : ", st_academic.stu_last_school, sizeof(st_academic.stu_last_school), &st_academic);

    // Last Session Year in Format 'YYYY-YYYY'
    readsession("Enter Last Session Year : ", st_academic.stu_last_session_year, sizeof(st_academic.stu_last_session_year));

    // Current Session Year in Format 'YYYY-YYYY'
    readsession("Enter Currect Session Year : ", st_academic.stu_academic_year, sizeof(st_academic.stu_academic_year));

    fwrite(&st_academic, sizeof(st_academic), 1, fp);
    fclose(fp);
}

// ========================== See Student Academic Deatils Function Items==========================

// Check Yes No Option

int confirm_yes_no(const char *msg)
{
    char choice[10];
    int ch;

    while (1)
    {
        printf("%s", msg);
        scanf("%9s", choice);

        // clear input buffer
        while ((ch = getchar()) != '\n' && ch != EOF)
            ;

        // convert to uppercase
        for (int i = 0; choice[i]; i++)
            choice[i] = toupper((unsigned char)choice[i]);

        if (strcmp(choice, "YES") == 0)
            return 1;

        if (strcmp(choice, "NO") == 0)
            return 0;

        printf("Invalid input! Enter YES or NO.\n");
    }
}

// Search Student Information by Registration Number

student_information_by_registration(int reg_no, struct student_info *st_info)
{
    FILE *fp = fopen("Student_information.dat", "rb");
    if (fp == NULL)
        return 0;

    while (fread(st_info, sizeof(*st_info), 1, fp))
    {
        if (st_info->Stu_registration_number == reg_no)
        {
            fclose(fp);
            return 1; // FOUND
        }
    }

    fclose(fp);
    return 0; // NOT FOUND
}

// Search Student Academic Information by Registration Number

student_academic_by_registration(int reg_no, struct student_academic_information *stu_aca_info)
{
    FILE *fp = fopen("Student_academic.dat", "rb");
    if (fp == NULL)
        return 0;

    while (fread(stu_aca_info, sizeof(*stu_aca_info), 1, fp))
    {
        if (stu_aca_info->stu_registration_number == reg_no)
        {
            fclose(fp);
            return 1; // FOUND
        }
    }
    fclose(fp);
    return 0; // NOT FOUND
}

// See Student Academic Details

void see_student_academic_details()
{
    int ch, registration_number;
    struct student_info st_in;
    struct student_academic_information stu_aca_data;
    char choice[10];

    while (1) // MAIN LOOP
    {
        printf("\nEnter Registration Number : ");

        if (scanf("%d", &registration_number) != 1)
        {
            printf("Invalid input! Enter numbers only.\n");
            while ((ch = getchar()) != '\n' && ch != EOF)
                ;
            continue;
        }

        while ((ch = getchar()) != '\n' && ch != EOF)
            ;

        /* -------- STUDENT NOT FOUND -------- */
        if (!check_student_registration_number(registration_number))
        {
            printf("Student not found!\n");

            while (1)
            {
                printf("Want to add this student? (YES/NO): ");
                scanf("%9s", choice);

                while ((ch = getchar()) != '\n' && ch != EOF)
                    ;

                for (int i = 0; choice[i]; i++)
                    choice[i] = toupper((unsigned char)choice[i]);

                if (strcmp(choice, "YES") == 0)
                {
                    add_student_personal_info();
                    add_student_academic_info();
                    break;
                }
                else if (strcmp(choice, "NO") == 0)
                {
                    break;
                }
                else
                {
                    printf("Invalid input! Enter YES or NO.\n");
                }
            }
            continue; // Ask Registration Number Again
        }

        /* -------- STUDENT FOUND -------- */
        if (!student_information_by_registration(registration_number, &st_in) ||
            !student_academic_by_registration(registration_number, &stu_aca_data))
        {
            printf("Academic details not found!\n");
            continue;
        }

        printf("\n----------------------------------------------\n");
        printf("            STUDENT ACADEMIC DETAILS\n            ");
        printf("\n----------------------------------------------\n");

        // Print Name Of the Student And Also Checks For The Middle Name
        if (strlen(st_in.stu_middlename) > 0)
        {
            printf("Name : %s %s %s\n",
                   st_in.stu_firstname,
                   st_in.stu_middlename,
                   st_in.stu_lastname);
        }
        else
        {
            printf("Name : %s %s\n",
                   st_in.stu_firstname,
                   st_in.stu_lastname);
        }

        printf("Registration No : %d\n", registration_number);
        printf("School Email    : %s\n", st_in.Stu_School_email);
        printf("Class           : %d\n", stu_aca_data.stu_class);
        printf("Section         : %c\n", stu_aca_data.stu_section);
        printf("Academic Year   : %s\n", stu_aca_data.stu_academic_year);

        while (1)
        {
            int check = confirm_yes_no("Serach Another Student (Yes/No)? : ");

            if (check == 1)
            {
                break;
            }
            else
            {
                return;
            }
        }
    }
}

//

// ========================== Update Student Personal Detail Function Items==========================

void update_student_information()
{
    printf("1. Student Name\n");
    printf("2. Father Name\n");
    printf("3. Mother Name\n");
    printf("4. Father Occupation\n");
    printf("5. Mother Occupation\n");
    printf("6. Date Of Birth(DOB)\n");
    printf("7. Gender\n");
    printf("8. Caste\n");
    printf("9. Student Email Id\n");
    printf("10. Student Mobile Number\n");
    printf("11. Father Mobile Number\n");
    printf("12. Address\n");
    printf("13. Exit\n");
}

// Update Student Name

void update_student_name(int reg_no)
{
    FILE *fp, *temp;
    struct student_info st_info;
    int found = 0;
    fp = fopen("Student_information.dat", "rb");
    temp = fopen("temp.dat", "wb");

    if (fp == NULL || temp == NULL)
    {
        printf("Error: File Not Open\n");
        remove("temp.dat");
        return;
    }

    while (fread(&st_info, sizeof(st_info), 1, fp))
    {
        if (st_info.Stu_registration_number == reg_no)
        {
            found = 1;
            readrequiredstring("Enter First Name : ", st_info.stu_firstname, sizeof(st_info.stu_firstname));
            readoptionalstring("Enter Middle Name : ", st_info.stu_middlename, sizeof(st_info.stu_middlename));
            readrequiredstring("Enter Last Name : ", st_info.stu_lastname, sizeof(st_info.stu_lastname));
        }
        fwrite(&st_info, sizeof(st_info), 1, temp);
    }
    fclose(fp);
    fclose(temp);
    if (!found)
    {
        printf("Student Not Found\n");
        return;
    }
    remove("Student_information.dat");
    rename("temp.dat", "Student_information.dat");
}

// Update Father Name

void update_father_name(int reg_no)
{
    FILE *fp, *temp;
    struct student_info st_info;
    int found = 0;
    fp = fopen("Student_information.dat", "rb");
    temp = fopen("temp.dat", "wb");
    if (fp == NULL || temp == NULL)
    {
        printf("Error: File Not Open\n");
        remove("temp.dat");
        return;
    }
    while (fread(&st_info, sizeof(st_info), 1, fp))
    {
        if (st_info.Stu_registration_number == reg_no)
        {
            found = 1;
            readrequiredstring("Enter Father Name : ", st_info.stu_fathername, sizeof(st_info.stu_fathername));
        }
        fwrite(&st_info, sizeof(st_info), 1, temp);
    }
    fclose(fp);
    fclose(temp);
    if (!found)
    {
        printf("Student Not Found\n");
        return;
    }
    remove("Student_information.dat");
    rename("temp.dat", "Student_information.dat");
}

// Update Mother Name

void update_mother_name(int reg_no)
{
    FILE *fp, *temp;
    struct student_info st_info;
    int found = 0;
    fp = fopen("Student_information.dat", "rb");
    temp = fopen("temp.dat", "wb");
    if (fp == NULL || temp == NULL)
    {
        printf("Error: File Not Open\n");
        remove("temp.dat");
        return;
    }
    while (fread(&st_info, sizeof(st_info), 1, fp))
    {
        if (st_info.Stu_registration_number == reg_no)
        {
            found = 1;
            readrequiredstring("Enter Mother Name : ", st_info.stu_mothername, sizeof(st_info.stu_mothername));
        }
        fwrite(&st_info, sizeof(st_info), 1, temp);
    }
    fclose(fp);
    fclose(temp);
    if (!found)
    {
        printf("Student Not Found\n");
        return;
    }
    remove("Student_information.dat");
    rename("temp.dat", "Student_information.dat");
}

void update_father_occupation(int reg_no)
{
    FILE *fp, *temp;
    struct student_info st_info;
    int found = 0;
    fp = fopen("Student_information.dat", "rb");
    temp = fopen("temp.dat", "wb");
    if (fp == NULL || temp == NULL)
    {
        printf("Error: File Not Open\n");
        remove("temp.dat");
        return;
    }
    while (fread(&st_info, sizeof(st_info), 1, fp))
    {
        if (st_info.Stu_registration_number == reg_no)
        {
            found = 1;
            readrequiredstring("Enter Father Occupation : ", st_info.stu_father_occu, sizeof(st_info.stu_father_occu));
        }
        fwrite(&st_info, sizeof(st_info), 1, temp);
    }
    fclose(fp);
    fclose(temp);
    if (!found)
    {
        printf("Student Not Found\n");
        return;
    }
    remove("Student_information.dat");
    rename("temp.dat", "Student_information.dat");
}

// Update Mother Occupation

void update_mother_occupation(int reg_no)
{
    FILE *fp, *temp;
    struct student_info st_info;
    int found = 0;
    fp = fopen("Student_information.dat", "rb");
    temp = fopen("temp.dat", "wb");
    if (fp == NULL || temp == NULL)
    {
        printf("Error: File Not Open\n");
        remove("temp.dat");
        return;
    }
    while (fread(&st_info, sizeof(st_info), 1, fp))
    {
        if (st_info.Stu_registration_number == reg_no)
        {
            found = 1;
            readrequiredstring("Enter Mother Occupation : ", st_info.stu_mother_occu, sizeof(st_info.stu_mother_occu));
        }
        fwrite(&st_info, sizeof(st_info), 1, temp);
    }
    fclose(fp);
    fclose(temp);
    if (!found)
    {
        printf("Student Not Found\n");
        return;
    }
    remove("Student_information.dat");
    rename("temp.dat", "Student_information.dat");
}

// Update DOB

void update_dob(int reg_no)
{
    FILE *fp, *temp;
    struct student_info st_info;
    int found = 0;
    fp = fopen("Student_information.dat", "rb");
    temp = fopen("temp.dat", "wb");
    if (fp == NULL || temp == NULL)
    {
        printf("Error: File Not Open\n");
        remove("temp.dat");
        return;
    }
    while (fread(&st_info, sizeof(st_info), 1, fp))
    {
        if (st_info.Stu_registration_number == reg_no)
        {
            found = 1;
            readdob("Enter DOB (DD/MM/YYYY) : ", st_info.stu_dob, sizeof(st_info.stu_dob));
        }
        fwrite(&st_info, sizeof(st_info), 1, temp);
    }
    fclose(fp);
    fclose(temp);
    if (!found)
    {
        printf("Student Not Found\n");
        return;
    }
    remove("Student_information.dat");
    rename("temp.dat", "Student_information.dat");
}

// Update Gender

void update_gender(int reg_no)
{
    FILE *fp, *temp;
    struct student_info st_info;
    int found = 0;
    fp = fopen("Student_information.dat", "rb");
    temp = fopen("temp.dat", "wb");
    if (fp == NULL || temp == NULL)
    {
        printf("Error: File Not Open\n");
        remove("temp.dat");
        return;
    }
    while (fread(&st_info, sizeof(st_info), 1, fp))
    {
        if (st_info.Stu_registration_number == reg_no)
        {
            found = 1;
            readgender("Enter Gender : ", st_info.stu_gender, sizeof(st_info.stu_gender));
        }
        fwrite(&st_info, sizeof(st_info), 1, temp);
    }
    fclose(fp);
    fclose(temp);
    if (!found)
    {
        printf("Student Not Found\n");
        return;
    }
    remove("Student_information.dat");
    rename("temp.dat", "Student_information.dat");
}

// Update Caste

void update_caste(int reg_no)
{
    FILE *fp, *temp;
    struct student_info st_info;
    int found = 0;
    fp = fopen("Student_information.dat", "rb");
    temp = fopen("temp.dat", "wb");
    if (fp == NULL || temp == NULL)
    {
        printf("Error: File Not Open\n");
        remove("temp.dat");
        return;
    }
    while (fread(&st_info, sizeof(st_info), 1, fp))
    {
        if (st_info.Stu_registration_number == reg_no)
        {
            found = 1;
            readcaste("Enter Caste : ", st_info.stu_caste, sizeof(st_info.stu_caste));
        }
        fwrite(&st_info, sizeof(st_info), 1, temp);
    }
    fclose(fp);
    fclose(temp);
    if (!found)
    {
        printf("Student Not Found\n");
        return;
    }
    remove("Student_information.dat");
    rename("temp.dat", "Student_information.dat");
}

// Update Student Personal Email Id

void update_student_email(int reg_no)
{
    FILE *fp, *temp;
    struct student_info st_info;
    int found = 0;
    fp = fopen("Student_information.dat", "rb");
    temp = fopen("temp.dat", "wb");
    if (fp == NULL || temp == NULL)
    {
        printf("Error: File Not Open\n");
        remove("temp.dat");
        return;
    }
    while (fread(&st_info, sizeof(st_info), 1, fp))
    {
        if (st_info.Stu_registration_number == reg_no)
        {
            found = 1;
            readmail("Enter Email Id : ", st_info.stu_email, sizeof(st_info.stu_email));
        }
        fwrite(&st_info, sizeof(st_info), 1, temp);
    }
    fclose(fp);
    fclose(temp);
    if (!found)
    {
        printf("Student Not Found\n");
        return;
    }
    remove("Student_information.dat");
    rename("temp.dat", "Student_information.dat");
}

// Update Student Mobile Number

void update_student_mobile_number(int reg_no)
{
    FILE *fp, *temp;
    struct student_info st_info;
    int found = 0;
    fp = fopen("Student_information.dat", "rb");
    temp = fopen("temp.dat", "wb");
    if (fp == NULL || temp == NULL)
    {
        printf("Error: File Not Open\n");
        remove("temp.dat");
        return;
    }
    while (fread(&st_info, sizeof(st_info), 1, fp))
    {
        if (st_info.Stu_registration_number == reg_no)
        {
            found = 1;
            readmobilenumber("Enter Student Movile Number : ", st_info.stu_mobile_number, sizeof(st_info.stu_mobile_number));
        }
        fwrite(&st_info, sizeof(st_info), 1, temp);
    }
    fclose(fp);
    fclose(temp);
    if (!found)
    {
        printf("Student Not Found\n");
        return;
    }
    remove("Student_information.dat");
    rename("temp.dat", "Student_information.dat");
}

// Update Father Mobile Number

void update_father_mobile_number(int reg_no)
{
    FILE *fp, *temp;
    struct student_info st_info;
    int found = 0;
    fp = fopen("Student_information.dat", "rb");
    temp = fopen("temp.dat", "wb");
    if (fp == NULL || temp == NULL)
    {
        printf("Error: File Not Open\n");
        remove("temp.dat");
        return;
    }
    while (fread(&st_info, sizeof(st_info), 1, fp))
    {
        if (st_info.Stu_registration_number == reg_no)
        {
            found = 1;
            readmobilenumber("Enter Father Mobile Number : ", st_info.stu_father_number, sizeof(st_info.stu_father_number));
        }
        fwrite(&st_info, sizeof(st_info), 1, temp);
    }
    fclose(fp);
    fclose(temp);
    if (!found)
    {
        printf("Student Not Found\n");
        return;
    }
    remove("Student_information.dat");
    rename("temp.dat", "Student_information.dat");
}

// Update Address

void update_address(int reg_no)
{
    FILE *fp, *temp;
    struct student_info st_info;
    int found = 0;
    fp = fopen("Student_information.dat", "rb");
    temp = fopen("temp.dat", "wb");
    if (fp == NULL || temp == NULL)
    {
        printf("Error: File Not Open\n");
        remove("temp.dat");
        return;
    }
    while (fread(&st_info, sizeof(st_info), 1, fp))
    {
        if (st_info.Stu_registration_number == reg_no)
        {
            found = 1;
            readrequiredstring("Enter Street Name : ", st_info.stu_street, sizeof(st_info.stu_street)); // Enter Street Name
            readrequiredstring("Enter Area : ", st_info.stu_area, sizeof(st_info.stu_area));            // Enter Area Name
            readrequiredstring("Enter City Name : ", st_info.stu_city, sizeof(st_info.stu_city));       // Enter City Name
            readrequiredstring("Enter State : ", st_info.stu_state, sizeof(st_info.stu_state));         // Enter State
            readzipcode("Enter Zipcode : ", &st_info.stu_zipcode);
        }
        fwrite(&st_info, sizeof(st_info), 1, temp);
    }
    fclose(fp);
    fclose(temp);
    if (!found)
    {
        printf("Student Not Found\n");
        return;
    }
    remove("Student_information.dat");
    rename("temp.dat", "Student_information.dat");
}

// Update Student Information Function

void update_student_info()
{
    int ch, update_option = 0, valid_reg = 0;
    struct student_info st_in;

    // Clear Buffer
    while ((ch = getchar()) != '\n' && ch != EOF)
        ;

    while (!valid_reg)
    {
        printf("Enter Registration Number : ");

        if (scanf("%d", &st_in.Stu_registration_number) != 1)
        {
            printf("Invalid input! Enter numbers only.\n");
            while ((ch = getchar()) != '\n' && ch != EOF)
                ;
            continue;
        }

        // clear buffer
        while ((ch = getchar()) != '\n' && ch != EOF)
            ;

        if (!check_student_registration_number(st_in.Stu_registration_number))
        {
            printf("Registration number not found! Please enter a valid one.\n");
            continue;
        }

        valid_reg = 1; // exit loop
    }

    while (1)
    {
        printf("Choose Which Item You Want to Update\n");
        update_student_information();
        printf("Enter option : ");

        if (scanf("%d", &update_option) != 1)
        {
            printf("Invalid input! Numbers only.\n");
            while ((ch = getchar()) != '\n' && ch != EOF)
                ;
            continue;
        }

        // Clear Buffer
        while ((ch = getchar()) != '\n' && ch != EOF)
            ;

        switch (update_option)
        {
        case 1:
            update_student_name(st_in.Stu_registration_number);
            break;
        case 2:
            update_father_name(st_in.Stu_registration_number);
            break;
        case 3:
            update_mother_name(st_in.Stu_registration_number);
            break;
        case 4:
            update_father_occupation(st_in.Stu_registration_number);
            break;
        case 5:
            update_mother_occupation(st_in.Stu_registration_number);
            break;
        case 6:
            update_dob(st_in.Stu_registration_number);
            break;
        case 7:
            update_gender(st_in.Stu_registration_number);
            break;
        case 8:
            update_caste(st_in.Stu_registration_number);
            break;
        case 9:
            update_student_email(st_in.Stu_registration_number);
            break;
        case 10:
            update_student_mobile_number(st_in.Stu_registration_number);
            break;
        case 11:
            update_father_mobile_number(st_in.Stu_registration_number);
            break;
        case 12:
            update_address(st_in.Stu_registration_number);
            break;
        case 13:
            printf("Exiting...\n");
            return;
        default:
            printf("Enter Valid Option\n");
            break;
        }

        // Update More Information

        if (!confirm_yes_no("Want to Update More Information? (YES/NO): "))
        {
            break;
            ; // Exit Function
        }
    }
}

// ========================== View All Student Function items ==========================

// Check Stream

int is_stream_match(int stu_class, char *record_stream, char *input_stream)
{
    if (stu_class < 11)
        return 1; // stream not applicable

    return strcmp(record_stream, input_stream) == 0;
}

// Print Student By Registration Number (Name and Registration Number)

void print_student_by_registration(int reg_no)
{
    FILE *fp;
    struct student_info stu_info;

    fp = fopen("Student_information.dat", "rb");
    if (fp == NULL)
    {
        printf("File Not open\n");
        return;
    }

    while (fread(&stu_info, sizeof(stu_info), 1, fp))
    {
        if (stu_info.Stu_registration_number == reg_no)
        {
            printf("%-15d %-15s %-15s %-15s\n", stu_info.Stu_registration_number, stu_info.stu_firstname, stu_info.stu_middlename, stu_info.stu_lastname);
            fclose(fp);
            return;
        }
    }

    fclose(fp);
}

// View Students of Particular Class ans Section

void view_student_by_class_section(int stu_class, char stu_section, char *stream)
{
    FILE *fp;
    struct student_academic_information stu_aca_info;
    int found = 0;

    fp = fopen("Student_academic.dat", "rb");
    if (fp == NULL)
    {
        printf("File Not Found\n");
        return;
    }

    printf("\nStudents of Class %d Section %c", stu_class, stu_section);
    if (stu_class >= 11)
        printf(" Stream %s", stream);
    printf("\n");

    printf("--------------------------------------------------\n");
    printf("%-15s %-15s %-15s %-15s\n",
           "Registration No.", "First Name", "Middle Name", "Last Name");
    printf("--------------------------------------------------\n");

    while (fread(&stu_aca_info, sizeof(stu_aca_info), 1, fp))
    {
        if (stu_aca_info.stu_class == stu_class &&
            stu_aca_info.stu_section == stu_section &&
            is_stream_match(stu_class, stu_aca_info.stream, stream))
        {
            print_student_by_registration(stu_aca_info.stu_registration_number);
            found = 1;
        }
    }

    fclose(fp);

    if (!found)
    {
        printf("No Student Found\n");
    }
}

// View All Student Main Function

void view_all_students()
{
    int ch;
    int stu_class;
    char stu_section;
    char stream[10] = "";

    // Clear buffer
    while ((ch = getchar()) != '\n' && ch != EOF)
        ;

    // Read class
    readclass("Enter class : ", &stu_class);

    // Read section
    readsection("Enter Section : ", stu_class, &stu_section);

    // Read stream ONLY for class 11 & 12
    if (stu_class >= 11)
    {
        readstream("Enter Stream (PCM/PCB/PCMB/COMMERCE/ARTS) : ", stream, sizeof(stream));
    }

    // View students
    view_student_by_class_section(stu_class, stu_section, stream);
}

// ========================== View Enrolled Courses Function Items==========================

// Print Subject by Class, Section and Stream

void print_subjects(int stu_class, char stu_section, char stu_stream[])
{
    int ch;
    struct student_academic_information stu_aca_info;

    // clear buffer safely
    while ((ch = getchar()) != '\n' && ch != EOF)
        ;

    // Prepare academic info
    stu_aca_info.stu_class = stu_class;
    stu_aca_info.stu_section = stu_section;

    if (stu_class > 10)
        strcpy(stu_aca_info.stream, stu_stream);
    else
        stu_aca_info.stream[0] = '\0';

    // Assign subjects based on class & stream
    assign_subjects(&stu_aca_info);

    // Print subjects
    printf("\nEnrolled Subjects\n");
    printf("---------------------------\n");
    printf("Class   : %d\n", stu_class);
    printf("Section : %c\n", stu_section);

    if (stu_class > 10)
        printf("Stream  : %s\n", stu_stream);

    printf("---------------------------\n");

    if (stu_aca_info.stu_subject_count == 0)
    {
        printf("No subjects assigned.\n");
        return;
    }

    for (int i = 0; i < stu_aca_info.stu_subject_count; i++)
    {
        printf("%d. %s\n", i + 1, stu_aca_info.stu_subjects[i]);
    }
}

// Get Subjects Of Student

void get_subject_by_registration(int stu_reg)
{
    FILE *fp;
    struct student_academic_information stu_aca_info;
    int ch, stu_class = 0;
    char stu_section = '\0', stu_stream[] = "";

    fp = fopen("Student_academic.dat", "rb");
    if (fp == NULL)
    {
        printf("Error: Unable to open academic file.\n");
        return;
    }

    // Clear buffer
    while ((ch = getchar()) != '\n' && ch != EOF)
        ;

    while (fread(&stu_aca_info, sizeof(stu_aca_info), 1, fp))
    {
        if (stu_aca_info.stu_registration_number == stu_reg)
        {
            stu_class = stu_aca_info.stu_class;
            stu_section = stu_aca_info.stu_section;
            if (stu_class > 10)
            {
                strcpy(stu_section, stu_aca_info.stream);
            }
            fclose(fp);
            print_subjects(stu_class, stu_section, stu_stream);
            break;
        }
    }
    fclose(fp);
    printf("Academic record not found for this student.\n");
}

// View Enrolled Courses

void view_courses()
{
    int ch, valid_reg = 0;
    struct student_academic_information st_academic;

    // Clear buffer
    while ((ch = getchar()) != '\n' && ch != EOF)
        ;

    while (!valid_reg)
    {
        printf("Enter Registration Number : ");

        if (scanf("%d", &st_academic.stu_registration_number) != 1)
        {
            printf("Invalid input! Enter numbers only.\n");
            while ((ch = getchar()) != '\n' && ch != EOF)
                ;
            continue;
        }

        // clear buffer
        while ((ch = getchar()) != '\n' && ch != EOF)
            ;

        if (!check_student_registration_number(st_academic.stu_registration_number))
        {
            printf("Registration number not found! Please enter a valid one.\n");
            continue;
        }
        valid_reg = 1; // exit loop
    }

    get_subject_by_registration(st_academic.stu_registration_number);
}

// ========================== Search Student By Different Things ==========================

// Print Student All Information

void print_all_information(int reg_number)
{
    FILE *fp1, *fp2;
    struct student_info stu_info;
    struct student_academic_information stu_aca_info;
    int found1 = 0, found2 = 0;
    LAST_FOUND_REGISTRATION = reg_number;

    // File Open
    fp1 = fopen("Student_information.dat", "rb");
    fp2 = fopen("Student_academic.dat", "rb");
    if (fp1 == NULL || fp2 == NULL)
    {
        printf("File Not Found\n");
        return;
    }

    while (fread(&stu_info, sizeof(stu_info), 1, fp1))
    {
        if (reg_number == stu_info.Stu_registration_number)
        {
            found1 = 1;
            printf("---------------------------- STUDENT FOUND ----------------------------\n");
            if (strlen(stu_info.stu_middlename) > 0)
            {
                printf("Student Name : %s %s %s\n", stu_info.stu_firstname, stu_info.stu_middlename, stu_info.stu_lastname);
            }
            else
            {
                printf("Student Name : %s %s\n", stu_info.stu_firstname, stu_info.stu_lastname);
            }
            printf("Registration Number : %d\n", stu_info.Stu_registration_number);
            printf("Father Name : %s\n", stu_info.stu_fathername);
            printf("Mother Name : %s\n", stu_info.stu_mothername);
            printf("Father Occupation : %s\n", stu_info.stu_father_occu);
            printf("Mother Occupation : %s\n", stu_info.stu_mother_occu);
            printf("DOB : %s\n", stu_info.stu_dob);
            printf("Gender : %s\n", stu_info.stu_gender);
            printf("Caste : %s\n", stu_info.stu_caste);
            printf("Student Email Id : %s\n", stu_info.stu_email);
            printf("School Email Id : %s\n", stu_info.Stu_School_email);
            printf("Student Mobile Number : %s\n", stu_info.stu_mobile_number);
            printf("Father Mobile Number : %s\n", stu_info.stu_father_number);
            printf("Address : %s, %s, %s, %s, %d\n", stu_info.stu_street, stu_info.stu_area, stu_info.stu_city, stu_info.stu_state, stu_info.stu_zipcode);
            break;
        }
    }

    while (fread(&stu_aca_info, sizeof(stu_aca_info), 1, fp2))
    {
        if (reg_number == stu_aca_info.stu_registration_number)
        {
            found2 = 1;
            printf("Class : %d\n", stu_aca_info.stu_class);
            printf("Section : %c\n", stu_aca_info.stu_section);
            if (stu_aca_info.stu_class > 10)
            {
                printf("Stream : %s\n", stu_aca_info.stream);
            }
            printf("Subjects : ");
            for (int i = 0; i < stu_aca_info.stu_subject_count; i++)
            {
                printf("%s ", stu_aca_info.stu_subjects[i]);
            }
            printf("\n");
            printf("Academic Year : %s\n", stu_aca_info.stu_academic_year);
            break;
        }
    }

    fclose(fp1);
    fclose(fp2);

    if (!found1)
    {
        printf("Student Not Found\n");
    }
    else if (!found2)
    {
        printf("Student Academic Information Not Found\n");
    }
}

// Search Student By Name

void search_student_by_name()
{
    FILE *fp;
    int ch, found = 0;
    struct student_info stu_info;

    char stu_first_name[100], stu_middle_name[100], stu_last_name[100];

    // Clear Buffer
    while ((ch = getchar()) != '\n' && ch != EOF)
        ;

    fp = fopen("Student_information.dat", "rb");
    if (fp == NULL)
    {
        printf("File Not Found\n");
        return;
    }

    readrequiredstring("Enter First Name : ", stu_first_name, sizeof(stu_first_name));
    readoptionalstring("Enter Middle Name : ", stu_middle_name, sizeof(stu_middle_name));
    readrequiredstring("Enter Last Name : ", stu_last_name, sizeof(stu_last_name));

    while (fread(&stu_info, sizeof(stu_info), 1, fp))
    {
        if (strcmp(stu_first_name, stu_info.stu_firstname) == 0 && (strlen(stu_middle_name) == 0 || strcmp(stu_middle_name, stu_info.stu_middlename) == 0) && strcmp(stu_last_name, stu_info.stu_lastname) == 0)
        {
            found = 1;
            print_all_information(stu_info.Stu_registration_number);
        }
    }
    fclose(fp);
    if (!found)
    {
        printf("Student Not Found\n");
    }
}

// Serach Student By Registration Number

void search_student_by_registration()
{
    int reg_number;

    printf("Enter Registration Number : ");
    scanf("%d", &reg_number);
    if (check_student_registration_number(reg_number))
    {
        print_all_information(reg_number);
    }
    else
    {
        printf("Student Not Found\n");
    }
}

// Search Student By Student Email Id

void search_student_by_student_email()
{
    FILE *fp;
    struct student_info stu_info;
    int found = 0, ch;
    char student_email_id[100];

    // Clear Buffer
    while ((ch = getchar()) != '\n' && ch != EOF)
        ;

    fp = fopen("Student_information.dat", "rb");
    if (fp == NULL)
    {
        printf("File Not Open\n");
        return;
    }

    // Check Email Id
    readmail("Enter Student Email Id : ", student_email_id, sizeof(student_email_id));

    while (fread(&stu_info, sizeof(stu_info), 1, fp))
    {
        if (strcmp(student_email_id, stu_info.stu_email) == 0)
        {
            found = 1;
            print_all_information(stu_info.Stu_registration_number);
            break;
        }
    }
    fclose(fp);
    if (!found)
    {
        printf("Student Not Found\n");
    }
}

// Search Student By Scholl Email Id

void search_student_by_school_email()
{
    FILE *fp;
    struct student_info stu_info;
    int found = 0, ch;
    char school_email_id[100];

    // Clear Buffer
    while ((ch = getchar()) != '\n' && ch != EOF)
        ;

    fp = fopen("Student_information.dat", "rb");
    if (fp == NULL)
    {
        printf("File Not Open\n");
        return;
    }

    // Check Email Id
    readmail("Enter School Email Id : ", school_email_id, sizeof(school_email_id));

    while (fread(&stu_info, sizeof(stu_info), 1, fp))
    {
        if (strcmp(school_email_id, stu_info.Stu_School_email) == 0)
        {
            found = 1;
            print_all_information(stu_info.Stu_registration_number);
            break;
        }
    }
    fclose(fp);
    if (!found)
    {
        printf("Student Not Found\n");
    }
}

// Student Mobile Number

void search_student_by_mobile()
{
    FILE *fp;
    struct student_info stu_info;
    int found = 0, ch;
    char student_number[100];

    // Clear Buffer
    while ((ch = getchar()) != '\n' && ch != EOF)
        ;

    fp = fopen("Student_information.dat", "rb");
    if (fp == NULL)
    {
        printf("File Not Open\n");
        return;
    }

    // Check Mobile Number
    readmobilenumber("Enter Student Number : ", student_number, sizeof(student_number));

    while (fread(&stu_info, sizeof(stu_info), 1, fp))
    {
        if (strcmp(student_number, stu_info.stu_mobile_number) == 0)
        {
            found = 1;
            print_all_information(stu_info.Stu_registration_number);
            break;
        }
    }
    fclose(fp);
    if (!found)
    {
        printf("Student Not Found\n");
    }
}

// Search Student By Information

void serach_by_items_list()
{
    printf("1. Student Name\n");
    printf("2. Registration Number\n");
    printf("3. Student Email Id\n");
    printf("4. School Emial Id\n");
    printf("5. Student Mobile Number\n");
    printf("6. Exit\n");
}

void search_student()
{
    int ch, search_option = 0;

    // Clear Buffer
    while ((ch = getchar()) != '\n' && ch != EOF)
        ;

    // Search student By Information
    search_by_items_list();

    // Switch Case
    while (1)
    {
        printf("Enter option : ");
        scanf("%d", &search_option);
        switch (search_option)
        {
        case 1:
            search_student_by_name();
            break;
        case 2:
            search_student_by_registration();
            break;
        case 3:
            search_student_by_student_email();
            break;
        case 4:
            search_student_by_school_email();
            break;
        case 5:
            search_student_by_mobile();
            break;
        case 6:
            printf("Exiting....\n");
            return;
        default:
            printf("Enter Valid option\n");
            break;
        }
    }
}

// ========================== View All Student Function items ==========================

// Print Result

void print_student_result()
{
    FILE *fp;
    struct student_academic_information stu_aca_info;

    fp = fopen("Student_academic.dat", "rb");
    if (fp == NULL)
    {
        printf("File Not Open\n");
        return;
    }

    while (fread(&stu_aca_info, sizeof(stu_aca_info), 1, fp))
    {
        if (LAST_FOUND_REGISTRATION == stu_aca_info.stu_registration_number)
        {
            for (int i = 0; i < stu_aca_info.stu_subject_count; i++)
            {
                printf("%s : %d\n", stu_aca_info.stu_subjects[i], stu_aca_info.stu_subject_numbers[i]);
            }
            fclose(fp);
            return;
        }
    }
    fclose(fp);
    printf("Student Not Found\n");
}

// View Student Result Main Function

void view_student_result()
{
    int ch;

    // Clear Buffer
    while ((ch = getchar()) != '\n' && ch != EOF)
        ;

    search_student_by_registration();

    // Print Result
    print_student_result();
}

// ========================== Count Total Student ==========================

// Total Number of Students in Class

int student_number_class(int stu_class)
{
    FILE *fp;
    int ch, count = 0;
    struct student_academic_information stu_aca_info;

    // Open File
    fp = fopen("Student_academic.dat", "rb");
    if (fp == NULL)
    {
        printf("File Not Open\n");
        return 0;
    }

    // Count Number of Students
    while (fread(&stu_aca_info, sizeof(stu_aca_info), 1, fp))
    {
        if (stu_class == stu_aca_info.stu_class)
        {
            count++;
        }
    }
    fclose(fp);
    return count;
}

// Count Number of Students in Section

int student_number_section(int stu_class, char stu_section)
{
    FILE *fp;
    int ch, count = 0;
    struct student_academic_information stu_aca_info;

    // Open File
    fp = fopen("Student_academic.dat", "rb");
    if (fp == NULL)
    {
        printf("File Not Open\n");
        return 0;
    }

    // Count Number of Students
    while (fread(&stu_aca_info, sizeof(stu_aca_info), 1, fp))
    {
        if (stu_class == stu_aca_info.stu_class && stu_section == stu_aca_info.stu_section)
        {
            count++;
        }
    }
    fclose(fp);
    return count;
}

// Count Total Students in School

int total_number_student()
{
    FILE *fp;
    struct student_info stu_info;
    int count = 0;

    fp = fopen("Student_information.dat", "rb");
    if (!fp)
        return 0;

    while (fread(&stu_info, sizeof(stu_info), 1, fp))
        count++;

    fclose(fp);
    return count;
}

// Count Student

void count_total_student()
{
    int stu_class;
    char stu_section;
    int ch;
    int stu_total_class, stu_total_section, stu_total;

    // Clear Buffer

    while ((ch = getchar()) != '\n' && ch != EOF)
        ;

    // Check Class and Section

    readclass("Enter Class : ", &stu_class);
    readsection("Enter Section : ", stu_class, &stu_section);

    stu_total_class = student_number_class(stu_class);
    stu_total_section = student_number_section(stu_class, stu_section);
    stu_total = total_number_student();

    printf("Total Number of Students in Class %d : %d\n", stu_class, stu_total_class);

    printf("Total Number of Students in Class %d and Section %c = %d\n", stu_class, stu_section, stu_total_section);

    printf("Total Number of Students in School : %d\n", stu_total);
}

// ========================== Delete Student ==========================

// Delete Student Information

int delete_student_information(int stu_reg)
{
    FILE *fp, *temp;
    struct student_info stu_info;
    int found = 0;

    fp = fopen("Student_information.dat", "rb");
    temp = fopen("temp.dat", "wb");

    if (fp == NULL || temp == NULL)
    {
        printf("File Not Open\n");
        return 0;
    }

    while (fread(&stu_info, sizeof(stu_info), 1, fp))
    {
        if (stu_reg == stu_info.Stu_registration_number)
        {
            found = 1;
            continue;
        }
        fwrite(&stu_info, sizeof(stu_info), 1, temp);
    }
    fclose(fp);
    fclose(temp);

    remove("Student_information.dat");
    rename("temp.dat", "Student_information.dat");

    return found;
}

// Delete Student Academic Information

void delete_student_academic_info(int stu_reg)
{
    FILE *fp, *temp;
    struct student_academic_information stu_aca_info;
    int found = 0;

    fp = fopen("Student_academic.dat", "rb");
    temp = fopen("temp.dat", "wb");

    if (fp == NULL || temp == NULL)
    {
        printf("File Not Found\n");
        return;
    }

    while (fread(&stu_aca_info, sizeof(stu_aca_info), 1, fp))
    {
        if (stu_reg == stu_aca_info.stu_registration_number)
        {
            found = 1;
            continue;
        }
        fwrite(&stu_aca_info, sizeof(stu_aca_info), 1, temp);
    }
    fclose(fp);
    fclose(temp);

    remove("Student_academic.dat");
    rename("temp.dat", "Student_academic.dat");
}

// Delete Student Main Function

void delete_student()
{
    int ch, stu_reg_num;

    while (1)
    {
        printf("Enter Registration Number : ");

        if (scanf("%d", &stu_reg_num) != 1)
        {
            printf("Invalid input! Numbers only.\n");
            while ((ch = getchar()) != '\n' && ch != EOF)
                ;
            continue;
        }

        // Clear buffer after valid input
        while ((ch = getchar()) != '\n' && ch != EOF)
            ;

        if (!check_student_registration_number(stu_reg_num))
        {
            printf("Student Not Found\n");
            continue;
        }

        if (delete_student_information(stu_reg_num))
        {
            delete_student_academic_info(stu_reg_num);
            printf("Student Deleted Successfully\n");
            return;
        }
        else
        {
            printf("Deletion Failed\n");
            return;
        }
    }
}

// ========================== Student All Features List ==========================

// Student Feature Select

void student_features(int feature_choice)
{
    switch (feature_choice)
    {
    case 1:
        add_student_personal_info(); // Add Student Personal Information
        break;
    case 2:
        add_student_academic_info(); // Add Student Academic Information
        break;
    case 3:
        see_student_academic_details();
        break;
    case 4:
        update_student_info(); // Update Student Information
        break;
    case 5:
        view_all_students(); // View All Students
        break;
    case 6:
        view_courses(); // View Course Enrolled of a Student
        break;
    case 7:
        search_student(); // Search Student according to - id, Registration number, gmail, name etc.
        break;
    case 8:
        view_student_result(); // View Student Result
        break;
    case 9:
        count_total_student(); // View number of students in school, class and section
        break;
    case 10:
        delete_student(); // Delete Student Detail
        break;
    case 11:
        printf("Exiting....\n"); // Exit Student Feature
        break;
    default:
        printf("Invalid Choice! Try Again.\n"); // Invalid Choice
        break;
    }
}

// ==============================================================================
// ============================== Teacher Function ==============================
// ==============================================================================

// ========================== Add Teacher Information Function Items==========================

// Generate Teacher Registration Number

int generate_teacher_registration_number()
{
    FILE *fp;
    struct teacher_info teach_info;

    fp = fopen("Teacher_information.dat", "rb");

    // If File not exist -> First Teacher
    if (fp == NULL)
    {
        fclose(fp);
        return 10000;
    }
    fseek(fp, 0, SEEK_END);

    // If File Is Empty
    if (ftell(fp) == 0)
    {
        fclose(fp);
        return 10000;
    }

    // Move pointer to last Teacher record
    fseek(fp, -sizeof(struct teacher_info), SEEK_END);

    // Read last teacher
    if (fread(&teach_info, sizeof(struct teacher_info), 1, fp) != 1)
    {
        fclose(fp);
        return 10000;
    }

    // Close File
    fclose(fp);

    return teach_info.teach_registration_number + 1;
}

// Add Teacher Information Function

void add_teacher_information()
{
    FILE *fp;
    struct teacher_info teach_info;
    int ch;

    // Clear Buffer
    while ((ch = getchar()) != '\n' && ch != EOF)
        ;

    fp = fopen("Teacher_information.dat", "ab");
    if (fp == NULL)
    {
        printf("Error: Unable To Open Teacher File\n");
        return;
    }

    // Registration Number
    teach_info.teach_registration_number = generate_teacher_registration_number();                                      // Generated egistration Number
    readrequiredstring("Enter First Name : ", teach_info.teach_firstname, sizeof(teach_info.teach_firstname));          // Enter First Name
    readoptionalstring("Enter Middle Name : ", teach_info.teach_middlename, sizeof(teach_info.teach_middlename));       // Enter Middle Name
    readrequiredstring("Enter Last Name : ", teach_info.teach_lastname, sizeof(teach_info.teach_lastname));             // Enter Last Name
    readmail("Enter Gmail Address : ", teach_info.teach_email, sizeof(teach_info.teach_email));                         // Enter Personal Gmail Id
    readmobilenumber("Enter Mobile Number : ", teach_info.teach_mobile_number, sizeof(teach_info.teach_mobile_number)); // Enter Mobile Number
    readgender("Enter Gender (M/F/O) : ", teach_info.teach_gender, sizeof(teach_info.teach_gender));                    // Enter Gender in 'M'/'F'/'O'
    readcaste("Enter Caste (Gen/OBC/SC/ST) : ", teach_info.teach_caste, sizeof(teach_info.teach_caste));                // Enter Caste - 'OBC'/'GEN'/'ST'/'SC'
    readrequiredstring("Enter Street Name : ", teach_info.teach_street, sizeof(teach_info.teach_street));               // Enter Street Name
    readrequiredstring("Enter Area Name : ", teach_info.teach_area, sizeof(teach_info.teach_area));                     // Enter Area Name
    readrequiredstring("Enter city Name : ", teach_info.teach_city, sizeof(teach_info.teach_city));                     // Enter City Name
    readrequiredstring("Enter State : ", teach_info.teach_state, sizeof(teach_info.teach_state));                       // Enter Stste
    readzipcode("Enter Zipcode : ", &teach_info.teach_zipcode);                                                         // Enter Zipcode in 6 digit code

    // School Email Id

    generate_school_email(
        teach_info.teach_firstname,
        teach_info.teach_lastname,
        teach_info.teach_registration_number,
        teach_info.teach_School_email,
        sizeof(teach_info.teach_School_email));

    printf("Generated Registration Number : %d\n", teach_info.teach_registration_number);
    printf("Generated School Gmail Id : %s\n", teach_info.teach_School_email);

    fwrite(&teach_info, sizeof(struct teacher_info), 1, fp);
    fclose(fp);
}

// ========================== Add Teacher Professional Information Function Items==========================

void readdesignation(char *msg,char *str, int size){

}

// Add Teacher Professional Information

void add_teacher_professional_information()
{
    FILE *fp;
    struct teacher_academic_information teach_aca_info;
    int ch, valid_reg = 0;

    // Clear Buffer
    while ((ch = getchar()) != '\n' && ch != EOF)
        ;

    fp = fopen("Teacher_Academic.dat", "ab");
    if (fp == NULL)
    {
        printf("Error: Unable to open Academic File!\n");
        return;
    }

    while (!valid_reg)
    {
        printf("Enter Registration Number : ");

        if (scanf("%d", &teach_aca_info.teacher_registration_number) != 1)
        {
            printf("Invalid input! Enter numbers only.\n");
            while ((ch = getchar()) != '\n' && ch != EOF)
                ;
            continue;
        }

        // Clear Buffer
        while ((ch = getchar()) != '\n' && ch != EOF)
            ;

        if (!check_teacher_registration_number(teach_aca_info.teacher_registration_number))
        {
            printf("Registration number not found! Please enter valid registration number\n");
            continue;
        }
        valid_reg = 1; // Exit Loop
    }

    readrequiredstring("Enter Designation : ", teach_aca_info.teacher_designation, sizeof(teach_aca_info.teacher_designation));                                             // Designation (PRT, TRT, PGT, Professor,Assistant Professor, etc.)
    reademploymenttype("Enter Employee Type : ", teach_aca_info.teacher_employment_type, sizeof(teach_aca_info.teacher_employment_type));                                   // Permanent, Contract, Visiting
    readhighestqualification("Enter Highest Qualification : ", teach_aca_info.teacher_highest_qualification, sizeof(teach_aca_info.teacher_highest_qualification));         
    readspecialization("Enter Specialization : ", teach_aca_info.teacher_specialization, sizeof(teach_aca_info.teacher_specialization));
    printf("Enter Number of Years of Experience : ");
    readInt(&teach_aca_info.teacher_experience_years);
    printf("Enter Joining Year : ");
    readInt(&teach_aca_info.teacher_joining_year);
    readteachinglevel("Enter Teaching Level : ", teach_aca_info.teaching_level, sizeof(teach_aca_info.teaching_level));
    printf("Enter Number of Subjects You Want to Teach : ");
    readInt(&teach_aca_info.teacher_subject_count);
    readsubjects_takes(teach_aca_info.teacher_subjects, teach_aca_info.teacher_subject_count);
    readnumberclasses("Enter Number of Classes You Want to Teach : ", &teach_aca_info.teacher_preferred_class_count);
    readclassestakes(teach_aca_info.teacher_preferred_classes, teach_aca_info.teacher_preferred_class_count);

    fwrite(&teach_aca_info, sizeof(teach_aca_info), 1, fp);
    fclose(fp);
}

// Teacher Features List

void teacher_features(int feature_option)
{
    switch (feature_option)
    {
    case 1:
        add_teacher_information();
        break;
    case 2:
        add_teacher_professional_information();
        break;
    case 3:
        update_teacher_information();
        break;
    case 4:
        view_all_teachers();
        break;
    case 5:
        view_student_under();
        break;
    case 6:
        view_courses_under();
        break;
    case 7:
        view_total_student_under();
        break;
    case 8:
        view_class_section_under();
        break;
    case 9:
        assign_new_class();
        break;
    case 10:
        search_teacher();
        break;
    case 11:
        view_student_result();
        break;
    case 12:
        view_class_result();
        break;
    case 13:
        add_result();
        break;
    case 14:
        printf("Exiting...\n");
        break;
    default:
        printf("Enter valid Option\n");
        break;
    }
}

// ========================== Main Function ==========================

// Main Function
int main()
{
    int dashboard_option = 0, option = 0;
    while (dashboard_option != 4)
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

            if (!readInt(&option))
            {
                continue;
            }
            if (option == 11)
            {
                break;
            }

            student_features(option);
            break;

        case 2:
            // Calling Teacher Dashboard
            teacher_dashboard();

            printf("Enter your choice = ");

            // Invalid Option Check

            if (!readInt(&option))
            {
                continue;
            }
            if (option == 14)
            {
                break;
            }

            teacher_features(option);
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