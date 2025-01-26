# FT_PRINTF
#### Video Demo:  https://youtu.be/Z9U-rA9D2uo
#### Description:

This is my final project for CS50, where I attempted to recreate the printf C function from the stdio.h library from scratch.

My function is called ft_printf, and it is also a project I made from my CS School a few weeks ago.

I wanted to push it further, so here is a few technical considerations :

## 🛠️ FUNCTION PROTOTYPES AND CONSIDERATIONS

Name of the function : ft_printf.

Prototype :     <code>int		ft_printf(const char *format, ...) </code>

Placeholders supported :  `` %, c, s, p, d, i, u, x, X``

Flags supported :  ``#+(space)``

Options supported :  `` -0. width``

These flags and options are 100% optional, but they can also be in combination following this pattern:


<code>%[flags][width][.precision]placeholder</code>

Also, I coded everything with only 3 libraries which are ``unistd.h``,``stdlib.h`` and ``stdarg.h``.

Here is a quick reminder of the supported placeholders, flags and options I found online (credits to @mcombeau on Github)

<table>
    <thead>
        <tr>
            <th colspan=3><h4>Flags</h4></th>
        </tr>
        <tr>
            <th>Flag</th>
            <th>Description</th>
        </tr>
    </thead>
    <tbody>
	</thead>
        <tr>
            <td align="center">-</td>
            <td>Left justify the result within the field. By default it is right justified.</td>
        </tr>
        <tr>
            <td align="center">+</td>
            <td>Forces to precede the result with a plus or minus sign (+ or -) even for positive numbers. By default, only negative numbers are preceded with a sign.</td>
        </tr>
        <tr>
            <td align="center">(space)</td>
            <td>If there is no sign, a space is attached to the beginning of the result.</td>
        </tr>
        <tr>
            <td align="center">#</td>
            <td>Used with x or X specifiers the value is preceded with 0x or 0X respectively for values different than zero.</td>
        </tr>
        <tr>
            <td align="center">0</td>
            <td>Leading zeros are used to pad the numbers instead of space.</td>
        </tr>
    </tbody>
	<thead>
        <tr>
            <th colspan=3><h4>Width</h4></th>
        </tr>
        <tr>
            <th>Value</th>
            <th>Description</th>
        </tr>
    </thead>
    <tbody>
	</thead>
        <tr>
            <td align="center">(number)</td>
            <td>Minimum number of characters to be printed. If the value to be printed is shorter than this number, the result is padded with blank spaces. The value is not truncated even if the result is larger.</td>
        </tr>
    </tbody>
	<thead>
        <tr>
            <th colspan=3><h4>Precision</h4></th>
        </tr>
        <tr>
            <th>Value</th>
            <th>Description</th>
        </tr>
    </thead>
    <tbody>
	</thead>
        <tr>
            <td align="center">.(number)</td>
            <td>For integer specifiers (d, i, u, x, X) − precision specifies the minimum number of digits to be written. If the value to be written is shorter than this number, the result is padded with leading zeros. The value is not truncated even if the result is longer. A precision of 0 means that no character is written for the value 0. For s − this is the maximum number of characters to be printed. By default all characters are printed until the ending null character is encountered. For c type − it has no effect. When no precision is specified, the default is 1. If the period is specified without an explicit value for precision, 0 is assumed.</td>
        </tr>
        <tr>
            <td align="center">.(*)</td>
            <td>The precision is not specified in the format string, but as an additional integer value argument preceding the argument that has to be formatted.</td>
        </tr>
    </tbody>
    <thead>
        <tr>
            <th colspan=3><h4>Specifiers</h4></th>
        </tr>
        <tr>
            <th>Format Specifier</th>
            <th>Description</th>
        </tr>
    </thead>
    <tbody>
	</thead>
        <tr>
            <td align="center">%</td>
            <td>% followed by another % character writes % to the screen.</td>
        </tr>
        <tr>
            <td align="center">c</td>
            <td>writes a single character.</td>
        </tr>
        <tr>
            <td align="center">s</td>
            <td>writes a character string.</td>
        </tr>
        <tr>
            <td align="center">p</td>
            <td>writes an implementation-defined character sequence defining a pointer address.</td>
        </tr>
        <tr>
            <td align="center">d or i</td>
            <td>writes a signed integer to decimal representation.</td>
        </tr>
        <tr>
            <td align="center">u</td>
            <td>writes an unsigned integer to decimal representation.</td>
        </tr>
        <tr>
            <td align="center">x or X</td>
            <td>writes an unsigned integer to hexadecimal representation.</td>
        </tr>
    </tbody>
</table>


## 🗃️ GLOBAL STRUCTURE

I started with the ``ft_printf.c`` file, which is the main file where all the logic stars.


Step 1 :
- I initialize va_list (which is a macro from ``stdarg.h``) which allows me to track infinitely every arguments plugged into the ft_printf function.
- I also initlaize a strcuture, which is the key of the function. This structure will contains every aspect of the flags, options and placeholder thanks to the turbo_parsing function, and will help me choose which behaviours to apply to which placeholders.

Step 2 :
- The program will run across the string provided as argument, and either :
1 / print it straight into the standart output (thanks to the ``write`` function from ``unistd.h``, which I encapsulated in a ``ft_putchar`` function).
2 / Stop at the first ``%`` sign, and then process to do the following.

Step 3 :
- The string pointer is passed to the ``turbo_parsing`` function in the ``parsing.c``, which first initialize the structure at zero, and run accross the string following the pattern <code>%[flags][width][.precision]placeholder</code>.
- One the current placeholder parsed with all the flags, it's time to use the parsed structure to print the corresponding plugged argument.

Step 4 :
- ``placeholder_behaviour`` function acts like customs, and redirect with a simple ``if/else`` statement what the placeholder previously parsed. ``va_arg`` allows us to bring the plugged variables and their types, as each placeholder is from a different type.

Step 5 :
- Depending on each placeholder, I decived to check the corresponding possibilities of flags within the function itself, to print or not the corresonding behaviour.


## 🧑‍💻 TECHNICAL CHOICES

- I chose not to implement a buffer management just like the real printf function, as the project would surpass my skills.
- I assumed that if there were several same flags in the string (such as two ``##``), it would be as if there was only one. So I had to implement a way to still count the flags for the return value without messing up the parsed strcuture.
- I haven't managed the return of error cases in scenarios where flags would be incompatible with certain placeholders (such as the ``#`` flag with the ``%c`` for instance). I just decided to ignore them, despite knowing that the real printf function spits error message and refuses to cooperate and to compile.


## ⚙️ USAGE

For simplicity, I made a Makefile that compiles this whole function into a static library.

Step 1 :

Run ``make`` to create a new file, a static library called ``libftprintf.a``

Then run ``make simple_test`` in your terminal to display at screen a simple function call.

(The source code can be found in simple_test.c)

I also created my own custom tester, which consists in calling both ``printf`` and my own ``ft_print``, and passing to them the exacts same arguments and displaying them on the screen.

To do so, run ``make full_test`` in your terminal to display the full tester.

(The source code can be found in full_tester.c)

My ``full_tester.c`` file consists in displaying in a colorful maneer the return values of both ``printf`` and ``ft_printf``, while actually printing the expected results.

NOTE : This tester was also an opportunity to write further code, and also the only way I found to test my function behaviour.

Lastly, I made a last command ``make how_to_use``, which displays a little guide on how to use the function in your own programs !


## 👨‍⚖️ SELF-CRITICISM

Despite working as expected, I know for a fact that my code base have 3 major flaws, or improvement ways :

- My codebase is long, very long, and redundant.
- I kind of follow a way of thinking made up of ``if``, ``else``, and ``while`` conditional statements, instead of building more complex but versatile functions.
- My parsing was a bit chaotic (in the ``parsing.c`` file) while working on it because across my codebase, I only plug copies of my original structure instead of a pointer towards it. It does works, but it can be prone to errors.
