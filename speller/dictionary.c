// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
// Recursive
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

int count_nodes(node *n);
void free_nodes(node *n);

// TODO: Choose number of buckets in hash table
// A-Z
const unsigned int N = 26;

// Hash table
// Linked list
// An array of 26 pointers to node structures, representing buckets indexed from 0 to 25
node *table[N];

// Returns true if word is in dictionary, else false
// 拿文章 text去和dictionary比對
bool check(const char *word)
{
    // TODO
    // Case-insensitively Return true if the word is found Return false if no word is found
    // Find the word on index of hash table
    int index = hash(word);
    // Head node, hash(Apple) is 0, so head is table[0], hash(zip) is 25 so head is table[25]
    node *head = table[index];
    // View all linked list
    while (head != NULL)
    {
        if (strcasecmp(head->word, word) == 0)
        {
            return true;
        }
        head = head->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    // Call hash(c) in load(dictionary), c as word to hash function
    // word[0] - 'A' 0-25 對應A到Z table[]
    unsigned int hash = 0;
    // First 5 letters
    for (int i = 0; i < 5 && word[i] != '\0'; i++)
    {
        // captalize first letter
        hash = hash * 26 + (toupper(word[i]) - 'A');
    }
    // N = 26
    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // Open the dictionary file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Could not open this %s.\n", dictionary);
        unload();
        return 1;
    }

    // Read each word in the file
    char c[LENGTH + 1];
    node *head = NULL;
    // 把字典的字放到node裡面
    // fread 用於讀取二進制數據或固定大小的數據塊，應使用 fscanf 或 fgets 來讀取每一行的文本。
    // EOF 是 "End Of File"
    // 的縮寫，用於表示文件結束。當文件讀取操作達到文件末尾時，大多數文件讀取函數會返回
    // EOF，用來指示不再有數據可供讀取。
    while (fscanf(file, "%s", c) != EOF)
    {
        // Set memory for new_node
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            printf("Malloc failed");
            unload();
            return false;
        }
        // Copy to new node
        strcpy(new_node->word, c);

        // Add new_node to the head of linked list
        // hash the word to get the hash value
        // Add each word to the hash table
        // A->0 B->1 ... Z->25, decide where to go
        int index = hash(c);

        new_node->next = table[index];
        table[index] = new_node;
    }
    // Close the dictionary file
    // If there is error
    if (ferror(file))
    {
        fclose(file);
        printf("Error reading %s.\n", dictionary);
        return false;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    int count = 0;
    // N = 26, the size of hash table table[N]
    for (int i = 0; i < N; i++)
    {
        // call the recursive function to calcualte amount of nodes of each linked list
        count += count_nodes(table[i]);
    }
    return count;
}
int count_nodes(node *n)
{
    // Linked list is NULL
    if (n == NULL)
    {
        return 0;
    }
    // The node so far plus remains
    else
    {
        return 1 + count_nodes(n->next);
    }
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    // N = 26, the size of hash table table[N]
    for (int i = 0; i < N; i++)
    {
        // call the recursive function to free all nodes
        free_nodes(table[i]);
    }
    return true;
}
void free_nodes(node *n)
{
    // Linked list is NULL
    if (n == NULL)
    {
        return;
    }
    // Free nodes
    else
    {
        // Free next node
        free_nodes(n->next);
        // Free current node
        free(n);
    }
}
