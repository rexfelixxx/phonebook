#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char name[50];
  char number[10];
} Contact;
int contacts_length = 1;

Contact *contacts;

void print_menu() {
  printf(
      "====Phonebook====\n1. Show Contacts\n2. Add Contacts\n3. Exit\nChoose:");
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

  Contact *temp = realloc(contacts, (contacts_length + 1) * 60);
  if (!temp)
    return 1;

  contacts = temp;

  char input[50];
  printf("Name: ");
  scanf("%s", &input);
  strcpy(contacts[contacts_length + 1].name, input);
  printf("Number: ");
  scanf("%s", &input);
  strcpy(contacts[contacts_length + 1].number, input);
  contacts_length++;
  return 0;
}

int main() {
  int c;
  contacts = (Contact *) calloc(1, 60);
  strcpy(contacts[0].name, "NAMA");
  strcpy(contacts[0].number, "NOMOR");
  while (1) {
    print_menu();
    scanf("%d", &c);
    switch (c) {
    case 1:
      show_contacts();
      break;
    case 2:
      add_new_contacts();
      break;
    default:
      printf("Exiting...\n");
      return 0;
    }
  }
  free(contacts);
  contacts = NULL;
}
