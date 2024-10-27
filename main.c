#include <gtk/gtk.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

char* getTime(int offset) {
    time_t rawtime;
    struct tm *timeinfo;
    char *buffer = (char*)malloc(80 * sizeof(char));

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    timeinfo->tm_hour += offset;
    mktime(timeinfo);
    strftime(buffer, 80, "%H:%M:%S", timeinfo);

    return buffer;
}

gboolean update_time_labels(gpointer data) {
    GtkLabel *time_local = (GtkLabel*)g_object_get_data(G_OBJECT(data), "time_local");
    GtkLabel *time_second = (GtkLabel*)g_object_get_data(G_OBJECT(data), "time_second");
    
    char *current_time = getTime(0);
    char *markup = g_markup_printf_escaped("<b>%s</b>", current_time);
    gtk_label_set_markup(time_local, markup);
    g_free(markup);
    free(current_time);

    current_time = getTime(1);  // Add one hour
    markup = g_markup_printf_escaped("<b>%s</b>", current_time);
    gtk_label_set_markup(time_second, markup);
    g_free(markup);
    free(current_time);

    return TRUE; // Continue calling this function
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *time_local;
    GtkWidget *time_local_place;
    GtkWidget *time_second;
    GtkWidget *time_second_place;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "UniClock");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_widget_set_size_request(window, 100, 50);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
    gtk_container_add(GTK_CONTAINER(window), grid);

    time_local = gtk_label_new(NULL);
    time_local_place = gtk_label_new("Milan"); // Set your city instead
    gtk_grid_attach(GTK_GRID(grid), time_local, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), time_local_place, 0, 1, 1, 1);

    time_second = gtk_label_new(NULL);
    time_second_place = gtk_label_new("New York"); // Set needed city instead
    gtk_grid_attach(GTK_GRID(grid), time_second, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), time_second_place, 1, 1, 1, 1);

    g_object_set_data(G_OBJECT(window), "time_local", time_local);
    g_object_set_data(G_OBJECT(window), "time_second", time_second);

    // Call update_time_labels every second
    g_timeout_add_seconds(1, update_time_labels, window);

    gtk_widget_show_all(window);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_main();

    return 0;
}

