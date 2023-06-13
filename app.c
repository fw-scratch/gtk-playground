#include <gtk/gtk.h>

static void
activate(GtkApplication *app,
         gpointer user_data)
{
  GtkWidget *window;
  GtkWidget *grid;

  window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), "Window");
  gtk_window_set_default_size(GTK_WINDOW(window), 800, 400);

  grid = gtk_grid_new();

  for (int i = 0; i < 10; i++)
  {
    for (int j = 0; j < 10; j++)
    {
      char s[10];
      sprintf(s, "  %d  ", i * j);
      gtk_grid_attach(GTK_GRID(grid), gtk_text_new_with_buffer(gtk_entry_buffer_new(s, 10)), i, j, 1, 1);
    }
  }
  gtk_window_set_child(GTK_WINDOW(window), grid);
  gtk_window_present(GTK_WINDOW(window));
}

int main(int argc,
         char **argv)
{
  GtkApplication *app;
  int status;

  app = gtk_application_new("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
  status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return status;
}
