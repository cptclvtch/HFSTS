struct nk_style *s = &ctx->style;
nk_style_push_color(ctx, &s->window.background, nk_rgba(0.15,0.4,0.15,1.0));
nk_style_push_style_item(ctx, &s->window.fixed_background, nk_style_item_color(nk_rgba(0.15,0.4,0.15,1.0)));
if(nk_begin(ctx, "Node Editor", nk_rect(0,0,width, height), NK_WINDOW_NO_SCROLLBAR))
{
    struct nk_command_buffer* canvas = nk_window_get_canvas(ctx);
    struct nk_rect total_space = nk_window_get_content_region(ctx);
    struct nk_vec2 scrolling;
    const struct nk_input* in = &ctx->input;

    nk_layout_row_dynamic(ctx, 0, 2);
    nk_option_label(ctx, "option", 1);
    nk_option_label(ctx, "option", 0);

    nk_layout_space_begin(ctx, NK_STATIC, total_space.h, INT_MAX);
    {
    }
    nk_layout_space_end(ctx);

    /* window content scrolling */
    if (nk_input_is_mouse_hovering_rect(in, nk_window_get_bounds(ctx)) &&
        nk_input_is_mouse_down(in, NK_BUTTON_RIGHT)) {
        scrolling.x += in->mouse.delta.x;
        scrolling.y += in->mouse.delta.y;
    }
}
nk_end(ctx);
nk_style_pop_color(ctx);
nk_style_pop_style_item(ctx);