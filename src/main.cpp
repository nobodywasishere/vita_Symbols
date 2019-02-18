#define VITASDK

#include <vita2d.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <psp2/ctrl.h>
#include <psp2/audioout.h>
#include <psp2/kernel/processmgr.h>


int main(int argc, char *argv[]) {

	SceCtrlData pad; //the control pad.
	vita2d_pgf *pgf; // the font, pgf, pvf, and font can be used.
	vita2d_pvf *symbols;

	vita2d_init(); //init vita2d, must be done before other vita2d stuff.
	vita2d_set_clear_color(RGBA8(0x40, 0x40, 0x40, 0xFF)); // sets the color used when calling vita2d_clear_screen()

  // the default font to be used. can also load from file using other formats.
	pgf = vita2d_load_default_pgf();
	symbols = vita2d_load_custom_pvf("app0:/fonts/psexchar.pvf");

	//set up the pad?
	memset(&pad, 0, sizeof(pad));

	while (1) {
		sceCtrlPeekBufferPositive(0, &pad, 1);

		//if start, exit loop.
		if (pad.buttons & SCE_CTRL_START)
			break;

		//start drawing and clear screen every frame.
		vita2d_start_drawing();
		vita2d_clear_screen();

		vita2d_pgf_draw_text(
			pgf,10,530,
			RGBA8(255,255,255,255),1.0f,
			"This is a test of PS Vita fonts"
		);

		int initpos = 30;
		float scale = 4.0f;

		vita2d_pvf_draw_text(
			symbols,10,initpos,
			RGBA8(255,255,255,255),scale,
			"ABCDEFG"
		);

		vita2d_pvf_draw_text(
			symbols,10,initpos+30,
			RGBA8(255,255,255,255),scale,
			"0123456789"
		);

		vita2d_pvf_draw_text(
			symbols,10,initpos+60,
			RGBA8(255,255,255,255),scale,
			"!\"#$%'()*+,-./"
		);

		vita2d_pvf_draw_text(
			symbols,10,initpos+90,
			RGBA8(255,255,255,255),scale,
			":;<=>@ "
		);

		//again, both of these at the end of every frame.
		vita2d_end_drawing();
		vita2d_swap_buffers();
	}

	//finish vita2d stuff.
	vita2d_fini();
	vita2d_free_pgf(pgf);
	vita2d_free_pvf(symbols);

	sceKernelExitProcess(0);
	return 0;
}
