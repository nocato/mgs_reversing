	opt	c+, at+, e+, n-
	section .text

	xdef change_800C5190
change_800C5190:
	dw 0x28A20008 ; 800C5190
	dw 0x10400003 ; 800C5194
	dw 0x240300FF ; 800C5198
	dw 0x08031478 ; 800C519C
	dw 0x24050080 ; 800C51A0
	dw 0x24A5FFF8 ; 800C51A4
	dw 0x28A20009 ; 800C51A8
	dw 0x14400002 ; 800C51AC
	dw 0x240600FF ; 800C51B0
	dw 0x24050008 ; 800C51B4
	dw 0x00C41023 ; 800C51B8
	dw 0x00450018 ; 800C51BC
	dw 0x00051900 ; 800C51C0
	dw 0x24020080 ; 800C51C4
	dw 0x00002012 ; 800C51C8
	dw 0x04810002 ; 800C51CC
	dw 0x00432823 ; 800C51D0
	dw 0x24840007 ; 800C51D4
	dw 0x000410C3 ; 800C51D8
	dw 0x00C21823 ; 800C51DC
	dw 0x00031200 ; 800C51E0
	dw 0x00A21025 ; 800C51E4
	dw 0x00031C00 ; 800C51E8
	dw 0x03E00008 ; 800C51EC
	dw 0x00431025 ; 800C51F0
