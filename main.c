#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char name[50];
  char number[20];
} Contact;
int contacts_length;

Contact *contacts;

int save_file_is_exist() {
  FILE *fptr = fopen("save.txt", "r");

  if (fptr == NULL)
    return 0;
  return 1;
}

void write_save() {
  FILE *fptr = fopen("save.txt", "w");
  for (int i = 0; i < contacts_length; i++) {
    fprintf(fptr, "%50s %20s", contacts[i].name, contacts[i].number);
  }
  fclose(fptr);
  fptr = fopen("contacts_length", "w");
  fprintf(fptr, "%d", contacts_length);
  fclose(fptr);
}

int load_contacts_length() {
  FILE *fptr = fopen("contacts_length", "r");
  if (fptr == NULL){
    contacts_length = 0;
    return 1;
  }
  fscanf(fptr, "%d", &contacts_length);
  fclose(fptr);
  return 0;
}

int load_contacts() {
  FILE *fptr = fopen("save.txt", "r");
  if(fptr == NULL) return 1;
  for (int i = 0; i < contacts_length; i++) {
    fscanf(fptr, "%50s %20s", contacts[i].name, contacts[i].number);
  }
  fclose(fptr);
  return 0;
}

int delete_contacts(int contact_id) {
  if(contact_id >= contacts_length || contact_id < 0){
    printf("it doesnt exist\n");
    return 1;
  }
  for (int i = contact_id; i < contacts_length; i++) {
    if (i == (contacts_length - 1))
      break;
    contacts[i] = contacts[i + 1];
  }
  contacts_length--;
  Contact *temp = realloc(contacts, contacts_length * sizeof(Contact));
  if (temp == NULL)
    return 1;
  contacts = temp;
  return 0;
}

void print_menu() {
  printf("====Phonebook====\n1. Show Contacts\n2. Add Contacts\n3. Delete "
         "Contact\n4. Exit\nChoose:");
}

int show_contacts() {
  if (contacts_length == 0) {
    printf("You have no contacts added");
    return 1;
  }
  for (int i = 0; i < contacts_length; i++) {
    printf("%3d \t %s \t %s\n", i, contacts[i].name, contacts[i].number);
  }
  return 0;
}

int add_new_contacts() {

  Contact *temp = realloc(contacts, (contacts_length + 1) * sizeof(Contact));
  if (!temp)
    return 1;

  contacts = temp;

  char input[50];
  printf("Name: ");
  scanf("%s", input);
  strcpy(contacts[contacts_length].name, input);
  printf("Number: ");
  scanf("%s", input);
  strcpy(contacts[contacts_length].number, input);
  contacts_length++;
  return 0;
}

int main() {
  int c;
  load_contacts_length();
  contacts = (Contact *)calloc(contacts_length, sizeof(Contact));
  load_contacts();
  write_save();
  while (1) {
    print_menu();
    scanf("%d", &c);
    switch (c) {
    case 1:
      show_contacts();
      break;
    case 2:
      add_new_contacts();
      write_save();
      break;
    case 3:
      printf("\nContacts ID: ");
      scanf("%d", &c);
      delete_contacts(c);
      write_save();
      break;
    default:
      printf("Exiting...\n");
      return 0;
    }
  }
  free(contacts);
  contacts = NULL;
}
