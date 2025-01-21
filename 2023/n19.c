#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { x, m, a, s} Category_t;

typedef struct
{
    Category_t category;
    char comparative;
    int limit;

    char* next;
} Rule_t;

typedef struct
{
    char* workflow_name;
    Rule_t* rules;
    int n_rules;
} Workflow_t;

typedef struct 
{
    int inf;
    int sup;
} Interval_t;

typedef struct
{
    Interval_t* ratings;
    char* cur_workflow;
} Part_t;

typedef struct elm
{
    Part_t* data;
    struct elm* next;
} elm_t;

typedef struct
{
    elm_t* head;
    elm_t* tail;
    int numelm;
} list_t;

void print_rule(Rule_t r)
{
    if(r.comparative)
    {
        printf("%d . %c . %d ", r.category, r.comparative, r.limit);
    }
    printf("%s\n", r.next);
}

void print_workflow(Workflow_t w)
{
    printf("%s\n", w.workflow_name);
    for (int i = 0; i < w.n_rules; i++)
    {
        print_rule(w.rules[i]);
    }
}

void enfiler(list_t *l, Part_t* data)
{
    elm_t* e = calloc(1, sizeof(elm_t));
    e->data = data;
    if (!l->numelm)
    {
        l->head = e;
    }
    else
    {
        l->tail->next = e;
    }
    l->tail = e;
    l->numelm++;
}

elm_t* defiler(list_t* l)
{
    elm_t* tmp = l->head;
    l->head = l->head->next;
    l->numelm--;
    return tmp;
}

Workflow_t* find_workflow(Workflow_t* Lw, int n, char* w_name)
{
    for (int i = 0; i < n; i++)
    {
        if (!strcmp(Lw[i].workflow_name, w_name))
        {
            return &(Lw[i]);
        }
    }
}

Part_t* duplicate(Part_t* p)
{
    Part_t* p2 = malloc(1 * sizeof(Part_t));
    p2->ratings = malloc(5 * sizeof(Interval_t));

    for (int i = 0; i < 4; i++)
    {
        p2->ratings[i].inf = p->ratings[i].inf;
        p2->ratings[i].sup = p->ratings[i].sup;
    }

    p2->cur_workflow = strdup(p->cur_workflow);
    return p2;
}

int main()
{
    Workflow_t* workflows = malloc(600 * sizeof(Workflow_t));
    int n_workflow = 0;

    int tmp;
    char* buf = calloc(10, sizeof(char));

    char c = getchar();
    while (c != '\n')
    {

        workflows[n_workflow].workflow_name = calloc(10, sizeof(char));
        workflows[n_workflow].rules = calloc(10, sizeof(Rule_t));
        workflows[n_workflow].n_rules = 0;

        tmp = 0;
        while (c != '{')
        {
            workflows[n_workflow].workflow_name[tmp++] = c;
            c = getchar();
        }
        c = getchar();

        while (c != '\n')
        {
            tmp = 0;
            while (c != '<' && c != '>' && c != '}')
            {
                buf[tmp++] = c;
                c = getchar();
            }
            buf[tmp] = '\0';

            if (c == '}')
            {
                workflows[n_workflow].rules[workflows[n_workflow].n_rules].next = strdup(buf);
            }

            else
            {
                switch (buf[0])
                {
                    case 'a':
                        workflows[n_workflow].rules[workflows[n_workflow].n_rules].category = a;
                        break;
                    case 'x':
                        workflows[n_workflow].rules[workflows[n_workflow].n_rules].category = x;
                        break;
                    case 'm':
                        workflows[n_workflow].rules[workflows[n_workflow].n_rules].category = m;
                        break;
                    case 's':
                        workflows[n_workflow].rules[workflows[n_workflow].n_rules].category = s;
                        break;
                }

                workflows[n_workflow].rules[workflows[n_workflow].n_rules].comparative = c;
                
                scanf("%d:", &(workflows[n_workflow].rules[workflows[n_workflow].n_rules].limit));

                tmp = 0;

                c = getchar();
                while (c != ',')
                {
                    buf[tmp++] = c;
                    c = getchar();
                }
                buf[tmp] = '\0';
                workflows[n_workflow].rules[workflows[n_workflow].n_rules].next = strdup(buf);
            }

            workflows[n_workflow].n_rules++;
            c = getchar();
        }
        n_workflow++;
        c = getchar();

    }

    Part_t* part = malloc(1 * sizeof(Part_t));
    part->ratings = malloc(5 * sizeof(Interval_t));
    for (int i = 0; i < 4; i++)
    {
        part->ratings[i].inf = 1;
        part->ratings[i].sup = 4000;
    }

    part->cur_workflow = malloc(10 * sizeof(char));
    part->cur_workflow[0] = 'i';
    part->cur_workflow[1] = 'n';
    part->cur_workflow[2] = '\0';

    long ans = 0;

    list_t* l = calloc(1, sizeof(list_t));

    enfiler(l, part);

    while(l->numelm > 0)
    {
        part = defiler(l)->data;

        Workflow_t* cur_workflow = find_workflow(workflows, n_workflow, part->cur_workflow);

        int fin = 0;

        for (int i = 0; i < cur_workflow->n_rules; i++)
        {
            switch(cur_workflow->rules[i].comparative)
            {
                case '<':
                    if (part->ratings[cur_workflow->rules[i].category].sup < cur_workflow->rules[i].limit)
                    //whole interval in the rule
                    {
                        fin = 1;
                        part->cur_workflow = strdup(cur_workflow->rules[i].next);
                    }
                    else if (part->ratings[cur_workflow->rules[i].category].inf < cur_workflow->rules[i].limit)
                    //beginning of interval in the rule
                    {
                        fin = 1;
                        Part_t* part2 = duplicate(part);
                        part2->ratings[cur_workflow->rules[i].category].inf = cur_workflow->rules[i].limit;
                        enfiler(l, part2);

                        part->ratings[cur_workflow->rules[i].category].sup = cur_workflow->rules[i].limit - 1;
                    }
                    break;
                case '>':
                    if (part->ratings[cur_workflow->rules[i].category].inf > cur_workflow->rules[i].limit)
                    //whole interval in the rule
                    {
                        fin = 1;
                        part->cur_workflow = strdup(cur_workflow->rules[i].next);
                    }
                    else if (part->ratings[cur_workflow->rules[i].category].sup > cur_workflow->rules[i].limit)
                    //beginning of interval in the rule
                    {
                        fin = 1;
                        Part_t* part2 = duplicate(part);
                        part2->ratings[cur_workflow->rules[i].category].sup = cur_workflow->rules[i].limit;
                        enfiler(l, part2);

                        part->ratings[cur_workflow->rules[i].category].inf = cur_workflow->rules[i].limit + 1;
                    }
                    break;
                default:
                    fin = 1;
                    part->cur_workflow = strdup(cur_workflow->rules[i].next);
                    break;
            }

            if (fin) break;
        }

        if (!strcmp(part->cur_workflow, "A"))
        {
            long tmp = 1;
            for (int i = 0; i < 4; i++)
            {
                tmp *= part->ratings[i].sup - part->ratings[i].inf + 1;
            }

            ans += tmp;
        }

        else if (strcmp(part->cur_workflow, "R"))
        {
            enfiler(l, part);
        }

    }

    printf("%ld\n", ans);

    free(buf);
    
    return 0;
}