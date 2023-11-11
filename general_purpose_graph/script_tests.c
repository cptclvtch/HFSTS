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

    #define SUBTITLE "Component Allocation"
    temp_component = allocate_new_node_component();
    VERIFY_SINGLE_VALUE(temp_component,!=,NULL)
    COLLECT_FINDINGS

    #undef SUBTITLE
    #define SUBTITLE "Component Deallocation - Best Case Scenario"
    result = deallocate_node_component(temp_component);
    VERIFY_SINGLE_VALUE(result,==,0)
    COLLECT_FINDINGS

    #undef SUBTITLE
    #define SUBTITLE "Component Deallocation - No component specified"
    result = deallocate_node_component(NULL);
    VERIFY_SINGLE_VALUE(result,==,NODE_ERROR_NO_NODE)
    COLLECT_FINDINGS

    #undef SUBTITLE
    #define SUBTITLE "Component Allocation - Allocating data"
    temp_component = allocate_new_node_component();
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
    #define SUBTITLE "Node Allocation"
    temp_node = allocate_new_node();
    VERIFY_SINGLE_VALUE(temp_node,!=,NULL)
    COLLECT_FINDINGS

    // node* new_node = allocate_new_node();
    
    // node_component* component;
    // component = new_node->components;

    // printf("%p\n", component);
    // component->text = "The integer is: ";
    // component->integer_number = 2;

    // component = add_new_node_component(new_node);
    // if(component) printf("Successfully added node component! %p\n", component);

    // component->text = "The float is: ";
    // component->float_number = 0.5;

    // PRINT_FN("%s\n", new_node->components[0].text);

    // //create two nodes
    // node* new_node;
    // new_node = allocate_new_node();

    // //create 3 node components
    // node_component* new_component;
    // new_component = allocate_new_node_component();

    // new_component->text = "Integer is: ";
    // new_component->integer_number = 2;

    // node->components = new_component;

    // new_component = allocate_new_node_component();

    // new_component->text = "Float is: ";
    // new_component->floating_number = 0.5f;

    // //create graph
    

    // //delete a node
    
    DEBRIEF
}