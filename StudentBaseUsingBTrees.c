#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define m 5

typedef enum {CS,EC,EE,ME,CV} dept_code;

typedef enum {STD,FEE,APP,ATT} rec;

typedef struct RollNo_tag //Format : yy-dc-no
{
	int year; 
	dept_code dc;
	int roll;
}RollNo;

typedef struct StudentRecord
{
    RollNo rollno;
	char name[50];
	dept_code code;
	int year;
	int classes_conducted[5];//for 5 courses
	int classes_attended[5];
}StdRec;

typedef struct FeeStatustag
{
    RollNo rollno;
	char status[7];
}FeeStat;

typedef struct ApplicantRecord
{
    RollNo rollno;
	char name[50];
	char application[2]; // A/NA
}AppRec;

typedef struct AttendanceRecordtag
{
    RollNo rollno;
	dept_code code;
	float attendance;
}AttRec;

typedef union data_tag
{
    StdRec SR;
    FeeStat FS;
    AppRec ApR;
    AttRec AR;
}Record;

typedef struct B_Tree_Node_tag
{
    Record data[m-1];
    rec r;
    int num; //number of data items present
    struct B_Tree_Node_tag* child[m];
}B_Tree_Node;

void InitializeStdRec(StdRec* ptr)
{
    int i;
    ptr->name[0] = '\0';
    ptr->code = -1;
    ptr->year = 0;
    ptr->rollno.year = 0;
    ptr->rollno.dc = -1;
    ptr->rollno.roll = 0;
    for (i = 0; i < 5; i++) {
        ptr->classes_conducted[i] = 0;
        ptr->classes_attended[i] = 0;
    }
}

void InitializeFeeStat(FeeStat* ptr)
{
    ptr->rollno.year = 0;
    ptr->rollno.dc = -1;
    ptr->rollno.roll = 0;
    ptr->status[0] = '\0';
}

void InitializeAppRec(AppRec* ptr)
{
    ptr->rollno.year = 0;
    ptr->rollno.dc = -1;
    ptr->rollno.roll = 0;
    ptr->name[0] = '\0';
    ptr->application[0] = '\0';
}

void InitializeAttRec(AttRec* ptr)
{
    ptr->rollno.year = 0;
    ptr->rollno.dc = -1;
    ptr->rollno.roll = 0;
    ptr->code = -1;
    ptr->attendance = 0.0;
}

void Initialize(B_Tree_Node** npptr)

{
    int i;
    B_Tree_Node* nptr=*npptr;
    nptr->num = 0;
    for (i = 0; i < m-1; i++) {
        if (nptr->r ==STD)
            InitializeStdRec(&nptr->data[i].SR);
        else if (nptr->r == FEE)
            InitializeFeeStat(&nptr->data[i].FS);
        else if (nptr->r == APP)
            InitializeAppRec(&nptr->data[i].ApR);
        else
            InitializeAttRec(&nptr->data[i].AR);
        nptr->child[i] = NULL;
    }
    nptr->child[i] = NULL;
    *npptr = nptr;
}

int cmp(Record r1,Record r2,rec r)
{
    int ret_val;
    if (r == STD)
    {
        if (r1.SR.rollno.year > r2.SR.rollno.year)
            ret_val = -1;
        else if (r1.SR.rollno.year < r2.SR.rollno.year)
            ret_val = 1;
        else 
        {
            if (r1.SR.rollno.dc < r2.SR.rollno.dc)
                ret_val = -1;
            else if (r1.SR.rollno.dc > r2.SR.rollno.dc)
                ret_val = 1;
            else
            {
                if (r1.SR.rollno.roll < r2.SR.rollno.roll)
                    ret_val = -1;
                else 
                    ret_val = 1;
            }
        }
    }
    else if (r == FEE)
    {
        if (r1.FS.rollno.year > r2.FS.rollno.year)
            ret_val = -1;
        else if (r1.FS.rollno.year < r2.FS.rollno.year)
            ret_val = 1;
        else 
        {
            if (r1.FS.rollno.dc < r2.FS.rollno.dc)
                ret_val = -1;
            else if (r1.FS.rollno.dc > r2.FS.rollno.dc)
                ret_val = 1;
            else
            {
                if (r1.FS.rollno.roll < r2.FS.rollno.roll)
                    ret_val = -1;
                else 
                    ret_val = 1;
            }
        }
    }
    else if (r == APP)
    {
        if (r1.ApR.rollno.year > r2.ApR.rollno.year)
            ret_val = -1;
        else if (r1.ApR.rollno.year < r2.ApR.rollno.year)
            ret_val = 1;
        else 
        {
            if (r1.ApR.rollno.dc < r2.ApR.rollno.dc)
                ret_val = -1;
            else if (r1.ApR.rollno.dc > r2.ApR.rollno.dc)
                ret_val = 1;
            else
            {
                if (r1.ApR.rollno.roll < r2.ApR.rollno.roll)
                    ret_val = -1;
                else 
                    ret_val = 1;
            }
        }
    }
    else
    {
        if (r1.AR.rollno.year > r2.AR.rollno.year)
            ret_val = -1;
        else if (r1.AR.rollno.year < r2.AR.rollno.year)
            ret_val = 1;
        else 
        {
            if (r1.AR.rollno.dc < r2.AR.rollno.dc)
                ret_val = -1;
            else if (r1.AR.rollno.dc > r2.AR.rollno.dc)
                ret_val = 1;
            else
            {
                if (r1.AR.rollno.roll < r2.AR.rollno.roll)
                    ret_val = -1;
                else 
                    ret_val = 1;
            }
        }
    }
    return ret_val;
}

B_Tree_Node* Insert(B_Tree_Node* root,Record d)
{
    int i,j;
    if ((root->num < m-1) && (root->child[0] == NULL))
    {
        i = 0;
        while (cmp(d,root->data[i],root->r) >= 0) {
            i++;
        }
        for(j = root->num-1; j >= i; j--) {
            root->data[j+1] = root->data[j];
        }
        root->data[i] = d;
        root->num++;
    }
    else if ((root->num == m-1)  && (root->child[0] == NULL))
    {
        B_Tree_Node* new1 = malloc(sizeof(B_Tree_Node));
        B_Tree_Node* new2 = malloc(sizeof(B_Tree_Node));
        if (cmp(d,root->data[m/2 - 1],root->r) < 0)
        {
            new2->data[0] = root->data[m/2 - 1];
            new2->num = 1;

            for(i = 0; i < m/2 ; i++)
            {
                new1->data[i] = root->data[i + m/2];
            }
            new1->num = m/2 - 1;
            root->num = m/2 - 1;
            root = Insert(root,d);

            new2->child[0] = root;
            new2->child[1] = new1;
            root = new2;
        }
        else if ((cmp(d,root->data[m/2 - 1],root->r) > 0) && (cmp(d,root->data[m/2],root->r) < 0))
        {
            for(i = 0; i < m/2 ; i++)
            {
                new1->data[i] = root->data[i + m/2];
            }
            new1->num = m/2 - 1;
            root->num = m/2;

            new2->data[0] = d;
            new2->child[0] = root;
            new2->child[1] = new1;
            root = new2;
        }
        else
        {
            new2->data[0] = root->data[m/2];
            new2->num = 1;

            for(i = 0; i < m/2 - 1; i++)
            {
                new1->data[i] = root->data[i + m/2 + 1];
            }
            new1->num = m/2 - 2;
            new1 = Insert(new1,d);
            root->num = m/2;

            new2->child[0] = root;
            new2->child[1] = new2;
            root = new2;
        }
    }
    else if ((root->num < m-1) && (root->child != NULL))
    {
        i = 0;
        while (cmp(d,root->data[i],root->r) >= 0) {
            i++;
        }
        root->child[i] = Insert(root->child[i],d);
        if ((root->child[i])->num == 1)
        {
            i = 0;
            while (cmp((root->child[i])->data[0],root->data[i],root->r) >= 0) {
                i++;
            }
            for(j = root->num-1; j > i; j--) {
                root->data[j+1] = root->data[j];
                root->child[j+2] = root->child[j+1];
            }
            root->data[i] = (root->child[i])->data[0];
            root->child[i+1] = (root->child[i])->child[1];
            root->child[i] = (root->child[i])->child[0];
        }
    }
    else
    {
        i = 0;
        while (cmp(d,root->data[i],root->r) >= 0) {
            i++;
        }
        root->child[i] = Insert(root->child[i],d);
        if (root->child[i]->num == 1)
        {
            B_Tree_Node* new;
            new = root->child[i];
            B_Tree_Node* new1 = malloc(sizeof(B_Tree_Node));
            B_Tree_Node* new2 = malloc(sizeof(B_Tree_Node));
            if (i < (m/2 - 1))
            {
                new2->data[0] = root->data[m/2 - 1];
                new2->num = 1;

                for(j = 0; j < m/2 ; j++)
                {
                    new1->data[j] = root->data[j + m/2];
                    new1->child[j] = root->child[j + m/2];
                    root->child[j + m/2] = NULL;
                }
                new1->child[j] = root->child[j + m/2];
                new1->num = m/2 - 1;
                root->num = m/2 ;
                for (j = root->num - 1; j > i; j++)
                {
                    root->data[j] = root->data[j-1];
                    root->child[j+1] = root->child[j-1];
                }
                root->data[i] = new->data[0];
                root->child[i] = new->child[0];
                root->child[i+1] = new->child[1];

                new2->child[0] = root;
                new2->child[1] = new1;
                root = new2;
            }
            else if ((i > (m/2 - 1)) && (i < m/2))
            {
                for(j = 0; j < m/2 ; j++)
                {
                    new1->data[j] = root->data[j + m/2];
                    new1->child[j] = root->child[j + m/2];
                    root->child[j + m/2] = NULL;
                }
                new1->child[j] = root->child[j + m/2];
                new1->num = m/2 - 1;
                root->num = m/2;

                root->child[root->num] = new->child[0];
                new2->child[0] = new->child[1];
                new->child[0] = root;
                new->child[1] = new1;
                root = new;
            }
            else
            {
                new2->data[0] = root->data[m/2];
                new2->num = 1;

                for(j = 0; j < m/2 - 1; j++)
                {
                    new1->data[j] = root->data[j + m/2 + 1];
                    new1->child[j] = root->child[j + m/2 + 1];
                    root->child[j + m/2 + 1] = NULL;
                }
                new1->num = m/2 - 1;
                root->num = m/2;
                for (j = new1->num - 1; j > i; j++)
                {
                    new1->data[j] = new1->data[j-1];
                    new1->child[j+1] = new1->child[j];
                }
                new1->data[i] = new->data[0];
                new1->child[i] = new->child[0];
                new1->child[i+1] = new->child[1];

                new2->child[0] = root;
                new2->child[1] = new2;
                root = new2;
            }
        }
        printf("\nInserted 4\n");
    }
    return root;
}

int* FindMCC(B_Tree_Node* root)
{
    int i;
    int *mcc;
    mcc = (int*)malloc(5*sizeof(int));
    for (i = 0; i < 5; i++)
    {
        mcc[i] = 0;
    }
    for (i = 0; i < root->num; i++)
    {
        if (root->child[i] != NULL)
            mcc = FindMCC(root);
        if (root->data[i].SR.code == CS)
        {
            int j;
            for (j = 1; j < 5; j++)
            {
                if (root->data[i].SR.classes_conducted[j] > root->data[i].SR.classes_conducted[mcc[0]])
                    mcc[0] = j;
            }
        }
        else if (root->data[i].SR.code == EC)
        {
            int j;
            for (j = 1; j < 5; j++)
            {
                if (root->data[i].SR.classes_conducted[j] > root->data[i].SR.classes_conducted[mcc[1]])
                    mcc[1] = j;
            }
        }
        else if (root->data[i].SR.code == EE)
        {
            int j;
            for (j = 1; j < 5; j++)
            {
                if (root->data[i].SR.classes_conducted[j] > root->data[i].SR.classes_conducted[mcc[2]])
                    mcc[2] = j;
            }
        }
        else if (root->data[i].SR.code == ME)
        {
            int j;
            for (j = 1; j < 5; j++)
            {
                if (root->data[i].SR.classes_conducted[j] > root->data[i].SR.classes_conducted[mcc[3]])
                    mcc[3] = j;
            }
        }
        else
        {
            int j;
            for (j =0; j < 5; j++)
            {
                if (root->data[i].SR.classes_conducted[j] > root->data[i].SR.classes_conducted[mcc[4]])
                    mcc[4] = j;
            }
        }
    }
    if (root->child[i] != NULL)
        mcc = FindMCC(root->child[i]);
    return mcc;
}

int* FindMax(B_Tree_Node* root)
{
    int *mcc;
    mcc = FindMCC(root);
    int *max = malloc(5*sizeof(int));
    int i;
    for (i = 0; i < 5; i++) {
        max[i] = 0;
    }
    for (i = 0; i < root->num; i++)
    {
        if (root->child[i] != NULL)
            max = FindMax(root);
        if (root->data[i].SR.code == CS)
        {
            if (root->data[i].SR.classes_attended[mcc[0]] > max[0])
                max[0] = root->data[i].SR.classes_attended[mcc[0]];            
        }
        else if (root->data[i].SR.code == EC)
        {
            if (root->data[i].SR.classes_attended[mcc[1]] > max[1])
                max[1] = root->data[i].SR.classes_attended[mcc[1]];
        }
        else if (root->data[i].SR.code == EE)
        {
            if (root->data[i].SR.classes_attended[mcc[2]] > max[2])
                max[2] = root->data[i].SR.classes_attended[mcc[2]];
        }
        else if (root->data[i].SR.code == ME)
        {
            if (root->data[i].SR.classes_attended[mcc[3]] > max[3])
                max[3] = root->data[i].SR.classes_attended[mcc[3]];
        }
        else
        {
            if (root->data[i].SR.classes_attended[mcc[4]] > max[4])
                max[4] = root->data[i].SR.classes_attended[mcc[4]];
        }
    }
    if (root->child[i] != NULL)
        max = FindMax(root->child[i]);
    return max;
}

void display(B_Tree_Node* root)
{
    int i;
    for (i = 0; i < root->num; i++)
    {
        if (root->child[i] != NULL)
        {
            display(root->child[i]);
    	}
		if (root->r == STD)
        {
            printf("\nName of student : %s\n",root->data[i].SR.name);
            if (root->data[i].SR.code == CS) {
                printf("Department : CS\n");
            }
            else if (root->data[i].SR.code == EC) {
                printf("Department : EC\n");
            }
            else if (root->data[i].SR.code == EE) {
                printf("Department : EE\n");
            }
            else if (root->data[i].SR.code == ME) {
                printf("Department : ME\n");
            }
            else {
                printf("Department : CV\n");
            }
            printf("Year : %d\n",root->data[i].SR.year);
            printf("Roll no : %d\n",root->data[i].SR.rollno.roll);
            int j;
            printf("Classes conducted: ");
            for (j = 0; j < 5; j++) {
                printf("%d ",root->data[i].SR.classes_conducted[j]);
            }
            printf("\nClasses attended: ");
            for (j = 0; j < 5; j++) {
                printf("%d ",root->data[i].SR.classes_attended[j]);
            }
        }
        else if (root->r == FEE)
        {
            printf("Roll no : %d\n",root->data[i].FS.rollno.roll);
            printf("Fee status : %s\n",root->data[i].FS.status);
        }
        else if (root->r == APP)
        {
            printf("Name of student : %s\n",root->data[i].ApR.name);
            printf("Roll no : %d\n",root->data[i].ApR.rollno.roll);
            printf("Application status : %s\n",root->data[i].ApR.application);
        }
    }
    if (root->child[i] != NULL) {
        display(root->child[i]);
    }
}

void CreateAR(B_Tree_Node** root1,B_Tree_Node** root2,B_Tree_Node** root3,B_Tree_Node** root4,B_Tree_Node** root5,B_Tree_Node* root,int* max,int* mcc)
{
    int i;
    for (i = 0; i < root->num; i++)
    {
        if (root->child[i] != NULL)
            CreateAR(root1,root2,root3,root4,root5,root->child[i],max,mcc);
        Record r;
        r.AR.rollno = root->data[i].SR.rollno;
        r.AR.code = root->data[i].SR.code;
        if (r.AR.code == CS) {
			r.AR.attendance = (float) (root->data[i].SR.classes_attended[mcc[0]]*100)/max[0];
        }
		else if (r.AR.code == EC) {
			r.AR.attendance = (float) (root->data[i].SR.classes_attended[mcc[1]]*100)/max[1];
        }
		else if (r.AR.code == EE) {
			r.AR.attendance = (float) (root->data[i].SR.classes_attended[mcc[2]]*100)/max[2];
        }
		else if (r.AR.code == ME) {
			r.AR.attendance = (float) (root->data[i].SR.classes_attended[mcc[3]]*100)/max[3];
        }
		else {
			r.AR.attendance = (float) (root->data[i].SR.classes_attended[mcc[4]]*100)/max[4];
        }
        //r.AR.attendance = (float) (root->data[i].SR.classes_attended[mcc[r.AR.code]]*100)/max[r.AR.code];

        if (root->data[i].AR.rollno.year == 2022) {
            *root1 = Insert(*root1,r);
        }
        else if (root->data[i].AR.rollno.year == 2021) {
            *root2 = Insert(*root2,r);
        }
        else if (root->data[i].AR.rollno.year == 2020) {
            *root3 = Insert(*root3,r);
        }
        else {
            *root4 = Insert(*root4,r);
        }
        *root5 = Insert(*root5,r);
    }
    if (root->child[i] != NULL) {
        CreateAR(root1,root2,root3,root4,root5,root->child[i],max,mcc);
    }
}

void NotApplied(B_Tree_Node* root)
{
    int i;
    for (i = 0; i < root->num; i++)
    {
        if (root->child[i] != NULL) 
            NotApplied(root->child[i]);
        if (strcmp(root->data[i].ApR.application,"NA") == 0) {
            printf("Year : %d\n",root->data[i].ApR.rollno.year);
            if (root->data[i].ApR.rollno.dc == CS) {
                printf("Department : CS\n");
            }
            else if (root->data[i].ApR.rollno.dc == EC) {
                printf("Department : EC\n");
            }
            else if (root->data[i].ApR.rollno.dc == EE) {
                printf("Department : EE\n");
            }
            else if (root->data[i].ApR.rollno.dc == ME) {
                printf("Department : ME\n");
            }
            else {
                printf("Department : CV\n");
            }
            printf("Name of student : %s\n",root->data[i].ApR.name);
        }
    }
}

void Eligible(B_Tree_Node* ARptr,B_Tree_Node* FSptr,B_Tree_Node* ApRptr)
{
    int i;
    for (i = 0; i < ARptr->num; i++)
    {
        if (ARptr->child[i] != NULL)
            Eligible(ARptr->child[i],FSptr->child[i],ApRptr->child[i]);
        if ((ARptr->data[i].AR.attendance > 75.0) && (strcmp(FSptr->data[i].FS.status,"clear") == 0) && (strcmp(ApRptr->data[i].ApR.application,"A") == 0))
        {
            printf("Year : %d\n",ARptr->data[i].AR.rollno.year);
            if (ARptr->data[i].AR.code == CS) {
                printf("Department : CS\n");
            }
            else if (ARptr->data[i].AR.code == EC) {
                printf("Department : EC\n");
            }
            else if (ARptr->data[i].AR.code == EE) {
                printf("Department : EE\n");
            }
            else if (ARptr->data[i].AR.code == ME) {
                printf("Department : ME\n");
            }
            else {
                printf("Department : CV\n");
            }
            printf("Roll no : %d\n",ARptr->data[i].AR.rollno.roll);
        }
    }
    if (ARptr->child[i] != NULL)
        Eligible(ARptr->child[i],FSptr->child[i],ApRptr->child[i]);
}

void Attendance(B_Tree_Node* root)
{
    int i;
    for (i = 0; i < root->num; i++)
    {
        if (root->child[i] != NULL)
            Attendance(root->child[i]);
        if (root->data[i].AR.attendance <= 75.0)
        {
            printf("Year : %d\n",root->data[i].AR.rollno.year);
            if (root->data[i].AR.code == CS) {
                printf("Department : CS\n");
            }
            else if (root->data[i].AR.code == EC) {
                printf("Department : EC\n");
            }
            else if (root->data[i].AR.code == EE) {
                printf("Department : EE\n");
            }
            else if (root->data[i].AR.code == ME) {
                printf("Department : ME\n");
            }
            else {
                printf("Department : CV\n");
            }
            printf("Roll no : %d\n",root->data[i].AR.rollno);
        }
    }
    if (root->child[i] != NULL)
        Attendance(root->child[i]);
}

void Status(B_Tree_Node* ARptr,B_Tree_Node* FSptr,B_Tree_Node* SRptr)
{
    int i;
    for (i = 0; i < ARptr->num; i++)
    {
        if (ARptr->child[i] != NULL)
            Status(ARptr->child[i],FSptr->child[i],SRptr->child[i]);
        if ((ARptr->data[i].AR.attendance > 75.0) && (strcmp(FSptr->data[i].FS.status,"pending") == 0))
        {
            printf("Name of Student : %s\n",SRptr->data[i].SR.name);
        }
    }
    if (ARptr->child[i] != NULL)
       Status(ARptr->child[i],FSptr->child[i],SRptr->child[i]);
}

void Defaulter(B_Tree_Node* ARptr,B_Tree_Node* FSptr)
{
    int i;
    int max[5];
    for (i = 0; i < 5; i++)
        max[i] = 0;
    for (i = 0; i < ARptr->num; i++)
    {
        if (ARptr->child[i] != NULL) {
            Defaulter(ARptr->child[i],FSptr->child[i]);
        }
        if ((ARptr->data[i].AR.attendance <= 75.0) || (strcmp(FSptr->data[i].FS.status,"pending") == 0)) 
        {
            if (ARptr->data[i].AR.code == CS) {
                printf("Department : CS\n");
            }
            else if (ARptr->data[i].AR.code == EC) {
                printf("Department : EC\n");
            }
            else if (ARptr->data[i].AR.code == EE) {
                printf("Department : EE\n");
            }
            else if (ARptr->data[i].AR.code == ME) {
                printf("Department : ME\n");
            }
            else {
                printf("Department : CV\n");
            }
            printf("Roll no : %d\n",ARptr->data[i].AR.rollno.roll);
            printf("Attendance : %.2f\n",ARptr->data[i].AR.attendance);
            printf("Fee status : %s\n",FSptr->data[i].FS.status);
            max[ARptr->data[i].AR.rollno.dc]++;
        }
    }
    if (ARptr->child[i] != NULL) {
        Defaulter(ARptr->child[i],FSptr->child[i]);
    }
    int d = 0;
    for (i = 1; i < 5; i++) {
        if (max[i] > max[d])
            d = i;
    }
    if (d == 0)
        printf("\nMax Defaulters are in : CS\n");
    else if (d == 1)
        printf("\nMax Defaulters are in : EC\n");
    else if (d == 2)
        printf("\nMax Defaulters are in : EE\n");
    else if (d == 3)
        printf("\nMax Defaulters are in : ME\n");
    else
        printf("\nMax Defaulters are in : CV\n");   
}

int comp(RollNo no1,RollNo no2)
{
    int ret_val = 0;
    if (no1.year > no2.year)
        ret_val = -1;
    else if (no1.year < no2.year)
        ret_val = 1;
    else 
    {
        if (no1.dc < no2.dc)
            ret_val = -1;
        else if (no1.dc > no2.dc)
            ret_val = 1;
        else
        {
            if (no1.roll < no2.roll)
                ret_val = -1;
            else 
                ret_val = 1;
        }
    }
    return ret_val;
}

void RangeSearch(B_Tree_Node* root,RollNo num1,RollNo num2)
{
    int i;
    for (i = 0; i < root->num; i++)
    {
        if (root->child[i] != NULL)
        {
            RangeSearch(root->child[i],num1,num2);
        }
        if ((comp(root->data[i].SR.rollno,num1) > 0) && comp(root->data[i].SR.rollno,num2) < 0) 
        {
            printf("Name of Student : %s\n",root->data[i].SR.name);
        }
    }
    if (root->child[i] != NULL)
    {
       RangeSearch(root->child[i],num1,num2);
    }
}

int Delete(B_Tree_Node** pptr,RollNo num)
{
    B_Tree_Node* root = *pptr;
    int ret_val = 1;
    int i=0;
    while (comp(num,root->data[i].SR.rollno) > 0) {
        i++;
    }
    if (comp(num,root->data[i].SR.rollno) == 0)  
    {
        if ((root->child[i] == NULL) && (root->num-1 >= ceil(m/2)-1))
        {
            int j;
            for (j = i; j < root->num-1; j++) {
                root->data[j] = root->data[j+1]; 
            }
            root->num--;
        }
        else if ((root->child[i] == NULL) && (root->num == ceil(m/2)-1))
        {
            int j;
            for (j = i; j >= 0; j--) {
                root->data[j] = root->data[j-1];
            }
            root->num--;
        }
        else
        {
            root->data[i] = root->child[i+1]->data[0];
            ret_val = Delete(&root->child[i+1],root->data[i].SR.rollno);
            if ((ret_val == 1) && (root->num == ceil(m/2)-1) && (root->child[i+1]->num < ceil(m/2)))
            {
                int j;
                B_Tree_Node* new = root->child[i+1];
                for (j = 1; j <= new->num; j++)
                {
                    root->child[j+i] = new->child[j];
                    root->data[j+i] = new->data[j];
                    root->num++;
                }
                root->child[j+i] = new->child[j];
                free(new);
            }
            else if (root->num == 1)
            {
                
            }
        }
    } 
    else
    {
        if (root->child[i] == NULL) {
            ret_val = 0;
        }
        else {
            ret_val = Delete(&root->child[i],num);
            int j = i;
            while ((ret_val == 1) && (root->child[j]->num < ceil(m/2)-1))
            {
                root->child[j]->num++;
                root->child[j]->data[0] = root->data[j-1];
                root->data[j-1] = root->child[j-1]->data[root->num-1];
                ret_val = Delete(&root->child[j-1],root->data[j-1].SR.rollno);
                j--;
            }
        }
    }
    *pptr = root;
    return ret_val;
}

int main()
{
    B_Tree_Node* SRptr = malloc(sizeof(B_Tree_Node));
    SRptr->r = STD;
    B_Tree_Node* FSptr = malloc(sizeof(B_Tree_Node));
    FSptr->r = FEE;
    B_Tree_Node* ApRptr = malloc(sizeof(B_Tree_Node));
    ApRptr->r = APP;
    B_Tree_Node* ARptr = malloc(sizeof(B_Tree_Node));
    B_Tree_Node* ARptr1 = malloc(sizeof(B_Tree_Node));
    B_Tree_Node* ARptr2 = malloc(sizeof(B_Tree_Node));
    B_Tree_Node* ARptr3 = malloc(sizeof(B_Tree_Node));
    B_Tree_Node* ARptr4 = malloc(sizeof(B_Tree_Node));
    ARptr->r = ATT;
    ARptr1->r = ATT;
    ARptr2->r = ATT;
    ARptr3->r = ATT;
    ARptr4->r = ATT;
    Initialize(&SRptr);  Initialize(&FSptr);  Initialize(&ApRptr);  Initialize(&ARptr);
    Initialize(&ARptr1);  Initialize(&ARptr2);  Initialize(&ARptr3);  Initialize(&ARptr4);

    FILE *fp;
    fp = fopen("file5.txt","r");
    int i;
	int cs,ec,ee,me,cv;
	cs=ec=ee=me=cv=0;
	while (!feof(fp))
	{
		Record r1,r2,r3;
        // r1-SR r2-FS r2-ApR

		//name input
		char name[50];
		fgets(name,50,fp);
		int len=strlen(name);
		if(name[len-1]=='\n')
		{
			name[len-1]='\0';
		}
		strcpy(r1.ApR.name,name);
		strcpy(r3.ApR.name,r1.SR.name);
		printf("\nName: %s\n",r1.ApR.name);
		
		//department code
		char dept[2];
		fgets(dept,5,fp);
		if(strcmp(dept,"CS\n")==0)
		{
			
			r1.SR.code = CS;
		}
		else if (strcmp(dept,"EC\n")==0)  r1.SR.code = EC;
		else if (strcmp(dept,"EE\n")==0)  r1.SR.code = EE;
		else if (strcmp(dept,"ME\n")==0)  r1.SR.code = ME;
		else  r1.SR.code = CV;
		printf("Department code: %d\n",r1.SR.code);
		
		//year
		char year[4];
		fgets(year,10,fp);
		if(year[len-1]=='\n')
		{
			year[len-1]='\0';
		}
		int nyear=atoi(year);
		r1.SR.year = nyear;
		printf("Year: %d\n",r1.SR.year);
		
		//roll no
		char rollno[4];
		fgets(rollno,10,fp);
		if(rollno[len-1]=='\n')
		{
			rollno[len-1]='\0';
		}
		int nrn=atoi(rollno);
		r1.SR.rollno.year = r1.SR.year;
		r1.SR.rollno.dc = r1.SR.code;
		r1.SR.rollno.roll = nrn;
		r2.FS.rollno = r1.SR.rollno;
		r3.ApR.rollno = r1.SR.rollno;
		printf("Roll number: %d\n",r1.SR.rollno.roll);
		
		//classes info input
		char cc[10];
		fgets(cc,15,fp);
		int num;
		int i;
		for (i = 0; i < 5; i++)
		{
			char cci[2]={cc[2*i],'\0'};
			num=atoi(cci);
			r1.SR.classes_conducted[i] = num;
			printf("%d ",r1.SR.classes_conducted[i]);
		}
		printf("\n");
		
		char ca[10];
	
		fgets(ca,15,fp);
		for (i = 0; i < 5; i++)
		{
			char cai[2]={ca[2*i],'\0'};
			num=atoi(cai);
			r1.SR.classes_attended[i] = num;
			printf("%d ",r1.SR.classes_attended[i]);
		}
		printf("\n");
		
		char stat[7];
		fgets(stat,15,fp);
		if(stat[strlen(stat)-1]=='\n')
		{
			stat[strlen(stat)-1]='\0';
		}
		strcpy(r2.FS.status,stat);
		printf("Fee status: %s\n",r2.FS.status);
		
		char app[2];
		fgets(app,5,fp);
		if(app[strlen(app)-1]=='\n')
		{
			app[strlen(app)-1]='\0';
		}
		strcpy(r3.ApR.application,app);
		printf("Application: %s\n",r3.ApR.application);

        Insert(SRptr,r1);  Insert(FSptr,r2);  Insert(ApRptr,r3);
        printf("\nInserted\n");
	}
    fclose(fp);
    printf("\nDisplaying Student Record:");
    display(SRptr); 
	printf("\nDisplaying Fee Status:\n");
    display(FSptr);  
    printf("Displaying Applicant:\n");
    display(ApRptr); 

    int *mcc;
    mcc = FindMCC(SRptr);
    int *max;
    max = FindMax(SRptr);
    CreateAR(&ARptr1,&ARptr2,&ARptr3,&ARptr4,&ARptr,SRptr,max,mcc);

    printf("\nStudents who didn't apply for exam : \n");
    NotApplied(ApRptr);

    printf("\nStudents who are eligible for exam : \n");
    Eligible(ARptr,FSptr,ApRptr);

    printf("\nStudents with attendance <= 75 : \n");
    Attendance(ARptr1);
    Attendance(ARptr2);
    Attendance(ARptr3);
    Attendance(ARptr4);

    printf("\nStudents whose attendance is > 75 but fee status is pending : ");
    printf("\n");
    Status(ARptr,FSptr,SRptr);
    
    printf("\nDefaulter Students : \n");
    Defaulter(ARptr,FSptr);

    RollNo r1,r2;
    char str1[2],str2[2];
    printf("\nEnter roll no.s : ");
    scanf("%d %s %d %d %s %d",&r1.year,str1,&r1.roll,&r2.year,str2,&r2.roll);
    if (strcmp(str1,"CS") == 0) {
        r1.dc = CS;
    }
    else if (strcmp(str1,"EC") == 0) {
        r1.dc = EC;
    }
    else if (strcmp(str1,"EE") == 0) {
        r1.dc = EE;
    }
    else if (strcmp(str1,"ME") == 0) {
        r1.dc = ME;
    }
    else {
        r1.dc = CV;
    }

    if (strcmp(str2,"CS") == 0) {
        r1.dc = CS;
    }
    else if (strcmp(str2,"EC") == 0) {
        r1.dc = EC;
    }
    else if (strcmp(str2,"EE") == 0) {
        r1.dc = EE;
    }
    else if (strcmp(str2,"ME") == 0) {
        r1.dc = ME;
    }
    else {
        r1.dc = CV;
    }
    printf("\nRange Search : \n");
    RangeSearch(SRptr,r1,r2);
}
