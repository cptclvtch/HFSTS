struct nk_rect total_space;
const struct nk_input* in = &ctx->input;
struct nk_command_buffer* canvas;
// struct node* updated = 0;

//node editor
// struct node_link links[64];
// int link_count;
// struct nk_rect bounds;
// struct node *selected;
struct nk_vec2 scrolling;
// struct node_linking linking;

//background color
// ctx->style.window.fixed_background = nk_style_item_color(nk_rgb(0.15*255,0.4*255,0.15*255));
ctx->style.window.fixed_background = nk_style_item_color(nk_rgb(1,77,78));
ctx->style.window.padding = nk_vec2(0,0);

if (nk_begin(ctx, "NodeEdit", nk_rect(0, 0, window_w, window_h), NK_WINDOW_BORDER|NK_WINDOW_NO_SCROLLBAR))
{
    /* allocate complete window space */
    canvas = nk_window_get_canvas(ctx);
    total_space = nk_window_get_content_region(ctx);
    nk_layout_space_begin(ctx, NK_STATIC, total_space.h, INT_MAX);
    {
        struct nk_rect size = nk_layout_space_bounds(ctx);
        // struct nk_panel* node = 0;

        /* display grid */
        float x, y;
        const float grid_size = 32.0f;
        // const struct nk_color grid_color = nk_rgb(200, 255, 200);
        const struct nk_color grid_color = nk_rgb(1, 55, 58);
        for (x = (float)fmod(size.x - scrolling.x, grid_size); x < size.w; x += grid_size)
            nk_stroke_line(canvas, x+size.x, size.y, x+size.x, size.y+size.h, 1.0f, grid_color);
        for (y = (float)fmod(size.y - scrolling.y, grid_size); y < size.h; y += grid_size)
            nk_stroke_line(canvas, size.x, y+size.y, size.x+size.w, y+size.y, 1.0f, grid_color);

        /* execute each node as a movable group */
        uint8_t i = 0;
        for(; i < main_graph->size; i++)
        {
            node* it = main_graph->nodes[i];
            /* calculate scrolled node window position and size */
            nk_layout_space_push(ctx, nk_rect(it->x - scrolling.x,
                it->y - scrolling.y, it->width, it->height));

            /* execute node window */
            ctx->style.window.fixed_background = nk_style_item_color(nk_rgb(50,50,50));
            if (nk_group_begin(ctx, "node", NK_WINDOW_MOVABLE|NK_WINDOW_NO_SCROLLBAR|NK_WINDOW_BORDER|NK_WINDOW_TITLE))
            {
                /* always have last selected node on top */
                // node = nk_window_get_panel(ctx);
                // if (nk_input_mouse_clicked(in, NK_BUTTON_LEFT, node->bounds)
                //     &&
                //     (!(it->prev && nk_input_mouse_clicked(in, NK_BUTTON_LEFT,
                //     nk_layout_space_rect_to_screen(ctx, node->bounds))))
                //     &&
                //     nodedit->end != it)
                // {
                //     updated = it;
                // }

                /* ================= NODE CONTENT =====================*/
                uint8_t j = 0;
                for(; j <= it->max_component_index; j++)
                {
                    nk_layout_row_dynamic(ctx, 25, 1);
                    it->components[j]->integer_number = (nk_byte)nk_propertyi(ctx, "#Int:", 0, it->components[j]->integer_number, 255, 1,1);
                    it->components[j]->float_number = (nk_byte)nk_propertyf(ctx, "#Float:", 0, it->components[j]->float_number, 255, 1,1);
                }
                /* ====================================================*/
                nk_group_end(ctx);
            }
        //     {
        //         /* node connector and linking */
        //         float space;
        //         struct nk_rect bounds;
        //         bounds = nk_layout_space_rect_to_local(ctx, node->bounds);
        //         bounds.x += scrolling.x;
        //         bounds.y += scrolling.y;
        //         it->bounds = bounds;

        //         /* output connector */
        //         space = node->bounds.h / (float)((it->output_count) + 1);
        //         for (n = 0; n < it->output_count; ++n)
        //         {
        //             struct nk_rect circle;
        //             circle.x = node->bounds.x + node->bounds.w-4;
        //             circle.y = node->bounds.y + space * (float)(n+1);
        //             circle.w = 8; circle.h = 8;
        //             nk_fill_circle(canvas, circle, nk_rgb(100, 100, 100));

        //             /* start linking process */
        //             if (nk_input_has_mouse_click_down_in_rect(in, NK_BUTTON_LEFT, circle, nk_true))
        //             {
        //                 nodedit->linking.active = nk_true;
        //                 nodedit->linking.node = it;
        //                 nodedit->linking.input_id = it->ID;
        //                 nodedit->linking.input_slot = n;
        //             }

        //             /* draw curve from linked node slot to mouse position */
        //             if (nodedit->linking.active && nodedit->linking.node == it &&
        //                 nodedit->linking.input_slot == n)
        //             {
        //                 struct nk_vec2 l0 = nk_vec2(circle.x + 3, circle.y + 3);
        //                 struct nk_vec2 l1 = in->mouse.pos;
        //                 nk_stroke_curve(canvas, l0.x, l0.y, l0.x + 50.0f, l0.y,
        //                     l1.x - 50.0f, l1.y, l1.x, l1.y, 1.0f, nk_rgb(100, 100, 100));
        //             }
        //         }

        //         /* input connector */
        //         space = node->bounds.h / (float)((it->input_count) + 1);
        //         for (n = 0; n < it->input_count; ++n)
        //         {
        //             struct nk_rect circle;
        //             circle.x = node->bounds.x-4;
        //             circle.y = node->bounds.y + space * (float)(n+1);
        //             circle.w = 8; circle.h = 8;
        //             nk_fill_circle(canvas, circle, nk_rgb(100, 100, 100));
        //             if (nk_input_is_mouse_released(in, NK_BUTTON_LEFT) &&
        //                 nk_input_is_mouse_hovering_rect(in, circle) &&
        //                 nodedit->linking.active && nodedit->linking.node != it)
        //             {
        //                 nodedit->linking.active = nk_false;
        //                 node_editor_link(nodedit, nodedit->linking.input_id,
        //                     nodedit->linking.input_slot, it->ID, n);
        //             }
        //         }
        //     }
        }

        // /* reset linking connection */
        // if (nodedit->linking.active && nk_input_is_mouse_released(in, NK_BUTTON_LEFT))
        // {
        //     nodedit->linking.active = nk_false;
        //     nodedit->linking.node = NULL;
        //     fprintf(stdout, "linking failed\n");
        // }

        // /* draw each link */
        // for (n = 0; n < nodedit->link_count; ++n)
        // {
        //     struct node_link *link = &nodedit->links[n];
        //     struct node *ni = node_editor_find(nodedit, link->input_id);
        //     struct node *no = node_editor_find(nodedit, link->output_id);
        //     float spacei = node->bounds.h / (float)((ni->output_count) + 1);
        //     float spaceo = node->bounds.h / (float)((no->input_count) + 1);
        //     struct nk_vec2 l0 = nk_layout_space_to_screen(ctx,
        //         nk_vec2(ni->bounds.x + ni->bounds.w, 3.0f + ni->bounds.y + spacei * (float)(link->input_slot+1)));
        //     struct nk_vec2 l1 = nk_layout_space_to_screen(ctx,
        //         nk_vec2(no->bounds.x, 3.0f + no->bounds.y + spaceo * (float)(link->output_slot+1)));

        //     l0.x -= scrolling.x;
        //     l0.y -= scrolling.y;
        //     l1.x -= scrolling.x;
        //     l1.y -= scrolling.y;
        //     nk_stroke_curve(canvas, l0.x, l0.y, l0.x + 50.0f, l0.y,
        //         l1.x - 50.0f, l1.y, l1.x, l1.y, 1.0f, nk_rgb(100, 100, 100));
        // }

        // if (updated) {
        //     /* reshuffle nodes to have least recently selected node on top */
        //     node_editor_pop(nodedit, updated);
        //     node_editor_push(nodedit, updated);
        // }

        /* node selection */
        // if (nk_input_mouse_clicked(in, NK_BUTTON_LEFT, nk_layout_space_bounds(ctx)))
        // {
        //     it = nodedit->begin;
        //     nodedit->selected = NULL;
        //     nodedit->bounds = nk_rect(in->mouse.pos.x, in->mouse.pos.y, 100, 200);
        //     while (it)
        //     {
        //         struct nk_rect b = nk_layout_space_rect_to_screen(ctx, it->bounds);
        //         b.x -= scrolling.x;
        //         b.y -= scrolling.y;
        //         if (nk_input_is_mouse_hovering_rect(in, b))
        //             nodedit->selected = it;
        //         it = it->next;
        //     }
        // }

        /* contextual menu */
        if (nk_contextual_begin(ctx, 0, nk_vec2(100, 220), nk_window_get_bounds(ctx)))
        {
            nk_layout_row_dynamic(ctx, 25, 1);
            if (nk_contextual_item_label(ctx, "New node", NK_TEXT_CENTERED))
            {
                node* n = create_node();
                n->x = in->mouse.pos.x + scrolling.x;
                n->y = in->mouse.pos.y + scrolling.y;
                n->width = 100;
                n->height = 100;
                add_graph_node(main_graph, n);
            }
            nk_contextual_end(ctx);
        }
    }
    nk_layout_space_end(ctx);

    /* window content scrolling */
    if (nk_input_is_mouse_hovering_rect(in, nk_window_get_bounds(ctx)) &&
        nk_input_is_mouse_down(in, NK_BUTTON_LEFT)) {
        scrolling.x -= in->mouse.delta.x;
        scrolling.y -= in->mouse.delta.y;
    }
}
nk_end(ctx);
