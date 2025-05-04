#include "api.h"

graph* trash;

//Node
node* create_node()
{
    node* new_node = (node*)realloc(NULL, sizeof(node));

    if(!new_node) return NULL;

    new_node->data = (uint8_t*)calloc(MAX_DATA_INDEX + 1, 1);

    new_node->context = NO_CONTEXT;

    return new_node;
}

uint8_t free_node(node* target)
{
    if(!target) return NODE_ERROR_NO_NODE;

    free(target->data);
    free(target);

    return NODE_NO_ERROR;
}

//Links
edge* edge_list;
uint32_t max_edge_index = DEFAULT_EDGE_LIST_SIZE;
uint32_t empty_edge_index = 0;

#define VALIDATE_EDGE_LIST() resize_edge_list(max_edge_index)
uint8_t resize_edge_list(uint32_t new_index)
{
    if(new_index == max_edge_index) return NODE_NO_ERROR;

    edge* temp;

    if(new_index > max_edge_index)
        temp = (edge*)realloc(edge_list, 2*max_edge_index*sizeof(edge));

    if(temp == NULL) return NODE_ERROR_NO_MEMORY;

    max_edge_index *= 2;
    edge_list = temp;

    return NODE_NO_ERROR;
}

void flip_edge_direction(uint32_t edge_index)
{
    if(edge_index > max_edge_index) return;
    
    node* temp = edge_list[edge_index].start;
    edge_list[edge_index].start = edge_list[edge_index].end;
    edge_list[edge_index].end = temp;
}

void switch_edge_type(uint32_t edge_index)
{
    edge_list[edge_index].type = !edge_list[edge_index].type;
}

uint8_t connect_existing_node(node* parent, node* target)
{
    if(!parent || !target) return NODE_ERROR_NO_NODE;

    //find next empty slot
    while(edge_list[empty_edge_index].start == NULL) empty_edge_index++;

    if(empty_edge_index > max_edge_index) resize_edge_list(empty_edge_index);

    edge_list[empty_edge_index].start = parent;
    edge_list[empty_edge_index].end = target;

    edge_list[empty_edge_index].type = NON_DIRECTED;

    empty_edge_index++;

    return NODE_NO_ERROR;
}

// uint8_t abandon_child(node* target, uint32_t child_index)
// {
//     if(!target) return NODE_ERROR_NO_NODE;

//     uint32_t i = child_index;
//     while(i < target->max_child_index)
//         target->children[i] = target->children[i++];

//     target->max_child_index--;

//     return NODE_NO_ERROR;
// }

// uint8_t murder_child(node* target, uint32_t child_index)
// {
//     if(!target) return NODE_ERROR_NO_NODE;

//     free_node_component(target->components[component_index]);
//     remove_node_component(target, component_index);

//     return NODE_NO_ERROR;
// }

//Graph
graph* create_graph()
{
    graph* g = (graph*)realloc(NULL, sizeof(graph));
    g->nodes = NULL;
    g->max_node_index = -1;
    
    return g;
}

uint8_t free_graph(graph* target, uint8_t recursive)
{
    if(!target) return NODE_ERROR_NO_GRAPH;

    if(recursive)
    {
        uint32_t i = 0;
        for(;i < target->max_node_index;i++)
        {
            free_node(target->nodes[i]);
        }
    }
    
    realloc(target->nodes,0);
    target->max_node_index = 0;

    realloc(target,0);

    return NODE_NO_ERROR;
}

// uint8_t save_graph(graph* target, char* path)
// {
//     if(!target) return NODE_ERROR_NO_GRAPH;



//     return NODE_NO_ERROR;
// }

uint8_t load_graph(graph* target, char* path)
{
    //load nodes, edge, trash and graphs

    if(!target) return NODE_ERROR_NO_GRAPH;

    #ifdef SDL_h_
    size_t data_size;
    graph* result = (graph*)SDL_LoadFile(path, &data_size);

    if(result == NULL) return NODE_ERROR_UNDEFINED;

    #endif

    return NODE_NO_ERROR;
}

uint8_t add_graph_node(graph* target, node* to_add)
{
    if(!target) return NODE_ERROR_NO_GRAPH;
    if(!to_add) return NODE_ERROR_NO_NODE;

    // #error here
    node** new_node_list = (node**)realloc(target->nodes, sizeof(node*)*(target->max_node_index+1+1));
    
    if(!new_node_list) return NODE_ERROR_NO_MEMORY;

    target->nodes = new_node_list;
    target->max_node_index++;
    target->nodes[target->max_node_index] = to_add;

    return NODE_NO_ERROR;
}

uint8_t add_new_graph_node(graph* target)
{
    node* n = create_node();

    uint8_t result = add_graph_node(target, n);

    if(result) free_node(n);

    return result;
}

uint8_t remove_graph_node(graph* target, uint32_t node_index)
{
    if(!target) return NODE_ERROR_NO_GRAPH;

    uint32_t i = node_index;
    while(i < target->max_node_index - 1)
        target->nodes[i] = target->nodes[i++];

    target->max_node_index--;

    return NODE_NO_ERROR;
}

uint8_t delete_graph_node(graph* target, uint32_t node_index)
{
    if(!target) return NODE_ERROR_NO_GRAPH;

    free_node(target->nodes[node_index]);
    remove_graph_node(target, node_index);

    return NODE_NO_ERROR;
}

//Trash
// void validate_trash()
// {
//     //Who's a good little trash? You are! Yes you aaare!
//     if(trash == NULL) trash = create_graph();
// }

// uint8_t trash_node(graph* target, uint32_t node_index)
// {
//     if(!target) return NODE_ERROR_NO_GRAPH;

//     validate_trash();

//     uint8_t result = edge_graph_node(trash, target->nodes[node_index]);
    
//     // if(result) return result;

//     add_graph_node(trash, target->nodes[node_index]);

//     remove_graph_node(target, node_index);

//     return NODE_NO_ERROR;
// }

// uint8_t clear_trash()
// {
//
// }
