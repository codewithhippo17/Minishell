#ifndef REDIRECTION_H
#define REDIRECTION_H

# include "./types.h"

int save_fds(t_red *red);
void restore_fds(t_red *red);
int apply_redirection(t_red *current);
void redirect_io(t_red *current);
int redirection(t_red *red);

#endif // !REDIRECTION_H
