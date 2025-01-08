#include <stdlib.h>

#include "api.c"

#include <stdio.h>

#define PRINT_FN printf
#include "../unit_testing.c"

int main()
{
    uint32_t temp;
    node* temp_node_a;
    node* temp_node_b;
    graph* temp_graph;

    #undef TITLE
    #define TITLE "Node"
    TEST_PRINT(TITLE"\n")

    #undef SUBTITLE
    #define SUBTITLE "Allocation"
    temp_node_a = create_node();
    VERIFY_SINGLE_VALUE(temp_node_a,!=,NULL)
    COLLECT_FINDINGS

    #undef SUBTITLE
    #define SUBTITLE "Deallocation - No node specified"
    result = free_node(NULL);
    VERIFY_SINGLE_VALUE(result,==,NODE_ERROR_NO_NODE)
    COLLECT_FINDINGS

    #undef SUBTITLE
    #define SUBTITLE "Deallocation - Non Recursive - Best Case scenario"
    result = free_node(temp_node_a);
    VERIFY_SINGLE_VALUE(result,==,NODE_NO_ERROR)
    COLLECT_FINDINGS

    ADD_SEPARATOR
    #undef TITLE
    #define TITLE "Connections"
    TEST_PRINT(TITLE"\n")

    #undef SUBTITLE
    #define SUBTITLE "Resizing edge list - Initial state"
    VALIDATE_EDGE_LIST();
    VERIFY_SINGLE_VALUE(edge_list,!=,NULL);
    VERIFY_SINGLE_VALUE(empty_edge_index,==,0);
    VERIFY_SINGLE_VALUE(max_edge_index,==,DEFAULT_EDGE_LIST_SIZE);
    COLLECT_FINDINGS

    #undef SUBTITLE
    #define SUBTITLE "Resizing edge list - Resize to lower size"
    resize_edge_list(max_edge_index - 1);
    VERIFY_SINGLE_VALUE(edge_list,!=,NULL);
    VERIFY_SINGLE_VALUE(max_edge_index,==,DEFAULT_EDGE_LIST_SIZE);
    COLLECT_FINDINGS
    
    #undef SUBTITLE
    #define SUBTITLE "Resizing edge list - Resize to same size"
    resize_edge_list(max_edge_index);
    VERIFY_SINGLE_VALUE(edge_list,!=,NULL);
    VERIFY_SINGLE_VALUE(max_edge_index,==,DEFAULT_EDGE_LIST_SIZE);
    COLLECT_FINDINGS
    
    #undef SUBTITLE
    #define SUBTITLE "Resizing edge list - Resize to a larger size"
    resize_edge_list(max_edge_index + 1);
    VERIFY_SINGLE_VALUE(edge_list,!=,NULL);
    VERIFY_SINGLE_VALUE(max_edge_index,==,DEFAULT_EDGE_LIST_SIZE*2);
    COLLECT_FINDINGS

    #undef SUBTITLE
    #define SUBTITLE "Connect Existing Node"
    temp_node_a = create_node();
    temp_node_b = create_node();
    connect_existing_node(temp_node_a, temp_node_b);
    VERIFY_SINGLE_VALUE(empty_edge_index,==,1);
    VERIFY_SINGLE_VALUE(edge_list[0].start,==,temp_node_a);
    VERIFY_SINGLE_VALUE(edge_list[0].end,==,temp_node_b);
    COLLECT_FINDINGS

    ADD_SEPARATOR
    #undef TITLE
    #define TITLE "Graph"
    TEST_PRINT(TITLE"\n")

    #undef SUBTITLE
    #define SUBTITLE "Allocation"
    temp_graph = create_graph();
	VERIFY_SINGLE_VALUE(temp_graph,!=,NULL)
	VERIFY_SINGLE_VALUE(temp_graph->max_node_index,==,0)
    COLLECT_FINDINGS
    
    #undef SUBTITLE
    #define SUBTITLE "Deallocation - No graph specifed"
    result = free_graph(NULL, NON_RECURSIVE);
	VERIFY_SINGLE_VALUE(result,==,NODE_ERROR_NO_GRAPH)
    COLLECT_FINDINGS

    #undef SUBTITLE
    #define SUBTITLE "Adding node to graph - No graph specified"
    result = add_graph_node(NULL, temp_node_a);
	VERIFY_SINGLE_VALUE(result,==,NODE_ERROR_NO_GRAPH)
    COLLECT_FINDINGS

    #undef SUBTITLE
    #define SUBTITLE "Adding node to graph - No node specified"
    result = add_graph_node(temp_graph, NULL);
	VERIFY_SINGLE_VALUE(result,==,NODE_ERROR_NO_NODE)
    COLLECT_FINDINGS
    
    #undef SUBTITLE
    #define SUBTITLE "Adding node to graph - Best Case Scenario"
    result = add_graph_node(temp_graph, temp_node_a);
	VERIFY_SINGLE_VALUE(result,==,NODE_NO_ERROR)
    VERIFY_SINGLE_VALUE(temp_graph->max_node_index,==,1)
    COLLECT_FINDINGS

    // ADD_SEPARATOR
    // #undef TITLE
    // #define TITLE "Deleting and trashing"
    // TEST_PRINT(TITLE"\n");

    // #undef SUBTITLE
    // #define SUBTITLE "Deleting node - Best Case Scenario"

    DEBRIEF
}