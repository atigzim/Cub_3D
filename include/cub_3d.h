#ifndef CUB_3D
# define CUB_3D

# include <mlx.h>
# include <math.h>
# include <ctype.h>
# include <fcntl.h>
# include <limits.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include "../libft/libft.h"


# define ESC 65307
# define W 119
# define A 97
# define S 115
# define D 100
# define CLOSE 17
# define TILE_SIZE 32
#define WIN_WIDTH 1900
#define WIN_HEIGHT 800
#define FOV 1.0471975512
typedef struct s_image
{
	void		*img_ptr;
	char		*pixel_data;
	int			bpp;
	int			endian;
	int			line_size;
	int			width;
	int			height;
}				t_image;

typedef struct s_player
{
	double		x;
	double		y;
	double		dx;
	double		dy;
	double		radius;
	double		angle;
	double		rotation_speed;
	double		move_speed;
	char		direction;
}				t_player;

typedef struct s_ray
{
     double             ray_angle;
     double             ray_dx;  
     double             ray_dy;
}t_ray;

typedef struct s_data
{
    char    *tex_no;
    char    *tex_so;
    char    *tex_we;
    char    *tex_ea;
    int     floor_color;
    int     ceiling_color;

    char    **map;       // array of map lines
    int     map_width;
    int     map_height;

    double  player_x;
    double  player_y;
    char    player_dir;
    void    *mlx;
    void    *window;
    t_image		*buffer;
    t_player        	*player;
    t_ray               *ray;
}   t_data;


        //UTILS
int has_cub_extension(const char *filename);
void parse_element(char *line, t_data *data);
int parse_rgb(char *str);
void check_map_walls(t_data *data);
void check_map_chars(t_data *data);
        //PARSE
void add_map_line(t_data *data, char *line);
void check_map_walls(t_data *data);
void check_map_chars(t_data *data);
void parse_cub(const char *filename, t_data *data);

        // raycasting
void	ft_raycastung(t_data *data);

#endif