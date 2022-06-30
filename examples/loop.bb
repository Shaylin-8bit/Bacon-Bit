; a loop state can be entered with whil
; as long as its byte is true it will conmtinue to run code between it and the next endl

push 5        ; push 5 to current location

whil cur      ; if the current location is true do the following, if not skip to endl
  disn cur    ; display the current value in number format
  disc 10     ; display a newline
  decr 1      ; decrement 1 from current location
endl          ; return to start of loop

disn cur      ; display current locations final value
