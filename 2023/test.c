#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char* receiver;
    char* sender; //conjunctions need to know the sender
    int pulse; //0 = low, 1 = high
} signal_t;

typedef struct 
{
    char type; // % = flip flop, & = conjunction 
    char* name;
    char** receiver;
    int n_receiver;

    int state;

    //for conjunction
    char** inputs;
    int n_inputs;
    int* state_of_input; 
} module_t;

typedef struct elm 
{
    signal_t* data;
    struct elm* next;
} elm_list_t;

typedef struct 
{
    elm_list_t* head;
    elm_list_t* tail;
    int num_elm;
} list_t;

void enfiler(list_t *l, signal_t* data)
{
    elm_list_t* e = calloc(1, sizeof(elm_list_t));
    e->data = data;
    if (!l->num_elm)
    {
        l->head = e;
    }
    else
    {
        l->tail->next = e;
    }
    l->tail = e;
    l->num_elm++;
}

signal_t* defiler(list_t* l)
{
    signal_t* tmp = l->head->data;
    l->head = l->head->next;
    l->num_elm--;
    return tmp;
}

module_t* find_module(module_t* modules, int n_module, char* name)
{
    for (int i = 0; i < n_module; i++)
    {
        if (!strcmp(modules[i].name, name))
        {
            return &(modules[i]);
        }
    }
    return NULL;
}

int is_in_receiver(module_t m1, module_t m2)
{
    for (int i = 0; i < m2.n_receiver; i++)
    {
        if (!strcmp(m2.receiver[i], m1.name))
        {
            return 1;
        }
    }
    return 0;
}


int find_index_input(module_t* conjunction, char* receiver)
{
    for (int i = 0; i < conjunction->n_inputs; i++)
    {
        if (!strcmp(conjunction->inputs[i], receiver))
        {
            return i;
        }
    }
}

int is_every_module_high(module_t* conjunction)
{
    for (int i = 0; i < conjunction->n_inputs; i++)
    {
        if (!conjunction->state_of_input[i])
        {
            return 0;
        }
    }

    return 1;
}

signal_t* duplicate_signal(signal_t* s)
{
    signal_t* ans = calloc(1, sizeof(signal_t));
    ans->sender = strdup(s->sender);
    ans->pulse = s->pulse;

    return ans;
}

int main()
{
    module_t* modules = malloc(100 * sizeof(module_t));
    int n_module = 0;
    char c = getchar();

    int tmp; 
    while (c != EOF)
    {
        modules[n_module].name = calloc(50, sizeof(char));
        modules[n_module].receiver = malloc(10 * sizeof(char*));
        modules[n_module].n_receiver = 0;

        modules[n_module].state = 0;

        modules[n_module].inputs = malloc(50 * sizeof(char*));
        modules[n_module].n_inputs = 0;
        modules[n_module].state_of_input = calloc(50, sizeof(int));        

        if (c != 'b')
        //b is for broadcaster
        {
            modules[n_module].type = c;
            c = getchar();   
        }
        else 
        {
            modules[n_module].type = '\0';
        }

        tmp = 0;
        while (c != ' ')
        {
            modules[n_module].name[tmp++] = c;
            c = getchar();
        }
        getchar(); getchar(); getchar();

        c = getchar();
        while (c != '\n')
        {
            tmp = 0;
            modules[n_module].receiver[modules[n_module].n_receiver] = calloc(5, sizeof(char));
            while (c != ',' && c != '\n')
            {
                modules[n_module].receiver[modules[n_module].n_receiver][tmp++] = c;
                c = getchar();
            }
            modules[n_module].n_receiver++;

            if (c != '\n') { getchar(); c = getchar();}
        }

        n_module++;

        c = getchar();
    }

    //init conjunction
    for (int i = 0; i < n_module; i++)
    {
        if (modules[i].type == '&')
        {
            for (int j = 0; j < n_module; j++)
            {
                if (is_in_receiver(modules[i], modules[j]))
                {
                    modules[i].inputs[modules[i].n_inputs++] = strdup(modules[j].name);
                }
            }
        }
    }

    list_t* Lsignals = calloc(1, sizeof(list_t));
    

    module_t* cur_module;

    int high_pulse = 0;
    int low_pulse = 0;

    for (int loop = 0; loop < 1000; loop++)
    {
        signal_t* s = malloc(1 * sizeof(signal_t));
        s->receiver = strdup("broadcaster");
        s->sender = strdup("button");
        s->pulse = 0;

        enfiler(Lsignals, s);

        while(Lsignals->num_elm > 0)
        {
            s = defiler(Lsignals);
            if (s->pulse)
            {
                high_pulse++;
            }
            else
            {
                low_pulse++;
            }

            cur_module = find_module(modules, n_module, s->receiver);

            if (!cur_module)
            {
                continue;
            }

            switch (cur_module->type)
            {
                case '%':
                //flip flop
                    if (!s->pulse)
                    {
                        cur_module->state = !cur_module->state;
                    }
                    else
                    {
                        continue;
                    }
                    break;

                case '&':
                //conjunction
                    cur_module->state_of_input[find_index_input(cur_module, s->sender)] = s->pulse;
                    cur_module->state = !is_every_module_high(cur_module);
                    break;

                default:
                //broadcaster
                    cur_module->state = s->pulse;
                    break;
            }

            s->pulse = cur_module->state;
            s->sender = strdup(cur_module->name);
            for (int i = 0; i < cur_module->n_receiver; i++)
            {
                s = duplicate_signal(s);
                s->receiver = strdup(cur_module->receiver[i]);
                
                enfiler(Lsignals, s);
            }
        }
    }

    printf("%d\n", low_pulse * high_pulse);
    return 0;
}