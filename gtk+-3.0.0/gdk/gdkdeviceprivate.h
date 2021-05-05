/* GDK - The GIMP Drawing Kit
 * Copyright (C) 2009 Carlos Garnacho <carlosg@gnome.org>
 *
 * This library is free software; you can redistribute it and/or
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
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#ifndef __GDK_DEVICE_PRIVATE_H__
#define __GDK_DEVICE_PRIVATE_H__

#include "gdkdevice.h"
#include "gdkdevicemanager.h"
#include "gdkevents.h"

G_BEGIN_DECLS

#define GDK_DEVICE_CLASS(c)     (G_TYPE_CHECK_CLASS_CAST ((c), GDK_TYPE_DEVICE, GdkDeviceClass))
#define GDK_IS_DEVICE_CLASS(c)  (G_TYPE_CHECK_CLASS_TYPE ((c), GDK_TYPE_DEVICE))
#define GDK_DEVICE_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS ((o), GDK_TYPE_DEVICE, GdkDeviceClass))

typedef struct _GdkDeviceClass GdkDeviceClass;
typedef struct _GdkDeviceKey GdkDeviceKey;

struct _GdkDeviceKey
{
  guint keyval;
  GdkModifierType modifiers;
};

struct _GdkDevice
{
  GObject parent_instance;

  gchar *name;
  GdkInputSource source;
  GdkInputMode mode;
  gboolean has_cursor;
  gint num_keys;
  GdkDeviceKey *keys;
  GdkDeviceManager *manager;
  GdkDisplay *display;
  /* Paired master for master,
   * associated master for slaves
   */
  GdkDevice *associated;
  GList *slaves;
  GdkDeviceType type;
  GArray *axes;
};

struct _GdkDeviceClass
{
  GObjectClass parent_class;

  gboolean (* get_history)   (GdkDevice      *device,
                              GdkWindow      *window,
                              guint32         start,
                              guint32         stop,
                              GdkTimeCoord ***events,
                              gint           *n_events);

  void (* get_state)         (GdkDevice       *device,
                              GdkWindow       *window,
                              gdouble         *axes,
                              GdkModifierType *mask);

  void (* set_window_cursor) (GdkDevice *device,
                              GdkWindow *window,
                              GdkCursor *cursor);

  void (* warp)              (GdkDevice  *device,
                              GdkScreen  *screen,
                              gint        x,
                              gint        y);
  gboolean (* query_state)   (GdkDevice       *device,
                              GdkWindow       *window,
                              GdkWindow      **root_window,
                              GdkWindow      **child_window,
                              gint             *root_x,
                              gint             *root_y,
                              gint             *win_x,
                              gint             *win_y,
                              GdkModifierType  *mask);
  GdkGrabStatus (* grab)     (GdkDevice        *device,
                              GdkWindow        *window,
                              gboolean          owner_events,
                              GdkEventMask      event_mask,
                              GdkWindow        *confine_to,
                              GdkCursor        *cursor,
                              guint32           time_);
  void          (*ungrab)    (GdkDevice        *device,
                              guint32           time_);

  GdkWindow * (* window_at_position) (GdkDevice       *device,
                                      gint            *win_x,
                                      gint            *win_y,
                                      GdkModifierType *mask,
                                      gboolean         get_toplevel);
  void (* select_window_events)      (GdkDevice       *device,
                                      GdkWindow       *window,
                                      GdkEventMask     event_mask);
};

void  _gdk_device_set_associated_device (GdkDevice *device,
                                         GdkDevice *relative);

void  _gdk_device_reset_axes (GdkDevice   *device);
guint _gdk_device_add_axis   (GdkDevice   *device,
                              GdkAtom      label_atom,
                              GdkAxisUse   use,
                              gdouble      min_value,
                              gdouble      max_value,
                              gdouble      resolution);

void _gdk_device_set_keys    (GdkDevice   *device,
                              guint        num_keys);

GdkAxisUse _gdk_device_get_axis_use (GdkDevice *device,
                                     guint      index);

gboolean   _gdk_device_translate_window_coord (GdkDevice *device,
                                               GdkWindow *window,
                                               guint      index,
                                               gdouble    value,
                                               gdouble   *axis_value);

gboolean   _gdk_device_translate_screen_coord (GdkDevice *device,
                                               GdkWindow *window,
                                               gint       window_root_x,
                                               gint       window_root_y,
                                               guint      index,
                                               gdouble    value,
                                               gdouble   *axis_value);

gboolean   _gdk_device_translate_axis         (GdkDevice *device,
                                               guint      index,
                                               gdouble    value,
                                               gdouble   *axis_value);

GdkTimeCoord ** _gdk_device_allocate_history  (GdkDevice *device,
                                               gint       n_events);

void _gdk_device_add_slave (GdkDevice *device,
                            GdkDevice *slave);
void _gdk_device_remove_slave (GdkDevice *device,
                               GdkDevice *slave);
gboolean   _gdk_device_query_state            (GdkDevice        *device,
                                               GdkWindow        *window,
                                               GdkWindow       **root_window,
                                               GdkWindow       **child_window,
                                               gint             *root_x,
                                               gint             *root_y,
                                               gint             *win_x,
                                               gint             *win_y,
                                               GdkModifierType  *mask);
GdkWindow * _gdk_device_window_at_position    (GdkDevice        *device,
                                               gint             *win_x,
                                               gint             *win_y,
                                               GdkModifierType  *mask,
                                               gboolean          get_toplevel);

G_END_DECLS

#endif /* __GDK_DEVICE_PRIVATE_H__ */
