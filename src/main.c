/*
	Copyright (C) 2003  Sridhar <r_sridhar@users.sf.net>
	
	This file is part of GNUSim8085.

	GNUSim8085 is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.

	GNUSim8085 is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with GNUSim8085; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gnome.h>

#include "interface.h"
#include "gui-app.h"
#include "gui-list-message.h"
#include "asm-ds-symtable.h"
#include "gui-list-data.h"
#include "gui-list-stack.h"
#include "gui-keypad.h"
#include "bridge.h"
#include "callbacks.h"
#include "file-op.h"

int
main (int argc, char *argv[])
{
	GtkWidget *appbar;

#ifdef ENABLE_NLS
	bindtextdomain (GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR);
	bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
	textdomain (GETTEXT_PACKAGE);
#endif

	gnome_program_init (PACKAGE, VERSION, LIBGNOMEUI_MODULE,
			    argc, argv,
			    GNOME_PARAM_APP_DATADIR, PACKAGE_DATA_DIR, NULL);

	/* create app */
	gui_app_new ();

	asm_sym_init ();

	/* add extra */
	gui_list_message_attach_me ();
	gui_list_data_attach_me ();
	gui_list_stack_attach_me ();
	gui_keypad_attach_me ();
	b_init ();

	/* Start with NEW file */
	on_new1_activate (NULL, NULL);

	/* show start with dialog */
	gui_app_show ();

	appbar = lookup_widget (app->window_main, "main_appbar");
	g_assert (appbar);

	gnome_appbar_push (GNOME_APPBAR (appbar), _("Simulator: Idle"));

	/* open file specified in command line if any */
	if (argc > 1)
		ori_open (argv[1], TRUE);
	else
		gtk_widget_show (create_window_start ());

	gtk_main ();

	return 0;
}
