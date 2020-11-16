#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbol.h"

// Current Scope location 
static int CurrentScope = 0;

// variable for our flag declarations
static int declare = 0; // 1: declaring, 0: not

static int type = 0;

//Functions for our Symbol Table
void InitHashTable() {
	int i;
	HashTable = malloc(SIZE * sizeof(list_t*));
	for (i = 0; i < SIZE; i++) HashTable[i] = NULL;
}

unsigned int Hash(char* Key) {
	unsigned int HashVal = 0;
	for (; *Key != '\0'; Key++) HashVal += *Key;
	HashVal += Key[0] % 11 + (Key[0] << 3) - Key[0];
	return HashVal % SIZE;
}

void setType(int val) {

	type = val;
}

void Insert_v(char* Name, int len, int lineno) {
	unsigned int HashVal = Hash(Name);
	list_t* i = HashTable[HashVal];

	while ((i != NULL) && (strcmp(Name, i->SymtableName) != 0)) i = i->next;

	// variable has not arrived to the table
	if (i == NULL) {
		// Entry setup
		i = (list_t*)malloc(sizeof(list_t));
		strncpy(i->SymtableName, Name, len);
		i->SymTable_Type = type;
		i->Scope = CurrentScope;
		i->Lines = (LineNumList*)malloc(sizeof(LineNumList));
		i->Lines->lineno = lineno;
		i->Lines->next = NULL;

		// adds the new variable to the hashtable 
		i->next = HashTable[HashVal];
		HashTable[HashVal] = i;
		printf("Inserted %s for the first time with linenumber %d!\n", Name, lineno);
	}
	// finds in the table
	else {
		// just add line number
		if (declare == 0) {
			// finds the last reference
			LineNumList* t = i->Lines;
			while (t->next != NULL) t = t->next;

			//  current line number will be added to the reference list
			t->next = (LineNumList*)malloc(sizeof(LineNumList));
			t->next->lineno = lineno;
			t->next->next = NULL;
			printf("Found %s again at line %d!\n", Name, lineno);
		}
		// new entry
		else {
			// checks the same Scope to see if it will show a multiple declaration error
			if (i->Scope == CurrentScope) {
				fprintf(stderr, "A multiple declaration of variable %s at line %d\n", Name, lineno);
				exit(1);
			}
			// if it is another Scope it will make a new entry
			else {
				// sets up entry
				i = (list_t*)malloc(sizeof(list_t));
				strncpy(i->SymtableName, Name, len);
				i->SymTable_Type = type;
				i->Scope = CurrentScope;
				i->Lines = (LineNumList*)malloc(sizeof(LineNumList));
				i->Lines->lineno = lineno;
				i->Lines->next = NULL;

				// will add to the hashtable 
				i->next = HashTable[HashVal];
				HashTable[HashVal] = i;
				printf("Inserted %s for a new Scope with linenumber %d!\n", Name, lineno);
			}
		}
	}
}
// will return NULL if it cannot be found or will return symbol if it is found 
list_t* LookUp(char* Name) {
	unsigned int HashVal = Hash(Name);
	list_t* i = HashTable[HashVal];
	while ((i != NULL) && (strcmp(Name, i->SymtableName) != 0)) i = i->next;
	return i;
}
// Scope Management Functions
// regresses in Scope 
void hideScope() {
	list_t* l;
	int i;
	printf("Hiding Scope \'%d\':\n", CurrentScope);
	// for every list
	for (i = 0; i < SIZE; i++) {
		if (HashTable[i] != NULL) {
			l = HashTable[i];
			// locates first item from another Scope
			while (l != NULL && l->Scope == CurrentScope) {
				printf("Hiding %s..\n", l->SymtableName);
				l = l->next;
			}
			// This will set the list equal to item
			HashTable[i] = l;
		}
	}
	CurrentScope--;
}
//moves to next Scope
void incrScope() {
	CurrentScope++;
}

// prints to an out
void build_symtab(FILE* of) {
	int x;

	fprintf(of, "  Name       Type   Scope  Line Repeats on\n");
	fprintf(of, " _______________________________________\n");
	for (x = 0; x < SIZE; ++x) {

		if (HashTable[x] != NULL) {
			list_t* i = HashTable[x];
			while (i != NULL) {
				LineNumList* t = i->Lines;
				fprintf(of, "| ");
				fprintf(of, "%-12s ", i->SymtableName);
				if (i->SymTable_Type == TYPE_INT) fprintf(of, "%-5s", "int");
				else if (i->SymTable_Type == TYPE_CHAR) fprintf(of, "%-5s", "char");
				else if (i->SymTable_Type == TYPE_BOOL) fprintf(of, "%-5s", "bool");
				else if (i->SymTable_Type == TYPE_DOUBLE) fprintf(of, "%-5s", "double");
				
			
				else if (i->SymTable_Type == TYPE_ARRAY) {
					fprintf(of, "array of ");
					if (i->inf_type == TYPE_INT) 		   fprintf(of, "%-5s", "int");
					else if (i->SymTable_Type == TYPE_CHAR) fprintf(of, "%-5s", "char");
					else if (i->SymTable_Type == TYPE_BOOL) fprintf(of, "%-5s", "bool");
					else if (i->SymTable_Type == TYPE_DOUBLE) fprintf(of, "%-5s", "double");
					
					else fprintf(of, "%-5s", "undefined");
				}
				
				else if (i->SymTable_Type == FUNCTION_TYPE) {
					fprintf(of, "%-5s", "function returns ");
					if (i->inf_type == TYPE_INT) 		   fprintf(of, "%-5s", "int");
					else if (i->SymTable_Type == TYPE_CHAR) fprintf(of, "%-5s", "char");
					else if (i->SymTable_Type == TYPE_BOOL) fprintf(of, "%-5s", "bool");
					else if (i->SymTable_Type == TYPE_DOUBLE) fprintf(of, "%-5s", "double");
					else fprintf(of, "%-5s", "undefined");
				}
				else fprintf(of, "%-5s", "undefined"); // if undefined or 0
				fprintf(of, "  %d  ", i->Scope);
				while (t != NULL) {
					fprintf(of, "%4d ", t->lineno);
					t = t->next;
				}
				fprintf(of, "%12s", " |\n");
				i = i->next;
			}
			fprintf(of, "|_______________________________________|\n");

		}
	}
}