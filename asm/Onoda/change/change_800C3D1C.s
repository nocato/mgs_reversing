	opt	c+, at+, e+, n-
	section .text

	xdef change_800C3D1C
change_800C3D1C:
	dw 0x8FBF003C ; 800C3D1C
	dw 0x8FB20038 ; 800C3D20
	dw 0x8FB10034 ; 800C3D24
	dw 0x8FB00030 ; 800C3D28
	dw 0x03E00008 ; 800C3D2C
	dw 0x27BD0040 ; 800C3D30
