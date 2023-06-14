#include <gtk/gtk.h>

int counter = 0;

static void
do_update(gpointer data)
{

  for (int i = 0; i < 10; i++)
  {
    for (int j = 0; j < 10; j++)
    {
      GtkWidget *text_cell = gtk_grid_get_child_at(GTK_GRID(data), i, j);
      char s[10];
      sprintf(s, "  %d  ", i * j + counter);
      gtk_text_set_buffer(GTK_TEXT(text_cell), gtk_entry_buffer_new(s, 10));
    }
  }
}

static void
do_update_plus(GtkWidget *widget, gpointer data)
{

  do_update(data);
  counter = counter + 1;
}

static void
do_update_minus(GtkWidget *widget, gpointer data)
{

  do_update(data);
  counter = counter - 1;
}

static void
activate(GtkApplication *app, gpointer user_data)
{
  GtkWidget *window;
  GtkWidget *grid;
  GtkWidget *box_spreadsheet;
  GtkWidget *box_toolbar;
  GtkWidget *buttonPlus;
  GtkWidget *buttonMinus;

  window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), "Window");
  gtk_window_set_default_size(GTK_WINDOW(window), 800, 400);

  buttonPlus = gtk_button_new_with_label("+");
  buttonMinus = gtk_button_new_with_label("-");

  box_spreadsheet = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
  gtk_box_set_homogeneous(GTK_BOX(box_spreadsheet), FALSE);

  box_toolbar = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
  gtk_box_set_homogeneous(GTK_BOX(box_spreadsheet), FALSE);

  grid = gtk_grid_new();

  for (int i = 0; i < 10; i++)
  {
    for (int j = 0; j < 10; j++)
    {
      char s[10];
      sprintf(s, "  %d  ", i * j);
      GtkWidget *text_cell = gtk_text_new_with_buffer(gtk_entry_buffer_new(s, 10));
      gtk_grid_attach(GTK_GRID(grid), text_cell, i, j, 1, 1);
    }
  }

  g_signal_connect(buttonPlus, "clicked", G_CALLBACK(do_update_plus), grid);
  g_signal_connect(buttonMinus, "clicked", G_CALLBACK(do_update_minus), grid);

  gtk_box_append(GTK_BOX(box_toolbar), buttonPlus);
  gtk_box_append(GTK_BOX(box_toolbar), buttonMinus);

  gtk_box_append(GTK_BOX(box_spreadsheet), box_toolbar);
  gtk_box_append(GTK_BOX(box_spreadsheet), grid);

  gtk_window_set_child(GTK_WINDOW(window), box_spreadsheet);
  gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char **argv)
{
  GtkApplication *app;
  int status;

  app = gtk_application_new("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
  status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return status;
}
