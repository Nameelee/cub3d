#include <mlx.h>
#include <stdlib.h> // Requis pour la fonction exit()
#include <stdio.h>  // Requis pour la fonction perror()

// Le keycode pour la touche ESC sur macOS (65307 sur Linux)
#define KEY_ESC 53

// Structure pour regrouper les variables relatives à la MLX
typedef struct s_game
{
	void	*mlx_ptr;
	void	*win_ptr;
}	t_game;

// Fonction pour fermer la fenêtre et quitter le programme proprement
int	close_game(t_game *game)
{
	mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	printf("Fenêtre fermée. Fin du programme.\n");
	exit(0);
	return (0);
}

// Fonction pour gérer les entrées clavier
int	key_press_handler(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
	{
		close_game(game);
	}
	return (0);
}

int	main(void)
{
	t_game	game;

	// 1. Initialisation de la MiniLibX
	game.mlx_ptr = mlx_init();
	if (game.mlx_ptr == NULL)
	{
		perror("Échec de l'initialisation de la MiniLibX");
		return (1);
	}

	// 2. Création d'une nouvelle fenêtre
	game.win_ptr = mlx_new_window(game.mlx_ptr, 800, 600, "cub3D");
	if (game.win_ptr == NULL)
	{
		perror("Échec de la création de la fenêtre");
		return (1);
	}

	// 3. Enregistrement des gestionnaires d'événements
	// Appelle la fonction 'key_press_handler' lorsqu'une touche est pressée
	mlx_key_hook(game.win_ptr, key_press_handler, &game);

	// Appelle la fonction 'close_game' lorsque le bouton 'X' de la fenêtre est cliqué
	// L'événement 17 correspond au bouton de fermeture sur macOS ( "DestroyNotify" sur Linux)
	mlx_hook(game.win_ptr, 17, 0, close_game, &game);

	// 4. Démarrage de la boucle d'événements
	printf("Fenêtre créée. Appuyez sur ESC pour quitter.\n");
	mlx_loop(game.mlx_ptr);
	
	return (0);
}