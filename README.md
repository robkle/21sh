# 21sh
Taking [minishell](https://github.com/robkle/minishell) to the next level.<br />
**21sh** is a Unix shell with:<br />
* line edition features<br />
* ctrl+D and ctrl+C handling<br />
* redirection '<', '>', '<<', and '>>'<br />
* pipe '|'
* file descriptor aggregation
* command line seperation with ';'<br />
* command history navigation with up and down arrows<br />
* complete managament of quotes and double quotes<br />

### Usage
Repository contains a Makefile for:<br /> 
* compiling executable (**make all**)<br />
* removing object files (**make clean**)<br />
* deleting executable (**make fclean**)<br />
* recompiling (**make re**)<br />

Example of 21sh:<br />
<img src="screenshot.png" alt="example" width="500"/><br />
#### Notes:
This project was done together with [VictoriaElisabet](https://github.com/VictoriaElisabet) and is part of my studies at Hive Helsinki.<br />
My part of the code handles the line edition, command history, and signal handling. <br />
This project was thoroughly tested by 5 fellow Hive students.
