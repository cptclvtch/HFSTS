#include "api.h"

//Node component
node_component* create_node_component()
{
    return (node_component*)realloc(NULL, sizeof(node_component));
}

uint8_t free_node_component(node_component* target)
{
    if(!target) return NODE_ERROR_NO_NODE;

    //recursive free component tree
    // if(target->children) free_node_component(target->children);
    realloc(target,0);

    return NODE_NO_ERROR;
}

//Node
node* create_node()
{
    node* new_node = (node*)realloc(NULL, sizeof(node));

    if(!new_node) return NULL;

    new_node->components = (node_component**)realloc(NULL, sizeof(node_component*));
    new_node->components[0] = create_node_component();
    new_node->max_component_index = 0;

    // new_node->connections = NULL;
    // new_node->number_of_connections = 0;

    // new_node->children = NULL;
    // new_node->number_of_children = 0;

    return new_node;
}

uint8_t free_node(node* target)
{
    if(!target) return NODE_ERROR_NO_NODE;

    uint32_t i = 0;
    for(;i <= target->max_component_index; i++)
        free_node_component(target->components[i]);

    // realloc(target->connections,0);
    // realloc(target->children,0);

    realloc(target,0);

    return NODE_NO_ERROR;
}

//Graph
graph* create_graph()
{
    return (graph*)realloc(NULL, sizeof(graph));
}

uint8_t free_graph(graph* target)
{
    if(!target) return NODE_ERROR_NO_GRAPH;

    uint32_t i = 0;
    for(;i < target->size;i++)
    {
        free_node(target->nodes[i]);
    }
    realloc(target->nodes,0);
    target->size = 0;

    realloc(target,0);
}

uint8_t add_graph_node(graph* target, node* to_add)
{
    if(!target) return NODE_ERROR_NO_GRAPH;
    if(!to_add) return NODE_ERROR_NO_NODE;

    node* new_node_list = (node*)realloc(target->nodes, sizeof(node)*(target->size+1));

    if(!new_node_list) return NODE_ERROR_NO_MEMORY;

    target->nodes[target->size] = to_add;
    target->size++;

    return NODE_NO_ERROR;
}

//Utilities
uint8_t add_node_component(node* target, node_component* component)
{
    if(!target) return NODE_ERROR_NO_NODE;
    if(!component) return NODE_ERROR_NO_COMPONENT;

    node_component* new_list = (node_component*)realloc(target->components,
                                                        sizeof(node_component)*target->max_component_index+2);

    if(!new_list) return NODE_ERROR_NO_MEMORY;

    target->max_component_index++;
    target->components[target->max_component_index] = component;

    return NODE_NO_ERROR;
}

// uint8_t add_connection(node* target, node* connection)
// {
//      return NODE_NO_ERROR;
// }