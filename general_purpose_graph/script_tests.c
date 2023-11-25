#include <stdlib.h>

#include "api.c"

#include <stdio.h>

#define PRINT_FN printf
#include "../unit_testing.c"

int main()
{
    #define TITLE "Node Component"
    TEST_PRINT(TITLE"\n")

    node_component* temp_component;
    node* temp_node;
    graph* temp_graph;
    uint32_t temp;

    #define SUBTITLE "Allocation"
    temp_component = create_node_component();
    VERIFY_SINGLE_VALUE(temp_component,!=,NULL)
    COLLECT_FINDINGS

    #undef SUBTITLE
    #define SUBTITLE "Deallocation - Best Case Scenario"
    result = free_node_component(temp_component);
    VERIFY_SINGLE_VALUE(result,==,NODE_NO_ERROR)
    COLLECT_FINDINGS

    #undef SUBTITLE
    #define SUBTITLE "Deallocation - No component specified"
    result = free_node_component(NULL);
    VERIFY_SINGLE_VALUE(result,==,NODE_ERROR_NO_NODE)
    COLLECT_FINDINGS

    #undef SUBTITLE
    #define SUBTITLE "Allocation - Allocating data"
    temp_component = create_node_component();
    temp_component->text = "t";
    temp_component->integer_number = 1;
    temp_component->float_number = 0.5;

    VERIFY_SINGLE_VALUE(*temp_component->text,==,'t')
    VERIFY_SINGLE_VALUE(*(temp_component->text+1),==,'\0')
    VERIFY_SINGLE_VALUE(temp_component->integer_number,==,1)
    VERIFY_SINGLE_VALUE(temp_component->float_number,==,0.5)
    COLLECT_FINDINGS

    // #undef SUBTITLE
    // #define SUBTITLE "Component Allocation - Allocating children"
    // child_component = allocate_new_node_component();
    // temp_component->children = child_component;

    // VERIFY_SINGLE_VALUE(temp_component->children,!=,NULL)
    // COLLECT_FINDINGS

    // #undef SUBTITLE
    // #define SUBTITLE "Component Deallocation - Deallocating children"
    // uint8_t result = deallocate_node_component(temp_component);
    // VERIFY_SINGLE_VALUE(result,==,NODE_ERROR_NO_NODE)
    // COLLECT_FINDINGS

    ADD_SEPARATOR
    #undef TITLE
    #define TITLE "Node"
    TEST_PRINT(TITLE"\n")

    #undef SUBTITLE
    #define SUBTITLE "Allocation"
    temp_node = create_node();
    VERIFY_SINGLE_VALUE(temp_node,!=,NULL)
    VERIFY_SINGLE_VALUE(temp_node->max_component_index,==,0)
    VERIFY_SINGLE_VALUE(temp_node->components,!=,NULL)
    COLLECT_FINDINGS

    #undef SUBTITLE
    #define SUBTITLE "Deallocation - Best Case scenario"
    result = free_node(temp_node);
    VERIFY_SINGLE_VALUE(result,==,NODE_NO_ERROR)
    COLLECT_FINDINGS

    #undef SUBTITLE
    #define SUBTITLE "Deallocation - No node specified"
    result = free_node(NULL);
    VERIFY_SINGLE_VALUE(result,==,NODE_ERROR_NO_NODE)
    COLLECT_FINDINGS

    #undef SUBTITLE
    #define SUBTITLE "Adding component - Best Case Scenario"
    temp = temp_node->max_component_index;
    result = add_node_component(temp_node, create_node_component());
    VERIFY_SINGLE_VALUE(temp_node->components[temp],!=,NULL)
    VERIFY_SINGLE_VALUE(temp_node->max_component_index,==,temp+1)
    COLLECT_FINDINGS

    #undef SUBTITLE
    #define SUBTITLE "Adding component - No node specified"
    result = add_node_component(NULL, temp_component);
	VERIFY_SINGLE_VALUE(result,==,NODE_ERROR_NO_NODE)
    COLLECT_FINDINGS

    #undef SUBTITLE
    #define SUBTITLE "Adding component - No component specified"
    result = add_node_component(temp_node, NULL);
	VERIFY_SINGLE_VALUE(result,==,NODE_ERROR_NO_COMPONENT)
    COLLECT_FINDINGS

    ADD_SEPARATOR
    #undef TITLE
    #define TITLE "Graph"
    TEST_PRINT(TITLE"\n")

    #undef SUBTITLE
    #define SUBTITLE "Allocation"
    temp_graph = create_graph();
	VERIFY_SINGLE_VALUE(temp_graph,!=,NULL)
	VERIFY_SINGLE_VALUE(temp_graph->size,==,0)
    COLLECT_FINDINGS
    
    #undef SUBTITLE
    #define SUBTITLE "Deallocation - No graph specifed"
    result = free_graph(NULL);
	VERIFY_SINGLE_VALUE(result,==,NODE_ERROR_NO_GRAPH)
    COLLECT_FINDINGS

    #undef SUBTITLE
    #define SUBTITLE "Adding node to graph - No graph specified"
    result = add_graph_node(NULL, temp_node);
	VERIFY_SINGLE_VALUE(result,==,NODE_ERROR_NO_GRAPH)
    COLLECT_FINDINGS

    #undef SUBTITLE
    #define SUBTITLE "Adding node to graph - No node specified"
    result = add_graph_node(temp_graph, NULL);
	VERIFY_SINGLE_VALUE(result,==,NODE_ERROR_NO_NODE)
    COLLECT_FINDINGS

    
    #undef SUBTITLE
    #define SUBTITLE "Adding node to graph"
    result = add_graph_node(temp_graph, temp_node);
	VERIFY_SINGLE_VALUE(result,==,NODE_NO_ERROR)
    VERIFY_SINGLE_VALUE(temp_graph->size,==,1);
    COLLECT_FINDINGS

    //-------------------------------
    //create two nodes
    // node* new_node;
    // new_node = allocate_new_node();

    //create 3 node components
    // node_component* new_component;
    // new_component = allocate_new_node_component();

    // new_component->text = "Integer is: ";
    // new_component->integer_number = 2;

    // new_node->components = new_component;

    // new_component = allocate_new_node_component();

    // new_component->text = "Float is: ";
    // new_component->floating_number = 0.5f;

    //create graph
    //-----------------------------
    
    DEBRIEF
}