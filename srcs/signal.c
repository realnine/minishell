#include "../minishell.h"

void	reset_prompt(void)
{
	ft_putstr_fd("\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	sig_int(int signo)
{
	pid_t	pid;

	pid = waitpid(-1, &signo, WNOHANG);
	if (pid == -1)
	{
		g_ret_number = 1;
		reset_prompt();
	}
	else
	{
		g_ret_number = 130;
		ft_putchar_fd('\n', 1);
	}
}

void	sig_quit(int sig)
{	
	(void)sig;
	g_ret_number = 131;
	ft_putstr_fd("Quit: 3\n", 1);
}

void	set_signal(int mode)
{
	if (mode == 1)
	{
		signal(SIGINT, sig_int);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == 2)
	{
		signal(SIGINT, sig_int);
		signal(SIGQUIT, sig_quit);
	}
}
