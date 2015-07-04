/*
 * Copyright (c) 2015 Sergi Granell (xerpi)
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <psp2/ctrl.h>
#include <psp2/touch.h>
#include <psp2/moduleinfo.h>
#include <psp2/kernel/processmgr.h>

#include <vita2d.h>

PSP2_MODULE_INFO(0, 0, "vita2dsample");

int main()
{
	vita2d_init();

	vita2d_texture *tex = vita2d_create_empty_texture(128, 128);
	unsigned int *tex_data = vita2d_texture_get_datap(tex);

	SceCtrlData pad;
	memset(&pad, 0, sizeof(pad));

	while (1) {

		sceCtrlPeekBufferPositive(0, &pad, 1);
		if (pad.buttons & PSP2_CTRL_START) break;

		vita2d_start_drawing();
		vita2d_clear_screen();

		vita2d_draw_rectangle(20, 20, 400, 250, RGBA8(255, 0, 0, 255));
		vita2d_draw_rectangle(700, 300, 100, 150, RGBA8(0, 0, 255, 255));

		int i, j;
		for (i = 0; i < 128; i++) {
			for (j = 0; j < 128; j++) {
				tex_data[j + i*128] = rand();
			}
		}

		vita2d_draw_texture_scale(tex, 64, 64, 2.0f, 0.5f);


		vita2d_end_drawing();
		vita2d_swap_buffers();

	}

	vita2d_fini();
	vita2d_free_texture(tex);

	sceKernelExitProcess(0);
	return 0;
}
