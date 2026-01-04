# REALLY - v1.3

REALLY (Really? Even Another Lacking Language? Yuck.) is a programming language designed for a minimalistic case of use. The REALLY programming language has only 14 commands, with 2 registers, the **A** register, which is the main one used when programming in REALLY, and **B**. 

The following data below are all the commands in REALLY:

| Character  | Instruction |
| ------------- | ------------- |
| ^ | Increments the A register by 1 |
| v | Decrements the A register by 1 |
| 0 | Resets the A register |
| & | Flips register value |
| ~ | Swap the A/B register values |
| @ | Combine the value of both registers |
| # | Subtract the stored state of the A register with the B register  |
| ( | Jump forward to next command after the end of loop if A register data IS 0 |
| ) | Jump back to start of loop command if A register data in NOT 0 |
| : | Stall program for 1 cycle |
| ; | Skip next instruction if executed |
| ' | Recieve input; Changes the A register with the increment values placed after this character, stops input once a non-incremental character (^, v, 0) is used |
| " | Output the data of the A register into ASCII |
| % | Output the data of the A register into decimal value |

## Getting Started.

REALLY is a minimalistic language with little to no commands, but a large variety of stuff you can create. This section will show you how to create printing system.

### Registers

REALLY uses only 2, registers, the A and B registers. The A register is the main register of the 2, and is used by default for incrementing, decrementing, zeroing, looping, inputting, and outputting. The B register is a data register used to hold backup data needed but is still used for commands like combining and subtracting. Although the A register might seem like the only useful one needed of the two, the B register allows for less boilercode, arithmetic equations, temporary storage, cleaner debugging, and a bunch of other stuff.

The code bases below will show how to do basic register input, and register swapping:
```
^^^
```

The `^` command increments the A register by 1, the code above incremented the A register by 3, making A = 3. The same can be said for `v`, which decrements by 1.
```
vv
```

Now with that, A is equal to 1. That is basic register input, but what if we have the A register to let's say 100 and want to bring it back down to 0? We can use the `0` command, which sets the A register to 0.
```
^^^^^^^^^^
0
```

Even though the A register was equal to 10, because we used `0`, A is brought back down to 0. This allows for going quickly back down to low values without extensive boilercode. Another neat command we have, like a combo of increment and zeroing, is the input command `'`. The input command allows you to set the A register to the increment values set after it. The input command automatically stops once a non-incremental command is set, all the incremental commands the input checks for is `^`, `v`, and `0`.
```
^^^^^^^^^^
'^^^
```

That code allowed us to set A from 10 to 3, without any boilercode like zeroing the register, or doing multiple decrements. The last command that you'll learn before getting into the actual printing is register swaps. The `~` command swaps the data of the A and B registers. If you have register A, with 5, and register B, with 9, and swap, A = 9, and B = 5. This allows us to actually use the B registers, alongside have 2 sets of data.
```
^^^^
~^^
```

The code above set the A register to 4, before swapping the values (0/4), than incrementing the A register back to 2. This basic command allows for you to reduce boilercode by hundreds of commands, and allows for anything past basic programs.

### Outputting

The REALLY programming language has 2 output types, the ASCII standard output `"`, and decimal output `%`. The ASCII standard output, called output for short, uses the ASCII table to output characters. For example, in ASCII, *H* is 72. The following code below will show how to print the exclamation point *!* (33).
```
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"
```

That short yet also long piece of code, increments the A register to 33, and outputs it, which in turn outputs **!**. We will now look at decimal outputs, which takes the literal value of the A register and outputs it, which is good for mathematical programs and printing raw numbers.
```
^^^%
```

That small piece of code increments the A register to 3 and prints its raw value, 3.

### Putting it all together

Using this all together, we will create a basic print, showing a letter N and colon **N:**, signifying number, and a number from the swapped B register. It's a good think to note that any character not used by the REALLY program is allowed to be put in due to the lexer skipping over them, making good for notes, and will be used to explain.

```
^^^~ | Set B register to 3 via a swap

^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" | Outputs the letter N
0^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" | Inputs 58 & outputs the colon

0^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" | 32 = SPACE

~% | Swap B and A, A = 3, and output.
```

Thanks for looking into REALLY, hopefully you learnt the basics of programming in it, and want to try it out some time. All code written in tests, README, and source code is written by one guy without AI, and even streamed somedays. Feel free to star the repository if you want to support me and get my name out there!
