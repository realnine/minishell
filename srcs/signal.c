#include "../minishell.h"

void	handler_reset_prompt(int signum)
{
	(void)signum;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	handler_exit_process(int signum)
{
	int	pid;

	(void)signum;
	pid = wait(NULL);
	printf("--------child exit(%d)-------\n", pid);
}

void	set_signal(int	mode)
{
	if (mode == 1)
	{
		signal(SIGINT, handler_reset_prompt);
		signal(SIGQUIT, SIG_IGN);
		//signal(SIGCHLD, handler_exit_process);
	}
	else if (mode == 2)
	{
		signal(SIGINT, handler_exit_process);
		signal(SIGQUIT, SIG_IGN);
	}
}