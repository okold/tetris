; BUFFER.S
;
;	Olga Koldachenko	okold525@mtroyal.ca
;   COMP 2659           Term Project
;   Winter 2020         Tyson Kendon
;
; UWORD* load_buffer()
;
; Loads a 256-byte aligned address for a secondary screen buffer.
; 32256 bytes are allocated, and the address of the buffer is aligned
; before being returned.

	xdef	_load_buffer

RESULT		equ	8

_load_buffer:	link	a6,#0
		movem.l	d2-4/a3,-(sp)

		lea	buffer,a3	;gets address ready for math
		move.l	a3,d0

		clr.l	d3		;aligns address by subtracting
		move.w	#256,d3		;the last byte from 256 and
		clr.l	d4		;adding the difference to it
		move.b	d0,d4		
		beq	done
		sub.w	d4,d3		
		add.l	d3,d0
					
done:		movem.l	(sp)+,d2-4/a3
		unlk	a6
		rts
		
buffer:		ds.b	32256
