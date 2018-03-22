;lib.asm
;Michael Black, 2007

;lib.asm contains assembly functions that you can use in the shell


	.global _interrupt
	.global _enableInterrupts
	.global _clear
	.global _block
	.global _timeCXFromInterrupt
	.global _timeDXFromInterrupt

;int timeDXFromInterrupt()
_timeDXFromInterrupt:
	mov ax,#0x00;
	int #0x1a;
	
	mov ax,dx;
	ret;

;int timeCXFromInterrupt()
_timeCXFromInterrupt:
	mov ax,#0x00;
	int #0x1a;
	
	mov ax,cx;
	ret;

;void block(a,b,c,d)
_block:
	mov ax,#0x0004;设置图形显示模式4
	int #0x10;
	
	mov si,#20;右下角的X坐标送入SI寄存器
    sub si,#5;减去左上角的X坐标，计算X方向上的点数
    mov cx,#5;左上角X坐标送入CX寄存器
	
b_loop1:
	mov di,#20;右下角的Y坐标送入DI寄存器
    sub di,#5;减去左上角的Y坐标，计算Y方向上的点数
    mov dx,#5;左上角的Y坐标送入DX寄存器
    mov al,#2;选择洋红色
	
b_loop2:
	mov ah,#0x0c;利用10H中断的0CH功能画点
    int #0x10
			
    inc dx;Y坐标加1，
    dec di;已画完Y方向上所有的点了吗？
    jnz b_loop2;若没画完Y方向上全部点，转B_LOOP2继续
			
    inc cx;X坐标加1，准备画下一条竖线
    dec si;X方向上所有竖线都画完了吗？
    jnz b_loop1;若未画完X方向上全部竖线，转B_LOOP1继续
			
    mov ah,#0;等待键盘输入
    int #0x16
			
    mov ax,#0x0003;设置字符显示模式3
    int #0x10
	ret
	
;void clear
_clear:
;	mov al,#0x00;
;	mov ah,#0x06;
;	mov ch,#0x00;
;	mov cl,#0x00;
;	mov dh,#0xff;
;	mov dl,#0xff;
;	int #0x10;
;;;;;;;;;;;;;;;;;;;;;;;;;;;
	mov al,#0x00;
	mov ah,#0x06;
	mov ch,#0x00;
	mov cl,#0x00;
	mov dh,#0x23;
	mov dl,#80;
	
	mov bh,#0x04;
	int #0x10;
	
	mov ah,#0x02;
	mov bh,#0x00;
	mov dh,#0x00;
	mov dh,#0x00;
	
	int #0x10;

	ret

;int interrupt (int number, int AX, int BX, int CX, int DX)
_interrupt:
	push bp
	mov bp,sp
	mov ax,[bp+4]	;get the interrupt number in AL
	push ds		;use self-modifying code to call the right interrupt
	mov bx,cs
	mov ds,bx
	mov si,#intr
	mov [si+1],al	;change the 00 below to the contents of AL
	pop ds
	mov ax,[bp+6]	;get the other parameters AX, BX, CX, and DX
	mov bx,[bp+8]
	mov cx,[bp+10]
	mov dx,[bp+12]

intr:	int #0x00	;call the interrupt (00 will be changed above)

	mov ah,#0	;we only want AL returned
	pop bp
	ret

;void enableInterrupts()
;call at the beginning of programs.  allows timer preemption
_enableInterrupts:
	sti
	ret
