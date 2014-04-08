#include "tree-view.h"

#define MAX_ELEMENTS 10

enum {
	COLUMN_NAME,
	NUM_COLUMNS
};

static void window_set_default_size(GtkWidget *window)
{
	GdkScreen *screen;
        int max_width;
        int max_height;

	screen = gdk_screen_get_default();
        max_width = gdk_screen_get_width(screen) * 1/4;
        max_height = gdk_screen_get_height(screen) * 1/4;

        gtk_window_set_default_size(GTK_WINDOW(window), max_width, max_height);
}

static gboolean on_delete_event(GtkWidget *widget,
				GdkEvent  *event,
				gpointer   data)
{
	/* If you return FALSE in the "delete_event" signal handler,
	 * GTK will emit the "destroy" signal. Returning TRUE means
	 * you don't want the window to be destroyed.
	 *
	 * This is useful for popping up 'are you sure you want to quit?'
	 * type dialogs.
	 */

	g_print("delete event occurred\n");

	return FALSE;
}

static gboolean selection_func(GtkTreeSelection *selection,
			       GtkTreeModel *model,
			       GtkTreePath *path,
			       gboolean path_currently_selected,
			       gpointer data)
{
	printf("selection_func\n");
	return TRUE;
}

static gboolean selection_changed_cb(GtkTreeSelection *selection,
				     gpointer user_data)
{
	printf("selection_changed_cb\n");
	return FALSE;
}

static gboolean button_press_event_cb(GtkWidget *widget,
				      GdkEventButton *event,
				      gpointer user_data)
{
	printf("button_press_event_cb\n");
	return FALSE;
}

static gboolean button_release_event_cb(GtkWidget *widget,
					GdkEventButton *event,
					gpointer user_data)
{
	printf("button_release_event_cb\n");
	return FALSE;
}

static void drag_begin_cb(GtkWidget *widget,
			  GdkDragContext *context,
			  gpointer user_data)
{
	printf("drag_begin_cb\n");
}

static gboolean row_activated_cb(GtkTreeView *tree_view,
				 GtkTreePath *path,
				 GtkTreeViewColumn *column,
				 gpointer user_data)
{
	printf("row selected\n");
	return TRUE;
}

static void add_columns(GtkTreeView *tree_view)
{
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;

	column = gtk_tree_view_column_new();

	gtk_tree_view_column_set_spacing(column, 1);
        gtk_tree_view_column_set_sizing(column, GTK_TREE_VIEW_COLUMN_AUTOSIZE);
        gtk_tree_view_column_set_resizable(column, TRUE);
        gtk_tree_view_column_set_sort_column_id(column, COLUMN_NAME);
        gtk_tree_view_column_set_title(column, "List");

	renderer = gtk_cell_renderer_text_new();
	g_object_set(renderer,
		     "ellipsize", PANGO_ELLIPSIZE_END,
		     NULL);

	gtk_tree_view_column_pack_start(column, renderer, TRUE);
	gtk_tree_view_column_set_attributes(column, renderer,
					    "text", COLUMN_NAME,
					    NULL);

        gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);
        gtk_tree_view_set_expander_column(GTK_TREE_VIEW(tree_view), column);

}

void populate_tree_store(GtkWidget *tree_widget, GtkTreeStore *tree_store)
{
	int i;

	for (i = 0; i < MAX_ELEMENTS; i++) {
		GtkTreeIter iter;
		char arr[10] = {0};

		sprintf(arr, "Entry %d", i);

		gtk_tree_store_append(tree_store, &iter, NULL);
		gtk_tree_store_set(tree_store, &iter,
				   COLUMN_NAME, arr,
				   -1);
	}
}

GtkWidget * create_tree_view(void)
{
	GtkWidget *scrolled, *tree_widget;
	GtkTreeStore *tree_store;
	GtkTreeSelection *selection;

	scrolled = gtk_scrolled_window_new(NULL, NULL);
	gtk_widget_set_hexpand(scrolled, TRUE);
	gtk_widget_set_vexpand(scrolled, TRUE);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled),
                                       GTK_POLICY_AUTOMATIC,
                                       GTK_POLICY_AUTOMATIC);
	gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(scrolled),
                                            GTK_SHADOW_IN);

	tree_widget = gtk_tree_view_new();

	gtk_container_add(GTK_CONTAINER(scrolled), tree_widget);
	tree_store = gtk_tree_store_new(NUM_COLUMNS,
					G_TYPE_STRING);
	gtk_tree_view_set_model(GTK_TREE_VIEW(tree_widget),
				GTK_TREE_MODEL(tree_store));
	gtk_tree_view_set_rules_hint(GTK_TREE_VIEW(tree_widget), TRUE);

	add_columns(GTK_TREE_VIEW(tree_widget));

	gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(tree_widget), TRUE);
	gtk_tree_view_set_enable_search(GTK_TREE_VIEW(tree_widget), TRUE);
	gtk_tree_view_set_search_column(GTK_TREE_VIEW(tree_widget), COLUMN_NAME);

	selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(tree_widget));
	gtk_tree_selection_set_mode(selection, GTK_SELECTION_MULTIPLE);
	gtk_tree_selection_set_select_function(selection,
					       selection_func,
					       tree_widget,
					       NULL);


	g_signal_connect(selection, "changed",
			 G_CALLBACK(selection_changed_cb),
			 tree_widget);
	g_signal_connect(tree_widget,
			 "button-press-event",
			 G_CALLBACK(button_press_event_cb),
			 tree_widget);
	g_signal_connect(tree_widget,
			 "button-release-event",
			 G_CALLBACK(button_release_event_cb),
			 tree_widget);
	g_signal_connect(tree_widget,
			 "drag-begin",
			 G_CALLBACK(drag_begin_cb),
			 tree_widget);
	g_signal_connect(tree_widget,
			 "row-activated",
			 G_CALLBACK(row_activated_cb),
			 tree_widget);
	/*
	g_signal_connect(tree_widget,
			 "motion-notify-event",
			 G_CALLBACK(motion_notify_event_cb),
			 tree_widget);
	*/

	populate_tree_store(tree_widget, tree_store);

	return scrolled;
}

static GtkWidget * new_window(void)
{
	GtkWidget *window, *tree_widget;

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "Tree View");
	window_set_default_size(window);

	tree_widget = create_tree_view();

	gtk_container_add(GTK_CONTAINER(window), tree_widget);


	return window;
}

int main(int argc, char **argv)
{
	GtkWidget *window;

	gtk_init(&argc, &argv);

	window = new_window();

	g_signal_connect(window,
			 "delete-event",
			 G_CALLBACK(on_delete_event),
			 NULL);

	g_signal_connect(window,
			 "destroy",
			 G_CALLBACK(gtk_main_quit),
			 NULL);

	gtk_container_set_border_width(GTK_CONTAINER(window), 10);


	gtk_widget_show_all(window);

	gtk_main();

	return 0;
}
