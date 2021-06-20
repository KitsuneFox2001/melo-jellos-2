/*
MM   MM  EEEEEEE  LL        OOOOO            JJJJJJJ  EEEEEEE  LL       LL        OOOOO    SSSSSS        22222
MMM MMM  EEE      LL       OO   OO                JJ  EEE      LL       LL       OO   OO  SS            22   22
MMMMMMM  EEEEEEE  LL       OO   OO  =======       JJ  EEEEEEE  LL       LL       OO   OO   SSSSS            22
MM M MM  EEE      LL       OO   OO           JJ   JJ  EEE      LL       LL       OO   OO       SS         22
MM   MM  EEEEEEE  LLLLLLL   OOOOO             JJJJJ   EEEEEEE  LLLLLLL  LLLLLLL   OOOOO   SSSSSS        2222222

by

========
|Adrian|
===========
|Makes    |
================
|Games         |   (C) 2019 for NESDev Compo 2018
================
*/

#include <stdio.h>
#include <stdlib.h>
#include "LIB/neslib.h"
#include "LIB/nesdoug.h"

#include "bgsplit_nam.h"	//packed nametable data
#include "title.h"	//packed nametable data
#include "options.h"	//packed nametable data
#include "ending.h"	//packed nametable data

#define u8 unsigned char
#define s8 signed char
#define u16 unsigned int
#define s16 signed int
#define PPUDATA ((*(volatile u8 *)0x2007))
#define PPUADDR ((*(volatile u8 *)0x2006))
#define PPUMASK		*((unsigned char*)0x2001)

const unsigned char palette[16]={ 0x0f,0x00,0x10,0x30,0x0f,0x01,0x21,0x30,0x0f,0x06,0x16,0x26,0x0f,0x09,0x19,0x29 };
const unsigned char firework[16]={ 0x0f,0x00,0x10,0x30,0x0f,0x0f,0x28,0x38,0x0f,0x04,0x15,0x25,0x0f,0x11,0x21,0x31 };
const unsigned char firework_flash1[16]={ 0x20,0x00,0x10,0x30,0x0f,0x2d,0x28,0x38,0x0f,0x04,0x15,0x25,0x0f,0x11,0x21,0x31 };
const unsigned char firework_flash2[16]={ 0x10,0x00,0x10,0x30,0x10,0x20,0x28,0x38,0x10,0x04,0x15,0x25,0x10,0x11,0x21,0x31 };
const unsigned char firework_flash3[16]={ 0x12,0x00,0x10,0x30,0x12,0x00,0x28,0x38,0x12,0x04,0x15,0x25,0x12,0x11,0x21,0x31 };
const unsigned char firework_flash4[16]={ 0x02,0x00,0x10,0x30,0x02,0x0f,0x28,0x38,0x02,0x04,0x15,0x25,0x02,0x11,0x21,0x31 };
const unsigned char palettes[6] = {0, 1, 2, 3, 2, 3};
const unsigned char numbers[10]={ 0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19 };
u16 addr;
u8 current;

unsigned char score100000, score10000, score1000, score100, score10;
unsigned char hi100000, hi10000;
unsigned char hi1000 = 3;
unsigned char hi100, hi10;
unsigned char level = 0;
unsigned char height = 0;
unsigned char timeminutes10, timeminutes1;
unsigned char timeseconds10, timeseconds1, frames;
unsigned char statusbar_changed = 1;
unsigned char map_updated = 1;
unsigned char next1, next2, next3, next4;
unsigned char block1, block2, block3, block4; 
unsigned char temp1, temp2, temp3, temp4; 
unsigned char blockX = 2;
unsigned char blockY;
unsigned char mapx, mapy, block_solid;
unsigned char updy;
unsigned char pad1;
unsigned char pad1_new;	
unsigned char loops;
unsigned char combo;
unsigned char droptimer = 100; 
unsigned char resetdrop = 100; 
signed char leftclear = 50;
signed char leftclear_modeB = 25;
unsigned char music = 0;
unsigned char mode = 0;
unsigned char state = 0;
unsigned char paused;
unsigned char titleframes = 0;
unsigned char easteregg = 0;
unsigned char menusel = 0;
unsigned char hiscore_beat = 0;
unsigned char firework_x = 0;
unsigned char firework_y = 0;
unsigned char firework_destx = 0;
unsigned char firework_desty = 0;
unsigned char firework_radius = 5;
unsigned char congratulations_frames = 0;
//repeat variables
unsigned char leftrepeat = 0;
unsigned char rightrepeat = 0;
unsigned char downrepeat = 0;
//variables for some dirty anti-flicker hacks later on
unsigned char loaded = 0;
unsigned char first_load = 0;
unsigned char lineupdated[10];
char score_str[6];
char hi_str[6];
char timeminutes_str[3];
char timeseconds_str[3];
char level_str[3];
char height_str[3];
char leftclear_str[3];
unsigned char game_array[8][10];
unsigned char attrib_array[6][14];
unsigned char update_buffer[5];
	
const unsigned char metasprites_0_data[]={

	  0,  0,0x42,0,
	  8,  0,0x43,0,
	  0,  8,0x52,0,
	  8,  8,0x53,0,
	128

};

const unsigned char metasprites_1_data[]={

	  0,  0,0x40,1,
	  8,  0,0x41,1,
	  0,  8,0x50,1,
	  8,  8,0x51,1,
	128

};

const unsigned char metasprites_2_data[]={

	  0,  0,0x40,2,
	  8,  0,0x41,2,
	  0,  8,0x50,2,
	  8,  8,0x51,2,
	128

};

const unsigned char metasprites_3_data[]={

	  0,  0,0x40,3,
	  8,  0,0x41,3,
	  0,  8,0x50,3,
	  8,  8,0x51,3,
	128

};

const unsigned char metasprites_4_data[]={

	  0,  0,0x42,2,
	  8,  0,0x43,2,
	  0,  8,0x52,2,
	  8,  8,0x53,2,
	128

};

const unsigned char metasprites_5_data[]={

	  0,  0,0x42,3,
	  8,  0,0x43,3,
	  0,  8,0x52,3,
	  8,  8,0x53,3,
	128

};

const unsigned char metasprites_6_data[]={

	  0,  0,0x8a,1,
	  8,  0,0x8b,1,
	  0,  8,0x9a,1,
	  8,  8,0x9b,1,
	128

};

const unsigned char metasprites_7_data[]={

	  0,  0,0x1e,2,
	128

};

const unsigned char metasprites_8_data[]={

	  0,  0,0xab,0,
	128

};

const unsigned char metasprites_9_data[]={

	  0,  0,0x1e,0,
	128

};

const unsigned char* const metasprites_list[]={

	metasprites_0_data,
	metasprites_1_data,
	metasprites_2_data,
	metasprites_3_data,
	metasprites_4_data,
	metasprites_5_data,
	metasprites_6_data,
	metasprites_7_data,
	metasprites_8_data,
	metasprites_9_data

};

const char ZERO_DIGIT = 0x30;

void put_str(unsigned int adr,const char *str)
{
	while(1)
	{
		if(!*str) break;

		one_vram_buffer((*str++)-0x20, adr);//-0x20 because ASCII code 0x20 is placed in tile 0 of the CHR
		adr++;
	}
}

//void setAttr(u8 x, u8 y, u8 topleft, u8 topright, u8 bottomleft, u8 bottomright) {

//find the metatile attr
//addr = 0x23c0 + (y * 8) + x;

//update_buffer[0] = (addr >> 8) | NT_UPD_HORZ; // MSB of address + control bit for direction
//update_buffer[1] = addr & 0xFF; // LSB of address
//update_buffer[2] = 1; // length of data to write (1 byte)
//update_buffer[3] = (bottomright << 6) | (bottomleft << 4) | (topright << 2) | (topleft << 0);
//update_buffer[4] = NT_UPD_EOF;

//set_vram_update(update_buffer); // give the update buffer to neslib to apply at next vblank
//ppu_wait_nmi(); // wait for the next frame so the changes will be applied
//set_vram_update(NULL); // disable the update so it doesn't keep re-using the buffer every frame.
  
//}

//hack no.1 to get rid of flickering
void setAttr(u8 x, u8 y, u8 pal) {

  //find the metatile attr
  addr = 0x23c0 + (y / 2 * 8) + x / 2;

  //read current value from it
  //PPUADDR = MSB(addr);
  //PPUADDR = LSB(addr);

  current = attrib_array[x/2][y/2]; //dummy read is necessary I think?

  //this is slow. I don't care.
  if (y & 1) {
    //bottom half
    if (x & 1) {
      //bottom right
      current &= 0x3f;
      current |= (pal << 6);
    } else {
      //bottom left
      current &= 0xcf;
      current |= (pal << 4);
    }
  } else {
    //top half
    if (x & 1) {
      //top right
      current &= 0xf3;
      current |= (pal << 2);
    } else {
      //top left
      current &= 0xfc;
      current |= (pal);
    }
  }

  update_buffer[0] = (addr >> 8) | NT_UPD_HORZ; // MSB of address + control bit for direction
  update_buffer[1] = addr & 0xFF; // LSB of address
  update_buffer[2] = 1; // length of data to write (1 byte)
  update_buffer[3] = current;
  update_buffer[4] = NT_UPD_EOF;
  
  attrib_array[x/2][y/2] = current;
  
  set_vram_update(update_buffer); // give the update buffer to neslib to apply at next vblank
}

void update_lines(char from, char to) {
	for (updy = from; updy < to; updy++) {
		lineupdated[updy] = 1;
	}
}

void generate_height(void) {
		for (mapx = 0; mapx<6; mapx++) {
		if (height >= 1) {
		game_array[mapx][9] = (rand() % 6) + 1;
		lineupdated[9] = 1;
		}
		if (height >= 2) {
		game_array[mapx][8] = (rand() % 6) + 1;
		lineupdated[8] = 1;
		}
		if (height >= 3) {
		game_array[mapx][7] = (rand() % 6) + 1;
		lineupdated[7] = 1;
		}
		if (height >= 4) {
		game_array[mapx][6] = (rand() % 6) + 1;
		lineupdated[6] = 1;
		}
		if (height >= 5) {
		game_array[mapx][5] = (rand() % 6) + 1;
		lineupdated[5] = 1;
		}
		}
				
		set_vram_buffer(); 	
		map_updated = 1;
}

void load_game(void) {
	//rendering is disabled at the startup, and palette is all black
	
	ppu_off();
	
	pal_bg(palette);//set background palette from an array
	pal_spr(palette);//set the same palette for sprites

	vram_adr(NAMETABLE_A);//unpack nametable into VRAM
	vram_unrle(bgsplit_nam);
	
	ppu_on_all(); // turn on screen
	music_play(music);
					 
	ppu_wait_nmi(); // wait
	
	// now fill the vram_buffer
	
	set_vram_buffer(); // points ppu update to vram_buffer, do this at least once
	
	clear_vram_buffer(); // resets the index to zero, to start filling the buffer
						 // do this at the beginning of every frame
	
}

void load_options(void) {
	//rendering is disabled at the startup, and palette is all black
	
	ppu_off();
	
	pal_bg(palette);//set background palette from an array
	pal_spr(palette);//set the same palette for sprites

	vram_adr(NAMETABLE_A);//unpack nametable into VRAM
	vram_unrle(options);
	
	ppu_on_all(); // turn on screen
	music_play(music);
					 
	ppu_wait_nmi(); // wait
	
	// now fill the vram_buffer
	
	set_vram_buffer(); // points ppu update to vram_buffer, do this at least once
	
	clear_vram_buffer(); // resets the index to zero, to start filling the buffer
						 // do this at the beginning of every frame
	
}

void load_ending(void) {
	//rendering is disabled at the startup, and palette is all black
	
	ppu_off();
	
	pal_bg(firework);//set background palette from an array
	pal_spr(firework);//set the same palette for sprites

	vram_adr(NAMETABLE_A);//unpack nametable into VRAM
	vram_unrle(ending);
	
	ppu_on_all(); // turn on screen
	music_play(7);
					 
	ppu_wait_nmi(); // wait
	
	// now fill the vram_buffer
	
	set_vram_buffer(); // points ppu update to vram_buffer, do this at least once
	
	clear_vram_buffer(); // resets the index to zero, to start filling the buffer
						 // do this at the beginning of every frame
	
}

void load_title(void) {
	//rendering is disabled at the startup, and palette is all black
	
	ppu_off();
	
	pal_bg(palette);//set background palette from an array
	pal_spr(palette);//set the same palette for sprites

	vram_adr(NAMETABLE_A);//unpack nametable into VRAM
	vram_unrle(title);
	
	ppu_on_all(); // turn on screen
	music_play(4);
					 
	ppu_wait_nmi(); // wait
	
	// now fill the vram_buffer
	
	set_vram_buffer(); // points ppu update to vram_buffer, do this at least once
	
	clear_vram_buffer(); // resets the index to zero, to start filling the buffer
						 // do this at the beginning of every frame
						 	
}

void fix_score(void) {
	if (score100000 > 9) {
		score100000 = 9;
	}
	if (score10000 >= 10) {
		score100000 = score100000 + 1;
		score10000 = score10000 - 10;
	}
	if (score1000 >= 10) {
		score10000 = score10000 + 1;
		score1000 = score1000 - 10;
	}
	if (score100 >= 10) {
		score1000 = score1000 + 1;
		score100 = score100 - 10;
	}
	if (score10 >= 10) {
		score100 = score100 + 1;
		score10 = score10 - 10;
	}
}

void highscore_check(void) {
	if (score100000 > hi100000) {
		hi100000 = score100000;
		hi10000 = score10000;
		hi1000 = score1000;
		hi100 = score100;
		hi10 = score10;
		hiscore_beat = 1;
	}
	if (score10000 > hi10000) {
		if (hi100000 == 0 || score100000 == hi100000) {
			hi10000 = score10000;
			hi1000 = score1000;
			hi100 = score100;
			hi10 = score10;
			hiscore_beat = 1;
		}
	}
	if (score1000 > hi1000) {
		if (hi10000 == 0 || score10000 == hi10000) {
			if (hi100000 == 0 || score100000 == hi100000) {
				hi1000 = score1000;
				hi100 = score100;
				hi10 = score10;
				hiscore_beat = 1;
			}
		}
	}
	if (score100 > hi100) {
		if (hi1000 == 0 || score1000 == hi1000) {
			if (hi10000 == 0 || score10000 == hi10000) {
				if (hi100000 == 0 || score100000 == hi100000) {
					hi100 = score100;
					hi10 = score10;
					hiscore_beat = 1;
				}
			}
		}
	}
	if (score10 > hi10) {
		if (hi100 == 0 || score100 == hi100) {
			if (hi1000 == 0 || score1000 == hi1000) {
				if (hi10000 == 0 || score10000 == hi10000) {
					if (hi100000 == 0 || score100000 == hi100000) {
						hi10 = score10;
						hiscore_beat = 1;
					}
				}
			}
		}
	}
}

void reset_game(void) {
	score100000 = 0;
	score10000 = 0;
	score1000 = 0;
	score100 = 0;
	score10 = 0;
	level = 0;
	height = 0;
	timeminutes10 = 0;
	timeminutes1 = 0;
	timeseconds10 = 0;
	timeseconds1 = 0; 
	frames = 0;
	statusbar_changed = 1;
	combo = 0;
	droptimer = 100; 
	resetdrop = 100; 
	leftclear = 50;
	leftclear_modeB = 25;
	hiscore_beat = 0;
	easteregg = 0;
	menusel = 0;
	for (mapy = 0; mapy<10; mapy++) {
		for (mapx = 0; mapx<6; mapx++) {
		game_array[mapx][mapy] = 0;
		}
	}
	block1 = rand() % 6;
	block2 = rand() % 6;
	block3 = rand() % 6;
	block4 = rand() % 6;
	
	blockX = 2;
	blockY = 0;
	
	next1 = rand() % 6;
	next2 = rand() % 6;
	next3 = rand() % 6;
	next4 = rand() % 6;
	
	firework_x = 0;
	firework_y = 0;
	firework_destx = 0;
	firework_desty = 0;
	firework_radius = 0;
	congratulations_frames = 0;

	map_updated = 1;
}

void check_match(void) {
				//horizontal
				for (mapy = 0; mapy<10; mapy++) {
				for (mapx = 0; mapx<8; mapx++) {
				if (game_array[mapx][mapy] != 0) {
				if (game_array[mapx][mapy] != 99) {
					
				if (game_array[mapx+1][mapy] == game_array[mapx][mapy]) {
				if (game_array[mapx+2][mapy] == game_array[mapx][mapy]) {
				if (game_array[mapx+3][mapy] == game_array[mapx][mapy]) {
				if (game_array[mapx+4][mapy] == game_array[mapx][mapy]) {
				if (game_array[mapx+5][mapy] == game_array[mapx][mapy]) {
				if (game_array[mapx+6][mapy] == game_array[mapx][mapy]) {
					game_array[mapx][mapy] = 0;
					game_array[mapx+1][mapy] = 0;
					game_array[mapx+2][mapy] = 0;
					game_array[mapx+3][mapy] = 0;
					game_array[mapx+4][mapy] = 0;
					game_array[mapx+5][mapy] = 0;
					game_array[mapx+6][mapy] = 0;
					update_lines(mapy, mapy+1);
					combo = combo + 1;
					score10 = score10 + 16 * combo;
					leftclear = leftclear - 7;
					if (combo < 6) {
					sfx_play(1+combo, 0);
					}
					if (combo >= 6) {
					sfx_play(6, 0);	
					}
				}
				else {
					game_array[mapx][mapy] = 0;
					game_array[mapx+1][mapy] = 0;
					game_array[mapx+2][mapy] = 0;
					game_array[mapx+3][mapy] = 0;
					game_array[mapx+4][mapy] = 0;
					game_array[mapx+5][mapy] = 0;
					update_lines(mapy, mapy+1);
					combo = combo + 1;
					leftclear = leftclear - 6;
					score10 = score10 + 8 * combo;
					if (combo < 6) {
					sfx_play(1+combo, 0);
					}
					if (combo >= 6) {
					sfx_play(6, 0);	
					}
				}		
				}
				else {
					game_array[mapx][mapy] = 0;
					game_array[mapx+1][mapy] = 0;
					game_array[mapx+2][mapy] = 0;
					game_array[mapx+3][mapy] = 0;
					game_array[mapx+4][mapy] = 0;
					update_lines(mapy, mapy+1);
					combo = combo + 1;
					leftclear = leftclear - 5;
					score10 = score10 + 4 * combo;
					if (combo < 6) {
					sfx_play(1+combo, 0);
					}
					if (combo >= 6) {
					sfx_play(6, 0);	
					}
				}	
				}
				else {
					game_array[mapx][mapy] = 0;
					game_array[mapx+1][mapy] = 0;
					game_array[mapx+2][mapy] = 0;
					game_array[mapx+3][mapy] = 0;
					update_lines(mapy, mapy+1);
					combo = combo + 1;
					leftclear = leftclear - 4;
					score10 = score10 + 2 * combo;
					if (combo < 6) {
					sfx_play(1+combo, 0);
					}
					if (combo >= 6) {
					sfx_play(6, 0);	
					}
				}		
				}
				else {
					game_array[mapx][mapy] = 0;
					game_array[mapx+1][mapy] = 0;
					game_array[mapx+2][mapy] = 0;
					update_lines(mapy, mapy+1);
					combo = combo + 1;
					leftclear = leftclear - 3;
					score10 = score10 + 1 * combo;
					if (combo < 6) {
					sfx_play(1+combo, 0);
					}
					if (combo >= 6) {
					sfx_play(6, 0);	
					}
				}				
				} 
				}
				
				}
				}
				}
				}
				
				//vertical
				for (mapx = 0; mapx<8; mapx++) {
				for (mapy = 0; mapy<10; mapy++) {
				if (game_array[mapx][mapy] != 0) {
				if (game_array[mapx][mapy] != 99) {
					
				if (game_array[mapx][mapy+1] == game_array[mapx][mapy]) {
				if (game_array[mapx][mapy+2] == game_array[mapx][mapy]) {
				if (game_array[mapx][mapy+3] == game_array[mapx][mapy]) {
				if (game_array[mapx][mapy+4] == game_array[mapx][mapy]) {
				if (game_array[mapx][mapy+5] == game_array[mapx][mapy]) {
				if (game_array[mapx][mapy+6] == game_array[mapx][mapy]) {
					game_array[mapx][mapy] = 0;
					game_array[mapx][mapy+1] = 0;
					game_array[mapx][mapy+2] = 0;
					game_array[mapx][mapy+3] = 0;
					game_array[mapx][mapy+4] = 0;
					game_array[mapx][mapy+5] = 0;
					game_array[mapx][mapy+6] = 0;
					update_lines(mapy, mapy+7);
					combo = combo + 1;
					leftclear = leftclear - 7;
					score10 = score10 + 16 * combo;
					if (combo < 6) {
					sfx_play(1+combo, 0);
					}
					if (combo >= 6) {
					sfx_play(6, 0);	
					}
				}
				else {
					game_array[mapx][mapy] = 0;
					game_array[mapx][mapy+1] = 0;
					game_array[mapx][mapy+2] = 0;
					game_array[mapx][mapy+3] = 0;
					game_array[mapx][mapy+4] = 0;
					game_array[mapx][mapy+5] = 0;
					update_lines(mapy, mapy+6);
					combo = combo + 1;
					leftclear = leftclear - 6;
					score10 = score10 + 8 * combo;
					if (combo < 6) {
					sfx_play(1+combo, 0);
					}
					if (combo >= 6) {
					sfx_play(6, 0);	
					}
				}		
				}
				else {
					game_array[mapx][mapy] = 0;
					game_array[mapx][mapy+1] = 0;
					game_array[mapx][mapy+2] = 0;
					game_array[mapx][mapy+3] = 0;
					game_array[mapx][mapy+4] = 0;
					update_lines(mapy, mapy+5);
					combo = combo + 1;
					leftclear = leftclear - 5;
					score10 = score10 + 4 * combo;
					if (combo < 6) {
					sfx_play(1+combo, 0);
					}
					if (combo >= 6) {
					sfx_play(6, 0);	
					}
				}	
				}
				else {
					game_array[mapx][mapy] = 0;
					game_array[mapx][mapy+1] = 0;
					game_array[mapx][mapy+2] = 0;
					game_array[mapx][mapy+3] = 0;
					update_lines(mapy, mapy+4);
					combo = combo + 1;
					leftclear = leftclear - 4;
					score10 = score10 + 2 * combo;
					if (combo < 6) {
					sfx_play(1+combo, 0);
					}
					if (combo >= 6) {
					sfx_play(6, 0);	
					}
				}		
				}
				else {
					game_array[mapx][mapy] = 0;
					game_array[mapx][mapy+1] = 0;
					game_array[mapx][mapy+2] = 0;
					update_lines(mapy, mapy+3);
					combo = combo + 1;
					leftclear = leftclear - 3;
					score10 = score10 + 1 * combo;
					if (combo < 6) {
					sfx_play(1+combo, 0);
					}
					if (combo >= 6) {
					sfx_play(6, 0);	
					}
				}				
				} 
				}
				
				}
				}
				}
				}
				
				//pseudodiagonal part1
				for (mapx = 0; mapx<8; mapx++) {
				for (mapy = 0; mapy<10; mapy++) {
				if (game_array[mapx][mapy] != 0) {
				if (game_array[mapx][mapy] != 99) {
					
				if (game_array[mapx-1][mapy+1] == game_array[mapx][mapy]) {
				if (game_array[mapx-2][mapy+2] == game_array[mapx][mapy]) {
				if (game_array[mapx-3][mapy+3] == game_array[mapx][mapy]) {
				if (game_array[mapx-4][mapy+4] == game_array[mapx][mapy]) {
				if (game_array[mapx-5][mapy+5] == game_array[mapx][mapy]) {
				if (game_array[mapx-6][mapy+6] == game_array[mapx][mapy]) {
					game_array[mapx][mapy] = 0;
					game_array[mapx-1][mapy+1] = 0;
					game_array[mapx-2][mapy+2] = 0;
					game_array[mapx-3][mapy+3] = 0;
					game_array[mapx-4][mapy+4] = 0;
					game_array[mapx-5][mapy+5] = 0;
					game_array[mapx-6][mapy+6] = 0;
					update_lines(mapy, mapy+7);
					combo = combo + 1;
					leftclear = leftclear - 7;
					score10 = score10 + 16 * combo;
					if (combo < 6) {
					sfx_play(1+combo, 0);
					}
					if (combo >= 6) {
					sfx_play(6, 0);	
					}
				}
				else {
					game_array[mapx][mapy] = 0;
					game_array[mapx-1][mapy+1] = 0;
					game_array[mapx-2][mapy+2] = 0;
					game_array[mapx-3][mapy+3] = 0;
					game_array[mapx-4][mapy+4] = 0;
					game_array[mapx-5][mapy+5] = 0;
					update_lines(mapy, mapy+6);
					combo = combo + 1;
					leftclear = leftclear - 6;
					score10 = score10 + 8 * combo;
					if (combo < 6) {
					sfx_play(1+combo, 0);
					}
					if (combo >= 6) {
					sfx_play(6, 0);	
					}
				}		
				}
				else {
					game_array[mapx][mapy] = 0;
					game_array[mapx-1][mapy+1] = 0;
					game_array[mapx-2][mapy+2] = 0;
					game_array[mapx-3][mapy+3] = 0;
					game_array[mapx-4][mapy+4] = 0;
					update_lines(mapy, mapy+5);
					combo = combo + 1;
					leftclear = leftclear - 5;
					score10 = score10 + 4 * combo;
					if (combo < 6) {
					sfx_play(1+combo, 0);
					}
					if (combo >= 6) {
					sfx_play(6, 0);	
					}
				}	
				}
				else {
					game_array[mapx][mapy] = 0;
					game_array[mapx-1][mapy+1] = 0;
					game_array[mapx-2][mapy+2] = 0;
					game_array[mapx-3][mapy+3] = 0;
					update_lines(mapy, mapy+4);
					combo = combo + 1;
					leftclear = leftclear - 4;
					score10 = score10 + 2 * combo;
					if (combo < 6) {
					sfx_play(1+combo, 0);
					}
					if (combo >= 6) {
					sfx_play(6, 0);	
					}
				}		
				}
				else {
					game_array[mapx][mapy] = 0;
					game_array[mapx-1][mapy+1] = 0;
					game_array[mapx-2][mapy+2] = 0;
					update_lines(mapy, mapy+3);
					combo = combo + 1;
					leftclear = leftclear - 3;
					score10 = score10 + 1 * combo;
					if (combo < 6) {
					sfx_play(1+combo, 0);
					}
					if (combo >= 6) {
					sfx_play(6, 0);	
					}
				}				
				} 
				}
				
				}
				}
				}
				}
				
				//pseudodiagonal part2
				for (mapx = 0; mapx<8; mapx++) {
				for (mapy = 0; mapy<10; mapy++) {
				if (game_array[mapx][mapy] != 0) {
				if (game_array[mapx][mapy] != 99) {
					
				if (game_array[mapx+1][mapy+1] == game_array[mapx][mapy]) {
				if (game_array[mapx+2][mapy+2] == game_array[mapx][mapy]) {
				if (game_array[mapx+3][mapy+3] == game_array[mapx][mapy]) {
				if (game_array[mapx+4][mapy+4] == game_array[mapx][mapy]) {
				if (game_array[mapx+5][mapy+5] == game_array[mapx][mapy]) {
				if (game_array[mapx+6][mapy+6] == game_array[mapx][mapy]) {
					game_array[mapx][mapy] = 0;
					game_array[mapx+1][mapy+1] = 0;
					game_array[mapx+2][mapy+2] = 0;
					game_array[mapx+3][mapy+3] = 0;
					game_array[mapx+4][mapy+4] = 0;
					game_array[mapx+5][mapy+5] = 0;
					game_array[mapx+6][mapy+6] = 0;
					update_lines(mapy, mapy+7);
					combo = combo + 1;
					leftclear = leftclear - 7;
					score10 = score10 + 16 * combo;
					if (combo < 6) {
					sfx_play(1+combo, 0);
					}
					if (combo >= 6) {
					sfx_play(6, 0);	
					}
				}
				else {
					game_array[mapx][mapy] = 0;
					game_array[mapx+1][mapy+1] = 0;
					game_array[mapx+2][mapy+2] = 0;
					game_array[mapx+3][mapy+3] = 0;
					game_array[mapx+4][mapy+4] = 0;
					game_array[mapx+5][mapy+5] = 0;
					update_lines(mapy, mapy+6);
					combo = combo + 1;
					leftclear = leftclear - 6;
					score10 = score10 + 8 * combo;
					if (combo < 6) {
					sfx_play(1+combo, 0);
					}
					if (combo >= 6) {
					sfx_play(6, 0);	
					}
				}		
				}
				else {
					game_array[mapx][mapy] = 0;
					game_array[mapx+1][mapy+1] = 0;
					game_array[mapx+2][mapy+2] = 0;
					game_array[mapx+3][mapy+3] = 0;
					game_array[mapx+4][mapy+4] = 0;
					update_lines(mapy, mapy+5);
					combo = combo + 1;
					leftclear = leftclear - 5;
					score10 = score10 + 4 * combo;
					if (combo < 6) {
					sfx_play(1+combo, 0);
					}
					if (combo >= 6) {
					sfx_play(6, 0);	
					}
				}	
				}
				else {
					game_array[mapx][mapy] = 0;
					game_array[mapx+1][mapy+1] = 0;
					game_array[mapx+2][mapy+2] = 0;
					game_array[mapx+3][mapy+3] = 0;
					update_lines(mapy, mapy+4);
					combo = combo + 1;
					leftclear = leftclear - 4;
					score10 = score10 + 2 * combo;
					if (combo < 6) {
					sfx_play(1+combo, 0);
					}
					if (combo >= 6) {
					sfx_play(6, 0);	
					}
				}		
				}
				else {
					game_array[mapx][mapy] = 0;
					game_array[mapx+1][mapy+1] = 0;
					game_array[mapx+2][mapy+2] = 0;
					update_lines(mapy, mapy+3);
					combo = combo + 1;
					leftclear = leftclear - 3;
					score10 = score10 + 1 * combo;
					if (combo < 6) {
					sfx_play(1+combo, 0);
					}
					if (combo >= 6) {
					sfx_play(6, 0);	
					}
				}				
				} 
				}
				
				}
				}
				}
				}
				
				map_updated = 1;
}


void update_gravity(void) {
				for (loops = 0; loops<9; loops++) {
				for (mapy = 0; mapy<9; mapy++) {
				for (mapx = 0; mapx<7; mapx++) {
				if (game_array[mapx][mapy] != 0) {
				if (game_array[mapx][mapy] != 99) {
				if (game_array[mapx][mapy+1] == 0) {
					game_array[mapx][mapy+1] = game_array[mapx][mapy];
					game_array[mapx][mapy] = 0;
					update_lines(mapy, mapy+3);
				}
				}
				}
				}
				}
				check_match();
				map_updated = 1;
				}
				map_updated = 1;
}

void move_left(void) {
	if (game_array[blockX-1][blockY] == 0) {
				if (game_array[blockX-1][blockY+1] == 0) {
					if (blockX != 0) {
					blockX = blockX-1;
					}
				}
			}
			if (blockY == 0) {
				if (blockX != 0) {
					if (game_array[blockX-1][blockY+1] == 0) {
						blockX = blockX-1;
					}
				}
			}
			leftrepeat = 0;
}

void move_right(void) {
	if (game_array[blockX+2][blockY] == 0) {
				if (game_array[blockX+2][blockY+1] == 0) {
					if (blockX != 4) {
					blockX = blockX+1;
					}
				}
			}
			if (blockY == 0) {
				if (blockX != 4) {
					if (game_array[blockX+2][blockY+1] == 0) {
						blockX = blockX+1;
					}
				}
			}
			rightrepeat = 0;
}

void move_down(void) {
	if (game_array[blockX][blockY+2] != 0 || game_array[blockX+1][blockY+2] != 0) {
				if (block_solid == 0) {
				game_array[blockX][blockY] = block1+1;
				game_array[blockX+1][blockY] = block2+1;
				game_array[blockX][blockY+1] = block3+1;
				game_array[blockX+1][blockY+1] = block4+1;
				lineupdated[blockY] = 1;
				lineupdated[blockY+1] = 1;
				block_solid = 1;
				combo = 0;
				}
				blockX = 2;
				blockY = -1;
				block1 = next1;
				block2 = next2;
				block3 = next3;
				block4 = next4;
				next1 = rand() % 6;
				next2 = rand() % 6;
				next3 = rand() % 6;
				next4 = rand() % 6;
				update_gravity();
				map_updated = 1;
			}
			droptimer = resetdrop;
			blockY = blockY+1;
			downrepeat = 0;
}

void render_game(void) {
	if (map_updated == 0) {
	if (game_array[2][1] != 0 || game_array[3][1] != 0) {
		paused = 2;
		music_play(2);
	}
	}
	if (mode == 1) {
		if (leftclear_modeB <= 0) {
			map_updated = 1;
			paused = 3;
			music_play(3);
		}
	}
if (statusbar_changed == 1) {
		score_str[0] = score100000 + ZERO_DIGIT;
		score_str[1] = score10000 + ZERO_DIGIT;
		score_str[2] = score1000 + ZERO_DIGIT;
		score_str[3] = score100 + ZERO_DIGIT;
		score_str[4] = score10 + ZERO_DIGIT;
		score_str[5] = '\0'; 

		hi_str[0] = hi100000 + ZERO_DIGIT;
		hi_str[1] = hi10000 + ZERO_DIGIT;
		hi_str[2] = hi1000 + ZERO_DIGIT;
		hi_str[3] = hi100 + ZERO_DIGIT;
		hi_str[4] = hi10 + ZERO_DIGIT;
		hi_str[5] = '\0'; 
		
		timeminutes_str[0] = timeminutes10 + ZERO_DIGIT;
		timeminutes_str[1] = timeminutes1 + ZERO_DIGIT;
		timeminutes_str[2] = '\0'; 
		
		timeseconds_str[0] = timeseconds10 + ZERO_DIGIT;
		timeseconds_str[1] = timeseconds1 + ZERO_DIGIT;
		timeseconds_str[2] = '\0'; 
		
		put_str(NTADR_A(4,1),score_str);
		put_str(NTADR_A(4,2),hi_str);
		put_str(NTADR_A(17,1),timeminutes_str);
		put_str(NTADR_A(20,1),timeseconds_str);
		put_str(NTADR_A(9,1),"0");
		put_str(NTADR_A(9,2),"0");
		
		}
		
		if (combo <= 1) {
		one_vram_buffer(0x00, NTADR_A(24,1));
		one_vram_buffer(0x00, NTADR_A(24,2));
		}
		
		if (combo == 2) {
		one_vram_buffer(0x6B, NTADR_A(24,1));
		one_vram_buffer(0x7B, NTADR_A(24,2));
		}
		
		if (combo == 3) {
		one_vram_buffer(0x6C, NTADR_A(24,1));
		one_vram_buffer(0x7C, NTADR_A(24,2));
		}
		
		if (combo == 4) {
		one_vram_buffer(0x6D, NTADR_A(24,1));
		one_vram_buffer(0x7D, NTADR_A(24,2));
		}
		
		if (combo == 5) {
		one_vram_buffer(0x6E, NTADR_A(24,1));
		one_vram_buffer(0x7E, NTADR_A(24,2));
		}
		
		if (combo >= 6) {
		one_vram_buffer(0x6F, NTADR_A(24,1));
		one_vram_buffer(0x7F, NTADR_A(24,2));
		}
		
		itoa(level, level_str, 10);
		if (level_str[1] == 0) {
			level_str[1] = level_str[0];
			level_str[0] = '0';
		}
		
		itoa(leftclear_modeB, leftclear_str, 10);
		if (leftclear_str[1] == 0) {
			leftclear_str[1] = leftclear_str[0];
			leftclear_str[0] = '0';
		}
		
		if (mode == 1) {
		one_vram_buffer(0x3B, NTADR_A(11,2));
		one_vram_buffer(0x3D, NTADR_A(12,2));
		put_str(NTADR_A(13,2),leftclear_str);
		}
		put_str(NTADR_A(13,1),level_str);
		put_str(NTADR_A(16,2),"      ");
		
		ppu_wait_nmi(); // waits till nmi, and push new updates to the ppu
		clear_vram_buffer(); // clear the buffer at the start of each frame
		
		statusbar_changed = 0;
		
		
		for (mapx = 0; mapx<7; mapx++) {
			game_array[mapx][10] = 99;
		}
		game_array[0][0] = 0;
		
		if (map_updated == 1) {
		
		//hack no.2 to get rid of flickering
		if (first_load == 0) {
		for (loops = 1; loops < 3; loops++) {
		for (mapy = 1; mapy<14; mapy++) {
		for (mapx = 0; mapx<8; mapx++) {
			setAttr(0+mapx, 0+mapy, 1);	
		}
		}
		}
		first_load = 1;
		}
			
		for (mapy = 1; mapy<10; mapy++) {
		if (lineupdated[mapy]) {	
		for (mapx = 0; mapx<6; mapx++) {
			if (game_array[mapx][mapy] != 0 && game_array[mapx][mapy] != 99) {
			setAttr(1+mapx, 3+mapy, palettes[game_array[mapx][mapy]-1]);
			}
			else {
			setAttr(1+mapx, 3+mapy, 1);	
			}
			ppu_wait_nmi(); // wait for the next frame so the changes will be applied
			set_vram_buffer();
		}	
		}
		}
		
		
			
		for (mapy = 0; mapy<10; mapy++) {
			if (lineupdated[mapy]) {
			for (mapx = 0; mapx<6; mapx++) {
			
			if (game_array[mapx][mapy]==0) {
				one_vram_buffer(0xA6, NTADR_A(2+mapx*2, 6+mapy*2));
				one_vram_buffer(0xA7, NTADR_A(3+mapx*2, 6+mapy*2));
				one_vram_buffer(0xB6, NTADR_A(2+mapx*2, 7+mapy*2));
				one_vram_buffer(0xB7, NTADR_A(3+mapx*2, 7+mapy*2));
			}
			if (game_array[mapx][mapy]==1 || game_array[mapx][mapy]==5 || game_array[mapx][mapy]==6) {
				one_vram_buffer(0x42, NTADR_A(2+mapx*2, 6+mapy*2));
				one_vram_buffer(0x43, NTADR_A(3+mapx*2, 6+mapy*2));
				one_vram_buffer(0x52, NTADR_A(2+mapx*2, 7+mapy*2));
				one_vram_buffer(0x53, NTADR_A(3+mapx*2, 7+mapy*2));
			}
			if (game_array[mapx][mapy]==2 || game_array[mapx][mapy]==3 || game_array[mapx][mapy]==4) {
				one_vram_buffer(0x40, NTADR_A(2+mapx*2, 6+mapy*2));
				one_vram_buffer(0x41, NTADR_A(3+mapx*2, 6+mapy*2));
				one_vram_buffer(0x50, NTADR_A(2+mapx*2, 7+mapy*2));
				one_vram_buffer(0x51, NTADR_A(3+mapx*2, 7+mapy*2));
			}
			
			}
			ppu_wait_nmi();
			clear_vram_buffer();
			}
		}
		if (combo == 0) {
		one_vram_buffer(0xB9, NTADR_A(14, 24));	
		one_vram_buffer(0x57, NTADR_A(15, 24));	
		one_vram_buffer(0xB9, NTADR_A(14, 25));	
		one_vram_buffer(0x57, NTADR_A(15, 25));	
		one_vram_buffer(0xB9, NTADR_A(14, 22));	
		one_vram_buffer(0x57, NTADR_A(15, 22));	
		one_vram_buffer(0xB9, NTADR_A(14, 23));	
		one_vram_buffer(0x57, NTADR_A(15, 23));	
		one_vram_buffer(0xB9, NTADR_A(14, 20));	
		one_vram_buffer(0x57, NTADR_A(15, 20));	
		one_vram_buffer(0xB9, NTADR_A(14, 21));	
		one_vram_buffer(0x57, NTADR_A(15, 21));	
		one_vram_buffer(0xB9, NTADR_A(14, 18));	
		one_vram_buffer(0x57, NTADR_A(15, 18));	
		one_vram_buffer(0xB9, NTADR_A(14, 19));	
		one_vram_buffer(0x57, NTADR_A(15, 19));	
		one_vram_buffer(0xB9, NTADR_A(14, 16));	
		one_vram_buffer(0x57, NTADR_A(15, 16));	
		one_vram_buffer(0xB9, NTADR_A(14, 17));	
		one_vram_buffer(0x57, NTADR_A(15, 17));
		}
		if (combo >= 2) {
		one_vram_buffer(0x8A, NTADR_A(14, 24));	
		one_vram_buffer(0x8B, NTADR_A(15, 24));	
		one_vram_buffer(0x9A, NTADR_A(14, 25));	
		one_vram_buffer(0x9B, NTADR_A(15, 25));
		}
		if (combo >= 3) {
		one_vram_buffer(0x8A, NTADR_A(14, 22));	
		one_vram_buffer(0x8B, NTADR_A(15, 22));	
		one_vram_buffer(0x9A, NTADR_A(14, 23));	
		one_vram_buffer(0x9B, NTADR_A(15, 23));	
		}
		if (combo >= 4) {
		one_vram_buffer(0x8A, NTADR_A(14, 20));	
		one_vram_buffer(0x8B, NTADR_A(15, 20));	
		one_vram_buffer(0x9A, NTADR_A(14, 21));	
		one_vram_buffer(0x9B, NTADR_A(15, 21));	
		}
		if (combo >= 5) {
		one_vram_buffer(0x8A, NTADR_A(14, 18));	
		one_vram_buffer(0x8B, NTADR_A(15, 18));	
		one_vram_buffer(0x9A, NTADR_A(14, 19));	
		one_vram_buffer(0x9B, NTADR_A(15, 19));	
		}
		if (combo >= 6) {
		one_vram_buffer(0x8A, NTADR_A(14, 16));	
		one_vram_buffer(0x8B, NTADR_A(15, 16));	
		one_vram_buffer(0x9A, NTADR_A(14, 17));	
		one_vram_buffer(0x9B, NTADR_A(15, 17));	
		}
		ppu_wait_nmi();
		clear_vram_buffer();
		
		for (mapy = 1; mapy<11; mapy++) {
			setAttr(0, 3+mapy, 1);
			setAttr(7, 3+mapy, 1);
		}
		
		for (mapx = 1; mapx<8; mapx++) {
			setAttr(0+mapx, 13, 1);
		}
		
		//hack no.3 to get rid of flickering
		for (mapy = 1; mapy<14; mapy++) {
		for (mapx = 1; mapx<7; mapx++) {
		if (loaded < 2) {
			setAttr(0+mapx, 0+mapy, 1);	
		}
		}
		}
		loaded = loaded + 1;
		if (loaded > 250) {
			loaded = 250;
		}
				
		set_vram_buffer(); 	
			
		}
		
		for (updy = 0; updy < 10; updy++) {
		lineupdated[updy] = 0;
		}
				
		map_updated = 0;
	
		oam_meta_spr(192,128,0,metasprites_list[next1]);
		oam_meta_spr(208,128,16,metasprites_list[next2]);
		oam_meta_spr(192,144,32,metasprites_list[next3]);
		oam_meta_spr(208,144,48,metasprites_list[next4]);
		
		if (block1 == 0) {
		oam_meta_spr((blockX+1)*16,(blockY+3)*16,64,metasprites_0_data);
		}
		if (block1 == 1) {
		oam_meta_spr((blockX+1)*16,(blockY+3)*16,64,metasprites_1_data);
		}
		if (block1 == 2) {
		oam_meta_spr((blockX+1)*16,(blockY+3)*16,64,metasprites_2_data);
		}
		if (block1 == 3) {
		oam_meta_spr((blockX+1)*16,(blockY+3)*16,64,metasprites_3_data);
		}
		if (block1 == 4) {
		oam_meta_spr((blockX+1)*16,(blockY+3)*16,64,metasprites_4_data);
		}
		if (block1 == 5) {
		oam_meta_spr((blockX+1)*16,(blockY+3)*16,64,metasprites_5_data);
		}
		
		if (block2 == 0) {
		oam_meta_spr((blockX+2)*16,(blockY+3)*16,80,metasprites_0_data);
		}
		if (block2 == 1) {
		oam_meta_spr((blockX+2)*16,(blockY+3)*16,80,metasprites_1_data);
		}
		if (block2 == 2) {
		oam_meta_spr((blockX+2)*16,(blockY+3)*16,80,metasprites_2_data);
		}
		if (block2 == 3) {
		oam_meta_spr((blockX+2)*16,(blockY+3)*16,80,metasprites_3_data);
		}
		if (block2 == 4) {
		oam_meta_spr((blockX+2)*16,(blockY+3)*16,80,metasprites_4_data);
		}
		if (block2 == 5) {
		oam_meta_spr((blockX+2)*16,(blockY+3)*16,80,metasprites_5_data);
		}
		
		if (block3 == 0) {
		oam_meta_spr((blockX+1)*16,(blockY+4)*16,96,metasprites_0_data);
		}
		if (block3 == 1) {
		oam_meta_spr((blockX+1)*16,(blockY+4)*16,96,metasprites_1_data);
		}
		if (block3 == 2) {
		oam_meta_spr((blockX+1)*16,(blockY+4)*16,96,metasprites_2_data);
		}
		if (block3 == 3) {
		oam_meta_spr((blockX+1)*16,(blockY+4)*16,96,metasprites_3_data);
		}
		if (block3 == 4) {
		oam_meta_spr((blockX+1)*16,(blockY+4)*16,96,metasprites_4_data);
		}
		if (block3 == 5) {
		oam_meta_spr((blockX+1)*16,(blockY+4)*16,96,metasprites_5_data);
		}
		
		if (block4 == 0) {
		oam_meta_spr((blockX+2)*16,(blockY+4)*16,112,metasprites_0_data);
		}
		if (block4 == 1) {
		oam_meta_spr((blockX+2)*16,(blockY+4)*16,112,metasprites_1_data);
		}
		if (block4 == 2) {
		oam_meta_spr((blockX+2)*16,(blockY+4)*16,112,metasprites_2_data);
		}
		if (block4 == 3) {
		oam_meta_spr((blockX+2)*16,(blockY+4)*16,112,metasprites_3_data);
		}
		if (block4 == 4) {
		oam_meta_spr((blockX+2)*16,(blockY+4)*16,112,metasprites_4_data);
		}
		if (block4 == 5) {
		oam_meta_spr((blockX+2)*16,(blockY+4)*16,112,metasprites_5_data);
		}
				
		ppu_wait_frame();	
		pad1 = pad_poll(0); // read the first controller
		pad1_new = get_pad_new(0);
		block_solid = 0;
		
		
		if(pad1 & PAD_LEFT){
		leftrepeat = leftrepeat + 1;	
		}
		
		if(pad1 & PAD_RIGHT){
		rightrepeat = rightrepeat + 1;	
		}
		
		if(pad1_new & PAD_LEFT){
			move_left();
		}
		
		if(leftrepeat > 5){
			move_left();
		}
		
		if(pad1_new & PAD_RIGHT){
			move_right();
		}
		
		if(rightrepeat > 5){
			move_right();
		}
		
		if(pad1_new & PAD_SELECT) {
			if (combo == 2) {
				for (mapx = 0; mapx<7; mapx++) {
				game_array[mapx][9] = 0;
				lineupdated[9] = 1;
				map_updated = 1;
				}	
				score100 = score100 + 2;
				leftclear = leftclear - 6;
				leftclear_modeB = leftclear_modeB - 1;
				update_gravity();
			}
			if (combo == 3) {
				for (mapx = 0; mapx<7; mapx++) {
				game_array[mapx][9] = 0;
				game_array[mapx][8] = 0;
				lineupdated[9] = 1;
				lineupdated[8] = 1;
				map_updated = 1;
				}	
				score100 = score100 + 4;
				leftclear = leftclear - 12;
				leftclear_modeB = leftclear_modeB - 2;
				update_gravity();
			}
			if (combo == 4) {
				for (mapx = 0; mapx<7; mapx++) {
				game_array[mapx][9] = 0;
				game_array[mapx][8] = 0;
				game_array[mapx][7] = 0;
				lineupdated[9] = 1;
				lineupdated[8] = 1;
				lineupdated[7] = 1;
				map_updated = 1;
				}	
				score100 = score100 + 8;
				leftclear = leftclear - 18;
				leftclear_modeB = leftclear_modeB - 3;
				update_gravity();
			}
			if (combo == 5) {
				for (mapx = 0; mapx<7; mapx++) {
				game_array[mapx][9] = 0;
				game_array[mapx][8] = 0;
				game_array[mapx][7] = 0;
				game_array[mapx][6] = 0;
				lineupdated[9] = 1;
				lineupdated[8] = 1;
				lineupdated[7] = 1;
				lineupdated[6] = 1;
				map_updated = 1;
				}	
				score100 = score100 + 16;
				leftclear = leftclear - 24;
				leftclear_modeB = leftclear_modeB - 4;
				update_gravity();
			}
			if (combo >= 6) {
				for (mapx = 0; mapx<7; mapx++) {
				game_array[mapx][9] = 0;
				game_array[mapx][8] = 0;
				game_array[mapx][7] = 0;
				game_array[mapx][6] = 0;
				game_array[mapx][5] = 0;
				lineupdated[9] = 1;
				lineupdated[8] = 1;
				lineupdated[7] = 1;
				lineupdated[6] = 1;
				lineupdated[5] = 1;
				map_updated = 1;
				}	
				score100 = score100 + 32;
				leftclear = leftclear - 30;
				leftclear_modeB = leftclear_modeB - 5;
				update_gravity();
			}
		if (combo >= 2) {
		combo = 0;
		sfx_play(7, 0);
		}
		}
		
		if (mode == 0) {
		if(leftclear <= 0){
		leftclear = 50;
		resetdrop = resetdrop - 10;
		level = level + 1;
		}
		}
		
		if (level >= 10) {
		resetdrop = 5;
		}
		
		if(pad1 & PAD_DOWN) {
		downrepeat = downrepeat + 1;
		}
		
		if(downrepeat > 5) {
			move_down();
		}
		
		if(pad1_new & PAD_DOWN){
			move_down();
		}
		
		if(droptimer == 0){
			move_down();
		}
		
		if(pad1_new & PAD_B){
		temp1 = block1;
		temp2 = block2;
		temp3 = block3;
		temp4 = block4;
		block1 = temp2;
		block2 = temp4;
		block3 = temp1;
		block4 = temp3;
		sfx_play(1, 0);
		}
		
		if(pad1_new & PAD_A){
		temp1 = block1;
		temp2 = block2;
		temp3 = block3;
		temp4 = block4;
		block1 = temp3;
		block2 = temp1;
		block3 = temp4;
		block4 = temp2;
		sfx_play(1, 0);
		}
		
		if(pad1_new & PAD_START){
		paused = 1;
		sfx_play(8, 0);
		}
		
		frames = frames + 1;
		droptimer = droptimer - 1;
		
		if (frames >= 60) {
		timeseconds1 = timeseconds1 + 1;
		statusbar_changed = 1;
		frames = 0;
		}
		if (timeseconds1 >= 10) {
		timeseconds10 = timeseconds10 + 1;
		timeseconds1 = 0;
		}
		if (timeseconds10 >= 6) {
		timeminutes1 = timeminutes1 + 1;
		timeseconds10 = 0;
		}
		if (timeminutes1 >= 10) {
		timeminutes10 = timeminutes10 + 1;
		timeminutes1 = 0;
		}
		if (timeminutes10 >= 10) {
		timeminutes10 = 9;
		timeminutes1 = 9;
		}
}

void render_pause(void) {
	put_str(NTADR_A(16,2),"PAUSE!");
		
	ppu_wait_nmi(); // waits till nmi, and push new updates to the ppu
	clear_vram_buffer(); // clear the buffer at the start of each frame
	
	PPUMASK = 0xEE;
	
	pad1 = pad_poll(0); // read the first controller
	pad1_new = get_pad_new(0);
	
	if(pad1_new & PAD_START){
		paused = 0;
	}
}

void render_gover(void) {
	put_str(NTADR_A(16,2),"OVER!!");
		
	ppu_wait_nmi(); // waits till nmi, and push new updates to the ppu
	clear_vram_buffer(); // clear the buffer at the start of each frame
	
	PPUMASK = 0x2E;
	
	pad1 = pad_poll(0); // read the first controller
	pad1_new = get_pad_new(0);
	
	first_load = 0;
	
	if(pad1_new & PAD_START){
		if (hiscore_beat == 0 || mode == 1) {
		reset_game();
		load_title();
		state = 0;
		music_play(4);
		paused = 0;
		} else {
		load_ending();
		music_play(7);
		paused = 0;
		state = 3;
		}
	}
}

void render_win(void) {
	put_str(NTADR_A(16,2),"WINNER");
		
	ppu_wait_nmi(); // waits till nmi, and push new updates to the ppu
	clear_vram_buffer(); // clear the buffer at the start of each frame
	
	PPUMASK = 0x4E;
	
	pad1 = pad_poll(0); // read the first controller
	pad1_new = get_pad_new(0);
	
	if(pad1_new & PAD_START){
		load_ending();
		music_play(7);
		paused = 0;
		state = 3;
	}
}

void render_title(void) {
	next1 = rand() % 6;
	next2 = rand() % 6;
	next3 = rand() % 6;
	next4 = rand() % 6;
	block1 = rand() % 6;
	block2 = rand() % 6;
	block3 = rand() % 6;
	block4 = rand() % 6;
	titleframes = titleframes + 1;
	if (titleframes < 10) {
	put_str(NTADR_A(8,21),"PUSH START KEY!!");
	}
	else {
	put_str(NTADR_A(8,21),"                ");	
	}
	if (titleframes >= 20) {
	titleframes = 0;
	}
	ppu_wait_nmi(); // waits till nmi, and push new updates to the ppu
	clear_vram_buffer(); // clear the buffer at the start of each frame
	
	pad1 = pad_poll(0); // read the first controller
	pad1_new = get_pad_new(0);
	
	if(pad1_new & PAD_UP){
	if(easteregg == 0) {
	pad1 = 0;
	pad1_new = 0;
	easteregg = easteregg + 1;
	}	
	}
	if(pad1_new & PAD_UP){
	if(easteregg == 1) {
	easteregg = easteregg + 1;
	}	
	}
	if(pad1_new & PAD_DOWN){
	if(easteregg == 2) {
	pad1 = 0;
	pad1_new = 0;
	easteregg = easteregg + 1;
	}	
	}
	if(pad1_new & PAD_DOWN){
	if(easteregg == 2) {
	easteregg = easteregg + 1;
	}	
	}
	if(pad1_new & PAD_LEFT){
	if(easteregg == 3) {
	easteregg = easteregg + 1;
	}	
	}
	if(pad1_new & PAD_RIGHT){
	if(easteregg == 4) {
	easteregg = easteregg + 1;
	}	
	}
	if(pad1_new & PAD_LEFT){
	if(easteregg == 5) {
	easteregg = easteregg + 1;
	}	
	}
	if(pad1_new & PAD_RIGHT){
	if(easteregg == 6) {
	easteregg = easteregg + 1;
	}	
	}
	if(pad1_new & PAD_B){
	if(easteregg == 7) {
	easteregg = easteregg + 1;
	}	
	}
	if(pad1_new & PAD_A){
	if(easteregg == 8) {
	easteregg = easteregg + 1;
	sfx_play(6, 0);
	}	
	}
	
	if(pad1_new & PAD_START){
		load_options();
		music_play(5);
		paused = 0;
		state = 1;
	}
}

void render_options(void) {
	ppu_wait_nmi(); // waits till nmi, and push new updates to the ppu
	clear_vram_buffer(); // clear the buffer at the start of each frame
	
	pad1 = pad_poll(0); // read the first controller
	pad1_new = get_pad_new(0);
	
	oam_meta_spr(48+level*16,55,32,metasprites_9_data);
	oam_meta_spr(48+height*16,86,48,metasprites_9_data);
	oam_meta_spr(96+mode*16,110,64,metasprites_9_data);
	oam_meta_spr(96+music*16,142,80,metasprites_9_data);
	
	if(mode == 0) {
		put_str(NTADR_A(8,15),"MARATHON     ");
	}
	if(mode == 1) {
		put_str(NTADR_A(8,15),"25-LINE CLEAR");
	}
	
	if(easteregg < 9) {
	if(music == 0) {
		put_str(NTADR_A(8,19),"HISPANIC TEA    ");
	}
	if(music == 1) {
		put_str(NTADR_A(8,19),"CSIKOS POST     ");
	}
	}
	else {
		put_str(NTADR_A(8,19),"SHE'LL BE COMIN'");
	}
	
	if(menusel == 0) {
	oam_meta_spr(48+level*16,55,16,metasprites_7_data);
	if(pad1_new & PAD_LEFT) {
	if(level != 0) {
	sfx_play(1, 0);
	level = level - 1;
	resetdrop = resetdrop + 10;
	}
	}
	if(pad1_new & PAD_RIGHT) {
	if(level != 9) {
	sfx_play(1, 0);
	level = level + 1;
	resetdrop = resetdrop - 10;
	}
	}
	}
	
	if(menusel == 1) {
	oam_meta_spr(48+height*16,86,16,metasprites_7_data);
	if(pad1_new & PAD_LEFT) {
	if(height != 0) {
	sfx_play(1, 0);
	height = height - 1;
	}
	}
	if(pad1_new & PAD_RIGHT) {
	if(height != 5) {
	sfx_play(1, 0);
	height = height + 1;
	}
	}
	}
	
	if(menusel == 2) {
	oam_meta_spr(96+mode*16,110,16,metasprites_7_data);
	if(pad1_new & PAD_LEFT) {
	if(mode != 0) {
	sfx_play(1, 0);
	mode = mode - 1;
	}
	}
	if(pad1_new & PAD_RIGHT) {
	if(mode != 1) {
	sfx_play(1, 0);
	mode = mode + 1;
	}
	}
	}
	
	if(menusel == 3) {
	oam_meta_spr(96+music*16,142,16,metasprites_7_data);
	if(pad1_new & PAD_LEFT) {
	if(music != 0) {
	sfx_play(1, 0);
	music = music - 1;
	}
	}
	if(pad1_new & PAD_RIGHT) {
	if(music != 1) {
	sfx_play(1, 0);
	music = music + 1;
	}
	}
	}
	
	
	if(pad1_new & PAD_UP) {
	if(menusel != 0) {
	sfx_play(2, 0);
	menusel = menusel - 1;
	}	
	}
	if(pad1_new & PAD_DOWN) {
	if(menusel != 3) {
		sfx_play(2, 0);
	menusel = menusel + 1;
	}
	}
	
	if(pad1_new & PAD_START){
		generate_height();
		load_game();
		if (easteregg != 9) {
		music_play(music);
		} else {
		music_play(6);
		}
		paused = 0;
		state = 2;
	}
}

void render_ending() {
	if (mode == 0) {
	put_str(NTADR_A(8,3),"SCORE");
	put_str(NTADR_A(14,3),score_str);
	put_str(NTADR_A(19,3),"0");
	}
	else {
	put_str(NTADR_A(8,3),"HGT. ");	
	put_str(NTADR_A(14,3),height_str);
	}
	put_str(NTADR_A(14,2),level_str);
	
	
	itoa(level, level_str, 10);
	if (level_str[1] == 0) {
		level_str[1] = level_str[0];
		level_str[0] = '0';
	}
		
	itoa(height, height_str, 10);
	if (height_str[1] == 0) {
		height_str[1] = height_str[0];
		height_str[0] = '0';
	}
	
	if (firework_radius == 8) {
		firework_destx = rand() % 20 + 6;
		firework_desty = rand() % 5	 + 8;
		firework_x = firework_destx * 8;
		firework_y = 255;
		firework_radius = 0;
		congratulations_frames = 0;
	}
	
	if (firework_y > firework_desty*8) {
		firework_y = firework_y - 2;
	}
	
	if (firework_y <= firework_desty*8) {
		congratulations_frames = congratulations_frames + 1;
		if (firework_radius == 0) {
			sfx_play(9, 0);
		}
	}
	
	if (congratulations_frames > 20) {
		firework_radius = firework_radius + 1;
	}
	
	if (firework_radius == 1) {
		one_vram_buffer(0xAC + rand() % 3, NTADR_A(firework_destx, firework_desty));
		pal_bg(firework_flash1);
		ppu_wait_nmi();
	}
	if (firework_radius == 2) {
		one_vram_buffer(0xAC + rand() % 3, NTADR_A(firework_destx-1, firework_desty-1));
		one_vram_buffer(0xAC + rand() % 3, NTADR_A(firework_destx-1, firework_desty+1));
		one_vram_buffer(0xAC + rand() % 3, NTADR_A(firework_destx+1, firework_desty-1));
		one_vram_buffer(0xAC + rand() % 3, NTADR_A(firework_destx+1, firework_desty+1));
		pal_bg(firework_flash2);
		ppu_wait_nmi();
	}
	if (firework_radius == 3) {
		one_vram_buffer(0xAC + rand() % 3, NTADR_A(firework_destx-2, firework_desty-2));
		one_vram_buffer(0xAC + rand() % 3, NTADR_A(firework_destx-2, firework_desty+2));
		one_vram_buffer(0xAC + rand() % 3, NTADR_A(firework_destx+2, firework_desty-2));
		one_vram_buffer(0xAC + rand() % 3, NTADR_A(firework_destx+2, firework_desty+2));
		pal_bg(firework_flash3);
		ppu_wait_nmi();
	}
	if (firework_radius == 4) {
		one_vram_buffer(0xAC + rand() % 3, NTADR_A(firework_destx-3, firework_desty-3));
		one_vram_buffer(0xAC + rand() % 3, NTADR_A(firework_destx-3, firework_desty+3));
		one_vram_buffer(0xAC + rand() % 3, NTADR_A(firework_destx+3, firework_desty-3));
		one_vram_buffer(0xAC + rand() % 3, NTADR_A(firework_destx+3, firework_desty+3));
		pal_bg(firework_flash4);
		ppu_wait_nmi();
	}
	if (firework_radius == 5) {
		one_vram_buffer(0x00, NTADR_A(firework_destx, firework_desty));
		pal_bg(firework);
		ppu_wait_nmi();
	}
	if (firework_radius == 6) {
		one_vram_buffer(0x00, NTADR_A(firework_destx-1, firework_desty-1));
		one_vram_buffer(0x00, NTADR_A(firework_destx-1, firework_desty+1));
		one_vram_buffer(0x00, NTADR_A(firework_destx+1, firework_desty-1));
		one_vram_buffer(0x00, NTADR_A(firework_destx+1, firework_desty+1));
	}
	if (firework_radius == 7) {
		one_vram_buffer(0x00, NTADR_A(firework_destx-2, firework_desty-2));
		one_vram_buffer(0x00, NTADR_A(firework_destx-2, firework_desty+2));
		one_vram_buffer(0x00, NTADR_A(firework_destx+2, firework_desty-2));
		one_vram_buffer(0x00, NTADR_A(firework_destx+2, firework_desty+2));
	}
	if (firework_radius == 8) {
		one_vram_buffer(0x00, NTADR_A(firework_destx-3, firework_desty-3));
		one_vram_buffer(0x00, NTADR_A(firework_destx-3, firework_desty+3));
		one_vram_buffer(0x00, NTADR_A(firework_destx+3, firework_desty-3));
		one_vram_buffer(0x00, NTADR_A(firework_destx+3, firework_desty+3));
	}
	
	oam_clear();
	oam_meta_spr(firework_x,firework_y,16,metasprites_8_data);
		
	score_str[0] = score100000 + ZERO_DIGIT;
	score_str[1] = score10000 + ZERO_DIGIT;
	score_str[2] = score1000 + ZERO_DIGIT;
	score_str[3] = score100 + ZERO_DIGIT;
	score_str[4] = score10 + ZERO_DIGIT;
	score_str[5] = '\0';
	
	ppu_wait_nmi(); // waits till nmi, and push new updates to the ppu
	clear_vram_buffer(); // clear the buffer at the start of each frame
	
	pad1 = pad_poll(0); // read the first controller
	pad1_new = get_pad_new(0);
	
	if(pad1_new & PAD_START){
		reset_game();
		load_title();
		state = 0;
		music_play(4);
		paused = 0;
	}
}

void main(void)
{
	load_title();
	while(1)
	{	
		while (state == 0) {
		render_title();
		oam_clear();
		}
		while (state == 1) {
		render_options();
		}
		while (state == 2) {
		while (paused == 0) {
		fix_score();
		highscore_check();
		render_game();
		}
		while (paused == 1) {
		render_pause();
		}
		while (paused == 2) {
		render_gover();
		}
		while (paused == 3) {
		render_win();
		}
		}
		while (state == 3) {
		render_ending();
		}
	}
}