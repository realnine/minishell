#include "../minishell.h"

// 이곳은 함수들은 자식 프로세스가 실행하는 곳이 아니다
// 이곳은 함수들은 오직 부모 프로세스만이 실행하는 곳이다 
// 자식 프로세스가 있다면 execve로 호출한 파일로 로직이 교체되어 실행되고 있을 것이고
// 자식은 기존의 SIGINT와 SIGQUIT의 디폴트 핸들러에 의해 그냥 종료될 것이다
// SIGINT와 SIGQUIT은 원래 프로세스 종료 시그널이다

void	reset_prompt(void)
{
	ft_putstr_fd("\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	sig_int(int signo) // cntrl + c
{
	pid_t	pid;
	//int		status;

	pid = waitpid(-1, &signo, WNOHANG);  
		// waitpid 인자 -1은 임의의 자식 프로세스를 기다린다는 의미
		// WNOHANG 옵션은 자식이 종료되지 않아도 부모 프로세스는 대기하지 않고 일단 지나감을 의미
		// waipid는 자식이 없을 때 -1을 리턴한다

	if (pid == -1) // 자식 프로세스가 없을 때,
	{
		g_ret_number = 1;
		reset_prompt();
	}
	else // 자식 프로세스가 있을 때,
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
	else if(mode == 2)
	{
		signal(SIGINT, sig_int);
		signal(SIGQUIT, sig_quit);
	}
}

