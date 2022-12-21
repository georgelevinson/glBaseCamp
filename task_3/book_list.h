
typedef struct bookData 
{
    double price;
    int pages;
    float weight;
    unsigned short year;

    // make flexible array members?
    char name[20];
    char lang[20];
} Value, *ValuePtr;
typedef struct bookListElement Element, *ElementPtr;
struct bookListElement
{
    Value value;
    ElementPtr next;
    ElementPtr prev;
};
typedef struct bookList
{
    ElementPtr first;
    ElementPtr last;
    unsigned int length;
} List, *ListPtr;


ListPtr init_list(ValuePtr values, unsigned int arrlen);
void free_list(ListPtr list);

void print_list(ListPtr list);
int delete_nth(ListPtr list, unsigned int index);
int append_elements(ListPtr list, ValuePtr values);
int insert_elements(ListPtr list, ValuePtr values, unsigned int val_arrlen, unsigned int index);
