# Description of the coding standards and good practices of libdbook2.

# Introduction #

Here at libdbook2, we think it is important that we adopt a coding style and set down some good practices; that is one unified style which we should all adopt. This will help us make clean and readable code.


# Details #

Here are the rules proposed by Edd (vext01).

## Bracing ##

Use K&R style bracing.

Eg:

```
int main(void) {
    /* code */
}
```

and **NOT** the Java way:

```
int main(void)
{
    /* code */
}
```


## Function Arguments ##

Do function arguments like this:

```
my_func(int arg1, int arg2) {
...
```

and **NOT** the BSD way:

```
my_func(arg1, arg2)
    int arg1, arg2 {
...
```

## Function Variable and Macro Naming ##

Use the C convention of naming your variables and functions, **NOT** camel case:

Eg:

```
int number_of_slots; /* GOOD! */
int numberOfSlots;   /* Bad boy! Go lick Sun's bum-bum */
```

Make sure all global symbols, functions and macros within the core library are prefixed 'dbook_', so as to not clash with other libraries with identical symbol names._

All preprocessor macros should be entirely upper case:

```
#define DBOOK_MY_MACRO "hello"
```

## Line Length ##

Try not to allow lines of code to exceed 78 chars if possible. Our code should look nice on a standard 80x25 terminal (like the standard xterm size). If a line needs to be long, start a new line and continue the remainder of the line with a "second level" indent (one more tab tham the previous line).

Eg.

```
        fprintf(stderr, "DBOOK_ERROR %d\t:\t%s\n", dbook_errno,
                dbook_err_descrs[dbook_errno]);

        /* Next line would be back to the normal indent level */
```

## Tabs ##

We use 4 spaces for indentation in libdbook2 code. Please ensure your editor does not make these spaces look like anything else.

If you are using Vim, this can be used to set tabbing up correctly for dbook hacking:

```
set expandtab
set tabstop=4
set shiftwidth=4
```

## To Space or not to Space ##

### Before Parenthesis ###

For parenthesis spacing, the rule is:
  * No space before functions.
  * One space before statements.

```
if (x == 1);         /* OK  */
if(x == 1);          /* Bad */
printf("hello\n");   /* OK  */
printf ("hello\n");  /* Bad */
```

Make sure you know the difference between functions and statements.

### In Function Arguments ###

Function arguments lists should have one space after commas only.

```
my_func(a, b, c);     /* GOOD  */
my_func(a,b,c);       /* YUCK! */
my_func( a , b , c ); /* SILLY */
```

### Between Operators ###

Operators should have one space either side:

```
if (a == 1)    /* OK         */
if (a==1)      /* NO WAY     */
if ( a == 1 )  /* TOO SPACEY */
```

## Comments ##

Comments should be C89 compatible, do not use double slash C++ comments. Remember some of the more obsure architectures on some systems do not even support GCC3, and so need to be GCC2 compatible.

## Standard Header ##

All C files in the core library of libdbook2 should have a header like this:

```
/*
 * DBOOK2
 * $Id: dbook-tool.c 73 2009-06-26 19:21:09Z vext01 $
 * -----------------------
 * Write here what the file does.
 */
```

Make sure the 'Id' property is set to expand when adding new files in svn:

```
svn propset svn:keywords 'Id' <filename>
```

## Error Reporting ##

The core library should not print anything to the console when errors occur. Instead the macro DBOOK\_SET\_ERROR() should used to set error information. This means the library implementer (eg. dbook-tool) can interpret the error information accordingly. Remember, the implementer may not want to put the error on the console; It may be a GUI app or may need to send the error over a network socket.

This DBOOK\_SET\_ERROR() macro sets the following globals:
  * dbook\_errno : An error code as defined in libdbook.h.
  * dbook\_err\_file : The file the error occurred in.
  * dbook\_err\_line : The line number the error occurred on.

A convenience function void dbook\_perror(), can be used to print info
about the error to stderr. This should not be used in the library, but
instead is provided to implementers who use console output. Remember
printing errors to the console would be useless for GUI apps. Errors
should be indicated by the return value of the library functions, then
info about the error can be extracted by the implementer.

Eg:
```
DBOOK_SET_ERROR(DBOOK_ERR_INVALID_ISBN);
dbook_perror();
```

Would print:
```
DBOOK_ERROR 2 (/home/edd/dbook2/libdbook/dbook-tool/dbook-tool.c:145):
              Invalid ISBN 
```

## Debugging ##

To print to stderr for debugging use `void dbook_debug(char *msg)`. This function will only print **if** the global 'dbook\_debug\_flag' is set. It is up to the library implementer to set this. When releasing code, make sure debgging is **off**.

## File Naming ##

Try to separate words with underscores in file names being importing into SVN. File names without underscores are hard to read.

## Committing Code ##

No code should be committed without another developer checking it and giving it an "OK". To initiate this process, send a diff to the mailing list for review. If a developer gives an "OK" (and you have an account on SVN), you may commit it.

If you break the SVN tree with smelly code, then you will be branded a big nancy and we will all point and laugh at you.

## Bad Code ##

If you should see any bad code in the tree, report a issue.