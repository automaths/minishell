#include "execution.h"

// <<a : 
// 		heredoc link avec le fichier temporaire
// <a : 
// 		si mauvais chmod ou existe pas erreur traite aucune commande 
// 		si a la suite le dernier est ouvert
// >a : 
// 		cree un fichier chmod 644 si existe pas 
// 		si mauvais chmod erreur traite aucune commande
// 		si elle se suive seulement derniere
// >>a : 
// 		comme >a mais en mode append
