/**
 * @file  vertex.c
 * @author Izan Robles
 * @brief Module for vertex implementation
 */

 #include "vertex.h"
 #include <string.h>
 
 /*----------------------------------------------------------------------------------------*/
 Status vertex_setField(Vertex *v, char *key, char *value);
 
 Status vertex_setField(Vertex *v, char *key, char *value)
 {
     if (!key || !value || !v)
         return ERROR;
 
     if (strcmp(key, "id") == 0)
     {
         return vertex_setId(v, atol(value));
     }
     else if (strcmp(key, "tag") == 0)
     {
         return vertex_setTag(v, value);
     }
     else if (strcmp(key, "state") == 0)
     {
         return vertex_setState(v, (Label)atoi(value));
     }
 
     return ERROR;
 }
 
 /*----------------------------------------------------------------------------------------*/
 Vertex *vertex_initFromString(char *descr)
 {
     char buffer[1024];
     char *token;
     char *key;
     char *value;
     char *p;
     Vertex *v;
 
     /* Check args: */
     if (!descr)
         return NULL;
 
     /* Allocate memory for vertex: */
     v = vertex_init();
     if (!v)
         return NULL;
 
     /* Read and tokenize description: */
     sprintf(buffer, "%s", descr);
     token = strtok(buffer, " \t\n");
     while (token)
     {
         p = strchr(token, ':');
         if (!p)
             continue;
 
         *p = '\0';
         key = token;
         value = p + 1;
 
         vertex_setField(v, key, value);
 
         token = strtok(NULL, " \t\n");
     }
 
     return v;
 }
 
 /*----------------------------------------------------------------------------------------*/
 Vertex *vertex_init()
 {
     Vertex *v = NULL;
 
     if (!(v = (Vertex *)malloc(sizeof(Vertex))))
     {
         return NULL;
     }
 
     vertex_setState(v, WHITE);
     vertex_setId(v, 0);
     v->index = -1;
 
     if (TAG_LENGTH > 0)
     {
         v->tag[0] = '\0';
     }
     else
     {
         /*means length of tag in vertex is too low to initalize*/
         free(v);
         return NULL;
     }
 
     return v;
 }
 
 /*----------------------------------------------------------------------------------------*/
 void vertex_free(void *v)
 {
     if (v != NULL)
     {
         free(v);
     }
 }
 
 /*----------------------------------------------------------------------------------------*/
 long vertex_getId(const Vertex *v)
 {
     if (v == NULL)
     {
         return -1;
     }
 
     return v->id;
 }
 
 /*----------------------------------------------------------------------------------------*/
 const char *vertex_getTag(const Vertex *v)
 {
     if (v == NULL)
     {
         return NULL;
     }
 
     return v->tag;
 }
 
 /*----------------------------------------------------------------------------------------*/
 Label vertex_getState(const Vertex *v)
 {
     if (v == NULL)
     {
         return ERROR_VERTEX;
     }
 
     return v->state;
 }
 
 /*----------------------------------------------------------------------------------------*/
 Status vertex_setId(Vertex *v, const long id)
 {
     if (v == NULL || id < 0)
     {
         return ERROR;
     }
 
     v->id = id;
 
     return OK;
 }
 
 /*----------------------------------------------------------------------------------------*/
 Status vertex_setTag(Vertex *v, const char *tag)
 {
     if (v == NULL || strlen(tag) > (TAG_LENGTH - 1))
     {
         return ERROR;
     }
 
     strcpy(v->tag, tag);
 
     return OK;
 }
 
 /*----------------------------------------------------------------------------------------*/
 Status vertex_setState(Vertex *v, const Label state)
 {
     if (v == NULL || (state != WHITE && state != BLACK && state != ERROR_VERTEX))
     {
         return ERROR;
     }
 
     v->state = state;
 
     return OK;
 }
 
 /*----------------------------------------------------------------------------------------*/
 int vertex_cmp(const void *v1, const void *v2)
 {
     int comparator;
     const Vertex *vert1;
     const Vertex *vert2;
 
     if (v1 == NULL || v2 == NULL)
     {
         return -2;
     }
 
     vert1 = (const Vertex *)v1;
     vert2 = (const Vertex *)v2;
 
     if (strlen(vert1->tag) < 1 || strlen(vert2->tag) < 1 || vert1->id < 0 || vert2->id < 0)
     {
         return -2;
     }
 
     if (vert1->id != vert2->id)
     {
         if (vert1->id > vert2->id)
         {
             return 1;
         }
         else if (vert1->id < vert2->id)
         {
             return -1;
         }
     }
 
     else
     {
         comparator = strcmp(vert1->tag, vert2->tag);
         if (comparator > 0)
         {
             return 1;
         }
         else if (comparator < 0)
         {
             return -1;
         }
         else
         {
             return 0;
         }
     }
 
     return -2;
 }
 
 /*----------------------------------------------------------------------------------------*/
 void *vertex_copy(const void *src)
 {
     const Vertex *source;
     Vertex *v = NULL;
 
     if (src == NULL)
     {
         return NULL;
     }
 
     source = (const Vertex *)src;
 
     if (is_invalid_vertex(source))
     {
         return NULL;
     }
 
     v = vertex_init();
 
     vertex_setId(v, vertex_getId(source));
     vertex_setTag(v, vertex_getTag(source));
     vertex_setState(v, vertex_getState(source));
 
     return v;
 }
 
 /*----------------------------------------------------------------------------------------*/
 int vertex_print(FILE *pf, const void *v)
 {
     const Vertex *source;
 
     if (pf == NULL || v == NULL)
     {
         return -1;
     }
 
     source = (const Vertex *)v;
 
     return fprintf(pf, "[%ld, %s, %d]", vertex_getId(source), vertex_getTag(source), vertex_getState(source));
 }
 
 /*----------------------------------------------------------------------------------------*/
 Bool is_invalid_vertex(const Vertex *v)
 {
     if (v->id < 0)
     {
         return TRUE;
     }
 
     if (strlen(v->tag) < 1 || strlen(v->tag) > TAG_LENGTH)
     {
         return TRUE;
     }
 
     if (v->state != WHITE && v->state != BLACK && v->state != ERROR_VERTEX)
     {
         return TRUE;
     }
 
     if (v->index < -1)
     {
         return TRUE;
     }
 
     return FALSE;
 }
 
 /*----------------------------------------------------------------------------------------*/
 Status vertex_set_index(Vertex *v, int index)
 {
     if (v == NULL || index < 0)
     {
         return ERROR;
     }
 
     v->index = index;
 
     return OK;
 }
 
 /*----------------------------------------------------------------------------------------*/
 int vertex_get_index(const Vertex *v)
 {
     if (v == NULL)
     {
         return -1;
     }
 
     return v->index;
 }