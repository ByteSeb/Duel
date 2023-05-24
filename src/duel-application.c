/* duel-application.c
 *
 * Copyright 2023 Seb
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "config.h"

#include "duel-application.h"
#include "duel-window.h"

struct _DuelApplication
{
	AdwApplication parent_instance;
};

G_DEFINE_TYPE (DuelApplication, duel_application, ADW_TYPE_APPLICATION)

DuelApplication *
duel_application_new (const char        *application_id,
                      GApplicationFlags  flags)
{
	g_return_val_if_fail (application_id != NULL, NULL);

	return g_object_new (DUEL_TYPE_APPLICATION,
	                     "application-id", application_id,
	                     "flags", flags,
	                     NULL);
}

static void
duel_application_activate (GApplication *app)
{
	GtkWindow *window;

	g_assert (DUEL_IS_APPLICATION (app));

	window = gtk_application_get_active_window (GTK_APPLICATION (app));

	if (window == NULL)
		window = g_object_new (DUEL_TYPE_WINDOW,
		                       "application", app,
		                       NULL);

	gtk_window_present (window);
}

static void
duel_application_class_init (DuelApplicationClass *klass)
{
	GApplicationClass *app_class = G_APPLICATION_CLASS (klass);

	app_class->activate = duel_application_activate;
}

static void
duel_application_about_action (GSimpleAction *action,
                               GVariant      *parameter,
                               gpointer       user_data)
{
	static const char *developers[] = {"ByteSeb", NULL};
	DuelApplication *self = user_data;
	GtkWindow *window = NULL;

	g_assert (DUEL_IS_APPLICATION (self));

	window = gtk_application_get_active_window (GTK_APPLICATION (self));

	adw_show_about_window (window,
	                       "application-name", "Duel",
	                       "application-icon", "com.byteseb.Duel",
	                       "developer-name", "\"ByteSeb\" Sebastián García",
	                       "version", "0.1.0",
	                       "developers", developers,
	                       "copyright", "© 2023 ByteSeb. Distributed under the GLPv3 license.",
	                       NULL);
}

static void
duel_application_quit_action (GSimpleAction *action,
                              GVariant      *parameter,
                              gpointer       user_data)
{
	DuelApplication *self = user_data;

	g_assert (DUEL_IS_APPLICATION (self));

	g_application_quit (G_APPLICATION (self));
}

static const GActionEntry app_actions[] = {
	{ "quit", duel_application_quit_action },
	{ "about", duel_application_about_action },
};

static void
duel_application_init (DuelApplication *self)
{
	g_action_map_add_action_entries (G_ACTION_MAP (self),
	                                 app_actions,
	                                 G_N_ELEMENTS (app_actions),
	                                 self);
	gtk_application_set_accels_for_action (GTK_APPLICATION (self),
	                                       "app.quit",
	                                       (const char *[]) { "<primary>q", NULL });
        gtk_application_set_accels_for_action (GTK_APPLICATION (self),
                                                "win.rock",
                                               (const char *[]) {"<primary>r", NULL });
        gtk_application_set_accels_for_action (GTK_APPLICATION (self),
                                                "win.paper",
                                               (const char *[]) {"<primary>p", NULL });
        gtk_application_set_accels_for_action (GTK_APPLICATION (self),
                                                "win.scissors",
                                               (const char *[]) {"<primary>s", NULL });
        gtk_application_set_accels_for_action (GTK_APPLICATION (self),
                                                "win.replay",
                                               (const char *[]) {"<primary>l", NULL });
}
