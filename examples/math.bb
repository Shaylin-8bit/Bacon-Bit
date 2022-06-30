; These operators can be used to perform basic mathmatics on the current byte
;
; incr: addition        mult: multiplication
; decr: subtraction     divi: division
;
; modu: divide by number and take remainder

push 10  incr 2   ; adds 2 to 10
disn cur disc 10  ; outputs 12

push 10  decr 2   ; subtracts 2 from 10
disn cur disc 10  ; outputs 8

push 10  mult 2   ; multiplys 10 by 2
disn cur disc 10  ; outputs 20

push 10  divi 2   ; divides 10 by 2
disn cur disc 10  ; outputs 5

push 10  modu 3   ; divided 10 by 3 and saves remainder
disn cur disc 10  ; outputs 1
