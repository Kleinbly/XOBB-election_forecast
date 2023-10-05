#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>


// Variables
GtkBuilder *builder;
char* glade_file_path = "/home/umurundi/XOBB/front-end/glade/frontend.glade";

// All windows
GtkWindow *window_homepage;
GtkWindow *window_credentials;
GtkWindow *window_dashboard;

// Homepage window
GtkButton *btn_login_homepage;
GtkButton *btn_sign_up_homepage;
GtkButton *btn_quit_homepage;

// Credentials window
GtkLabel *lbl_signup_confirmation;
GtkLabel *lbl_identifier_credentials;
GtkEntry *txt_identifier_credentials;
GtkLabel *lbl_password_credentials;
GtkEntry *txt_password_credentials;
GtkLabel *msg_error_invalid_attempt;
GtkButton *btn_sign_in_credentials;
GtkLabel *lbl_instruction;
GtkLinkButton *link_sign_up_window;


int main(int argc, char *argv[])
{
	
	// Initialisation de GTK
	gtk_init(&argc, &argv);
	builder = gtk_builder_new();

	// Chargement des fenêtres
	gtk_builder_add_from_file(builder, glade_file_path, NULL);
	
	window_homepage = GTK_WINDOW(gtk_builder_get_object(builder, "window_homepage"));
	window_credentials = GTK_WINDOW(gtk_builder_get_object(builder, "window_credentials"));
	window_dashboard = GTK_WINDOW(gtk_builder_get_object(builder, "window_dashboard"));
	
	// Définition de la taille des fenêtres
	gtk_window_set_default_size(window_homepage, 500, 300);
	gtk_window_set_default_size(window_credentials, 700, 500);
	gtk_window_set_default_size(window_dashboard, 700, 500);
	
	
	// Récupération des widgets: Homepage
	btn_login_homepage = GTK_BUTTON(gtk_builder_get_object(builder, "btn_login_homepage"));
	btn_sign_up_homepage = GTK_BUTTON(gtk_builder_get_object(builder, "btn_sign_up_homepage"));
	btn_quit_homepage = GTK_BUTTON(gtk_builder_get_object(builder, "btn_quit_homepage"));
	
	// Récupération de widgets: Credentials
	lbl_signup_confirmation = GTK_LABEL(gtk_builder_get_object(builder, "lbl_signup_confirmation"));
	lbl_identifier_credentials = GTK_LABEL(gtk_builder_get_object(builder, "lbl_identifier_credentials"));
	txt_identifier_credentials = GTK_ENTRY(gtk_builder_get_object(builder, "txt_identifier_credentials"));
	lbl_password_credentials = GTK_LABEL(gtk_builder_get_object(builder, "lbl_password_credentials"));
	txt_password_credentials = GTK_ENTRY(gtk_builder_get_object(builder, "txt_password_credentials"));
	msg_error_invalid_attempt = GTK_LABEL(gtk_builder_get_object(builder, "msg_error_invalid_attempt"));
	btn_sign_in_credentials = GTK_BUTTON(gtk_builder_get_object(builder, "btn_sign_in_credentials"));
	lbl_instruction = GTK_LABEL(gtk_builder_get_object(builder, "lbl_instruction"));
	link_sign_up_window = GTK_LINK_BUTTON(gtk_builder_get_object(builder, "link_sign_up_window"));



	// suite.........
	gtk_builder_connect_signals(builder, NULL);
	
	// Affichage de la fenêtre principale
	gtk_window_present(window_homepage);
	
	// Lancement de la boucle principale de GTK
	gtk_main();

	// Libérer la mémoire utilisée par le builder
	g_object_unref(builder);
	
	return 0;

}
