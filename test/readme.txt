I will test your bc program interactively as well as using I/O redirection.
The test file that contains commands (expressions) that should work is

bc2_run

If you enter the commands in this file one at a time, you might get 
something like the what is in the file bc2_expectedInteractive.

If you capture the output with I/O redirection you will not see the 
commands entered, only the output.  The dumps may not display the 
variables in the same order as given.

bc < bc2_run > bc2_expectedRedirect

The file, bc2_run_results puts the answer to each expression on the same
line for verification of the correct answer.  This is not what I would expect or
want your output to appear.  Just use this one as a reference to verify
the values.
