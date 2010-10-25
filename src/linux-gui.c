/*B-em v2.1 by Tom Walker
  Linux GUI*/

#ifndef WIN32
#include <allegro.h>
#include <alleggl.h>
#include "b-em.h"
#include "resources.h"

#undef printf

int timerspeeds[]={5,12,25,38,50,75,100,150,200,250};
int frameskips[] ={0,0, 0, 0, 0, 0, 1,  2,  3,  4};
int emuspeed=4;

void setejecttext(int d, char *s)
{
}
void setquit()
{
}

extern int quited;
extern int windx,windy;
extern int dcol;

MENU filemenu[4];
MENU discmenu[8];
MENU tapespdmenu[3];
MENU tapemenu[5];
MENU modelmenu[16];
MENU tubespdmenu[6];
#ifdef NS32016
MENU tubemenu[7];
#else
MENU tubemenu[6];
#endif
MENU displaymenu[4];
MENU bordersmenu[4];
MENU videomenu[4];
MENU sidtypemenu[15];
MENU methodmenu[3];
MENU residmenu[3];
MENU waveformmenu[6];
MENU ddtypemenu[3];
MENU ddvolmenu[4];
MENU soundmenu[10];
MENU keymenu[3];
MENU idemenu[2];
MENU settingsmenu[7];
MENU miscmenu[3];
MENU speedmenu[11];
MENU mainmenu[6];

void updatelinuxgui()
{
        int x;
        discmenu[4].flags=(writeprot[0])?D_SELECTED:0;
        discmenu[5].flags=(writeprot[1])?D_SELECTED:0;
        discmenu[6].flags=(defaultwriteprot)?D_SELECTED:0;
        tapespdmenu[0].flags=(!fasttape)?D_SELECTED:0;
        tapespdmenu[1].flags=(fasttape)?D_SELECTED:0;
        for (x=0;x<14;x++) modelmenu[x].flags=(curmodel==x)?D_SELECTED:0;
        #ifdef NS32016
        for (x=0;x<5;x++)  tubemenu[x].flags=(selecttube==(int)tubemenu[x].dp)?D_SELECTED:0;
        #else
        for (x=0;x<4;x++)  tubemenu[x].flags=(selecttube==(int)tubemenu[x].dp)?D_SELECTED:0;
        #endif
        for (x=0;x<5;x++)  tubespdmenu[x].flags=(tube6502speed==(int)tubespdmenu[x].dp)?D_SELECTED:0;
        displaymenu[0].flags=(linedbl)?D_SELECTED:0;
        displaymenu[1].flags=(comedyblit)?D_SELECTED:0;
        displaymenu[2].flags=(interlace)?D_SELECTED:0;
        videomenu[2].flags=(fullscreen)?D_SELECTED:0;
        for (x=0;x<3;x++)  bordersmenu[x].flags=(fullborders==(int)bordersmenu[x].dp)?D_SELECTED:0;
        soundmenu[0].flags=(sndinternal)?D_SELECTED:0;
        soundmenu[1].flags=(sndbeebsid)?D_SELECTED:0;
        soundmenu[2].flags=(sndddnoise)?D_SELECTED:0;
        soundmenu[3].flags=(sndtape)?D_SELECTED:0;
        soundmenu[4].flags=(soundfilter)?D_SELECTED:0;
        for (x=0;x<5;x++)  waveformmenu[x].flags=(curwave==(int)waveformmenu[x].dp)?D_SELECTED:0;
        for (x=0;x<14;x++) sidtypemenu[x].flags=(cursid==(int)sidtypemenu[x].dp)?D_SELECTED:0;
        methodmenu[0].flags=(!sidmethod)?D_SELECTED:0;
        methodmenu[1].flags=(sidmethod)?D_SELECTED:0;
        ddtypemenu[0].flags=(!ddtype)?D_SELECTED:0;
        ddtypemenu[1].flags=(ddtype)?D_SELECTED:0;
        for (x=0;x<3;x++)  ddvolmenu[x].flags=(ddvol==(int)ddvolmenu[x].dp)?D_SELECTED:0;
        keymenu[1].flags=(keyas)?D_SELECTED:0;
        for (x=0;x<10;x++) speedmenu[x].flags=(emuspeed==(int)speedmenu[x].dp)?D_SELECTED:0;
        idemenu[0].flags=(ideenable)?D_SELECTED:0;
}

int gui_keydefine();

int gui_return()
{
        return D_CLOSE;
}

int gui_reset()
{
        restartbbc();
        return D_O_K;
}

int gui_exit()
{
        quited=1;
        return D_CLOSE;
}

MENU filemenu[4]=
{
        {"&Return",gui_return,NULL,0,NULL},
        {"&Hard reset",gui_reset,NULL,0,NULL},
        {"&Exit",gui_exit,NULL,0,NULL},
        {NULL,NULL,NULL,0,NULL}
};

int gui_load0()
{
        char tempname[260];
        int ret,c;
        int xsize=windx-32,ysize=windy-16;
        memcpy(tempname,discfns[0],260);
        ret=file_select_ex("Please choose a disc image",tempname,"SSD;DSD;IMG;ADF;ADL;FDI",260,xsize,ysize);
        if (ret)
        {
                closedisc(0);
                memcpy(discfns[0],tempname,260);
                loaddisc(0,discfns[0]);
                if (defaultwriteprot) writeprot[0]=1;
        }
        updatelinuxgui();
        return D_O_K;
}
int gui_load1()
{
        char tempname[260];
        int ret,c;
        int xsize=windx-32,ysize=windy-16;
        memcpy(tempname,discfns[1],260);
        ret=file_select_ex("Please choose a disc image",tempname,"SSD;DSD;IMG;ADF;ADL;FDI",260,xsize,ysize);
        if (ret)
        {
                closedisc(1);
                memcpy(discfns[1],tempname,260);
                loaddisc(1,discfns[1]);
                if (defaultwriteprot) writeprot[1]=1;
        }
        updatelinuxgui();
        return D_O_K;
}

int gui_eject0()
{
        closedisc(0);
        discfns[0][0]=0;
        return D_O_K;
}
int gui_eject1()
{
        closedisc(1);
        discfns[1][0]=0;
        return D_O_K;
}

int gui_wprot0()
{
        writeprot[0]=!writeprot[0];
        if (fwriteprot[0]) fwriteprot[0]=1;
        updatelinuxgui();
        return D_O_K;
}
int gui_wprot1()
{
        writeprot[1]=!writeprot[1];
        if (fwriteprot[1]) fwriteprot[1]=1;
        updatelinuxgui();
        return D_O_K;
}
int gui_wprotd()
{
        defaultwriteprot=!defaultwriteprot;
        updatelinuxgui();
        return D_O_K;
}

MENU discmenu[8]=
{
        {"Load disc :&0/2...",gui_load0,NULL,0,NULL},
        {"Load disc :&1/3...",gui_load1,NULL,0,NULL},
        {"Eject disc :0/2",gui_eject0,NULL,0,NULL},
        {"Eject disc :1/3",gui_eject1,NULL,0,NULL},
        {"Write protect disc :0/2",gui_wprot0,NULL,0,NULL},
        {"Write protect disc :1/3",gui_wprot1,NULL,0,NULL},
        {"Default write protect",gui_wprotd,NULL,0,NULL},
        {NULL,NULL,NULL,0,NULL}
};

int gui_normal()
{
        fasttape=0;
        updatelinuxgui();
        return D_O_K;
}
int gui_fast()
{
        fasttape=1;
        updatelinuxgui();
        return D_O_K;
}

MENU tapespdmenu[3]=
{
        {"Normal",gui_normal,NULL,0,NULL},
        {"Fast",gui_fast,NULL,0,NULL},
        {NULL,NULL,NULL,0,NULL}
};

int gui_loadt()
{
        char tempname[260];
        int ret,c;
        int xsize=windx-32,ysize=windy-16;
        memcpy(tempname,tapefn,260);
        ret=file_select_ex("Please choose a tape image",tempname,"UEF;CSW",260,xsize,ysize);
        if (ret)
        {
                closeuef();
                closecsw();
                memcpy(tapefn,tempname,260);
                loadtape(tapefn);
                tapeloaded=1;
        }
        return D_O_K;
}

int gui_rewind()
{
        closeuef();
        closecsw();
        loadtape(tapefn);
        return D_O_K;
}

int gui_ejectt()
{
        closeuef();
        closecsw();
        tapeloaded=0;
        return D_O_K;
}

MENU tapemenu[]=
{
        {"Load tape...",gui_loadt,NULL,0,NULL},
        {"Rewind tape",gui_rewind,NULL,0,NULL},
        {"Eject tape",gui_ejectt,NULL,0,NULL},
        {"Tape speed",NULL,tapespdmenu,0,NULL},
        {NULL,NULL,NULL,0,NULL}
};

int gui_model()
{
        oldmodel=curmodel;
        curmodel=(int)active_menu->dp;
        restartbbc();
        updatelinuxgui();
        return D_O_K;
}

MENU modelmenu[16]=
{
        {"BBC A w/OS 0.1",gui_model,NULL,0,(void *)0},
        {"BBC B w/OS 0.1",gui_model,NULL,0,(void *)1},
        {"BBC A",gui_model,NULL,0,(void *)2},
        {"BBC B w/8271 FDC",gui_model,NULL,0,(void *)3},
        {"BBC B w/8271+SWRAM",gui_model,NULL,0,(void *)4},
        {"BBC B w/1770 FDC",gui_model,NULL,0,(void *)5},
        {"BBC B US",gui_model,NULL,0,(void *)6},
        {"BBC B German",gui_model,NULL,0,(void *)7},
        {"BBC B+ 64K",gui_model,NULL,0,(void *)8},
        {"BBC B+ 128K",gui_model,NULL,0,(void *)9},
        {"BBC Master 128",gui_model,NULL,0,(void *)10},
        {"BBC Master 512",gui_model,NULL,0,(void *)11},
        {"BBC Master Turbo",gui_model,NULL,0,(void *)12},
        {"BBC Master Compact",gui_model,NULL,0,(void *)13},
        {"ARM Evaluation System",gui_model,NULL,0,(void *)14},
        {NULL,NULL,NULL,0,NULL}
};

int gui_tubespd()
{
        tube6502speed=(int)active_menu->dp;
        updatetubespeed();
        updatelinuxgui();
        return D_O_K;
}

MENU tubespdmenu[6]=
{
        {"4mhz",gui_tubespd,NULL,0,(void *)1},
        {"8mhz",gui_tubespd,NULL,0,(void *)2},
        {"16mhz",gui_tubespd,NULL,0,(void *)3},
        {"32mhz",gui_tubespd,NULL,0,(void *)4},
        {"64mhz",gui_tubespd,NULL,0,(void *)5},
        {NULL,NULL,NULL,0,NULL}
};


int gui_tube()
{
        selecttube=(int)active_menu->dp;
        restartbbc();
        updatelinuxgui();
        return D_O_K;
}

#ifdef NS32016
MENU tubemenu[7]=
#else
MENU tubemenu[6]=
#endif
{
        {"None",gui_tube,NULL,0,(void *)-1},
        {"6502",gui_tube,NULL,0,(void *)0},
        {"65816",gui_tube,NULL,0,(void *)4},
        {"Z80",gui_tube,NULL,0,(void *)2},
#ifdef NS32016
        {"32016",gui_tube,NULL,0,(void *)5},
#endif
        {"6502 tube speed",NULL,tubespdmenu,0,NULL},
        {NULL,NULL,NULL,0,NULL}
};

int gui_linedbl()
{
        linedbl=1;
        comedyblit=interlace=0;
        updatelinuxgui();
        return D_O_K;
}
int gui_scanlines()
{
        comedyblit=1;
        linedbl=interlace=0;
        updatelinuxgui();
        return D_O_K;
}
int gui_interlaced()
{
        interlace=1;
        linedbl=comedyblit=0;
        updatelinuxgui();
        return D_O_K;
}

MENU displaymenu[4]=
{
        {"Line doubling",gui_linedbl,NULL,0,NULL},
        {"Scanlines",gui_scanlines,NULL,0,NULL},
        {"Interlaced",gui_interlaced,NULL,0,NULL},
        {NULL,NULL,NULL,0,NULL}
};

int gui_borders()
{
        fullborders=(int)active_menu->dp;
        updatelinuxgui();
        return D_O_K;
}

MENU bordersmenu[4]=
{
        {"None", gui_borders,NULL,0,(void *)0},
        {"Small",gui_borders,NULL,0,(void *)1},
        {"Full", gui_borders,NULL,0,(void *)2},
        {NULL,NULL,NULL,0,NULL}
};

int gui_fullscreen()
{
        if (fullscreen)
        {
                fullscreen=0;
                leavefullscreen();
        }
        else
        {
                fullscreen=1;
                enterfullscreen();
        }
        return D_EXIT;
}

MENU videomenu[4]=
{
        {"Display type",NULL,displaymenu,0,NULL},
        {"Borders",NULL,bordersmenu,0,NULL},
        {"Fullscreen",gui_fullscreen,NULL,0,NULL},
        {NULL,NULL,NULL,0,NULL}
};

int gui_sidtype()
{
        cursid=(int)active_menu->dp;
        setsidtype(sidmethod, cursid);
        updatelinuxgui();
        return D_O_K;
}

MENU sidtypemenu[15]=
{
        {"6581",                    gui_sidtype,NULL,0,(void *)SID_MODEL_6581},
        {"8580",                    gui_sidtype,NULL,0,(void *)SID_MODEL_8580},
        {"8580 + digi boost",       gui_sidtype,NULL,0,(void *)SID_MODEL_8580D},
        {"6581R4",                  gui_sidtype,NULL,0,(void *)SID_MODEL_6581R4},
        {"6581R3 4885",             gui_sidtype,NULL,0,(void *)SID_MODEL_6581R3_4885},
        {"6581R3 0486S",            gui_sidtype,NULL,0,(void *)SID_MODEL_6581R3_0486S},
        {"6581R3 3984",             gui_sidtype,NULL,0,(void *)SID_MODEL_6581R3_3984},
        {"6581R4AR 3789",           gui_sidtype,NULL,0,(void *)SID_MODEL_6581R4AR_3789},
        {"6581R3 4485",             gui_sidtype,NULL,0,(void *)SID_MODEL_6581R3_4485},
        {"6581R4 1986S",            gui_sidtype,NULL,0,(void *)SID_MODEL_6581R4_1986S},
        {"8580R5 3691",             gui_sidtype,NULL,0,(void *)SID_MODEL_8580R5_3691},
        {"8580R5 3691 + digi boost",gui_sidtype,NULL,0,(void *)SID_MODEL_8580R5_3691D},
        {"8580R5 1489",             gui_sidtype,NULL,0,(void *)SID_MODEL_8580R5_1489},
        {"8580R5 1489 + digi boost",gui_sidtype,NULL,0,(void *)SID_MODEL_8580R5_1489D},
        {NULL,NULL,NULL,0,NULL}
};

int gui_method()
{
        sidmethod=(int)active_menu->dp;
        setsidtype(sidmethod, cursid);
        updatelinuxgui();
        return D_O_K;
}

MENU methodmenu[3]=
{
        {"Interpolating", gui_method,NULL,0,(void *)0},
        {"Resampling",    gui_method,NULL,0,(void *)1},
        {NULL,NULL,NULL,0,NULL}
};

MENU residmenu[3]=
{
        {"Model",NULL,sidtypemenu,0,NULL},
        {"Sample method",NULL,methodmenu,0,NULL},
        {NULL,NULL,NULL,0,NULL}
};

int gui_waveform()
{
        curwave=(int)active_menu->dp;
        updatelinuxgui();
        return D_O_K;
}

MENU waveformmenu[6]=
{
        {"Square",gui_waveform,NULL,0,(void *)0},
        {"Saw",gui_waveform,NULL,0,(void *)1},
        {"Sine",gui_waveform,NULL,0,(void *)2},
        {"Triangle",gui_waveform,NULL,0,(void *)3},
        {"SID",gui_waveform,NULL,0,(void *)4},
        {NULL,NULL,NULL,0,NULL}
};

int gui_ddtype()
{
        ddtype=(int)active_menu->dp;
        closeddnoise();
        loaddiscsamps();
        updatelinuxgui();
        return D_O_K;
}

MENU ddtypemenu[3]=
{
        {"5.25",gui_ddtype,NULL,0,(void *)0},
        {"3.5",gui_ddtype,NULL,0,(void *)1},
        {NULL,NULL,NULL,0,NULL}
};

int gui_ddvol()
{
        ddvol=(int)active_menu->dp;
        updatelinuxgui();
        return D_O_K;
}

MENU ddvolmenu[4]=
{
        {"33%",gui_ddvol,NULL,0,(void *)1},
        {"66%",gui_ddvol,NULL,0,(void *)2},
        {"100%",gui_ddvol,NULL,0,(void *)3},
        {NULL,NULL,NULL,0,NULL}
};

int gui_internalsnd()
{
        sndinternal=!sndinternal;
        updatelinuxgui();
        return D_O_K;
}
int gui_beebsid()
{
        sndbeebsid=!sndbeebsid;
        updatelinuxgui();
        return D_O_K;
}
int gui_ddnoise()
{
        sndddnoise=!sndddnoise;
        updatelinuxgui();
        return D_O_K;
}
int gui_tnoise()
{
        sndtape=!sndtape;
        updatelinuxgui();
        return D_O_K;
}
int gui_filter()
{
        soundfilter=!soundfilter;
        updatelinuxgui();
        return D_O_K;
}

MENU soundmenu[10]=
{
        {"Internal sound chip",gui_internalsnd,NULL,0,NULL},
        {"BeebSID",gui_beebsid,NULL,0,NULL},
        {"Disc drive noise",gui_ddnoise,NULL,0,NULL},
        {"Tape noise",gui_tnoise,NULL,0,NULL},
        {"Internal sound filter",gui_filter,NULL,0,NULL},
        {"Internal waveform",NULL,waveformmenu,0,NULL},
        {"reSID configuration",NULL,residmenu,0,NULL},
        {"Disc drive type",NULL,ddtypemenu,0,NULL},
        {"Disc drive volume",NULL,ddvolmenu,0,NULL},
        {NULL,NULL,NULL,0,NULL}
};

int gui_mapas()
{
        keyas=!keyas;
        updatelinuxgui();
        return D_O_K;
}

MENU keymenu[3]=
{
        {"Redefine keyboard",gui_keydefine,NULL,0,NULL},
        {"&Map CAPS/CTRL to A/S",gui_mapas,NULL,0,NULL},
        {NULL,NULL,NULL,0,NULL}
};

int gui_ide()
{
        ideenable=!ideenable;
        restartbbc();
        updatelinuxgui();
        return D_O_K;
}

MENU idemenu[2]=
{
        {"&Enable IDE hard discs",gui_ide,NULL,0,NULL},
        {NULL,NULL,NULL,0,NULL}
};

MENU settingsmenu[7]=
{
        {"&Model",NULL,modelmenu,0,NULL},
        {"&Second processor",NULL,tubemenu,0,NULL},
        {"&Video",NULL,videomenu,0,NULL},
        {"&Sound",NULL,soundmenu,0,NULL},
        {"&Keyboard",NULL,keymenu,0,NULL},
        {"&IDE",NULL,idemenu,0,NULL},
        {NULL,NULL,NULL,0,NULL}
};

int gui_scrshot()
{
        char tempname[260];
        int ret,c;
        int xsize=windx-32,ysize=windy-16;
        tempname[0]=0;
        ret=file_select_ex("Please enter filename",tempname,"BMP",260,xsize,ysize);
        if (ret)
        {
                memcpy(scrshotname,tempname,260);
                savescrshot=1;
        }
        return D_O_K;
}

int gui_speed()
{
        emuspeed=(int)active_menu->dp;
        changetimerspeed(timerspeeds[emuspeed]);
        fskipmax=frameskips[emuspeed];
        updatelinuxgui();
        return D_O_K;
}

MENU speedmenu[11]=
{
        {"&10%",gui_speed,NULL,0,(void *)0},
        {"&25%",gui_speed,NULL,0,(void *)1},
        {"&50%",gui_speed,NULL,0,(void *)2},
        {"&75%",gui_speed,NULL,0,(void *)3},
        {"&100%",gui_speed,NULL,0,(void *)4},
        {"&150%",gui_speed,NULL,0,(void *)5},
        {"&200%",gui_speed,NULL,0,(void *)6},
        {"&300%",gui_speed,NULL,0,(void *)7},
        {"&400%",gui_speed,NULL,0,(void *)8},
        {"&500%",gui_speed,NULL,0,(void *)9},
        {NULL,NULL,NULL,0,NULL}
};

MENU miscmenu[3]=
{
        {"&Speed",NULL,speedmenu,0,NULL},
        {"Save screenshot",gui_scrshot,NULL,0,NULL},
        {NULL,NULL,NULL,0,NULL}
};

MENU mainmenu[6]=
{
        {"&File",NULL,filemenu,0,NULL},
        {"&Disc",NULL,discmenu,0,NULL},
        {"&Tape",NULL,tapemenu,0,NULL},
        {"&Settings",NULL,settingsmenu,0,NULL},
        {"&Misc",NULL,miscmenu,0,NULL},
        {NULL,NULL,NULL,0,NULL}
};

DIALOG bemgui[]=
{
        {d_ctext_proc, 200, 260, 0,  0, 15,0,0,0,     0,0,"B-em v2.1"},
        {d_menu_proc,  0,   0,   0,  0, 15,0,0,0,     0,0,mainmenu},
        {d_yield_proc},
        {0,0,0,0,0,0,0,0,0,0,0,NULL,NULL,NULL}
};

BITMAP *mouse,*_mouse_sprite;

void entergui()
{
        int x=1;
        DIALOG_PLAYER *dp;

        BITMAP *guib;

        while (keypressed()) readkey();
        while (key[KEY_F11]) rest(100);

        updatelinuxgui();

        if (curtube!=3) install_mouse();

        set_color_depth(dcol);
        show_mouse(screen);
        bemgui[0].x=(windx/2)-36;
        bemgui[0].y=windy-8;
        bemgui[0].fg=makecol(255,255,255);
        if (opengl)
        {
                guib=create_bitmap(SCREEN_W,SCREEN_H);
                clear(guib);
                gui_set_screen(guib);
                allegro_gl_set_allegro_mode();
        }
        dp=init_dialog(bemgui,0);
        while (x && !key[KEY_F11] && !key[KEY_ESC])
        {
                if (opengl)
                {
                        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                }
                x=update_dialog(dp);
                if (opengl)
                {
                        blit(guib,screen,0,0,0,0,SCREEN_W,SCREEN_H);
                        algl_draw_mouse();
                        allegro_gl_flip();
                }
        }
        shutdown_dialog(dp);
        show_mouse(NULL);
        if (opengl)
        {
                destroy_bitmap(guib);
                allegro_gl_unset_allegro_mode();
        }
        set_color_depth(8);

        if (curtube!=3) remove_mouse();

        while (key[KEY_F11]) rest(100);

        clearscreen();
}
#endif