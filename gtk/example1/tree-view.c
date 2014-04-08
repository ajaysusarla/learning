/*
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "tree-view.h"

enum {
	COLUMN_NAME,
	NUM_COLUMNS
};

typedef struct {
	GtkTreeStore *tree_store;

	gboolean dragging:1; /* if dragging items */
	gboolean drag_started:1; /* drag started */
	gboolean drag_selection:1; /* should row be selected or not*/
	int drag_start_x;
	int drag_start_y;
} TvTreePrivate;

G_DEFINE_TYPE_WITH_PRIVATE(TvTree,
			   tv_tree,
			   GTK_TYPE_TREE_VIEW);

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
	GtkTreeView *tree_view;
	GtkTreePath *path;
	GtkTreeSelection *selection;
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

/* class implementation */
static void tv_tree_finalize(GObject *object)
{
	G_OBJECT_CLASS(tv_tree_parent_class)->finalize(object);
}

static void tv_tree_class_init(TvTreeClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	GtkWidgetClass *widget_class = GTK_WIDGET_CLASS(klass);

	object_class->finalize = tv_tree_finalize;

	widget_class->drag_begin = NULL;
}

static void tv_tree_init(TvTree *tree)
{
	GtkTreeSelection *selection;
	TvTreePrivate *priv;

	priv = tv_tree_get_instance_private(tree);

	priv->tree_store = gtk_tree_store_new(NUM_COLUMNS,
					      G_TYPE_STRING);
	gtk_tree_view_set_model(GTK_TREE_VIEW(tree),
				GTK_TREE_MODEL(priv->tree_store));
	gtk_tree_view_set_rules_hint(GTK_TREE_VIEW(tree), TRUE);

	add_columns(GTK_TREE_VIEW(tree));

	gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(tree), TRUE);
	gtk_tree_view_set_enable_search(GTK_TREE_VIEW(tree), TRUE);
	gtk_tree_view_set_search_column(GTK_TREE_VIEW(tree), COLUMN_NAME);

	selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(tree));
	gtk_tree_selection_set_mode(selection, GTK_SELECTION_MULTIPLE);
	gtk_tree_selection_set_select_function(selection,
					       selection_func,
					       tree,
					       NULL);


	g_signal_connect(selection, "changed",
			 G_CALLBACK(selection_changed_cb),
			 tree);
	g_signal_connect(tree,
			 "button-press-event",
			 G_CALLBACK(button_press_event_cb),
			 tree);
	g_signal_connect(tree,
			 "button-release-event",
			 G_CALLBACK(button_release_event_cb),
			 tree);
	g_signal_connect(tree,
			 "drag-begin",
			 G_CALLBACK(drag_begin_cb),
			 tree);
	g_signal_connect(tree,
			 "row-activated",
			 G_CALLBACK(row_activated_cb),
			 tree);
}

/* public methods */
GtkWidget *tv_tree_new(void)
{
	TvTree *tree;

	tree = g_object_new(TV_TYPE_TREE, NULL);

	return GTK_WIDGET(tree);
}

void tv_tree_append_item(TvTree *tree, char *entry)
{
	TvTreePrivate *priv;
	GtkTreeIter iter;

	priv = tv_tree_get_instance_private(tree);

	gtk_tree_store_append(priv->tree_store, &iter, NULL);
	gtk_tree_store_set(priv->tree_store, &iter,
			   COLUMN_NAME, entry,
			   -1);

	return;
}
