# Convert SIGNAME to int or int to SIGNAME

## Usage
### String to int
Use string name of a signal and get its value:

`strsignal SIGKILL` or `strsignal KILL`

Output: `9`
### Int to string
Use value of a signal to get its name (according to your system):

`strsignal 9`

Output: `SIGKILL`
