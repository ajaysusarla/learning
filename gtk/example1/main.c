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

#include <stdio.h>
#include "tree-view.h"

#define MAX_ELEMENTS 10

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
	return FALSE;
}

void populate_tree(GtkWidget *widget)
{
	int i;

	for (i = 0; i < MAX_ELEMENTS; i++) {
		char arr[10] = {0};

		sprintf(arr, "Entry %d", i);
		tv_tree_append_item(TV_TREE(widget), arr);
	}
}

static GtkWidget * new_window(void)
{
	GtkWidget *window, *tree_widget;
	GtkWidget *scrolled;

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "Tree View");
	window_set_default_size(window);

	scrolled = gtk_scrolled_window_new(NULL, NULL);
	gtk_widget_set_hexpand(scrolled, TRUE);
	gtk_widget_set_vexpand(scrolled, TRUE);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled),
                                       GTK_POLICY_AUTOMATIC,
                                       GTK_POLICY_AUTOMATIC);
	gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(scrolled),
                                            GTK_SHADOW_IN);

	gtk_container_add(GTK_CONTAINER(window), scrolled);

	tree_widget = tv_tree_new();

	gtk_container_add(GTK_CONTAINER(scrolled), tree_widget);

	populate_tree(tree_widget);

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
