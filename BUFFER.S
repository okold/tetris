; UWORD* load_buffer()
;
; Loads a 256-byte aligned address for a secondary screen buffer.
; 32256 bytes are allocated, and the address of the buffer is aligned
; before being returned.

	xdef	_load_buffer

RESULT		equ	8

_load_buffer:	link	a6,#0
		movem.l	d0-2/a0,-(sp)

		lea	buffer,a0	;gets address ready for math
		move.l	a0,d0

		clr.l	d2		;aligns address by subtracting
		move.w	#256,d2		;the last byte from 256 and
		clr.l	d1		;adding the difference to it
		move.b	d0,d1		
		beq	done
		sub.w	d1,d2		
		add.l	d2,d0
					
done:		move.l	d0,RESULT(a6)
		movem.l	(sp)+,d0-2/a0
		unlk	a6
		rts
		
buffer:		ds.b	32256
