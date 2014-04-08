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

#ifndef TREE_VIEW_H
#define TREE_VIEW_H

#include <gtk/gtk.h>

#define TV_TYPE_TREE              (tv_tree_get_type())
#define TV_TREE(obj)              (G_TYPE_CHECK_INSTANCE_CAST((obj), TV_TYPE_TREE, TvTree))
#define TV_TREE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST((klass), TV_TYPE_TREE, TvTreeClass))
#define TV_IS_TREE(obj)           (G_TYPE_CHECK_INSTANCE_TYPE((obj), TV_TYPE_TREE))
#define TV_IS_TREE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE((klass), TV_TYPE_TREE))
#define TV_TREE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS((obj), TV_TYPE_TREE, TvTreeClass))

typedef struct _TvTree TvTree;
typedef struct _TvTreeClass TvTreeClass;

struct _TvTree {
	GtkTreeView parent;
};

struct _TvTreeClass {
	GtkTreeViewClass parent_class;
};

GType tv_tree_get_type(void);
GtkWidget *tv_tree_new(void);
void tv_tree_append_item(TvTree *tree, char *entry);

#endif /* TREE_VIEW_H */
