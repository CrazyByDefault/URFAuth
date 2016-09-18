#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <security/pam_appl.h>
#include <security/pam_modules.h>

#include <unistd.h>
#include <stdio.h>

#include <sys/wait.h>

/* expected hook */
PAM_EXTERN int pam_sm_setcred( pam_handle_t *pamh, int flags, int argc, const char **argv ) {
	return PAM_SUCCESS;
}

PAM_EXTERN int pam_sm_acct_mgmt(pam_handle_t *pamh, int flags, int argc, const char **argv) {
	printf("Acct mgmt\n");
	return PAM_SUCCESS;
}

/* expected hook, this is where custom stuff happens */
PAM_EXTERN int pam_sm_authenticate( pam_handle_t *pamh, int flags,int argc, const char **argv ) {
	int retval;
  pid_t pid;

	const char* pUsername;
	retval = pam_get_user(pamh, &pUsername, "Username: ");

	printf("Welcome %s\n", pUsername);

	if (retval != PAM_SUCCESS) {
	  printf("LUL EPIC FAIL%s\n", pUsername);
		return retval;
	}

  pid = fork();
  if (pid > 0) {
    int status;

    waitpid(pid, &status, 0);
    printf("%d\n", status);
    if (status == 0)
      return PAM_SUCCESS;
    
    return PAM_AUTH_ERR;
    printf("%d\n", status);
    return PAM_SUCCESS;
  }

  execv("/Users/goutham/code/exp/pam/simple/true", NULL);
  return 0;
}
