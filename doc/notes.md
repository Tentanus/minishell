	| Signal      | Status                    | Action                 | Exit code   |
	| ----------- | ------------------------- | ---------------------- | ----------- |
[✅] | ctrl-C      | interactive mode          | new prompt             | 1           |
[✅] | ctrl-C      | waiting for user input    | print ^C, new prompt   | 130         |
[✅] | ctrl-C      | in heredoc                | new prompt             | 1           |
[✅] | ctrl-C      | in cat | cat | ls         | print ^C, new prompt   | 0           | to do: print ^C
  	| ----------- | ------------------------- | ---------------------- | ----------- |
[✅] | ctrl-D      | interactive mode          | print exit, exit shell | 0           | to do: print "exit" on same line as prompt
[✅] | ctrl-D      | waiting for user input    | new prompt             | 0           |
[✅] | ctrl-D      | in heredoc                | new prompt             | 0           |
[✅] | ctrl-D      | in cat | cat | ls         | new prompt             | 0           |
	| ----------- | ------------------------- | ---------------------- | ----------- |
[✅] | ctrl-\      | interactive mode          | do nothing             | unchanged   |
[✅] | ctrl-\      | waiting for user input    | print ^\Quit: 3        | 131         |
[✅] | ctrl-\      | in heredoc                | do nothing             | N/A         |
[✅] | ctrl-\      | in cat | cat | ls         | new prompt             | 0           |
	| ----------- | ------------------------- | ---------------------- | ----------- |






some minor mistakes: Overal beautifull shelly.

[x] leaks for wrong command while expansion. 
[x] ctrl-\ during a command should quit the command
[x] heredoc signals werken niet goed en moet aangepast worden
[x] SHLVL update (gaan we dit doen??)
[x] check env met multiple exports
[x] unset multiple variables
[x] cd ~
[x] cd ~/Documents/GitHub/mini-shell
[x] cd - (also print pwd at cd -)
[x] cd -- (go to home folder)
[x] /../../../bin/ls && /../../bin/ls
[x] error code 0 --> 1 bij cd error
[x] echo $? leaks 
[x] << k < test6 cat --> LEAKS (en blijft hangen)
[x] echo shctaje >> ja > nee LEAKS en deze moet door outputten naar de laastste 1
[x] 'cat | cat | ls' should work

[x] < unexisting_file | ls
[x] < unexisting_file  ls
[x] > unexisting_file (create empty file)
[x] ping localhost | cat -e
[x] ping localhost | sleep 2
[x] export
[x] signals working correct in multi layers of minishell

[x] expansion quotes
	echo "$USER"'$USER'
		expected output:	mdaan$USER
		our output:			mdaan'mdaan
	echo ""$USER"'$USER'"
		expected output:	mdaan'mdaan'
		our output:			mdaan'mdaan"

[x] export x="idil idil" y=5. (seg faults)
[x] echo $USER$USER
[x] fd leakage
[x] multiple pipes between commands
[ ] export =100
	bash: export: `=8000': not a valid identifier
