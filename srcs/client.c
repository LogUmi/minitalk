/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgerard <lgerard@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:20:19 by lgerard           #+#    #+#             */
/*   Updated: 2025/08/31 20:40:23 by lgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

int	main(int argc, char **argv)
{
	struct sigaction	sa;
	unsigned int 		check;

	if (argc != 3)
		deb_error();
	else if (test_pid(&argv[1][0]) == 0 && argv[2][0] == 0)
		ft_printf("Error abort\n chaine vide ou PID pas un nombre\n");
	else
	{
		sa.sa_flags = SA_SIGINFO | SA_RESTART;
		sa.sa_sigaction = handlerc;
		sigemptyset(&sa.sa_mask);
		sigaction(SIGUSR1, &sa, NULL);
		sigaction(SIGUSR2, &sa, NULL);
		check = checksum(&argv[2][0]);
		error_msg(initiate(ft_atoi(&argv[1][0]), &argv[2][0], 0, check));
		sa.sa_handler = SIG_DFL;
		sigemptyset(&sa.sa_mask);
		sa.sa_flags = 0;
		sigaction(SIGUSR1, &sa, NULL);
		sigaction(SIGUSR2, &sa, NULL);
	}
	return (0);
}
/*
ARG="0123456789t0123456789v0123456789t0123456789q0123456789c0123456789s0123456789s0123456789q0123456789q0123456789cent"
ARG="En se réveillant un matin après des rêves agités, Gregor Samsa se retrouva, dans son lit, métamorphosé en un monstrueux insecte. Il était sur le dos, un dos aussi dur qu’une carapace, et, en relevant un peu la tête, il vit, bombé, brun, cloisonné par des arceaux plus rigides, son abdomen sur le haut duquel la couverture, prête à glisser tout à fait, ne tenait plus qu’à peine. Ses nombreuses pattes, lamentablement grêles par comparaison avec la corpulence qu’il avait par ailleurs, grouillaient désespérément sous ses yeux.« Qu’est-ce qui m’est arrivé ? » pensa-t-il. Ce n’était pas un rêve. Sa chambre, une vraie chambre humaine, juste un peu trop petite, était là tranquille entre les quatre murs qu’il connaissait bien. Au-dessus de la table où était déballée une collection d’échantillons de tissus - Samsa était représentant de commerce - on voyait accrochée l’image qu’il avait récemment découpée dans un magazine et mise dans un joli cadre doré. Elle représentait une dame munie d’une toque et d’un boa tous les deux en fourrure et qui, assise bien droite, tendait vers le spectateur un lourd manchon de fourrure où tout son avant-bras avait disparu. Le regard de Gregor se tourna ensuite vers la fenêtre, et le temps maussade - on entendait les gouttes de pluie frapper le rebord en zinc - le rendit tout mélancolique. « Et si je redormais un peu et oubliais toutes ces sottises ? » se dit-il ; mais c’était absolument irréalisable, car il avait l’habitude de dormir sur le côté droit et, dans l’état où il était à présent, il était incapable de se mettre dans cette position. En se réveillant un matin après des rêves agités, Gregor Samsa se retrouva, dans son lit, métamorphosé en un monstrueux insecte. Il était sur le dos, un dos aussi dur qu’une carapace, et, en relevant un peu la tête, il vit, bombé, brun, cloisonné par des arceaux plus rigides, son abdomen sur le haut duquel la couverture, prête à glisser tout à fait, ne tenait plus qu’à peine. Ses nombreuses pattes, lamentablement grêles par comparaison avec la corpulence qu’il avait par ailleurs, grouillaient désespérément sous ses yeux.« Qu’est-ce qui m’est arrivé ? » pensa-t-il. Ce n’était pas un rêve. Sa chambre, une vraie chambre humaine, juste un peu trop petite, était là tranquille entre les quatre murs qu’il connaissait bien. Au-dessus de la table où était déballée une collection d’échantillons de tissus - Samsa était représentant de commerce - on voyait accrochée l’image qu’il avait récemment découpée dans un magazine et mise dans un joli cadre doré. Elle représentait une dame munie d’une toque et d’un boa tous les deux en fourrure et qui, assise bien droite, tendait vers le spectateur un lourd manchon de fourrure où tout son avant-bras avait disparu. Le regard de Gregor se tourna ensuite vers la fenêtre, et le temps maussade - on entendait les gouttes de pluie frapper le rebord en zinc - le rendit tout mélancolique. « Et si je redormais un peu et oubliais toutes ces sottises ? » se dit-il ; mais c’était absolument irréalisable, car il avait l’habitude de dormir sur le côté droit et, dans l’état où il était à présent, il était incapable de se mettre dans cette position. En se réveillant un matin après des rêves agités, Gregor Samsa se retrouva, dans son lit, métamorphosé en un monstrueux insecte. Il était sur le dos, un dos aussi dur qu’une carapace, et, en relevant un peu la tête, il vit, bombé, brun, cloisonné par des arceaux plus rigides, son abdomen sur le haut duquel la couverture, prête à glisser tout à fait, ne tenait plus qu’à peine. Ses nombreuses pattes, lamentablement grêles par comparaison avec la corpulence qu’il avait par ailleurs, grouillaient désespérément sous ses yeux.« Qu’est-ce qui m’est arrivé ? » pensa-t-il. Ce n’était pas un rêve. Sa chambre, une vraie chambre humaine, juste un peu trop petite, était là tranquille entre les quatre murs qu’il connaissait bien. Au-dessus de la table où était déballée une collection d’échantillons de tissus - Samsa était représentant de commerce - on voyait accrochée l’image qu’il avait récemment découpée dans un magazine et mise dans un joli cadre doré. Elle représentait une dame munie d’une toque et d’un boa tous les deux en fourrure et qui, assise bien droite, tendait vers le spectateur un lourd manchon de fourrure où tout son avant-bras avait disparu. Le regard de Gregor se tourna ensuite vers la fenêtre, et le temps maussade - on entendait les gouttes de pluie frapper le rebord en zinc - le rendit tout mélancolique. « Et si je redormais un peu et oubliais toutes ces sottises ? » se dit-il ; mais c’était absolument irréalisable, car il avait l’habitude de dormir sur le côté droit et, dans l’état où il était à présent, il était incapable de se mettre dans cette position.En se réveillant un matin après des rêves agités, Gregor Samsa se retrouva, dans son lit, métamorphosé en un monstrueux insecte. Il était sur le dos, un dos aussi dur qu’une carapace, et, en relevant un peu la tête, il vit, bombé, brun, cloisonné par des arceaux plus rigides, son abdomen sur le haut duquel la couverture, prête à glisser tout à fait, ne tenait plus qu’à peine. Ses nombreuses pattes, lamentablement grêles par comparaison avec la corpulence qu’il avait par ailleurs, grouillaient désespérément sous ses yeux.« Qu’est-ce qui m’est arrivé ? » pensa-t-il. Ce n’était pas un rêve. Sa chambre, une vraie chambre humaine, juste un peu trop petite, était là tranquille entre les quatre murs qu’il connaissait bien. Au-dessus de la table où était déballée une collection d’échantillons de tissus - Samsa était représentant de commerce - on voyait accrochée l’image qu’il avait récemment découpée dans un magazine et mise dans un joli cadre doré. Elle représentait une dame munie d’une toque et d’un boa tous les deux en fourrure et qui, assise bien droite, tendait vers le spectateur un lourd manchon de fourrureFIN"
*/