#include "ssg_components_list.h"

/*
   new_components_list()
   Returns a pointer to a new heap allocated "ssg_components_list".
 */
SSGComponents* new_components_list()
{
    SSGComponents* new = malloc(sizeof(SSGComponents));
    new->component = NULL;
    new->next = NULL;
    return new;
}

/*
   add_component()
   Adds a new heap allocated "ssg_component" to
   "ssg_components_list" pointed to by "list".
   Allocates a new "ssg_components_list" too,
   which is a new element in the linked list
 */
void add_component (SSGComponents* list, SSGComponent* component)
{
    SSGComponents* p = list;

    // TODO: Check if (p != NULL) before to use it.
    while (p->next)
        p = p->next;
    p->next = malloc(sizeof(SSGComponents));
    p->next->component = component;
    p->next->next = NULL;
}

/*
   free_components_list()
   Frees the memory region pointed to by list, so as each component in the
   "ssg_components_list".
 */
void free_components_list (SSGComponents* list)
{
    SSGComponents* p = list;
    // TODO: Check if (p != NULL) before to use it.
    SSGComponents* p2 = list->next;

    free (p);
    p = p2;
    while(p)
    {
        p2 = p->next;
        free_component (p->component);
        free (p);
        p = p2;
    }
}
