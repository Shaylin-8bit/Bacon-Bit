; use disn to output numerical values

disn 100

; use disc to output characters

disc 10  ; \n
disc 72  ; H
disc 101 ; e
disc 108 ; l
disc 108 ; l
disc 111 ; 0
disc 10  ; \n

; both disc and disn can output Global values as well

disn cur  ; value at current byte as integer
disc 10   ; \n
disc cur  ; value at current byte as character
disc 10   ; \n

disn ind  ; current byte location as integer
disc 10   ; \n
disc ind  ; current byte location as character
disc 10   ; \n

disn inp  ; next byte in stdin as integer
disc 10   ; \n
disc inp  ; next byte in stdin as character
disc 10   ; \n
