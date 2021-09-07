.text
		ldi r1, 0		//r1 used to update loop counter
		ldi r10, 10
		ldi r20,20		//load 20 to r20
		ldi r7, 1		//load 1 to r7
		ldi r2, 18		//set x to 18
		ldi r3, 0		//set y to 0
loop:	sub r8, r1, r10
		bz r8, end
		sub r9, r2,r20	//compare x to 20
		ldi r10, 50		//register for memory location
		bz  r9, q		//if x==20, jump to q:y = y + 1 and store
		sub r3, r3,r7	//else y = y - 1
		st  r3, r10		//store in m[10,000]
		br	always
q:		add r3, r3, r7
		st  r3, r10,30	//store in m[20,000]
always:	add r2, r2, r7	//x = x + 1
		add r1, r1, r7
		br loop
end:	quit

