# REALLY

REALLY (Really? Even Another Lacking Language? Yuck.) is a programming language designed for a minimalistic case of use. The REALLY programming language has only 13 commands, with 2 registers, the **A** register, which is the main one used when programming in REALLY, and **B**. 

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
| ' | Recieve input; Changes the A register with the increment values placed after this character, stops input once a non-incremental charecter (^, v, 0) is used |
| " | Output the data of the A register into ASCII |
