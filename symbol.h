//Max SIZE
#define SIZE 211

//Max Token Length
#define MAXTOKENLEN 40

//Defining Token types
//Determines Type for Symbol table
#define UNDEF 0
#define TYPE_INT 1
#define TYPE_REAL 2
#define TYPE_STRING 3
#define LOGIC_TYPE 4
#define TYPE_ARRAY 5
//#define POINTER_TYPE 6
#define FUNCTION_TYPE 7
#define TYPE_CHAR 8
#define TYPE_BOOL 9
#define TYPE_DOUBLE 10

// a linked list of references (lineno's) for each variable
typedef struct LineNumList {
	int lineno;
	struct LineNumList* next;
}LineNumList;

// struct that represents a list node
typedef struct list_t {
	// Name, size of Name, Scope and occurrences (lines)
	char SymtableName[MAXTOKENLEN];
	int st_size;
	int Scope;
	LineNumList* Lines;

	// to store value and sometimes more information
	int st_ival; double st_fval; char* st_sval;

	// type
	int SymTable_Type;

	// for arrays (info type), for pointers (pointing type)
	// and for functions (return type)
	int inf_type;

	// array stuff
	int* i_vals; double* f_vals; char** s_vals;
	int array_size;

	// pointer to next item in the list
	struct list_t* next;
}list_t;

// The Hash table
static list_t** HashTable;

// Function Declarations
void InitHashTable(); // initialize Hash table
unsigned int Hash(char* Key); // Hash function 
void Insert_v(char* Name, int len, int lineno); // insert entry
list_t* LookUp(char* Name); // search for entry
void HideScope(); // hide the current Scope
void incrScope(); // go to next Scope
void build_symtab(FILE* of); // dump file
void setType(int val);