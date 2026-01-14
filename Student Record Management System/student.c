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

// Add Student Acaedmic Data

struct student_academic_information
{
    int stu_registration_number; // Student Registration Number

    int stu_class;    // Student Current Class
    char stu_section; // Student Class Section
    int stu_section_count;
    char stream[10]; // Stream of student only if the class is greater than 10

    char stu_subjects[MAX_SUBJECTS][SUBJECT_LEN]; // Subjects Enrolled to student
    int stu_subject_count;                        // Number of subject Enrolled

    float stu_last_percentage; // Last Year Percentage
    char stu_last_school[100]; // Last School Name

    char stu_last_address_street[100]; // Last School Street Name When Not Same
    char stu_last_address_area[100];   // Last School Area Name When Not Same
    char stu_last_address_city[100];   // Last School City Name When Not Same
    char stu_last_address_state[100];  // Last School State Name When Not Same

    char stu_last_session_year[10]; // Last Session Year in 'YYYY-YYYY' Format
    char stu_academic_year[10];     // Current Session Year in 'YYYY-YYYY' Foramt
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
    printf("1. Add Student Personal Details");
    printf("2. Add Academic Details\n");
    printf("3. See Student Academic Details.\n");
    printf("4. Update Student Information\n");
    printf("5. View All Students\n");
    printf("6. View Courses & Teachers Assigned\n");
    printf("7. Search Student\n");
    printf("8. Sort Student Records\n");
    printf("9. View Student Result\n");
    printf("10. Count Total Students\n");
    printf("11. Delete Student Record\n");
    printf("12. Exit\n");
}

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

// ========================== add_student_personal_info Function Items==========================

// Gennerate Registration Number

int generate_registration_number()
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

void generate_student_email(char *firstname, char *lastname, int reg_num, char *email, int size)
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
    st_in.Stu_registration_number = generate_registration_number();

    readrequiredstring("Enter First Name : ", st_in.stu_firstname, sizeof(st_in.stu_firstname));                   // Enter First Name
    readoptionalstring("Enter Middle Name : ", st_in.stu_middlename, sizeof(st_in.stu_middlename));                // Enter Middle Name
    readrequiredstring("Enter Last Name : ", st_in.stu_lastname, sizeof(st_in.stu_lastname));                      // Enter Last Name
    readrequiredstring("Enter Father's Name : ", st_in.stu_fathername, sizeof(st_in.stu_fathername));              // Enter Father's Name
    readrequiredstring("Enter Mother's Name : ", st_in.stu_mothername, sizeof(st_in.stu_mothername));              // Enter Mother's Name
    readrequiredstring("Enter Father's Occupation : ", st_in.stu_father_occu, sizeof(st_in.stu_father_occu));      // Enter Father's Occupation
    readrequiredstring("Enter Mother's Occupation : ", st_in.stu_mother_occu, sizeof(st_in.stu_mother_occu));      // Enter Mother's Occupation
    readrequiredstring("Enter D.O.B (DD/MM/YYYY): ", st_in.stu_dob, sizeof(st_in.stu_dob));                        // Enter DOB in DD/MM//YYYY Format
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

    generate_student_email( // School Gmail Id (Autogenerate)
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

// Check Registration Number exist or not

int check_registration_number_exist(int reg_number)
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

        if (!check_registration_number_exist(st_academic.stu_registration_number))
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
        while ((ch = getchar()) != '\n' && ch != EOF);

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
        if (!check_registration_number_exist(registration_number))
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
            printf("Search another student? (YES/NO): ");
            scanf("%9s", choice);

            while ((ch = getchar()) != '\n' && ch != EOF);

            // Convert to uppercase
            for (int i = 0; choice[i]; i++)
                choice[i] = toupper((unsigned char)choice[i]);

            if (strcmp(choice, "YES") == 0)
            {
                break; // go back to main loop (ask reg number again)
            }
            else if (strcmp(choice, "NO") == 0)
            {
                return; // exit function completely
            }
            else
            {
                printf("Invalid input! Please enter YES or NO.\n");  // loop continues automatically
            }
        }
    }
}

// ========================== See Student Academic Deatils Function Items==========================

void update_student_information(struct student_info *stu_info){
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

// Update Student Information

void update_student_info(){
    int ch, registration_number,update_option = 0;
    struct student_info st_in;
    char ask_update[3];
    while (1)
    {
        printf("Choose Which Item You Want to Update\n");
        update_student_information(&st_in);
        while (1)
        {
            printf("Enter option : ");
            scanf("%d",&update_option);
            switch (update_option)
            {
            case 1:
                update_student_name();
                break;
            case 2:
                update_father_name();
                break;
            case 3:
                update_mother_name();
                break;
            case 4:
                update_father_occupation();
                break;
            case 5:
                update_mother_occupation();
                break;
            case 6:
                update_dob();
                break;
            case 7:
                update_gender();
                break;
            case 8:
                update_caste();
                break;
            case 9:
                update_student_email();
                break;
            case 10:
                update_student_mobile_number();
                break;
            case 11:
                update_father_mobile_number();
                break;
            case 12:
                update_address();
                break;
            case 13:
                printf("Exiting...\n");
                break;
            default:
                printf("Enter Valid Option\n");
                break;
            }

            printf("Want to Update More Details (Yes/No) : ");
            scanf("%s",&ask_update);

        }
        
    }
    
}

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
    case 4:
        update_student_info(); // Update Student Information
        break;
    case 5:
        view_all_students(); // View All Students
        break;
    case 6:
        view_course_teacher(); // View Course and Teacher Enrolled of a Student
        break;
    case 7:
        search_student(); // Search Student according to - id, Registration number, gmail, name etc.
        break;
    case 8:
        sort_student_record(); // Sort all Student Details by name, registration number, etc.
        break;
    case 9:
        view_student_result(); // View Student Result
        break;
    case 10:
        count_total_student(); // View number of students in school, class and section
        break;
    case 11:
        delete_student(); // Delete Student Detail
        break;
    case 12:
        printf("Exiting....\n"); // Exit Student Feature
        break;
    default:
        printf("Invalid Choice! Try Again.\n"); // Invalid Choice
        break;
    }
}

// ========================== Main Function ==========================

// Main Function
int main()
{
    int dashboard_option, student_option;
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

            if (!readInt(&student_dashboard))
            {
                continue;
            }
            while (student_dashboard != 12)
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