/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int gappx     = 3;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "JetBrains Mono:size=11", "JoyPixels:pixelsize=11:antialias=true:autohint=true"};
static const char dmenufont[]       = "JetBrains Mono:size=11";
static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#bbbbbb";
static char selbordercolor[]        = "#555555";
static char selbgcolor[]            = "#555555";
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5" };
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class                instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "TelegramDesktop",    NULL,     NULL,           0,         0,          0,           0,        -1 },
	{ "obs",                NULL,     NULL,           0,         1,          0,           0,        -1 },
	{ "Lutris",             NULL,     NULL,           0,         1,          0,           0,        -1 },
	{ "firefox",   		      NULL,     NULL,           1 << 2,    0,          0,          -1,        -1 },
	{ "St",                 NULL,     NULL,           0,         0,          1,           0,        -1 },
	{ NULL,                 NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG)												\
	{1, {{MODKEY, KEY}},								view,           {.ui = 1 << TAG} },	\
	{1, {{MODKEY|ControlMask, KEY}},					toggleview,     {.ui = 1 << TAG} }, \
	{1, {{MODKEY|ShiftMask, KEY}},						tag,            {.ui = 1 << TAG} }, \
	{1, {{MODKEY|ControlMask|ShiftMask, KEY}},			toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont};
static const char *termcmd[]  = { "alacritty", NULL };
static const char *browsercmd[]  = { "chromium", NULL };
   
static Keychord keychords[] = {
  /* function keys  */
 	{1, {{ 0,                            XK_F1 }},     spawn,          SHCMD("get-info")},
	{1, {{ 0,                            XK_F2 }},     spawn,          SHCMD("brightness -d 100")},
	{1, {{ 0,                            XK_F3 }},     spawn,          SHCMD("brightness -i 100")},
	{1, {{ 0,                            XK_F4 }},     spawn,          SHCMD("screen -f")},
	{1, {{ 0,                            XK_F6 }},     spawn,          SHCMD("volume -m")},
	{1, {{ 0,                            XK_F7 }},     spawn,          SHCMD("volume -d")},
	{1, {{ 0,                            XK_F8 }},     spawn,          SHCMD("volume -i")},
	{1, {{ 0,                            XK_F9 }},     spawn,          SHCMD("moc -n")},
	{1, {{ 0,                            XK_F10 }},    spawn,          SHCMD("moc -p")},
	{1, {{ 0,                            XK_F12 }},    spawn,          SHCMD("slock")},

  /* Key chords */
	{2, {{ MODKEY, XK_backslash }, { 0, XK_h }},      spawn,          SHCMD("get-help")},
	{2, {{ MODKEY, XK_backslash }, { 0, XK_w }},      spawn,          SHCMD("wifi")},
	{2, {{ MODKEY, XK_backslash }, { 0, XK_b }},      spawn,          SHCMD("bluetooth")},
  {2, {{ MODKEY, XK_backslash }, { 0, XK_c }},      spawn,          SHCMD("saveclip -s")},
	{2, {{ MODKEY, XK_backslash }, { 0, XK_v }},      spawn,          SHCMD("saveclip")},
	{2, {{ MODKEY, XK_backslash }, { 0, XK_e }},      spawn,          SHCMD("emoji")},
	{2, {{ MODKEY, XK_backslash }, { 0, XK_s }},      spawn,          SHCMD("screen")},

  /* layout chords */
	{2, {{ MODKEY, XK_l },         { 0, XK_x }},      setlayout,      {.v = &layouts[1]} },
	{2, {{ MODKEY, XK_l },         { 0, XK_m }},      setlayout,      {.v = &layouts[2]} },
	{2, {{ MODKEY, XK_l },         { 0, XK_t }},      setlayout,      {.v = &layouts[0]} },
	{2, {{ MODKEY, XK_l },         { 0, XK_f }},  	  togglefloating, {0} },
	{2, {{ MODKEY, XK_l },         { 0, XK_h }},      incnmaster,     {.i = -1 } },
	{2, {{ MODKEY, XK_l },         { 0, XK_v }},      incnmaster,     {.i = +1 } },

	{1, {{ MODKEY,                 XK_g  }},          togglebar,      {0} },
	{1, {{ Mod1Mask,               XK_Tab  }},	      zoom,           {0} },
	{1, {{ MODKEY,		             XK_q  }},          killclient,     {0} },

	{1, {{ MODKEY,                 XK_space }},       spawn,          {.v = dmenucmd } },
	{1, {{ MODKEY|ShiftMask,       XK_q }},			      quit,           {0} },
	{1, {{ MODKEY|ShiftMask,       XK_Left }},        setmfact,       {.f = -0.05} },
	{1, {{ MODKEY|ShiftMask,       XK_Right }},       setmfact,       {.f = +0.05} },
	{1, {{ MODKEY,                 XK_Left }},        focusstack,     {.i = -1 } },
	{1, {{ MODKEY,                 XK_Right }},       focusstack,     {.i = +1 } },
	{1, {{ MODKEY,			           XK_Return }},      spawn,          {.v = termcmd } },
	{1, {{ MODKEY|ShiftMask,		   XK_Return }},      spawn,          SHCMD("chromium --profile-directory='Default'")},
	{1, {{ MODKEY,                 XK_Tab }},         view,           {0} },

	{1, {{ MODKEY,                 XK_0 }},           view,           {.ui = ~0 } },
	{1, {{ MODKEY|ShiftMask,       XK_0 }},           tag,            {.ui = ~0 } },
	{1, {{ MODKEY,                 XK_comma }},       focusmon,       {.i = -1 } },
	{1, {{ MODKEY,                 XK_period }},      focusmon,       {.i = +1 } },
	{1, {{ MODKEY|ShiftMask,       XK_comma }},       tagmon,         {.i = -1 } },
	{1, {{ MODKEY|ShiftMask,       XK_period }},      tagmon,         {.i = +1 } },
	{1, {{ MODKEY,			           XK_minus }},       setgaps,	      {.i = -1 } },
	{1, {{ MODKEY,			           XK_equal }},       setgaps,	      {.i = +1 } },
	{1, {{ MODKEY|ShiftMask,		   XK_equal }},       setgaps,	      {.i =  0 } },
	{1, {{ MODKEY,                 XK_F5 }},          xrdb,           {.v = NULL } },

  /* Tag keys */
	TAGKEYS(                       XK_1,                      0)
	TAGKEYS(                       XK_2,                      1)
	TAGKEYS(                       XK_3,                      2)
	TAGKEYS(                       XK_4,                      3)
	TAGKEYS(                       XK_5,                      4)
	TAGKEYS(                       XK_6,                      5)
	TAGKEYS(                       XK_7,                      6)
	TAGKEYS(                       XK_8,                      7)
	TAGKEYS(                       XK_9,                      8)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

