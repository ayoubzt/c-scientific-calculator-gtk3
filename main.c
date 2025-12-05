#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "evaluation.h"

GtkWidget *entry;
GtkCssProvider *css_provider;
char evString[1000] = {0};
typedef struct but but;
struct but { const char *label; const char *tok; };

// Append character to entry
void on_button_append(GtkWidget *widget, gpointer data) {
    const char *txt = (const char *)data;
    const char *current = gtk_entry_get_text(GTK_ENTRY(entry));
    char buffer[512];
    snprintf(buffer, sizeof(buffer), "%s%s", current, txt);
    gtk_entry_set_text(GTK_ENTRY(entry), buffer);
    strcat(evString, txt);
}

void on_button_append2(GtkWidget *widget, gpointer data) {
    but* dat = (but *)data;
    const char *txt = dat->label;
    const char *current = gtk_entry_get_text(GTK_ENTRY(entry));
    char buffer[512];
    snprintf(buffer, sizeof(buffer), "%s%s", current, txt);
    gtk_entry_set_text(GTK_ENTRY(entry), buffer);
    const char *evText = dat->tok;
    strcat(evString, evText);
}

// Clear entry
void on_clear(GtkWidget *widget, gpointer data) {
    gtk_entry_set_text(GTK_ENTRY(entry), "");
    for (int i = 0; i<1000; i++) {evString[i] = 0;}
}

void on_backs(GtkWidget *widget, gpointer data) {
    char post[1000];
    const char *current = gtk_entry_get_text(GTK_ENTRY(entry));
    strcat(post, current);
    post[strlen(current)-1] = 0;
    gtk_entry_set_text(GTK_ENTRY(entry), post);
    evString[strlen(evString)-1] = 0;
}

// Evaluate expression
void on_equals(GtkWidget *widget, gpointer data) {
    // const char *text = gtk_entry_get_text(GTK_ENTRY(entry));
    // char expr[600];
    // snprintf(expr, sizeof(expr), "%s~", text);  // Add the mandatory "~"
    if (evString[0]) {
        const char* cond = "~";
        strcat(evString, cond); 
        double result = Evaluate(evString);
        char buffer[256];
        snprintf(buffer, sizeof(buffer), "%g", result);
        gtk_entry_set_text(GTK_ENTRY(entry), buffer);
        strcpy(evString, buffer);
    } else gtk_entry_set_text(GTK_ENTRY(entry), "");
}

// Dark mode CSS (default)
const char *dark_css =
"window { background-color: #111111; }"
"entry, button {"
" font-family: 'Montserrat'; font-weight: bold; font-size: 28px;"
" color: #ffffff; background: #1e1e1e;"
" border-radius: 12px; border: 2px solid #444444; transition: 150ms; }"
"entry { padding: 12px; background: #111111; border: 2px solid #555555; }"
"button:hover { background: #222222; border-color: #ff0000; box-shadow: 0px 0px 12px #ff0000; }"
"button:active { background: #660000; }";

// Light mode CSS
const char *light_css =
"window { background-color: #f5f5f5; }"
"entry, button {"
" font-family: 'Montserrat'; font-weight: bold; font-size: 28px;"
" color: #000000; background: #e0e0e0;"
" border-radius: 12px; border: 2px solid #999999; transition: 150ms; }"
"entry { padding: 12px; background: #ffffff; border: 2px solid #aaaaaa; }"
"button:hover { background: #cccccc; border-color: #ff0000; box-shadow: 0px 0px 12px #ff0000; }"
"button:active { background: #999999; }";

// Toggle dark/light mode
void toggle_theme(GtkWidget *widget, gpointer data) {
    static int dark = 1;  // dark mode default
    dark = !dark;
    gtk_css_provider_load_from_data(css_provider, dark ? dark_css : light_css, -1, NULL);
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    // Apply CSS
    css_provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(css_provider, dark_css, -1, NULL);
    gtk_style_context_add_provider_for_screen(
        gdk_screen_get_default(),
        GTK_STYLE_PROVIDER(css_provider),
        GTK_STYLE_PROVIDER_PRIORITY_USER
    );

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Scientific Calculator");
    gtk_window_set_default_size(GTK_WINDOW(window), 720, 900);
    gtk_window_set_resizable(GTK_WINDOW(window), TRUE);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 5);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 5);
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
    gtk_container_set_border_width(GTK_CONTAINER(grid), 10);
    gtk_container_add(GTK_CONTAINER(window), grid);

    // Entry
    entry = gtk_entry_new();
    gtk_entry_set_alignment(GTK_ENTRY(entry), 1.0);
    gtk_widget_set_hexpand(entry, TRUE);
    gtk_widget_set_vexpand(entry, FALSE);
    gtk_grid_attach(GTK_GRID(grid), entry, 0, 0, 5, 1);

    // Dark/Light toggle button (top-right)
    GtkWidget *mode_toggle = gtk_button_new_with_label("🌞/🌙");
    gtk_widget_set_hexpand(mode_toggle, TRUE);
    gtk_widget_set_vexpand(mode_toggle, FALSE);
    g_signal_connect(mode_toggle, "clicked", G_CALLBACK(toggle_theme), NULL);
    gtk_grid_attach(GTK_GRID(grid), mode_toggle, 5, 0, 1, 1);

    // Scientific buttons
    but sci[] = {
        {"sin", "s"}, {"cos", "c"}, {"tan", "t"},
        {"log", "l"}, {"ln", "l"}, {"sqrt", "S"},
        {"(", "("}, {")", ")"}, {"^", "^"}, 
        {"!", "f"}, {"π", "p"}, {"e", "e"}
    };

    int sci_pos = 0;
    for(int row=1; row<=2; row++){
        for(int col=0; col<6; col++){
            if(sci_pos >= 12) break;
            GtkWidget *btn = gtk_button_new_with_label(sci[sci_pos].label);
            gtk_widget_set_hexpand(btn, TRUE);
            gtk_widget_set_vexpand(btn, TRUE);
            g_signal_connect(btn, "clicked", G_CALLBACK(on_button_append2), (gpointer)&sci[sci_pos]);
            gtk_grid_attach(GTK_GRID(grid), btn, col, row, 1, 1);
            sci_pos++;
        }
    }

    // Number buttons
    const char *nums[] = {"7","8","9","4","5","6","1","2","3"};
    int pos = 0;
    for(int row=3; row<=5; row++){
        for(int col=0; col<3; col++){
            GtkWidget *btn = gtk_button_new_with_label(nums[pos]);
            gtk_widget_set_hexpand(btn, TRUE);
            gtk_widget_set_vexpand(btn, TRUE);
            g_signal_connect(btn, "clicked", G_CALLBACK(on_button_append), (gpointer)nums[pos]);
            gtk_grid_attach(GTK_GRID(grid), btn, col, row, 1, 1);
            pos++;
        }
    }

    // Zero button
    GtkWidget *zero = gtk_button_new_with_label("0");
    gtk_widget_set_hexpand(zero, TRUE);
    gtk_widget_set_vexpand(zero, TRUE);
    g_signal_connect(zero, "clicked", G_CALLBACK(on_button_append), (gpointer)"0");
    gtk_grid_attach(GTK_GRID(grid), zero, 0, 6, 2, 1);

    // Operators
    const char *ops[] = {"+","-","*","/"};
    for(int i=0; i<4; i++){
        GtkWidget *btn = gtk_button_new_with_label(ops[i]);
        gtk_widget_set_hexpand(btn, TRUE);
        gtk_widget_set_vexpand(btn, TRUE);
        g_signal_connect(btn, "clicked", G_CALLBACK(on_button_append), (gpointer)ops[i]);
        gtk_grid_attach(GTK_GRID(grid), btn, 3, i+3, 1, 1);
    }

    // Equals button
    GtkWidget *equals = gtk_button_new_with_label("=");
    gtk_widget_set_hexpand(equals, TRUE);
    gtk_widget_set_vexpand(equals, TRUE);
    g_signal_connect(equals, "clicked", G_CALLBACK(on_equals), NULL);
    gtk_grid_attach(GTK_GRID(grid), equals, 2, 6, 1, 1);

    GtkWidget *back = gtk_button_new_with_label("DEL");
    gtk_widget_set_hexpand(back, TRUE);
    gtk_widget_set_vexpand(back, TRUE);
    g_signal_connect(back, "clicked", G_CALLBACK(on_backs), NULL);
    gtk_grid_attach(GTK_GRID(grid), back, 4, 5, 2, 1);

    // Clear button
    GtkWidget *clear = gtk_button_new_with_label("Clear");
    gtk_widget_set_hexpand(clear, TRUE);
    gtk_widget_set_vexpand(clear, TRUE);
    g_signal_connect(clear, "clicked", G_CALLBACK(on_clear), NULL);
    gtk_grid_attach(GTK_GRID(grid), clear, 4, 6, 2, 1);

    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}
