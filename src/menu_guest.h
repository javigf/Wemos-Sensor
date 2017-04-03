// File to display guest menu

int guest_menu (String, String);

int guest_menu (String name, String chat_id){

	String welcome = "Bienvenido, " + name + ".\n";
        welcome += "Este usuario no tiene permisos para efectuar ninguna actividad en este dispositivo.\n\n";
  /*      welcome += "Si requiere soporte por favor contactese con " + contact_info.telegram + " \n";
		welcome += "Vía email: " + contact_info.email + "\n";
		welcome += "Si estás interesado en el producto, llamanos: " + MOBILE + "\n";
		welcome += "Y Preguntá por la promoción: " + DEVICE_NAME + "\n";
		welcome += "Muchas gracias, esperamos tener noticias tuyas pronto...\n";
*/
        //bot.sendMessage(chat_id, welcome, "Markdown");

	return 0;
}
