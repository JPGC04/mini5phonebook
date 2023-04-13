struct PHONE_NODE {
    char name[50];
    char birthdate[12];
    char phone[15];
    struct PHONE_NODE *next;
};

extern struct PHONE_NODE *head;

int addRecord(char *name, char *birthdate, char *phone);
struct PHONE_NODE *findRecord(char *name);
int listRecords();
int saveCSV(char *filename);
int loadCSV(char *filename);
void printHeading();
void printContent(char *name, char *birthdate, char *phone);
int delete(char name[]);
int clear();
