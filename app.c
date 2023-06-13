#include <gtk/gtk.h>

int counter = 0;
GtkWidget *label;


static void
print_hello(GtkWidget *widget,
            gpointer data)
{
  const char *s = gtk_button_get_label(GTK_BUTTON(widget));
  if (g_strcmp0 (s, "+") == 0) {
    counter = counter + 1;
  } else if (g_strcmp0 (s, "-") == 0) {
    counter = counter - 1;
  }
  g_print(s);
  char str[4];
  sprintf(str, "%d", counter);
  g_print(str);
  gtk_label_set_label(GTK_LABEL(label), str);
}

static void
activate(GtkApplication *app,
         gpointer user_data)
{
  GtkWidget *window;
  GtkWidget *buttonPlus;
  GtkWidget *buttonMinus;
  GtkWidget *box;

  window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), "Window");
  gtk_window_set_default_size(GTK_WINDOW(window), 800, 800);

  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
  gtk_box_set_homogeneous(GTK_BOX(box), TRUE);
  gtk_window_set_child(GTK_WINDOW(window), box);

  buttonPlus = gtk_button_new_with_label("+");
  g_signal_connect(buttonPlus, "clicked", G_CALLBACK(print_hello), NULL);

  buttonMinus = gtk_button_new_with_label("-");
  g_signal_connect(buttonMinus, "clicked", G_CALLBACK(print_hello), NULL);

  label = gtk_label_new("0");

  gtk_box_append(GTK_BOX(box), buttonPlus);
  gtk_box_append(GTK_BOX(box), buttonMinus);
  gtk_box_append(GTK_BOX(box), label);

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
