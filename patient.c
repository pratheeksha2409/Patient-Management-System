#include<stdio.h>
struct patient
{
 int pid;
 char name[30];
 char Address[100];
 char Email[50];
 char Phone[10];
}ptn;
//    FUNCTION TO INSERT RECORDS TO THE FILE
void insert()
{
 FILE *fp;
 fp = fopen("Record", "a");
 printf("Enter the Patient Id   :");
 scanf("%d", &ptn.pid);
 printf("Enter the Name      :");
 scanf("%s", &ptn.name);
 printf("Enter the Address      :");
 scanf("%f", &ptn.Address);
 printf("Enter the Email      :");
 scanf("%f", &ptn.Email);
 printf("Enter the Phone      :");
 scanf("%f", &ptn.Phone);
 fwrite(&ptn, sizeof(ptn), 1, fp);
 fclose(fp);
}
//    FUNCTION TO DISPLAY RECORDS
void disp()
{
 FILE *fp1;
 fp1 = fopen("Record", "r");
 printf("\Patient Id\tName\tAddress\tEmail\tPhone\n\n");
 while (fread(&ptn, sizeof(ptn), 1, fp1))
 printf("  %d\t\t%s\t\t%s\t\t%s\t\t%s\n", ptn.pid, ptn.name, ptn.Address, ptn.Email, ptn.Phone);
 fclose(fp1);
}
//    FUNCTION TO SEARCH THE GIVEN RECORD
void search()
{
 FILE *fp2;
 int r, s, avl;
 printf("\nEnter the Patient Id you want to search  :");
 scanf("%d", &r);
 avl = avlptnid(r);
 if (avl == 0)
  printf("Patient Id %d is not available in the file\n",r);
 else
 {
  fp2 = fopen("Record", "r");
  while (fread(&ptn, sizeof(ptn), 1, fp2))
  {
   s = ptn.pid;
   if (s == r)
   {
    printf("\nPatient Id = %d", ptn.pid);
    printf("\nName        = %s", ptn.name);
    printf("\nAddress     = %s\n", ptn.Address);
    printf("\nEmail       = %s\n", ptn.Email);
    printf("\nPhone       = %s\n", ptn.Phone);
   }
  }
  fclose(fp2);
 }
}
//    FUNCTION TO DELETE A RECORD


void deletefile()
{
 FILE *fpo;
 FILE *fpt;
 int r, s;
 printf("Enter the Patient Id you want to delete :");
 scanf("%d", &r);
 if (avlptnid(r) == 0)
  printf("Patient Id %d is not available in the file\n", r);
 else
 {
  fpo = fopen("Record", "r");
  fpt = fopen("TempFile", "w");
  while (fread(&ptn, sizeof(ptn), 1, fpo))
  {
   s = ptn.pid;
   if (s != r)
    fwrite(&ptn, sizeof(ptn), 1, fpt);
  }
  fclose(fpo);
  fclose(fpt);
  fpo = fopen("Record", "w");
  fpt = fopen("TempFile", "r");
  while (fread(&ptn, sizeof(ptn), 1, fpt))
   fwrite(&ptn, sizeof(ptn), 1, fpo);
  printf("\nRECORD DELETED\n");
  fclose(fpo);
  fclose(fpt);
 }

}
//    FUNCTION TO UPDATE THE RECORD
void update()
{
 int avl;
 FILE *fpt;
 FILE *fpo;
 int s, r, ch;
 printf("Enter Patient Id to update:");
 scanf("%d", &r);
 avl = avlptnid(r);
 if (avl == 0)
 {
  printf("Patient Id %d is not Available in the file", r);
 }
 else
 {
  fpo = fopen("Record", "r");
  fpt = fopen("TempFile", "w");
  while (fread(&ptn, sizeof(ptn), 1, fpo))
  {
   s = ptn.pid;
   if (s != r)
    fwrite(&ptn, sizeof(ptn), 1, fpt);
   else
   {
    printf("Enter Name: ");
    scanf("%s", &ptn.name);
    printf("Enter Address: ");
    scanf("%f", &ptn.Address);
    printf("Enter Email: ");
     scanf("%s", &ptn.Email);
     printf("Enter Phone: ");
     scanf("%f", &ptn.Phone);
    fwrite(&ptn, sizeof(ptn), 1, fpt);
   }
  }
  fclose(fpo);
  fclose(fpt);
  fpo = fopen("Record", "w");
  fpt = fopen("TempFile", "r");
  while (fread(&ptn, sizeof(ptn), 1, fpt))
  {
   fwrite(&ptn, sizeof(ptn), 1, fpo);
  }
  fclose(fpo);
  fclose(fpt);
  printf("RECORD UPDATED");
 }
}
//    FUNCTION TO CHECK GIVEN ROLL NO IS AVAILABLE //
int avlptnid(int id)
{
 FILE *fp;
 int c = 0;
 fp = fopen("Record", "r");
 while (!feof(fp))
 {
  fread(&ptn, sizeof(ptn), 1, fp);

  if (id == ptn.pid)
  {
   fclose(fp);
   return 1;
  }
 }
 fclose(fp);
 return 0;
}
//FUNCTION TO CHECK THE FILE IS EMPTY OR NOT
int empty()
{
 int c = 0;
 FILE *fp;
 fp = fopen("Record", "r");
 while (fread(&ptn, sizeof(ptn), 1, fp))
  c = 1;
 fclose(fp);
 return c;
}
// MAIN PROGRAM
void main()
{
 int c, ptn;
 do
 {
  printf("\n\t---Select your choice---------\n");
  printf("\n\t1. INSERT\n\t2. DISPLAY\n\t3. SEARCH");
  printf("\n\t4. DELETE\n\t5. UPDATE");
  printf("\n\t6. EXIT");
  printf("\n\n------------------------------------------\n");
  printf("\nEnter your choice:");
  scanf("%d", &c);
  printf("\n");
  switch (c)
  {
  case 1:
   insert();
   break;
  case 2:
   ptn = empty();
   if (ptn == 0)
    printf("\nThe file is EMPTY\n");
   else
    disp();
   break;
  case 3:
   search();
   break;
  case 4:
   deletefile();
   break;
  case 5:
   update();
   break;
  case 6:
   exit(1);
   break;
  default:
   printf("\nYour choice is wrong\nPlease try again...\n");
   break;

  }
 } while (c != 6);
}