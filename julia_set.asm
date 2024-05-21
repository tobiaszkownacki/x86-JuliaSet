;-----------------------------------------------------
; Arguments:
; rdi - data
; rsi - pitch
; rdx - height_and_width
; xmm0 - c_real
; xmm1 - c_imag
; xmm2 - scale
; xmm3 - disp_x_left
; xmm4 - disp_y_top
;-----------------------------------------------------
; Used registers:
; rdi - data_pointer
; rsi - pitch
; rdx - height_and_width
; rcx - recursive sequence iterator
; r8 - columnt counter
; r9 - row counter
; r10 - register to index pixel in row arrey

; xmm0 - c_real
; xmm1 - c_imag
; xmm2 - scale
; xmm3 - saved_x_left
; xmm4 - current y and on the begining saved_y_left
; xmm5 - current x
; xmm6 - real value of variable in recursive sequence
; xmm7 - imaginary value of variable in recursive sequence
; xmm8 - used in recursive_sequence
; xmm9 - used in recursive_sequence
; xmm10 - there is 4.0
; ----------------------------------------------------

section .text
global julia_set

julia_set:

    push rbp
    mov rbp, rsp        ; now not needed, but for consistency

    ;push xmm6
    ;push xmm7
    ;push xmm8
    ;push xmm9
    ;push xmm10

    mov r8, rdx         ; r8 = height
    mov r10, 4          ; convert 4 to double
    cvtsi2sd xmm10, r10

column_loop:
    mov r9, rdx         ; r9 = width
    movsd xmm5, xmm3    ; x = x_left movsd - Move scalar Double Precision Floating-Point Values
    xor r10, r10        ; zero index pixel in row arrey

row_loop:
    xor rcx, rcx       ; zero iteration register
    movsd xmm6, xmm5   ; assign valuues of x and y to other register
    movsd xmm7, xmm4   ; used in next loop

recursive_sequence:
    ; newIm = 2 * oldRe * oldIm + cIm;
    ; newRe = oldRe * oldRe - oldIm * oldIm + cRe;
    ; if((newRe * newRe + newIm * newIm) > 4) break;

    movsd xmm8, xmm7   ; assign oldIm

    ; calculate newIm
    mulsd xmm8, xmm6    ; oldIm * oldRe
    addsd xmm8, xmm8    ; 2 * oldIm * oldRe
    addsd xmm8, xmm1    ; 2 * oldRe * oldIm + cIm;

    ; calculate newRe
    mulsd xmm6, xmm6    ; oldRe * oldRe
    mulsd xmm7, xmm7    ; oldIm * oldIm
    subsd xmm6, xmm7    ; oldRe * oldRe - oldIm * oldIm
    addsd xmm6, xmm0

    ; wolne 8 - wartość newIM, 9

    movsd xmm7, xmm8   ; move newIm to oldIm

    ; calculate modul
    movsd xmm9, xmm6   ; move newRe to xmm9

    mulsd xmm9, xmm9    ; newRe * newRe
    mulsd xmm8, xmm8    ; newIm * newIm
    addsd xmm8, xmm9    ; (newRe * newRe + newIm * newIm)

    inc ecx             ; incease number of interations
    cmp ecx, 255
    ja after_sequence   ; if iterations > 255 go after_sequence

    comisd xmm8, xmm10
    jbe recursive_sequence  ; if modul <= 4 go to recursive_sequence

after_sequence:
    mov byte [rdi + r10], 0        ; draw pixels
    mov byte [rdi + r10 + 1], 0
    mov byte [rdi + r10 + 2], 0

    add r10, 3         ; incease index to draw in good place

    addsd xmm5, xmm2   ; go to the pixel
    dec r9
    jnz row_loop       ; if row is not finished, go to row_loop


end_row_loop:
    add rdi, rsi        ; add pitch to pointer on data to pointer to the next row
    subsd xmm4, xmm2    ; sub scale to go to the next pixel

    dec r8              ; decrease height counter
    jnz column_loop     ; if height == 0, then exit

epilog:

    ;pop xmm10
    ;pop xmm9
    ;pop xmm8
    ;pop xmm7
    ;pop xmm6

    mov rsp, rbp    ; now not needed, but for consistency
    pop rbp
    ret