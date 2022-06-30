; all memory is initialized as 0
disn cur ; outputs 0
disc 10  ; \n

; we can write to the current location using push, incr, and decr.

push 5   ; write 5 to current location
disn cur ; outputs 5
disc 10  ; \n

incr 1   ; increments current location to 6
disn cur ; outputs 6
disc 10  ; \n

decr 1   ; decrements current location back to 5
disn cur ; outputs 5
disc 10  ; \n

; we can move to any memory location with move

move 107 ; set location to byte 107
push ind ; write the current locations index to the current location

disn cur ; outputs 107
disc 10  ; \n

; we can also move forward or backwords a set number of bytes with forw and back

forw 4   ; move forward 4 bytes
disn ind ; outputs 111
disc 10  ; \n

back 12  ; move back 12 bytes
disn ind ; outputs 99
disc 10  ; \n
