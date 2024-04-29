#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_var t_var;

// Descripción: Esta estructura representa un nodo en 
// el árbol de análisis sintáctico.
// Campos:
// 	operator: Un puntero a una cadena que representa 
// 		el operador asociado al nodo. Por ejemplo, >, <, ;, etc.
// 	prev_operator: Un puntero a una cadena que 
// 		representa el operador previo al nodo.
// 	command: Un puntero a una cadena que representa 
// 		el comando asociado al nodo.
// 	checked: Un entero que indica si el nodo ha sido 
// 		verificado durante el análisis sintáctico.
// 	left: Un puntero al hijo izquierdo del nodo.
// 	right: Un puntero al hijo derecho del nodo.
typedef struct s_info_tree {
	char *operator;
	char *prev_operator;
	char *command;
	int checked;
	struct s_info_tree *left;
	struct s_info_tree *right;
} t_info_tree;

// Descripción: Esta estructura representa una variable
// de entorno en la shell.
// Campos:
// 	name: Un puntero a una cadena que representa el 
// 		nombre de la variable de entorno.
// 	value: Un puntero a una cadena que representa 
// 		el valor de la variable de entorno.
// 	end_type: Un entero que indica el tipo de finalización.
// 	prev: Un puntero al elemento previo en la lista enlazada.
// 	next: Un puntero al siguiente elemento en la lista enlazada.
typedef struct s_env {
	char *name;
	char *value;
	struct s_env *prev;
	struct s_env *next;
} t_env;

// Descripción: Esta estructura representa una acción (
// comando interno) que puede ejecutar la shell.
// Campos:
// 	action: Un puntero a una cadena que representa 
// 		el nombre de la acción.
// 	function: Un puntero a una función que ejecuta 
// 		la acción.
typedef struct s_actions {
	char *action;
	void (*function)(t_var *var, char **params);
} t_actions;

// Descripción: Esta estructura representa una acción 
// (por ejemplo, redirección, secuenciador) que puede ejecutar la shell.
// Campos:
// 	action: Un puntero a una cadena que representa 
// 		el nombre de la acción.
// 	function: Un puntero a una función que ejecuta 
// 		la acción.
typedef struct s_actions_op {
	char *action;
	void (*function)(t_var *var, t_info_tree *tree);
} t_actions_op;

// Descripción: Esta estructura representa el estado 
// general de la shell.
// Campos:
//     tree: Un puntero a la raíz del árbol de análisis 
//		sintáctico que se construye a partir de los comandos ingresados por el usuario.
//     env: Un puntero a una lista enlazada que contiene 
//		las variables de entorno de la shell.
//     act: Un puntero a una lista de acciones 
//		(comandos internos) que puede ejecutar la shell.
//     op: Un puntero a una lista de operadores 
//		(redirecciones, secuenciadores) que pueden estar presentes en los comandos.
typedef struct s_var {
	struct s_info_tree *tree;
	struct s_env *env;
	struct s_actions *act;
	struct s_actions_op *op;
} t_var;

typedef struct s_pipe {
	int **pipes;
	int save;
	int num_pipes;
} t_pipe;

#endif