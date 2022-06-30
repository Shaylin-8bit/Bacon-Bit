; This program uses nested loops to multiply two numbers

move 0 push 5       ; first number pushed to location 0

whil cur            ; while first number more than 0
  move 1 push 5     ; second number pushed to location 1
  whil cur          ; while second number more than 0
    move 2 incr 1   ; increment location 2
    move 1 decr 1   ; decrement second number
  endl              ; return to start of second loop
  move 0 decr 1     ; decrement first number
endl                ; return to start of first loop
                   
move 2 disn cur     ; output result
