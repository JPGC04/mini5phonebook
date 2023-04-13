struct PHONE_NODE {
        char name[50];
        char birthdate[12];
        char phone[15];
        struct PHONE_NODE *next;
};

extern struct PHONE_NODE *head = NULL;
